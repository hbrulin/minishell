/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:09:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 14:53:11 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_var(t_list *lst, char *key)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		if (!(ft_strncmp(lst->content, key, (int)ft_strlen(key))))
			return(lst->content);
		lst = next;
	}
	return(NULL);
}

int		set_var(t_list *lst, char *key, char *value)
{
	t_list *temp = NULL;
	char *tmp;
	if (!value)
		tmp = ft_strdup(key);
	else
	{
		if(!(tmp = ft_strjoin(key, value)))
		return (-1);
	}
	if (!(temp = malloc(sizeof(t_list))))
		return (-1);
	if (!(temp->content = ft_strdup(tmp)))
		return (-1);
	temp->next = 0;
	ft_lstadd_back(&lst, temp);
	return (1);
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
