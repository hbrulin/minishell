/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:36:47 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 17:47:00 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_sort(t_list *lst)
{
	t_bool	sort;
	t_list	*head;
	void	*swp;

	if (!lst->next)
		return ;
	sort = true;
	head = lst;
	while (sort)
	{
		sort = false;
		while (lst)
		{
			while (lst->next && ft_strcmp(lst->content, lst->next->content) > 0)
			{
				sort = true;
				swp = lst->next->content;
				lst->next->content = lst->content;
				lst->content = swp;
			}
			lst = lst->next;
		}
		lst = head;
	}
}
