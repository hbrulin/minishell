/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 19:34:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsexec(char *cmd)
{
	char **args = NULL;
	char **cpy = NULL;

	if(!(args = parse_arg(cmd)))
		return(ft_error("minishell: error fatal: command was not allocated properly\n", 0, cmd, NULL));
	free(cmd);
	if (interpreter(args) == 1)
	{
		ft_tabdel((void *)args); 
		return(ft_error("minishell: error syntax\n", 1, NULL, NULL));
	}
	cpy = tab_cpy_custom(args); //securiser
	ft_tabdel((void *)args); 
	if (!(run_dmc(cpy)))
	{
		ft_tabdel((void *)cpy); 
		return(0); 
	}
	ft_tabdel((void *)cpy);
	return(1);
}


int parse_cmds(char *s)
{
	int i;
	int j;
	int open;
	char quote;
	char *cmd = NULL;
	if (!s)
		return(1);
	if (ft_strchr(s, ';') == NULL) 
	{
		if(!(cmd = ft_strdup(s)))
			return(ft_error("minishell: error fatal: command was not allocated properly\n", 0, NULL, NULL));
		if(!(parsexec(cmd)))
			return(0); 
		return(1);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ';' && s[i + 1] == ';')
			return(ft_error("minishell: syntax error near unexpected token `;;'\n", 1, NULL, NULL));
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
				return(ft_error("minishell: error fatal: command was not allocated properly\n", 0, NULL, NULL));
			if(!(parsexec(cmd)))
				return(0);
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
				return(ft_error("minishell: error fatal: command was not allocated properly\n", 0, NULL, NULL));
			i++;
			while(ft_is_space(s[i]))
				i++;
			j = i;
			if(!(parsexec(cmd)))
				return(0);
		}
		i++;
	}
	return(1);
}
