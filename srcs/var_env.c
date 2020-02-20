/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:09:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 17:26:43 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_list *lst, char *key)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		if (!(ft_strncmp(lst->content, key, (int)ft_strlen(key))))
			return (ft_strdup((char *)&(lst->content)[ft_strlen(key)]));
		lst = next;
	}
	return (NULL);
}

int		set_var_full(t_list *lst, char *key, char *value)
{
	t_list	*next;
	char	*tmp;
	char	*new;

	if (!key || !(new = ft_strdup(value)))
		return (-1);
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
	free(key);
	return (1);
}

int		set_var(t_list *lst, char *key, char *value)
{
	t_list	*next;
	char	*tmp;
	char	*new;

	if (!value)
	{
		if (!(new = ft_strdup(key)))
			return (-1);
	}
	else if (!(new = ft_strjoin(key, value)))
		return (-1);
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
	return (1);
}

t_list	*del_var(t_list *lst, char *key)
{
	t_list	*tmp;
	t_list	*previous;
	int		ret;

	previous = lst;
	if (!(ft_strncmp(previous->content, key, ft_strlen(key))))
	{
		lst = previous->next;
		ft_lstdelone(previous, free);
		return (lst);
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		ret = ft_strncmp(tmp->content, key, ft_strlen(key));
		if (ret == 0)
		{
			previous->next = tmp->next;
			ft_lstdelone(tmp, free);
			return (lst);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (lst);
}
