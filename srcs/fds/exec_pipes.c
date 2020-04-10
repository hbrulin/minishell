#include "minishell.h"

static void     apply_redirs(t_redir **redirs)
{
    t_fd    redir_fd;

    while (*redirs)
	{
		if ((*redirs)->direction == INPUT)
		{
			if ((redir_fd = open((*redirs)->name, O_RDONLY)) == ERROR)
			{
				perror((*redirs)->name);
				exit(errno);
			}
			if (dup2(redir_fd, STDIN) == ERROR)
			{
				perror("dup input redirection");
				exit(errno);
			}
		}
		else if ((*redirs)->direction == OUTPUT)
		{
			if ((redir_fd = \
			open((*redirs)->name, O_WRONLY | O_CREAT, 0644)) == ERROR)
			{
				perror((*redirs)->name);
				exit(errno);
			}
			if (dup2(redir_fd, STDOUT) == ERROR)
			{
				perror("dup output redirection");
				exit(errno);
			}
		}
		if ((*redirs)->direction == APPEND)
		{
			if ((redir_fd = open((*redirs)->name, \
			O_WRONLY | O_CREAT | O_APPEND, 0644)) == ERROR)
			{
				perror((*redirs)->name);
				exit(errno);
			}
			if (dup2(redir_fd, STDOUT) == ERROR)
			{
				perror("dup append redirection");
				exit(errno);
			}
		}
        close(redir_fd);
		redirs++;
	}
}

static void     execute_cmd(t_cmd *cmd, char **env)
{
	if (cmd->redirs)
        apply_redirs(cmd->redirs);
	execve(cmd->path, cmd->arguments, env);
	/* si on reviens ici c'est qu'il a eu erreur. */
	perror(cmd->arguments[0]);
	exit(errno);
}

static t_status	ret_status(t_pid last_pid)
{
	t_pid		pid;
	t_status	status;
	t_status	last_status;

	//is_forking(3);//MODIF ICI
	while ((pid = waitpid(-1, &status, 0)) != ERROR)
		if (pid == last_pid)
			last_status = status;
    //handle_sig(status);
    //is_forking(0);
	if (errno != ECHILD)
	{
		perror("wait pipe childs");
		return (errno);
	}
	return (last_status);
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
			if (input_pipe) // sauf la première commande
			{
				if (dup2(input_pipe, STDIN) == ERROR)
				{
					perror("dup pipe stdin");
					exit(errno);
				}
			}
			if (*(pipeline + 1)) // sauf la dernière commande
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
			if (input_pipe) // sauf la première commande
			{
				if (close(input_pipe) == ERROR)
				{
					perror("parent close pipe input");
					return (errno);
				}
			}
			if (*(pipeline + 1)) // sauf la dernière commande
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

static t_size   count_pipes(t_cmd **cmds)
{
    t_size len;

    len = 1;
	while (cmds[len]->pipe_flag)
		len++;
	return (len + 1);
}

static void     create_pipeline(t_cmd **cmds, t_cmd **pipeline)
{
    t_index i;

    i = 0;
	while (cmds[i]->pipe_flag)
	{
		pipeline[i] = cmds[i];
		i++;
	}
	pipeline[i] = cmds[i]; // la dernière commande avec pipe en entrée
	pipeline[i + 1] = NULL;
}

static t_status	execute_pipes(t_cmd ***cmds, char **env)
{
	t_size	pipeline_len = count_pipes(*cmds);
	t_cmd	*pipeline[pipeline_len];

	create_pipeline(*cmds, pipeline);
	(*cmds) += pipeline_len;
	return (execute_pipeline(pipeline, env));
}

t_status execute_cmds(t_cmd **cmds, char **env)
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
