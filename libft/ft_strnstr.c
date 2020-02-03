/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:41:29 by hbrulin           #+#    #+#             */
/*   Updated: 2019/11/11 12:12:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*large;
	char	*small;
	size_t	i;

	large = (char*)haystack;
	small = (char*)needle;
	if (*small == '\0')
		return (large);
	i = ft_strlen(small);
	while (*large && len-- >= i)
	{
		if (ft_memcmp(large, small, i) == 0)
			return (large);
		large++;
	}
	return (NULL);
}
