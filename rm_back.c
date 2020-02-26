/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_back.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:17:02 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/26 13:20:26 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

typedef struct		s_parse_tools
{
	int		i;
	int		j;
	int		open;
	char	quote;
	char	*tmp;
}					t_parse_tools;

void	set_quote(char c, t_parse_tools *t)
{
	if ((c == '\'' || c == '\"') && t->open == 0)
	{
		t->open = !t->open;
		t->quote = c;
	}
	else if (t->open == 1 && c == t->quote)
		t->open = !t->open;
}

int		ft_count_back(char *s, int i)
{
	int count = 0;
	while (s[i] == '\\')
	{
		i++;
		count++;
	}
	return(count);
}

int		rm_back(char *s, int i)
{
	int count = 0;
	int done = 0;
	t_parse_tools	t;
	ft_bzero(&t, sizeof(t_parse_tools));

	while (s[t.i])
	{
		if (s[t.i] != '\\')
			done = 0;
		set_quote(s[t.i], &t);
		if (s[t.i] == '\\' && t.open == 0 && done == 0)
		{
			count = ft_count_back(s, t.i);
			done = 1;
		}
		if (count && count % 2 == 0)
			t.i++;
		t.i++;		
	}
	return (t.i++);
}

int main(void)
{
	char *s = ft_strdup("echo \\\\;\\\\;");
	printf("%s\n", s);
	rm_back(s);
	printf("%s\n", s);
}
