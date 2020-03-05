/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:19:55 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/05 18:30:15 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execve_pipes(char *path, char **args)
{
	char	**tab_env;

	tab_env = NULL;
	if (!(tab_env = ft_lst_to_tab(g_env)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	
	if ((execve(path, args, tab_env)) == -1)
			exit(ft_ret_errno(NULL, NULL, path));
	return (0);
}

int		path_exec_pipes(char **sub)
{
	char	*path;
	char	*tmp;

	path = ft_strrchr(sub[0], '/');
	if (path && !(path = ft_strdup(try_path(sub[0]))))
		return (ft_strerror(NULL, NULL, sub[0], NULL));
	else if (!path)
	{
		if (!(tmp = get_var(g_env, "PATH=")))
		{
			g_ret = 127;
			return (ft_error(NO_FILE, path, NULL, sub[0]));
		}
		path = build_path(tmp, sub[0]);
		free(tmp);
	}
	if (!path)
		return (ft_error(CMD_NOT_FOUND, NULL, NULL, sub[0]));
	else
	{
		ft_execve_pipes(path, sub);
		set_io(1);
		free(path);
	}
	return (0);
}





