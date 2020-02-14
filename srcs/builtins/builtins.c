/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/12 19:37:06 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(void)
{
	char *dir;
	char *old_dir;

	dir = NULL;
	old_dir = NULL;
	if(!(old_dir = get_var(env, "PWD=")))
		return(ft_error(MALLOC_FAIL, 1, NULL, NULL));
	if (!(dir = getcwd(dir, 0)))
		return(ft_error(MALLOC_FAIL, 1, old_dir, NULL));
	set_var(env, "PWD=", dir);
	set_var(export, "PWD=", dir);
	set_var(env, "OLDPWD=", old_dir);
	set_var(export, "OLDPWD=", old_dir);
	free(dir);
	free(old_dir);
	return (0);
}

char	*get_home()
{
	char *ret;
	char *var;

	if(!(var = get_var(env, "HOME=")))
		return(NULL);
	ret = ft_substr(var, ft_strlen("HOME="), ft_strlen(var) - ft_strlen("HOME"));
	return(ret);
}

int		ft_cd(char **args)
{
	int len;
	char *home;

	len = ft_tablen(args);
	if (len == 1 || !(ft_strcmp(args[1], "")))
	{
		if(!(home = get_home()))
			return(ft_error("cd: HOME not set\n", 0, NULL, NULL));
		if ((chdir(home)) == -1)
			ft_printf_fd(2, NO_FILE, home);
		free(home);
	}
	else if (len == 2)
	{
		if ((chdir(args[1])) == -1)
			ft_printf_fd(2, NO_FILE, args[1]);
	}
	return(update_pwd());
}

int		ft_pwd(char **args)
{
	char *dir;
	dir = NULL;
	if (ft_tablen(args) > 1)
		return(ft_error(MANY_ARGS, 0, NULL, args[0]));
	if (!(dir = getcwd(dir, 0)))
		return(ft_error(MALLOC_FAIL, 1, NULL, NULL));
	ft_printf_fd(1, "%s\n", dir);
	free(dir);
	return (0);
}

int		ft_env(char **args)
{
	if (ft_tablen(args) > 1)
		return(ft_error(MANY_ARGS, 0, NULL, args[0]));
	ft_lstprint(env);
	return (0);
}

int		ft_exit(char **args)
{
	int i;
	i = 0;
	if (ft_tablen(args) > 2)
		return(ft_error(MANY_ARGS, 0, NULL, args[0]));
	if (ft_tablen(args) == 1)
		return(1);
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i])))
			return(ft_error(EXIT_NUM, 1, NULL, args[1]));
		i++;
	}
	g_ret = ft_atoi(args[1]);
	return (1);
}
