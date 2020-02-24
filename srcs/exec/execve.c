/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/24 15:51:23 by helenebruli      ###   ########.fr       */
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

int		ft_execve(char *path, char **args)
{
	pid_t	pid;
	pid_t	wpid;
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
			exit(ft_strerror(NULL, NULL, path, NULL));
	}
	else if (pid > 0)
	{
		is_forking(1);
		if ((wpid = wait(&status)) == -1)
			return (ft_strerror(NULL, NULL, "wait", NULL));
		g_ret = WEXITSTATUS(status);
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
			return (ft_strerror(path, sub, sub[0], NULL));
		path = build_path(tmp, sub[0]);
		free(tmp);
	}
	if (!path)
		return (ft_error(CMD_NOT_FOUND, NULL, sub, sub[0]));
	else
	{
		ft_execve(path, sub);
		set_io(1);
		ft_tabdel((void *)sub);
		free(path);
		return (0);
	}
	return (0);
}
