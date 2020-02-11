/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:09:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/11 17:28:44 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//(char *)&tmp[ft_strlen(key)]

char    *get_var(t_list *lst, char *key)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		if (!(ft_strncmp(lst->content, key, (int)ft_strlen(key))))
			return(ft_strdup((char *)&(lst->content)[ft_strlen(key)]));
		lst = next;
	}
	return(NULL);
}

int		set_var_full(t_list *lst, char *key, char *value)
{
	t_list *next;
	char *tmp = NULL;
	char *new;

	new = ft_strdup(value);
	while (lst)
	{
		next = lst->next;
		if (!(ft_strncmp(lst->content, key, (int)ft_strlen(key))))
		{
			tmp = lst->content;
			lst->content = new;
			free(tmp);
		}
		lst = next;
	}
	return(1);
}


int		set_var(t_list *lst, char *key, char *value)
{
	t_list *next;
	char *tmp = NULL;
	char *new;

	if (!value)
		new = ft_strdup(key);
	else
	{
		if(!(new = ft_strjoin(key, value)))
			return (-1);
	}
	while (lst)
	{
		next = lst->next;
		if (!(ft_strncmp(lst->content, key, (int)ft_strlen(key))))
		{
			tmp = lst->content;
			lst->content = new;
			free(tmp);
		}
		lst = next;
	}
	return(1);
}

t_list    *del_var(t_list *lst, char *key)
{
	t_list *tmp;
	t_list *previous;
	int ret;
	previous = lst;
	if (!(ft_strncmp(previous->content, key, ft_strlen(key))))
	{
  		lst = previous->next;
  		free(previous);
  		return (lst);
	}
	tmp = previous->next;
	while(tmp != NULL)
	{
		ret = ft_strncmp(tmp->content, key, ft_strlen(key));
  		if (ret == 0)
  		{
    		previous->next = tmp->next;
    		free(tmp);
    		return (lst);
  		}
  		previous = tmp; 
  		tmp = tmp->next;
	}
	return (lst);
}
