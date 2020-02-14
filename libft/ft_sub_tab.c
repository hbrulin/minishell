/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:33:13 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 18:09:48 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_sub_tab(char **tab, int start, int len)
{
	char	**cpy;
	char	**cpy_ret;
	int		i;

	i = 0;
	cpy = NULL;
	cpy_ret = NULL;
	if (!(cpy = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	cpy_ret = cpy;
	cpy[len] = NULL;
	while (len)
	{
		cpy[i] = ft_strdup(tab[start]);
		len--;
		i++;
		start++;
	}
	return (cpy_ret);
}
