/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:02:11 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/22 18:06:32 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_start(char const *s1, char const *set)
{
	int i;
	int j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != set[j])
		{
			j++;
			if (set[j] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

int		get_end(char const *s1, char const *set)
{
	int i;
	int j;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (s1[i] != set[j])
		{
			if (set[j] == '\0')
				return (i + 1);
			j++;
		}
		i--;
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		start;
	int		end;
	int		i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set);
	len = ft_strlen(s1) - start - (ft_strlen(s1) - end);
	if (len <= 0)
		return (ft_strdup(""));
	i = 0;
	s2 = ft_strnew(len + 1);
	while (len)
	{
		s2[i] = s1[start];
		i++;
		start++;
		len--;
	}
	s2[i] = '\0';
	return (s2);
}
