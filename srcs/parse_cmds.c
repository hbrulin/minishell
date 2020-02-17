/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/17 11:31:59 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_cmds(char *s)
{
	t_parse_tools t;
	char *cmd;
	
	cmd = NULL;
	ft_bzero(&t, sizeof(t_parse_tools));
	if (!s)
		return(0);
	if (ft_strchr(s, ';') == NULL) 
	{
		if(!(cmd = ft_strdup(s)))
			return(g_ret = ft_strerror(NULL, NULL, NULL, NULL));
		if(parsexec(cmd))
			return(1); 
		return(0);
	}
	while (s[t.i])
	{
		if (s[t.i] == ';' && s[t.i + 1] == ';')
			return(g_ret = ft_error(SYNTAX_ERR, NULL, NULL, NULL));
		t.i++;
	}
	t.i = 0;
	while (s[t.i])
	{
		if (ft_strchr(s + t.i, ';') == NULL)
		{
			if(!(cmd = ft_strdup(s + t.j)))
				return(g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			parsexec(cmd);
			break;
		}
		if ((s[t.i] == '\'' || s[t.i] == '\"') && t.open == 0)
		{
			t.open = !t.open;
			t.quote = s[t.i];
		}
		else if (t.open == 1 && s[t.i] == t.quote)
			t.open = !t.open;
		if (s[t.i] == ';' && t.open == 0)
		{
			if(!(cmd = ft_substr(s, t.j, t.i - t.j)))
				return(g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			t.i++;
			while(ft_is_space(s[t.i]))
				t.i++;
			t.j = t.i;
			parsexec(cmd);
		}
		t.i++;
	}
	return(0);
}
