/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/14 21:04:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_cmds(char *s)
{
	int i;
	int j;
	int open;
	char quote;
	char *cmd = NULL;
	if (!s)
		return(0);
	if (ft_strchr(s, ';') == NULL) 
	{
		if(!(cmd = ft_strdup(s)))
			return(ft_strerror(NULL, NULL, NULL, NULL));
		if(parsexec(cmd))
			return(1); 
		return(0);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ';' && s[i + 1] == ';')
			return(ft_error(SYNTAX_ERR, NULL, NULL, NULL));
		i++;
	}
	i = 0;
	j = 0;
	open = 0;
	while (s[i])
	{
		if (ft_strchr(s + i, ';') == NULL)
		{
			if(!(cmd = ft_strdup(s + j)))
				return(ft_strerror(NULL, NULL, NULL, NULL));
			if(parsexec(cmd))
				return(1);
			break;
		}
		if ((s[i] == '\'' || s[i] == '\"') && open == 0)
		{
			open = !open;
			quote = s[i];
		}
		else if (open == 1 && s[i] == quote)
			open = !open;
		if (s[i] == ';' && open == 0)
		{
			if(!(cmd = ft_substr(s, j, i - j)))
				return(ft_strerror(NULL, NULL, NULL, NULL));
			i++;
			while(ft_is_space(s[i]))
				i++;
			j = i;
			if(parsexec(cmd))
				return(1);
		}
		i++;
	}
	return(0);
}
