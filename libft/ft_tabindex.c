/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:23:37 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 18:23:39 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabindex(const char **tab, const char *s)
{
	int i;

	i = -1;
	while (tab && tab[++i])
		if (s && !ft_strcmp(tab[i], s))
			return (i);
	return (-1);
}
