/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:21:21 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/15 11:34:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	while (s[index])
	{
		if (s[index] != c)
		{
			count++;
			while (s[index] != c && s[index])
				index++;
		}
		else
			index++;
	}
	return (count);
}

static size_t	ft_size(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] != c && s[size])
		size++;
	return (size);
}

static size_t	ft_nextindex(char const *s, char c, size_t index)
{
	while (s[index] != c && s[index])
		index++;
	while (s[index] == c && s[index])
		index++;
	return (index);
}

char			**ft_null_s(char **tab)
{
	if (!(tab = (char**)ft_calloc(1, sizeof(char*))))
		return (NULL);
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	size_t	str_i;
	size_t	tab_i;
	char	**tab;

	tab = NULL;
	if (!s)
		return (ft_null_s(tab));
	if (!(tab = (char**)ft_calloc(ft_count(s, c) + 1, sizeof(char*))))
		return (NULL);
	tab_i = 0;
	str_i = 0;
	while (s[str_i] == c && s[str_i])
		str_i++;
	while (tab_i < ft_count(s, c))
	{
		if (!(tab[tab_i] = ft_substr(s, str_i, ft_size(s + str_i, c))))
		{
			ft_tabdel((void **)tab);
			return (NULL);
		}
		str_i = ft_nextindex(s, c, str_i);
		tab_i++;
	}
	return (tab);
}
