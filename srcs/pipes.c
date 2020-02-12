/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/12 20:40:27 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_pipe(char **a_cmd, char **b_cmd, int *fd)
{
	static int	fd_in;
	pid_t		pid;

	if (!fd_in)
		fd_in = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, 0);
		dup2((!b_cmd) ? fd[1] : -1, 1);
		run_dmc(a_cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
		//close(fd[1]);
		fd_in = fd[0];
	}
	return (0);
}


int	run_dmc_pipes(char **args)
{
	int fd[2];
	char **a_cmd;
	char **b_cmd;
	int i = 0;

	static int adv;

	if (!adv)
		adv = 0;

	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			a_cmd = copy_n_tab(args, adv, i);
			b_cmd = copy_n_tab(args, i + 1, ft_tablen(args) - i - 1); //fin de la copy a revoir
			pipe(fd);
			adv = i + 1;
			return(run_pipe(a_cmd, b_cmd, fd)); //return 1 si fail
		}
		i++;
	}
	return (0);
}
