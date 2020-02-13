/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_n_cmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:25:57 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 13:41:14 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstiter_n_cmp(t_list *lst, char *arg)
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
		if (!(ft_strncmp(lst->content, tmp, (int)ft_strlen(tmp))))
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
