/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 19:39:38 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int run_pipe(char **a_cmd, int *fd, int next)
{
	static int	fd_in;
	pid_t		pid;
	int			status;

	if (!fd_in)
		fd_in = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, 0);
		dup2((next) ? fd[1] : -1, 1);
		close(fd[1]);
		if(run_dmc(a_cmd))
		{
			exit(EXIT_FAILURE);
			return(1);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&status);
		close(fd[1]);
		fd_in = fd[0];
	}
	return (0);
}

int	run_dmc_pipes(char **args)
{
	int fd[2];
	char **a_cmd;
	int i;
	int next = 0;

	int adv;

	adv = 0;
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			if (adv == 0)
				a_cmd = ft_sub_tab(args, adv, i);
			else
				a_cmd = ft_sub_tab(args, adv, adv + (ft_tab_chr_i((char **)&args[i + 1], "|") - 1));
			adv = i + 1;
			pipe(fd);
			next = 1;
			if (run_pipe(a_cmd, fd, next))
				return(1);
		}
		else if (ft_iter_tab_cmp((char **)&args[i + 1], "|"))
		{
			a_cmd = ft_sub_tab(args, i, ft_tablen(args) - i);
			pipe(fd);
			next = 0;
			if (run_pipe(a_cmd, fd, next))
				return(1);
			break;
			//printf("%i - a:\n", i);
			//ft_tab_print(a_cmd);
		}
		i++;
	}
	return (0);
}
