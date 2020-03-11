/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/11 21:28:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXIT_ERROR(message) { perror(message); exit(errno);} //retirer 

void	dup_stdio(int pipe_fd[2], int std_fileno)
{
	if (dup2(pipe_fd[std_fileno], std_fileno) == ERROR)
		EXIT_ERROR("dup2");
	if (close(pipe_fd[1]) == ERROR)
		EXIT_ERROR("close");
	if (close(pipe_fd[0]) == ERROR)
		EXIT_ERROR("close");
}

void	execute_pipes(t_cmd *cmd, size_t index, size_t len, int parent_fd[2])
{
	pid_t	pid;
	int		pipe_fd[2];
	char	**sub;
	int		status;

	set_io(0);
	if (index)
		dup_stdio(parent_fd, STDIN_FILENO);
	if (index < len - 1)
	{
		if (pipe(pipe_fd) == ERROR)
			EXIT_ERROR("pipe");
		if ((pid = fork()) == ERROR)
			EXIT_ERROR("fork");
		if (pid == 0)
			execute_pipes(cmd, index + 1, len, pipe_fd);
		dup_stdio(pipe_fd, STDOUT_FILENO);
	}
	if (!(sub = redirect(cmd[index].argv)))
	{
		set_io(1);
		g_ret = ft_error(NULL, NULL, NULL, NULL);
		return ;
	}
	if (run_dmc_pipes(sub) == 1)
		EXIT_ERROR("execve");
	set_io(1);
	int ret = 1;
	while (ret == 1)
		ret = wait(&status);
	exit(0);
}

int		handle_pipes(char **args)
{
	t_pipe_tools	t;
	pid_t			pid;
	int				status;
	int				len;
	t_cmd			*cmd;
	int				j;

	len = count_pipes(args) + 1;
	ft_bzero(&t, sizeof(t_pipe_tools));
	cmd = malloc(sizeof(t_cmd) * len);
	j = 0;
	while (args[t.i])
	{
		if (ft_strcmp(args[t.i], "|") == 0)
		{
			if (!(t.a_cmd = get_cmd(args, t.adv, t.i, 1)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			cmd[j].path = ft_strdup(t.a_cmd[0]);
			cmd[j].argv = copy_tab(t.a_cmd);
			t.adv = t.i + 1;
			ft_tabdel((void *)t.a_cmd);
			j++;
		}
		else if (ft_iter_tab_cmp((char **)&args[t.i + 1], "|"))
		{
			if (!(t.a_cmd = get_cmd(args, t.adv, t.i, 2)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			cmd[j].path = ft_strdup(t.a_cmd[0]);
			cmd[j].argv = copy_tab(t.a_cmd);
			ft_tabdel((void *)t.a_cmd);
			break ;
		}
		t.i++;
	}
	pid = fork();
	if (pid == 0)
		execute_pipes(cmd, 0, len, 0);
	else if (pid > 0)
	{
		is_forking(1);
		waitpid(pid, &status, 0);
		handle_sig_pipes(status);
		is_forking(0);
	}
	free_t_cmd(cmd, len);
	return (0);
}
