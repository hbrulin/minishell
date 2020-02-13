/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_search_n_destroy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:38:49 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 13:41:00 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_search_n_destroy(t_list *lst, char *key)
{
	t_list	*tmp;
	t_list	*previous;

	previous = lst;
	if (!lst)
		return (lst);
	if (!(ft_strncmp(previous->content, key, ft_strlen(key))))
	{
		lst = previous->next;
		ft_lstdelone(previous, free);
		return (lst);
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (!(ft_strncmp(tmp->content, key, ft_strlen(key))))
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
