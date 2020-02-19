/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:33:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 17:07:13 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_error(char *s)
{
	int i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == ';' && s[i + 1] == ';')
		{
			g_ret = ESYNTAX;
			return (ft_error(SYNTAX_ERR, NULL, NULL, NULL));
		}
		i++;
	}
	return (0);
}

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

int		parse_cmds(char *s)
{
	t_parse_tools	t;
	char			*cmd;

	cmd = NULL;
	ft_bzero(&t, sizeof(t_parse_tools));
	if (check_error(s))
		return (1);
	if (ft_strchr(s, ';') == NULL)
		return (malloc_and_exec(cmd, s, &t, 1));
	while (s[t.i])
	{
		if (ft_strchr(s + t.i, ';') == NULL)
		{
			if (malloc_and_exec(cmd, s, &t, 2))
				return (1);
			break ;
		}
		set_quote(s[t.i], &t);
		if (s[t.i] == ';' && t.open == 0)
		{
			if (malloc_and_exec(cmd, s, &t, 3))
				return (1);
			t.i++;
			while (ft_is_space(s[t.i]))
				t.i++;
			t.j = t.i;
		}
		t.i++;
	}
	return (0);
}
