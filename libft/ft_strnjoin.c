/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:34:00 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/14 13:57:48 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(const char *s1, const char *s2, int n)
{
	char	*s;
	int		i;

	if (!s1)
		i = 0;
	else
		i = ft_strlen(s1);
	if (n > i || i == 0)
		n = i;
	if (!s2)
		i = 0;
	else
		i = ft_strlen(s2);
	if (!(s = (char*)malloc(sizeof(char) * (n + i + 1))))
		return (s);
	i = 0;
	while (i < n)
	{
		s[i] = s1[i];
		i++;
	}
	n = 0;
	while (s2 && s2[n])
	{
		s[i] = s2[n];
		n++;
		i++;
	}
	s[i] = 0;
	return (s);
}
