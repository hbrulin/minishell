/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:47:06 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/07 11:00:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_fc	g_builtin_functions[] = {
	&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit
};

int		builtin_fno(const char *name)
{
	static const char	*builtin_names[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};

	return (ft_tabindex(builtin_names, name));
}

char	**pre_run(char **args)
{
	char	**sub;
	char	**rm_void;

	if (!(sub = redirect(args)))
	{
		set_io(1);
		g_ret = ft_error(NULL, NULL, NULL, NULL);
		return (NULL);
	}
	if (interpreter(sub) == 1)
	{
		g_ret = 2;
		ft_error(SYNTAX_ERR, NULL, sub, NULL);
		return (NULL);
	}
	if (!(rm_void = copy_tab_void(sub)))
	{
		ft_strerror(NULL, sub, NULL, NULL);
		return (NULL);
	}
	ft_tabdel((void *)sub);
	return (rm_void);
}

int		run_dmc(char **args)
{
	int		i;
	char	**rm_void;

	if (!args || !*args)
		return (0);
	if (!ft_strcmp(args[0], "ls"))
	{
		if (ls_part(args))
			return (0);
	}
	if (!(rm_void = pre_run(args)))
		return (0);
	if ((i = builtin_fno(rm_void[0])) != -1)
	{
		g_ret = g_builtin_functions[i](rm_void);
		set_io(1);
		ft_tabdel((void *)rm_void);
		return (g_ret);
	}
	path_exec(rm_void);
	ft_tabdel((void *)rm_void);
	return (0);
}

char	**pre_run_pipes(char **args)
{
	char	**rm_void;

	if (interpreter(args) == 1)
	{
		g_ret = 2;
		ft_error(SYNTAX_ERR, NULL, NULL, NULL);
		return (NULL);
	}
	if (!(rm_void = copy_tab_void(args)))
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (NULL);
	}
	return (rm_void);
}

int		run_dmc_pipes(char **args)
{
	int		i;
	char	**rm_void;

	if (!args || !*args)
		return (0);
	if (!ft_strcmp(args[0], "ls"))
	{
		if (ls_part(args))
			return (0);
	}
	if (!(rm_void = pre_run_pipes(args)))
		return (0);
	if ((i = builtin_fno(rm_void[0])) != -1)
	{
		g_ret = g_builtin_functions[i](rm_void);
		set_io(1);
		ft_tabdel((void *)rm_void);
		return (g_ret);
	}
	path_exec_pipes(rm_void);
	ft_tabdel((void *)rm_void);
	return (0);
}

