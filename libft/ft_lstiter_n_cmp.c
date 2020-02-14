/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_n_cmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:25:57 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 14:10:43 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstiter_n_cmp(t_list *lst, char *arg)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		if (!(ft_strncmp(lst->content, arg, (int)ft_strlen(arg))))
			return (0);
		lst = next;
	}
	return (1);
}
