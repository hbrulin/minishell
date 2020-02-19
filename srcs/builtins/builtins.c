/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 15:26:47 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		update_pwd(void)
{
	char *dir;
	char *old_dir;

	dir = NULL;
	old_dir = NULL;
	if(!(old_dir = get_var(env, "PWD=")))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	if (!(dir = getcwd(dir, 0)))
		return (ft_strerror(old_dir, NULL, NULL, NULL));
	set_var(env, "PWD=", dir);
	set_var(export, "PWD=", dir);
	set_var(env, "OLDPWD=", old_dir);
	set_var(export, "OLDPWD=", old_dir);
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
		if(!(home = get_var(env, "HOME=")))
			return (ft_error("cd: HOME not set\n", NULL, NULL, NULL));
		if ((chdir(home)) == -1)
			return (ft_strerror(home, NULL, home, NULL));
		free(home);
	}
	else if (len == 2)
	{
		if ((chdir(args[1])) == -1)
			return (ft_strerror(NULL, NULL, "cd", args[1]));
	}
	return (update_pwd());
}

int		ft_pwd(char **args)
{
	char *dir;

	dir = NULL;
	(void)args;
	if (ft_tablen(args) > 1)
		return (ft_error(MANY_ARGS, NULL, NULL, args[0]));
	if (!(dir = getcwd(dir, 0)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	ft_printf_fd(1, "%s\n", dir);
	free(dir);
	return (0);
}

int		ft_env(char **args)
{
	if (ft_tablen(args) > 1)
		return(ft_error(MANY_ARGS, NULL, NULL, args[0]));
	ft_lstprint(env);
	return (0);
}

int		ft_exit(char **args)
{
	int i;
	unsigned int j;

	i = 0;
	if (ft_tablen(args) > 2)
		return (ft_error(MANY_ARGS, NULL, NULL, args[0]));
	if (ft_tablen(args) == 1)
		exit(0);
	if (args[1][i] == '+' || args[1][i] == '-')
		i++;
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i])))
		{
			ft_error(EXIT_NUM, NULL, NULL, args[1]);
			exit(0);
		}
		i++;
	}
	if((i = ft_atoi(args[1])) < 0)
		j = (unsigned char)i;
	else
		j = i;
	exit(j);
}
