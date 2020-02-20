/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:18:10 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 18:23:09 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		set_len(const char *s1, const char *s2, int n)
{
	int i;
	int len;

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
	len = n + i + 1;
	return (len);
}

char	*ft_strnjoin(const char *s1, const char *s2, int n)
{
	char	*s;
	int		i;

	i = set_len(s1, s2, n);
	if (!(s = (char*)malloc(sizeof(char) * i)))
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
