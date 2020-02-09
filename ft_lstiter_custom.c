/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_custom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:23:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 18:39:14 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstiter_custom(t_list *lst, char *arg, int (*f)(void *, void *, int))
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		if (!(f(lst->content, arg, (int)ft_strlen(arg))))
			return(0);
		lst = next;
	}
	return(1);
}
