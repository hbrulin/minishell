/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:54:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 16:07:03 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_error(char *arg)
{
	int i;

	i = 0;
	if (envvar_authorized_character(arg[i], TRUE) == FALSE)
		return (ft_error(INVALID_ID_X, NULL, NULL, arg));
	while (arg[++i] && arg[i] != '=')
	{
		if (envvar_authorized_character(arg[i], FALSE) == FALSE)
			return (ft_error(INVALID_ID_X, NULL, NULL, arg));
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
	int i;
	int err;
	int k;
	char *key;
	
	if (ft_tablen(args) == 1)
	{
		ft_lstprint_export(export);
		return(0);
	}
	i = 1;
	k = 0;
	err = 0;
	key = NULL;
	while (args[i])
	{
		if(!(export_error(args[i])))
		{
			while (args[i][k] != '=' && args[i][k])
				k++;
			if (!(ft_lstiter_custom(export, args[i], (int (*)(void *, void *, int))&ft_strncmp)))
			{
				if(!(key = ft_substr(args[i], 0, k + 1)))
					return(ft_strerror(NULL, NULL, NULL, NULL));
				if (ft_strchr(args[i], '='))
				{
					if (set_var_full(export, key, args[i]) == -1)
						return(ft_strerror(key, NULL, NULL, NULL));
					if (set_var_full(env, key, args[i]) == -1)
						return(ft_strerror(key, NULL, NULL, NULL));
				}
				free(key);
			}
			else
			{
				if (add_var(args[i], &export))
					return(ft_strerror(NULL, NULL, NULL, NULL));
				if (ft_strchr(args[i], '='))
				{
					if (add_var(args[i], &env))
						return(ft_strerror(NULL, NULL, NULL, NULL));
				}
			}
		}
		else
			err++;	
		i++;
	}
	if (err > 0)
		return (1);
	return (0);
}
