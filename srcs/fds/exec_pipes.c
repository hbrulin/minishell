/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:52:56 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/11 18:59:37 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_cmd(t_cmd *cmd, char **env)
{
	if (cmd->redirs)
		apply_redirs(cmd->redirs);
	execve(cmd->path, cmd->arguments, env);
	exit(errno);
}

void			child_exec(t_cmd **pipeline, char **env, t_pipeline_tools *t)
{
	if (t->input_pipe)
	{
		if (dup2(t->input_pipe, STDIN) == ERROR)
		{
			perror("dup pipe stdin");
			exit(errno);
		}
	}
	if (*(pipeline + 1))
	{
		if (dup2(t->pipes[PIPEOUT], STDOUT) == ERROR)
		{
			perror("dup pipe stdout");
			exit(errno);
		}
	}
	if (close(t->pipes[PIPEIN]) == ERROR)
	{
		perror("child close pipe input");
		exit(errno);
	}
	execute_cmd(*pipeline, env);
}

static t_status	execute_pipeline(t_cmd **pipeline, char **env)
{
	t_pipeline_tools t;

	t.input_pipe = 0;
	while (*pipeline)
	{
		if (pipe(t.pipes) == ERROR)
			return (errno);
		if ((t.pid = fork()) == ERROR)
			return (errno);
		else if (t.pid == CHILD)
			child_exec(pipeline, env, &t);
		else
		{
			if (t.input_pipe)
				close(t.input_pipe);
			if (*(pipeline + 1))
				t.input_pipe = t.pipes[PIPEIN];
			if (close(t.pipes[PIPEOUT]) == ERROR)
				return (errno);
			pipeline++;
		}
	}
	return (ret_status(t.pid));
}

static t_status	execute_pipes(t_cmd ***cmds, char **env, t_size pipeline_len)
{
	t_cmd	*pipeline[pipeline_len];

	create_pipeline(*cmds, pipeline);
	(*cmds) += pipeline_len;
	return (execute_pipeline(pipeline, env));
}

t_status		execute_cmds(t_cmd **cmds, char **env)
{
	t_pid		pid;
	t_status	status;

	while (*cmds)
	{
		if ((*cmds)->pipe_flag)
			status = execute_pipes(&cmds, env, count_pipes(cmds));
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
