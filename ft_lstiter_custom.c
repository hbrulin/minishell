/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_custom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:23:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 19:18:25 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstiter_custom(t_list *lst, char *arg, int (*f)(void *, void *, int))
{
	t_list *next;
	char *tmp;
	int i = 0;

	tmp = NULL;
	while (arg[i] != '=' && arg[i])
		i++;
	if (i > 0)
		tmp = ft_substr(arg, 0, i);
	while (lst)
	{
		next = lst->next;
		if (!(f(lst->content, tmp, (int)ft_strlen(tmp))))
			return(0);
		lst = next;
	}
	if (tmp)
		free(tmp);
	return(1);
}
