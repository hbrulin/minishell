/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/05 18:04:30 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR -1
#define EXIT_ERROR(message) { perror(message); exit(errno);} //retirer 

typedef struct	s_cmd
{
	char		*path;
	char		**argv;
}				t_cmd;

void	execute_pipes(t_cmd *cmd, size_t index, size_t len, int parent_fd[2])
{
	pid_t	pid;
	int		pipe_fd[2];

	char	**tab_env;
	if (!(tab_env = ft_lst_to_tab(g_env)))
		return ;

	if (index < len - 1)
	{
		if (pipe(pipe_fd) == ERROR)
			EXIT_ERROR("pipe");
		if ((pid = fork()) == ERROR)
			EXIT_ERROR("fork");
		if (pid == 0)
			execute_pipes(cmd, index + 1, len, pipe_fd);
		//ft_printf_fd(2, "dup out cmd %lu\n", index);
		if (dup2(pipe_fd[0], STDIN_FILENO) == ERROR)
			EXIT_ERROR("dup2");
		if (close(pipe_fd[1]) == ERROR)
			EXIT_ERROR("close");
		if (close(pipe_fd[0]) == ERROR)
			EXIT_ERROR("close");
		//ft_printf_fd(2, "wait cmd %lu\n", index);
		wait(NULL);
	}
	if (index)
	{
		//ft_printf_printf(2, "dup in cmd %lu\n", index);
		if (dup2(parent_fd[1], STDOUT_FILENO) == ERROR)
			EXIT_ERROR("dup2");
		if (close(parent_fd[0]) == ERROR)
			EXIT_ERROR("close");
		if (close(parent_fd[1]) == ERROR)
			EXIT_ERROR("close");
	}
	//ft_printf_fd(2, "exec cmd %lu\n", index);
	
	//ft_printf_fd(1, "%s\n", cmd[index].path);
	//dprintf(2, "%lu\n", index);
	//ft_tab_print(cmd[index].argv);

	if (execve(cmd[index].path, cmd[index].argv, tab_env) == ERROR)
		EXIT_ERROR("execve");
	ft_tabdel((void**)tab_env);
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



int		run_dmc_pipes(char **args)
{
	t_pipe_tools	t;
	pid_t	pid;
	int status;
	int len = 2; //countnb pipes
	ft_bzero(&t, sizeof(t_pipe_tools));

	t_cmd	*cmd;
	cmd = malloc(sizeof(t_cmd) * len);
	
	int j = len - 1;

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
			j--;
		}
		else if (ft_iter_tab_cmp((char **)&args[t.i + 1], "|"))
		{
			if (!(t.a_cmd = get_cmd(args, t.adv, t.i, 2)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			cmd[j].path = ft_strdup(t.a_cmd[0]);
			cmd[j].argv = copy_tab(t.a_cmd);
			//ft_tab_print(cmd[j].argv);
			break ;
		}
		t.i++;
	}

	pid = fork();
	if (pid == 0)
		execute_pipes(cmd, 0, len, 0);
	if (pid > 0)
		wait(&status);

	return (0);
}
