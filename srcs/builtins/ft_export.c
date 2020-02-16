/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:54:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/12 16:14:17 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_error(char *arg)
{
	int i = 0;

	if (envvar_authorized_character(arg[i], TRUE) == FALSE)
		return(ft_error(INVALID_ID_X, NULL, NULL, arg));
	while (arg[++i] && arg[i] != '=')
	{
		if (envvar_authorized_character(arg[i], FALSE) == FALSE)
			return(ft_error(INVALID_ID_X, NULL, NULL, arg));
	}
	return(0);
}

int		ft_export(char **args)
{
	int i;
	int k;
	char *key = NULL;
	t_list *temp = NULL;
	t_list *temp2 = NULL;
	//ft_printf_fd(1, "IN");
	ft_list_sort(export);
	if (ft_tablen(args) == 1)
	{
		ft_lstprint_export(export);
		return(0);
	}
	i = 1;
	k = 0;
	while (args[i])
	{
		while (args[i][k] != '=' && args[i][k])
			k++;
		if(!(export_error(args[i])))
		{
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
				if (!(temp = malloc(sizeof(t_list))))
					return(ft_strerror(NULL, NULL, NULL, NULL));
				if (!(temp->content = ft_strdup(args[i])))
						return(ft_strerror(NULL, NULL, NULL, NULL));
				temp->next = 0;
				if (!(ft_strchr(args[i], '=')))
					ft_lstadd_back(&export, temp);
				else 
				{
					ft_lstadd_back(&export, temp);
					if (!(temp2 = malloc(sizeof(t_list))))
						return(ft_strerror(NULL, NULL, NULL, NULL));
					if (!(temp2->content = ft_strdup(args[i])))
						return(ft_strerror(NULL, NULL, NULL, NULL));
					ft_lstadd_back(&env, temp2);
				}	
			}
		}
		i++;
	}
	return (0);
}
