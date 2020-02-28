/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:28:49 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 17:44:30 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int count;

	count = 0;
	while (s[i] == '\\')
	{
		i++;
		count++;
	}
	return (count);
}

void	set_escape(t_parse_tools *t, char *s)
{
	if (s[t->i] != '\\')
		t->done = 0;
	else if (s[t->i] == '\\' && t->open == 0 && t->done == 0)
	{
		t->count = ft_count_back(s, t->i);
		t->done = 1;
	}
}

int		check_error_cmds(char *s)
{
	t_parse_tools	t;

	ft_bzero(&t, sizeof(t_parse_tools));
	while (s[t.i])
	{
		set_quote(s[t.i], &t);
		set_escape(&t, s);
		if (s[t.i] == ';' && t.open == 0 && (!t.count || t.count % 2 == 0))
		{
			t.i++;
			while (ft_is_space(s[t.i]))
				t.i++;
			if (s[t.i] == ';')
			{
				g_ret = ESYNTAX;
				return (ft_error(SYNTAX_ERR, NULL, NULL, NULL));
			}
			else if (s[t.i] == ';' && t.open == 0)
				t.count = 0;
		}
		t.i++;
	}
	return (0);
}
