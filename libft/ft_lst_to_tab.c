/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:17:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 13:38:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_tab(t_list *list)
{
	char	**ret;
	t_list	*tmp;
	int		i;

	if (!(ret = (char**)malloc(sizeof(char *) * ft_lstsize(list) + 1)))
		return (NULL);
	i = 0;
	tmp = list;
	while (tmp)
	{
		if (!(ret[i] = ft_strdup(tmp->content)))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
