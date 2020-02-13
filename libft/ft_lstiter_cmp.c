/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:29:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 13:37:45 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstiter_cmp(t_list *lst, char *arg)
{
	t_list	*next;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	if (i > 0)
		tmp = ft_substr(arg, 0, i);
	else
		return (1);
	while (lst)
	{
		next = lst->next;
		if (!(ft_strcmp(lst->content, tmp)))
		{
			free(tmp);
			return (0);
		}
		lst = next;
	}
	if (tmp)
		free(tmp);
	return (1);
}
