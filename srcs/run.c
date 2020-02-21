/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:47:06 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/21 16:25:53 by hbrulin          ###   ########.fr       */
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

int		run_dmc(char **args)
{
	int		i;
	char	**sub;

	if (!args || !*args)
		return (0);
	if (!(sub = redirect(args)))
	{
		set_io(1);
		return (g_ret = ft_error(NULL, NULL, NULL, NULL));
	}
	if (interpreter(sub) == 1)
		return (g_ret = ft_error(SYNTAX_ERR, NULL, sub, NULL));
	if ((i = builtin_fno(sub[0])) != -1)
	{
		g_ret = g_builtin_functions[i](sub);
		set_io(1);
		ft_tabdel((void *)sub);
		return (g_ret);
	}
	return (g_ret = path_exec(sub));
}
