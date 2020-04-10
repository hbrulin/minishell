/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:15:17 by fhenrion          #+#    #+#             */
/*   Updated: 2020/04/10 16:14:58 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* Macros utiles et norme compatible */
# define ERROR -1
# define STDIN 0
# define STDOUT 1
# define CHILD 0
# define PIPEIN 0
# define PIPEOUT 1

/* typedef parce que c'est plus clair et que je suis toqué */
typedef size_t	t_size;
typedef size_t	t_index;
typedef	int		t_fd;
typedef pid_t	t_pid;
typedef int		t_status;

typedef enum	e_dir
{
	NO_REDIR,
	INPUT,
	OUTPUT,
	APPEND
}				t_dir;

/* 
** Pour la plupart des structures j'ai fait des listes dans mon
** implémentation mais ici je fait des tableaux pour simplifier vu
** que je n'implémente pas la partie parsing.
*/
typedef struct	s_redir
{
	t_dir		direction;
	char		*name;
}				t_redir;

typedef struct	s_cmd
{
	char		*path;
	char		**arguments;
	int			pipe_flag;
	t_redir		**redirs;
}				t_cmd;

/*
** Dans mon implementation certaines choses que je fait ici
** sont faites lors du parsing, la encore ça dépasse les 25 lignes
** a cause des gestions d'erreur.
*/
static void		apply_redirs(t_redir **redirs)
{
	t_fd	redir_fd;

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
		redirs++;
	}
}

/*
** On applique les redirs ici, dans le cas d'un pipe
** dup2 referme le pipe déjà dupliqué sur l'entrée/sortie.
*/
static void		execute_cmd(t_cmd *cmd, char **env)
{
	apply_redirs(cmd->redirs);
	execve(cmd->path, cmd->arguments, env);
	/* si on reviens ici c'est qu'il a eu erreur. */
	perror(cmd->arguments[0]);
	exit(errno);
}

/*
** On attend tout les fils mais on ne retourne bien
** que le code de retour de la dernière commande
** qui n'est pas forcément la dernière à se terminer.
*/
static t_status	ret_status(t_pid last_pid)
{
	t_pid		pid;
	t_status	status;
	t_status	last_status;
	
	while ((pid = waitpid(-1, &status, 0)) != ERROR)
		if (pid == last_pid)
			last_status = status;
	if (errno != ECHILD)
	{
		perror("wait pipe childs");
		return (errno);
	}
	return (last_status);
}

/*
** Bon ici ça fait largement plus de 25 lignes a cause toutes
** les gestions d'erreur, pas sûre qu'elles soit toutes indispensables
** mais c'est plus clair comme ça.
*/
static t_status	execute_pipeline(t_cmd **pipeline, char **env)
{
	t_pid	pid;
	t_fd	pipes[2];
	t_fd	input_pipe;

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

/*
** Compte les pipe_flags + 1, la dernière commande
** avec pipe en entrée n'ayant pas le flag.
*/
static t_size	count_pipes(t_cmd **cmds)
{
	t_size len;

	len = 1;
	while (cmds[len]->pipe_flag)
		len++;
	return (len);
}

static void		create_pipeline(t_cmd **cmds, t_cmd **pipeline)
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

/*
** Prepare le tableau des commandes de la suite de pipe
** fait avancer le pointeur sur commande et retourne
** le code de retour de l'execution.
*/
static t_status	execute_pipes(t_cmd ***cmds, char **env)
{
	/*
	** A la norme on ne pourrais pas faire ça il faudrait
	** soit compter avant et envoyer en paramètre
	** soit malloc mais la c'est plus simple comme ça.
	*/
	t_size	pipeline_len = count_pipes(*cmds);
	t_cmd	*pipeline[pipeline_len + 1];

	create_pipeline(*cmds, pipeline);
	/*
	** On fait avancer le pointeur sur commande
	** jusqu'a la prochaine commande sans pipe
	** déréférençant le pointeur sur pointeur.
	*/
	(*cmds) += pipeline_len;
	return (execute_pipeline(pipeline, env));
}

/*
** on execute commande par commande et sinon
** une fonction spéciale poir les pipes
*/
static t_status	execute_cmds(t_cmd **cmds, char **env)
{
	t_pid		pid;
	t_status	status;

	while (*cmds)
	{
		/*
		** On envoi un pointeur sur pointeur pour avoir
		** directement la prochaine commande au retour.
		*/
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

int				main(int argc, char *argv[], char *env[])
{
	/* commandes créées sans parsing */
	/* fuck la norme ici */
	/* ls > file | cat | wc < file */
	/* ls */
	char	*ls_args[] = {"cat", NULL};
	t_redir *ls_redirs[] = {NULL};
	t_cmd	ls = {"/bin/cat", ls_args, 1, ls_redirs};
	/* cat */
	char	*cat_args[] = {"ls", NULL};
	t_redir *cat_redirs[] = {NULL};
	t_cmd	cat = {"/bin/ls", cat_args, 0, cat_redirs};
	/* tableau des commandes */
	t_cmd	*fake_cmds[] = {&ls, &cat, NULL};

	printf("\nCode de retour : %i\n", execute_cmds(fake_cmds, env));
	return (0);
}
