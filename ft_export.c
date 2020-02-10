/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:54:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 17:39:47 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		export_error(char *arg)
{
	int i = 0;

	if (ft_strcmp(arg, "=") == 0)
		return(ft_error("export: bad assignment\n", 1, NULL, NULL));
	if(ft_isdigit(arg[0]) || arg[0] == '=')
		return(ft_error("export: not an identifier: %s\n", 1, NULL, arg));
	while (arg[i])
	{
		if (envvar_authorized_character(arg[i], TRUE) == FALSE)
		{
			if (arg[i] != '=')
				return(ft_error("export: not an identifier: %s\n", 1, NULL, arg));
		}
		i++;
	}
	return(0);
}


int		ft_export(char **args)
{
	int i;
	int k;
	char *key = NULL;
	t_list *temp = NULL;
	//ft_tab_print(args);
	ft_list_sort(export);
	if (ft_tablen(args) == 1)
	{
		ft_lstprint(export);
		return(1);
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
				if (ft_strchr(args[i], '=') && args[i][k + 1] == '\0')
				{
					key = ft_substr(args[i], 0, k + 1);
					del_var(export, key);
					set_var(export, key, "''"); 
					del_var(env, key);
					set_var(env, key, NULL); 
				}
				else if (ft_strchr(args[i], '='))
				{
					key = ft_substr(args[i], 0, k + 1);
					del_var(export, key);
					set_var(export, key, args[i] + k + 1);
					del_var(env, key);
					set_var(env, key, args[i] + k +1);
				}
				free(key);
			}
			else
			{
				if (!(temp = malloc(sizeof(t_list))))
					return (0); //il faut msg error, ft_error
				if (!(ft_strchr(args[i], '=')))
				{
					if (!(temp->content = ft_strjoin(args[i], "=''")))
						return (0); //idem
				}	
				else if (ft_strchr(args[i], '=') && args[i][k + 1] == '\0')
				{
					if (!(temp->content = ft_strjoin(args[i], "''")))
						return (0); //idem
				}	
				else
				{
					if (!(temp->content = ft_strdup(args[i])))
					return (0); //idem
				}
				temp->next = 0;
				ft_lstadd_back(&export, temp);
			}
		}
		i++;
	}
	return (1);
}
