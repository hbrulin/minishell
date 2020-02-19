/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:33:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 16:44:42 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_error(char *s)
{
	int i;

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

int		parse_cmds(char *s)
{
	t_parse_tools	t;
	char			*cmd;

	cmd = NULL;
	ft_bzero(&t, sizeof(t_parse_tools));
	if (!s)
		return (0);
	if (ft_strchr(s, ';') == NULL)
	{
		if (!(cmd = ft_strdup(s)))
			return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
		if (parsexec(cmd))
			return (1);
		return (0);
	}
	if (check_error(s))
		return (1);
	while (s[t.i])
	{
		if (ft_strchr(s + t.i, ';') == NULL)
		{
			if (!(cmd = ft_strdup(s + t.j)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			parsexec(cmd);
			break ;
		}
		set_quote(s[t.i], &t);
		if (s[t.i] == ';' && t.open == 0)
		{
			if (!(cmd = ft_substr(s, t.j, t.i - t.j)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			t.i++;
			while (ft_is_space(s[t.i]))
				t.i++;
			t.j = t.i;
			parsexec(cmd);
		}
		t.i++;
	}
	return (0);
}
