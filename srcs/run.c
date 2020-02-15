/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:47:06 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/14 15:47:08 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_fc	g_builtin_functions[] = {
	&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit
};

int	builtin_fno(const char *name)
{
	static const char	*builtin_names[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};
	
	return (ft_tabindex(builtin_names, name));
}

int	run_dmc(char **args)
{
	int		err;
	char	*path;
	char	*tmp; // find a better solution

	if (!args || !*args)
		return (0);
	if ((err = builtin_fno(args[0])) != -1)
		return (g_ret = g_builtin_functions[err](args));
	path = ft_strrchr(args[0], '/');
	err = 0;
	if (path)
		path = ft_strdup(try_path(args[0], &err));
	else
	{
		tmp = get_var(env, "PATH="); // oh waw...
		if (!(path = tryent_dirs(tmp, args[0])))
			err = ENOSYS; // for test only, this error is not the right one
		free(tmp);
	}
	if (err)
		return(ft_printf_fd(2, "minishell: %s: %s\n", args[0], strerror(err)));
	else
		return(ft_execve(path, args));
	return(g_ret);
}
