/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:16:11 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 17:46:46 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**copy_tab(char **tab)
{
	char	**cpy;
	char	**cpy_ret;
	size_t	len;

	if (!(len = ft_tablen(tab)))
		return (NULL);
	if (!(cpy = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	cpy_ret = cpy;
	cpy[len] = NULL;
	while (len--)
	{
		if(!(*cpy++ = ft_strdup(*tab++)))
			return(NULL);
	}
	return (cpy_ret);
}
