/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 18:22:17 by hbrulin           #+#    #+#             */
/*   Updated: 2019/11/13 09:48:55 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int len;
	int i;

	if (!lst)
		return (NULL);
	len = ft_lstsize(lst);
	i = 0;
	while (i < len - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
