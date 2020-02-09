/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:28:40 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 17:58:12 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *next;

	if (!lst || !f)
		return ;
	while (lst)
	{
		next = lst->next;
		f(lst->content);
		ft_putstr("\n");
		lst = next;
	}
}
