/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:30:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/11 13:11:22 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unset_error(char *arg)
{
	int i = 0;

	if (envvar_authorized_character(arg[i], TRUE) == FALSE)
		return(ft_error("unset: not a valid identifier: %s\n", 1, NULL, arg));
	while (arg[++i])
	{
		if (envvar_authorized_character(arg[i], FALSE) == FALSE)
			return(ft_error("unset: not a valid identifier: %s\n", 1, NULL, arg));
	}
	return(0);
}

int		ft_unset(char **args)
{
	int i;
	i = 0;
	if (ft_tablen(args) == 1)
		return(ft_error("unset: not enough arguments\n", 1, NULL, NULL));
	while (args[i])
	{
		if (!(unset_error(args[i])))
		{
			del_var(export, args[i]);
			del_var(env, args[i]);
		}
		i++;
	}
	return (1);
}
