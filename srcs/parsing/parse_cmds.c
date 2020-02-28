/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:33:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 17:53:31 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		malloc_and_exec2(char *cmd, char *s, t_parse_tools *t, int flag)
{
	if (flag == 3)
	{
		if (!(cmd = ft_substr(s, t->j, t->i - t->j)))
			return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
		parsexec(cmd);
		return (0);
	}
	if (flag == 4)
	{
		if (!(cmd = ft_substr(s, t->j, t->i - t->j + 1)))
			return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
		parsexec(cmd);
		return (0);
	}
	return (1);
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
	return (1);
}

int		loop_cases(char *s, char *cmd, t_parse_tools *t)
{
	if (s[t->i] == ';' && t->open == 0 && t->count % 2 != 0 && s[t->i + 1]
		== '\0')
	{
		if (malloc_and_exec2(cmd, s, t, 4))
			return (1);
		t->j = t->i;
	}
	else if (s[t->i] == ';' && t->open == 0 && (!t->count || t->count % 2
		== 0))
	{
		if (malloc_and_exec2(cmd, s, t, 3))
			return (1);
		t->i++;
		while (ft_is_space(s[t->i]))
			t->i++;
		t->j = t->i;
	}
	else if (s[t->i] == ';' && t->open == 0)
		t->count = 0;
	return (0);
}

int		loop(char *s, char *cmd, t_parse_tools *t)
{
	while (s[t->i])
	{
		if (ft_strchr(s + t->i, ';') == NULL)
		{
			if (malloc_and_exec(cmd, s, t, 2))
				return (1);
			break ;
		}
		set_quote(s[t->i], t);
		set_escape(t, s);
		if (loop_cases(s, cmd, t))
			return (1);
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
	if (check_error_cmds(s))
		return (1);
	if (ft_strchr(s, ';') == NULL)
		return (malloc_and_exec(cmd, s, &t, 1));
	if (loop(s, cmd, &t))
		return (1);
	return (0);
}
