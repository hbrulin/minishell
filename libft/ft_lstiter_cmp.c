/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:29:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 14:10:50 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstiter_cmp(t_list *lst, char *arg)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		if (!(ft_strcmp(lst->content, arg)))
			return (0);
		lst = next;
	}
	return (1);
}
