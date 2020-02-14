/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_chr_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:40:37 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 17:37:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tab_chr_i(char **tab, char *arg)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (!(ft_strcmp(tab[i], arg)))
			return (i);
		i++;
	}
	return (0);
}