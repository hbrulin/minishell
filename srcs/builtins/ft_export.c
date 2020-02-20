/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:54:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 16:24:49 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_error(char *arg, int *err)
{
	int i;

	i = 0;
	if (envvar_authorized_character(arg[i], TRUE) == FALSE)
		return (*err = ft_error(INVALID_ID_X, NULL, NULL, arg));
	while (arg[++i] && arg[i] != '=')
	{
		if (envvar_authorized_character(arg[i], FALSE) == FALSE)
			return (*err = ft_error(INVALID_ID_X, NULL, NULL, arg));
	}
	return (0);
}

int		add_var(char *s, t_list **list)
{
	t_list	*temp;

	temp = NULL;
	if (!(temp = malloc(sizeof(t_list))))
		return (1);
	if (!(temp->content = ft_strdup(s)))
		return (1);
	temp->next = 0;
	ft_lstadd_back(list, temp);
	return (0);
}

int		ft_export(char **args)
{
	int		i;
	int		err;
	int		k;

	if (ft_tablen(args) == 1)
		return (ft_lstprint_export(export));
	i = 1;
	err = 0;
	while (args[i] && !(export_error(args[i], &err)))
	{
		k = 0;
		while (args[i][k] != '=' && args[i][k])
			k++;
		if (!(ft_lstiter_custom(export, args[i], (int (*)(void *,
			void *, int))&ft_strncmp)))
		{
			if (ft_strchr(args[i], '='))
			{
				if (set_var_full(export, ft_substr(args[i], 0, k + 1), args[i]) == -1)
					return (ft_strerror(NULL, NULL, NULL, NULL));
				if (set_var_full(env, ft_substr(args[i], 0, k + 1), args[i]) == -1)
					return (ft_strerror(NULL, NULL, NULL, NULL));
			}
		}
		else
		{
			if (add_var(args[i], &export))
				return (ft_strerror(NULL, NULL, NULL, NULL));
			if (ft_strchr(args[i], '='))
			{
				if (add_var(args[i], &env))
					return (ft_strerror(NULL, NULL, NULL, NULL));
			}
		}
		i++;
	}
	return (err);
}
