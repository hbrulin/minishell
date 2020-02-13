/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 19:31:47 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int run_pipe(char **a_cmd, int *fd)
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
		dup2(1, fd[1]);
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
		fd_in = fd[1];
	}
	return (0);
}


int	run_dmc_pipes(char **args)
{
	int fd[2];
	char **a_cmd;
	//char **b_cmd;
	int i;

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
			//else
			//	b_cmd = ft_sub_tab(args, i + 1, i + (ft_tab_chr_i((char **)&args[i + 1], "|") - 1));
			//pipe(fd);
			adv = i + 1;
			pipe(fd);
			if (run_pipe(a_cmd, fd))
				return(1);
			//printf("%i - a:\n", i);
			//ft_tab_print(a_cmd);		
			//free(a_cmd);
			//free(b_cmd);
		}
		else if (ft_iter_tab_cmp((char **)&args[i + 1], "|"))
		{
			a_cmd = ft_sub_tab(args, i, ft_tablen(args) - i);
			pipe(fd);
			if (run_pipe(a_cmd, fd))
				return(1);
			break;
			//printf("%i - a:\n", i);
			//ft_tab_print(a_cmd);
		}
		i++;
	}
	return (0);
}
