/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_search_n_destroy.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:20:57 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 13:21:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list    *ft_lst_search_n_destroy(t_list *lst, char *key)
{
	t_list *tmp;
	t_list *previous;
	int ret;
	previous = lst;
	if (!lst)
		return(lst);
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
