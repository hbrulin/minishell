/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:39:48 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 14:40:06 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_chr(char **tab, char *arg)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (!(ft_strcmp(tab[i], arg)))
			return ((char **)&tab[i]);
		i++;
	}
	return (NULL);
}
