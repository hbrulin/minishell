/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/25 11:42:22 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	dup2 transforme newfd (arg2) en une copie de old fd (arg1), fermant
**	auparavant newfd. si oldfd n'est pas valide, l'appel echoue et newfd
**	n'est pas fermé -> ligne 33 stdout normal si pas de next cmd a piper.
**
**	Deroulement : dans le fils, je ferme fd[0] car je ne vais qu'y ecrire.
**	je tranforme ma sortie standard en une copie de fd[1], 
**	l'extrémité d'ecriture du tube. je close cette extremité de lecture,
**	car elle a ete copiee comme sortie standard. La commande run et va ecrire
**	dans cette copie. Dans le pere, l'extremité de lecture fd[0] a recupéré
**	ce qui a été écrit. Je met la valeur de ce fd dans fd_in, afin de pouvoir
**	récupérer ce qui a été lu en entree standard pour la prochaine cmd.
**	Pas besoin de close fd[0] dans le pere car cette lecture va tjrs etre 
**	l'entree standard, et dup2 va tjrs tout fd de lecture supplémentaire.
**	idem, la sortie standard est fermee par dup2 sauf en cas de fd[1] == -1.
**	apres fin de la cmd tout est reset.
*/

int		run_pipe(char **a_cmd, int *fd, int next)
{
	static int	fd_in;
	pid_t		pid;
	int			status;

	if (!fd_in)
		fd_in = 0;
	if ((pid = fork()) == -1)
		return (ft_strerror(NULL, NULL, "fork", NULL));
	if (pid == 0)
	{
		dup2(fd_in, 0);
		dup2((next) ? fd[1] : -1, 1);
		close(fd[0]);
		close(fd[1]);
		if (run_dmc(a_cmd))
		{
			exit(EXIT_FAILURE);
			return (1);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (wait(&status) == -1)
		{
			close(fd[1]);
			return (ft_strerror(NULL, NULL, "wait", NULL));
		}
		close(fd[1]);
		fd_in = fd[0];
	}
	return (0);
}

int		run_dmc_pipes(char **args)
{
	int		fd[2];
	char	**a_cmd;
	int		i;
	int		next;
	int		adv;

	adv = 0;
	i = 0;
	a_cmd = NULL;
	next = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			if (adv == 0)
				a_cmd = ft_sub_tab(args, adv, i);
			else
				a_cmd = ft_sub_tab(args, adv, (ft_tab_chr_i((char **)&args[adv], "|")));
			adv = i + 1;
			pipe(fd);
			next = 1;
			if (run_pipe(a_cmd, fd, next))
				return (ft_error(NULL, NULL, a_cmd, NULL));
			ft_tabdel((void *)a_cmd);
		}
		else if (ft_iter_tab_cmp((char **)&args[i + 1], "|"))
		{
			a_cmd = ft_sub_tab(args, i, ft_tablen(args) - i);
			pipe(fd);
			next = 0;
			if (run_pipe(a_cmd, fd, next))
				return (ft_error(NULL, NULL, a_cmd, NULL));
			ft_tabdel((void *)a_cmd);
			break ;
		}
		i++;
	}
	return (0);
}
