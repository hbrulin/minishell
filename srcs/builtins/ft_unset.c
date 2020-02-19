/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:30:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 18:37:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unset_error(char *arg)
{
	int i;

	i = 0;
	if (envvar_authorized_character(arg[i], TRUE) == FALSE)
		return (ft_error(INVALID_ID_U, NULL, NULL, arg));
	while (arg[++i])
	{
		if (envvar_authorized_character(arg[i], FALSE) == FALSE)
			return (ft_error(INVALID_ID_U, NULL, NULL, arg));
	}
	return (0);
}

int		ft_unset(char **args)
{
	int i;

	i = 0;
	if (ft_tablen(args) == 1)
		return (ft_error(NO_ARG, NULL, NULL, args[0]));
	while (args[i])
	{
		if (!(unset_error(args[i])))
		{
			del_var(export, args[i]);
			del_var(env, args[i]);
		}
		else
			return (1);
		i++;
	}
	return (0);
}
