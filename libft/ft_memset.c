/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:12:08 by hbrulin           #+#    #+#             */
/*   Updated: 2019/11/11 16:20:31 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int					i;
	unsigned char		*start;

	i = 0;
	start = b;
	while (len)
	{
		start[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
