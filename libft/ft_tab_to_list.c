/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:17:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 17:28:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_tab_to_list(t_list *lst, char **tab)
{
	t_list *temp = NULL;
	int i;

	i = 0;
	while(tab[i])
	{
		if (!(temp = malloc(sizeof(t_list))))
			return (NULL);
		if (!(temp->content = ft_strdup(tab[i])))
			return (NULL);
		temp->next = 0;
		ft_lstadd_back(&lst, temp);
		i++;
	}
	return(lst);
}
