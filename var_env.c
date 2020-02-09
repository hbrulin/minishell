/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:09:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 20:57:28 by hbrulin          ###   ########.fr       */
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
			if (!value)
			{
				if(!(tmp = ft_strdup(key)))
					return (-1);
			}
			else
			{
				if(!(tmp = ft_strjoin(key, value)))
					return (-1);
			}
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


int		set_var_export(char *key, char *value)
{
	t_list *temp = NULL;
	char *tmp;
	if(!(tmp = ft_strjoin(key, value)))
		return (-1);
	if (!(temp = malloc(sizeof(t_list))))
		return (-1);
	if (!(temp->content = ft_strdup(tmp)))
		return (-1);
	temp->next = 0;
	ft_lstadd_back(&export, temp);
	return (1);
}


t_list    *del_var_export(char *key)
{
	t_list *tmp;
	t_list *previous;
	int ret;
	previous = export;
	if (!(ft_strncmp(export->content, key, ft_strlen(key))))
	{
  		export = previous->next;
  		free(previous);
  		return (export);
	}
	tmp = previous->next;
	while(tmp != NULL)
	{
		ret = ft_strncmp(tmp->content, key, ft_strlen(key));
  		if (ret == 0)
  		{
    		previous->next = tmp->next;
    		free(tmp);
    		return (export);
  		}
  		previous = tmp; 
  		tmp = tmp->next;
	}
	return (export);
}
