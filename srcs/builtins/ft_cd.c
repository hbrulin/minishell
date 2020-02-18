/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/18 14:07:06 by pmouhali         ###   ########.fr       */
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
