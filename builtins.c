/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 15:00:29 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(void)
{
	char *dir;
	char *old_dir;

	dir = NULL;
	old_dir = get_var("PWD=");
	if (!(dir = getcwd(dir, 0)))
	{
		ft_printf_fd(2, "minishell: error fatal: getcwd did not allocate properly\n");
		return(0);
	}
	set_var("PWD=", dir);
	set_var("OLDPWD=", old_dir);
	free(dir);
	free(old_dir);
	return (1);
}

int		ft_cd(char **args)
{
	int len;

	len = ft_tablen(args);
	if (len > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2); 
		return (1);
	}
	else if (len == 1)
	{
		if ((chdir(get_var("HOME="))) == -1)
			ft_putstr_fd("minishell: cd: error finding home directory\n", 2);
	}
	else if (len == 2)
	{
		if ((chdir(args[1])) == -1)
			ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", args[1]);
	}
	return(update_pwd());
}

int		ft_pwd(char **args)
{
	char *dir;

	dir = NULL;
	if (ft_tablen(args) > 1)
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2); 
		return (1);
	}
	if (!(dir = getcwd(dir, 0)))
	{
		ft_printf_fd(2, "minishell: error fatal: getcwd did not allocate properly\n");
		return(0);
	}
	ft_printf_fd(1, "%s\n", dir);
	free(dir);
	return (1);
}

int		ft_env(char **args)
{
	int i;
	if (ft_tablen(args) > 1)
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (1);
	}
	i = 0;
	while(g_env[i])
	{
		ft_putstr(g_env[i]);
		ft_putstr("\n");
		i++;
	}
	return (1);
}

int		ft_exit(char **args)
{
	int i;
	i = 0;
	if (ft_tablen(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return(1);
	}
	if (ft_tablen(args) == 1)
		return(0);
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i])))
		{
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", args[1]);
			return (0);
		}
		i++;
	}
	g_ret = ft_atoi(args[1]);
	return (0);
}
