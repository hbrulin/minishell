/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:38:15 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/02 14:55:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		update_pwd(void)
{
	char *dir;
	char *old_dir;

	dir = NULL;
	old_dir = NULL;
	if (!(old_dir = get_var(g_env, "PWD=")))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	if (!(dir = getcwd(dir, 0)))
		return (ft_strerror(old_dir, NULL, NULL, NULL));
	set_var(g_env, "PWD=", dir);
	set_var(g_export, "PWD=", dir);
	set_var(g_env, "OLDPWD=", old_dir);
	set_var(g_export, "OLDPWD=", old_dir);
	free(dir);
	free(old_dir);
	return (0);
}

int		ft_cd(char **args)
{
	int		len;
	char	*home;

	len = ft_tablen(args);
	if (len == 1 || !(ft_strcmp(args[1], "")))
	{
		if (!(home = get_var(g_env, "HOME=")))
			return (ft_error("cd: HOME not set\n", NULL, NULL, NULL));
		if ((chdir(home)) == -1)
			return (ft_strerror(home, NULL, home, NULL));
		free(home);
	}
	else if (len >= 2)
	{
		if ((chdir(args[1])) == -1)
			return (ft_strerror(NULL, NULL, "cd", args[1]));
	}
	return (update_pwd());
}
