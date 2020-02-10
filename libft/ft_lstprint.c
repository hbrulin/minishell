/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:16:48 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 13:17:58 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	t_list *next;

	if (!lst)
		return ;
	while (lst)
	{
		next = lst->next;
		ft_putstr(lst->content);
		ft_putstr("\n");
		lst = next;
	}
}
