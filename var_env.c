/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:09:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 18:41:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    set_var(char *key, char *value)
{
    int i;
    char * tmp;

    i = 0;
	while(g_env[i])
	{
		if (ft_strncmp(g_env[i], key, ft_strlen(key)) == 0)
        {
            if(!(tmp = ft_strjoin(key, value)))
				return (-1);
            free(g_env[i]);
            if(!(g_env[i] = ft_strdup(tmp)))
				return(ft_error(NULL, -1, tmp, NULL));
			free(tmp);
        }
		i++;
	}
	return (1);
}

char    *get_var(char *key)
{
    int i;
    char *tmp = NULL;

    i = 0;
	while(g_env[i])
	{
		if (ft_strncmp(g_env[i], key, ft_strlen(key)) == 0)
            tmp = ft_substr(g_env[i], ft_strlen(key), ft_strlen(g_env[i]) - ft_strlen(key));
		i++;
	}
    return (tmp);
}

int		ft_export(char **args)
{
	int i;
	int j;

	t_list *temp = NULL;
	ft_list_sort(export);
	if (ft_tablen(args) == 1)
	{
		ft_lstiter(export, (void (*)(void *))&ft_putstr);
		return(1);
	}
	i = 1;
	while (args[i])
	{
		if(ft_isdigit(args[i][0]))
			ft_error("export: not an identifier: %s\n", 1, NULL, args[i]);
		j = 0;
		while (args[i][j])
		{
			if (!(ft_isalnum(args[i][j])))
				ft_error("export: syntax error: %s\n", 1, NULL, args[i]);
			j++;
		}
		if (!(ft_lstiter_custom(export, args[i], (int (*)(void *, void *, int))&ft_strncmp)))
		{
			ft_putstr("ok\n");
		}
		else
		{
			if (!(temp = malloc(sizeof(t_list))))
				return (0); //il faut msg error
			if (!(temp->content = ft_strdup(args[i])))
				return (0); //idem
			temp->next = 0;
			ft_lstadd_back(&export, temp);
		}
		i++;
	}
	return (1);
}
