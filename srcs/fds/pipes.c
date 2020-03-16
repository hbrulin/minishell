/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/16 15:02:20 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(int *fd, int fd_in, int next)
{
	dup2(fd_in, 0);
	dup2((next) ? fd[1] : -1, 1);
	close(fd[0]);
	close(fd[1]);
}

int		run_pipe(char **a_cmd, int *fd, int next)
{
	static int	fd_in;
	pid_t		pid;
	//int			status;

	if (!fd_in)
		fd_in = 0;
	if ((pid = fork()) == -1)
		return (ft_strerror(NULL, NULL, "fork", NULL));
	if (pid == 0)
	{
		set_fd(fd, fd_in, next);
		if (run_dmc(a_cmd))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		//if (wait(&status) == -1)
		//	return (ft_strerror(NULL, NULL, "wait", NULL));
		close(fd[1]);
		fd_in = fd[0];
	}
	return (0);
}

char	**get_cmd(char **args, int adv, int i, int flag)
{
	char **cmd;

	if (flag == 1)
	{
		if (adv == 0)
		{
			if (!(cmd = ft_sub_tab(args, adv, i)))
				return (NULL);
		}
		else
		{
			if (!(cmd = ft_sub_tab(args, adv, (ft_tab_chr_i((char **)&args[adv],
				"|")))))
				return (NULL);
		}
	}
	if (flag == 2)
	{
		if (!(cmd = ft_sub_tab(args, i, ft_tablen(args) - i)))
			return (NULL);
	}
	return (cmd);
}

int		iter_pipes(char **args, t_pipe_tools *t, int *fd)
{
	int status;
	//int old_status = 1;
	int ret = 1;

	while (args[t->i])
	{
		if (ft_strcmp(args[t->i], "|") == 0)
		{
			if (!(t->a_cmd = get_cmd(args, t->adv, t->i, 1)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			t->adv = t->i + 1;
			pipe(fd);
			if (run_pipe(t->a_cmd, fd, 1))
				return (ft_error(NULL, NULL, t->a_cmd, NULL));
			ft_tabdel((void *)t->a_cmd);
		}
		else if (ft_iter_tab_cmp((char **)&args[t->i + 1], "|"))
		{
			if (!(t->a_cmd = get_cmd(args, t->adv, t->i, 2)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			pipe(fd);
			if (run_pipe(t->a_cmd, fd, 0))
				return (ft_error(NULL, NULL, t->a_cmd, NULL));
			break ;
		}
		t->i++;
	}
	while (ret == 1)
		ret = wait(&status);
	return (0);
}

int		run_dmc_pipes(char **args)
{
	int				fd[2];
	t_pipe_tools	t;

	ft_bzero(&t, sizeof(t_pipe_tools));
	if (iter_pipes(args, &t, fd))
		return (ft_error(NULL, NULL, t.a_cmd, NULL));
	ft_tabdel((void *)t.a_cmd);
	return (0);
}