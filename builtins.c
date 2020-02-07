/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 17:26:15 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(void)
{
	char *dir;

	dir = NULL;
	if (!(dir = getcwd(dir, 0)))
	{
		ft_printf("PWD malloc fail\n");
		return(0);
	}
	set_var("PWD=", dir);
	free(dir);
	return (1);
}

int		ft_cd(char **args)
{
	int len;

	len = ft_tablen(args);
	if (len > 2)
	{
		ft_putstr("minishell: cd: too many arguments\n"); 
		return (1);
	}
	else if (len == 1)
	{
		if ((chdir(get_var("HOME="))) == -1)
			ft_putstr("minishell: cd: error\n");
	}
	else if (len == 2)
	{
		if ((chdir(args[1])) == -1)
			ft_putstr("minishell: cd: error\n");
	}
	return(update_pwd());
}

int		ft_pwd(char **args)
{
	char *dir;

	dir = NULL;
	if (ft_tablen(args) > 1)
	{
		ft_putstr("minishell: pwd: too many arguments\n"); //pas obligé
		return (1);
	}
	if (!(dir = getcwd(dir, 0)))
	{
		ft_printf("Malloc fail\n");
		return(0);
	}
	ft_printf("%s\n", dir);
	free(dir);
	return (1);
}

int		ft_env(char **args)
{
	int i;
	if (ft_tablen(args) > 1)
	{
		ft_putstr("minishell: env: too many arguments\n");
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
		ft_putstr("minishell: exit: too many arguments\n");
		return(1);
	}
	if (ft_tablen(args) == 1)
		return(0);
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i])))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
			return (0);
		}
		i++;
	}
	g_ret = ft_atoi(args[1]);
	return (0);
}
