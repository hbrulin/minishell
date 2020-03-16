/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:47:06 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/16 14:51:52 by helenebruli      ###   ########.fr       */
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
	return (sub);
}

int		run_dmc(char **args)
{
	int		i;
	char	**sub;

	if (!args || !*args)
		return (0);
	if (!(sub = pre_run(args)))
		return (0);
	if ((i = builtin_fno(sub[0])) != -1)
	{
		g_ret = g_builtin_functions[i](sub);
		set_io(1);
		ft_tabdel((void *)sub);
		return (g_ret);
	}
	path_exec(sub);
	ft_tabdel((void *)sub);
	return (0);
}