/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 16:06:09 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_forking(int val)
{
	static int is_forking = 0;

	if (val != 2)
		is_forking = val;
	return (is_forking);
}

void	handle_sig(int status)
{
	g_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_ret = SIG_CODE + WTERMSIG(status);
	if (WTERMSIG(status) == 3)
		ft_printf_fd(1, "Quit: %i\n", SIGQUIT);
	if (WTERMSIG(status) == 2)
		ft_putstr("\n");
}

int		ft_execve(char *path, char **args)
{
	pid_t	pid;
	int		status;
	char	**tab_env;

	tab_env = NULL;
	if (!(tab_env = ft_lst_to_tab(g_env)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	if ((pid = fork()) == -1)
		return (ft_strerror(NULL, tab_env, "fork", NULL));
	if (pid == 0)
	{
		if ((execve(path, args, tab_env)) == -1)
			exit(ft_ret_errno(NULL, NULL, path));
	}
	else if (pid > 0)
	{
		is_forking(1);
		if (wait(&status) == -1)
			return (ft_strerror(NULL, NULL, "wait", NULL));
		handle_sig(status);
		is_forking(0);
		ft_tabdel((void**)tab_env);
		return (0);
	}
	return (0);
}

int		path_exec(char **sub)
{
	char	*path;
	char	*tmp;

	path = ft_strrchr(sub[0], '/');
	if (path && !(path = ft_strdup(try_path(sub[0]))))
		return (ft_strerror(path, sub, sub[0], NULL));
	else if (!path)
	{
		if (!(tmp = get_var(g_env, "PATH=")))
		{
			g_ret = 127;
			return (ft_error(NO_FILE, path, sub, sub[0]));
		}
		path = build_path(tmp, sub[0]);
		free(tmp);
	}
	if (!path)
		return (ft_error(CMD_NOT_FOUND, NULL, sub, sub[0]));
	else
	{
		ft_execve(path, sub);
		set_io(1);
		ft_error(NULL, path, sub, NULL);
	}
	return (0);
}
