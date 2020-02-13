/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 15:07:25 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_pipe(char **a_cmd, char **b_cmd, int *fd)
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
		if (b_cmd)
			fd[1] = open(*b_cmd, O_RDONLY);
		else
			fd[1] = -1;
		if(run_dmc(a_cmd))
			return(1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&status);
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
	int i;

	int adv;

	adv = 0;
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			a_cmd = ft_sub_tab(args, adv, i);
			if (ft_iter_tab_cmp((char **)&args[i + 1], "|"))
				b_cmd = ft_sub_tab(args, i + 1, ft_tablen(args) - i - 1);
			else
				b_cmd = ft_sub_tab(args, i + 1, ft_tab_chr_i((char **)&args[i + 1], "|") - 1);
			pipe(fd);
			adv = i + 1;
			if (run_pipe(a_cmd, b_cmd, fd))
				return(1);
		}
		i++;
	}
	return (0);
}
