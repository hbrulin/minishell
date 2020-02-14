/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_tab_cmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:38:55 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 14:43:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iter_tab_cmp(char **tab, char *arg)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (!(ft_strcmp(tab[i], arg)))
			return (0);
		i++;
	}
	return (1);
}
