/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:47:06 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/16 16:05:02 by helenebruli      ###   ########.fr       */
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
	int i;
	char	*path;
	char	*tmp; // find a better solution
	char 	**sub;

	if (!args || !*args)
		return (0);
	sub = ft_rmfd(args);
	ft_tabdel((void *)args);
	if ((i = builtin_fno(sub[0])) != -1)
		return (g_ret = g_builtin_functions[i](sub));
	path = ft_strrchr(sub[0], '/');
	if (path && !(path = ft_strdup(try_path(sub[0])))) // a complete path was given, we only want to check it, errors will be : ENOENT, EISDIR, ENOTDIR
		return (ft_strerror(path, sub, sub[0], NULL));
	// a command name was given, we'll try to build paths from $PATH var, error will be custom : 'command not found'
	else if (!path)
	{
		tmp = get_var(env, "PATH=");
		path = build_path(tmp, sub[0]);
		free(tmp);
	}
	if (!path) // command name could not be find in given directories
		return (ft_error(CMD_NOT_FOUND, NULL, NULL, sub[0]));
	else
		return (g_ret = ft_execve(path, sub));
	return (0);
}
