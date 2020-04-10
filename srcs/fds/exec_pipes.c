/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:52:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/10 19:56:48 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void     execute_cmd(t_cmd *cmd, char **env)
{
	if (cmd->redirs)
        apply_redirs(cmd->redirs);
	execve(cmd->path, cmd->arguments, env);
	exit(errno);
}

static t_status execute_pipeline (t_cmd **pipeline, char **env)
{
    t_pid pid;
    t_fd    pipes[2];
    t_fd    input_pipe;

	input_pipe = 0;
	while (*pipeline)
	{
		if (pipe(pipes) == ERROR)
		{
			perror("pipe");
			return (errno);
		}
		if ((pid = fork()) == ERROR)
		{
			perror("fork");
			return (errno);
		}
		else if (pid == CHILD)
		{
			if (input_pipe)
			{
				if (dup2(input_pipe, STDIN) == ERROR)
				{
					perror("dup pipe stdin");
					exit(errno);
				}
			}
			if (*(pipeline + 1))
			{
				if (dup2(pipes[PIPEOUT], STDOUT) == ERROR)
				{
					perror("dup pipe stdout");
					exit(errno);
				}
			}
			if (close(pipes[PIPEIN]) == ERROR)
			{
				perror("child close pipe input");
				exit(errno);
			}
			execute_cmd(*pipeline, env);
		}
		else
		{
			if (input_pipe)
			{
				if (close(input_pipe) == ERROR)
				{
					perror("parent close pipe input");
					return (errno);
				}
			}
			if (*(pipeline + 1))
				input_pipe = pipes[PIPEIN];
			if (close(pipes[PIPEOUT]) == ERROR)
			{
				perror("parent close pipe output");
				return (errno);
			}
			pipeline++;
		}
	}
	return (ret_status(pid));
}

static t_status	execute_pipes(t_cmd ***cmds, char **env)
{
	t_size	pipeline_len = count_pipes(*cmds);
	t_cmd	*pipeline[pipeline_len];

	create_pipeline(*cmds, pipeline);
	(*cmds) += pipeline_len;
	return (execute_pipeline(pipeline, env));
}

t_status		execute_cmds(t_cmd **cmds, char **env)
{
    t_pid       pid;
    t_status    status;

	while (*cmds)
	{
		if ((*cmds)->pipe_flag)
			status = execute_pipes(&cmds, env);
		else
		{
			if ((pid = fork()) == ERROR)
			{
				perror("fork");
				return (errno);
			}
			if (pid == CHILD)
				execute_cmd(*cmds, env);
			if (wait(&status) == ERROR)
			{
				perror("wait");
				return (errno);
			}
			cmds++;
		}
	}
	return (status);
}
