/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:33:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/26 13:54:51 by hbrulin          ###   ########.fr       */
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

int		check_error(char *s)
{
	t_parse_tools	t;

	ft_bzero(&t, sizeof(t_parse_tools));
	while (s[t.i])
	{
		set_quote(s[t.i], &t);
		if (s[t.i] == ';' && t.open == 0  && s[t.i - 1] != '\\')
		{
			t.i++;
			while (ft_is_space(s[t.i]))
				t.i++;
			if (s[t.i] == ';')
			{
				g_ret = ESYNTAX;
				return (ft_error(SYNTAX_ERR, NULL, NULL, NULL));
			}
		}
		t.i++;
	}
	return (0);
}

int		malloc_and_exec(char *cmd, char *s, t_parse_tools *t, int flag)
{
	if (flag == 1)
	{
		if (!(cmd = ft_strdup(s)))
			return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
		if (parsexec(cmd))
			return (1);
		return (0);
	}
	if (flag == 2)
	{
		if (!(cmd = ft_strdup(s + t->j)))
			return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
		parsexec(cmd);
		return (0);
	}
	if (flag == 3)
	{
		if (!(cmd = ft_substr(s, t->j, t->i - t->j)))
			return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
		parsexec(cmd);
		return (0);
	}
	return (1);
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

int		loop(char *s, char *cmd, t_parse_tools *t)
{
	int done = 0;
	int count = 0;

	while (s[t->i])
	{
		if (ft_strchr(s + t->i, ';') == NULL)
		{
			if (malloc_and_exec(cmd, s, t, 2))
				return (1);
			break ;
		}
		set_quote(s[t->i], t);
		if (s[t->i] != '\\')
			done = 0;
		else if (s[t->i] == '\\' && t->open == 0 && done == 0)
		{
			count = ft_count_back(s, t->i);
			done = 1;
		}
		if (s[t->i] == ';' && t->open == 0 && (!count || count % 2 == 0))
		{
			if (malloc_and_exec(cmd, s, t, 3))
				return (1);
			t->i++;
			while (ft_is_space(s[t->i]))
				t->i++;
			t->j = t->i;
		}
		else if (s[t->i] == ';' && t->open == 0)
			count = 0;
		t->i++;
	}
	return (0);
}

int		parse_cmds(char *s)
{
	t_parse_tools	t;
	char			*cmd;

	if (!s)
		return (1);
	cmd = NULL;
	ft_bzero(&t, sizeof(t_parse_tools));
	if (check_error(s))
		return (1);
	if (ft_strchr(s, ';') == NULL)
		return (malloc_and_exec(cmd, s, &t, 1));
	if (loop(s, cmd, &t))
		return (1);
	return (0);
}
