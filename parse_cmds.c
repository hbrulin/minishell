/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 14:54:26 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsexec(char *cmd)
{
	char **args = NULL;

	if(!(args = parse_arg(cmd)))
	{
		ft_printf_fd(2, "minishell: error fatal: command was not allocated properly\n");
		free(cmd);
		return(0);
	}
	free(cmd);

	//interpreteur(args);
		
	if (!(run_dmc(args))) //cas ou cmd == exit
	{
		ft_tabdel((void *)args); 
		return(0); 
	}
	ft_tabdel((void *)args);
	return(1);
}


int parse_cmds(char *s)
{
	int i;
	int j;
	int open;
	char quote;
	char *cmd = NULL;
	if (ft_strchr(s, ';') == NULL) //retirer en fixant erreur free si 0 ;
	{
		if(!(cmd = ft_strdup(s)))
		{
			ft_printf_fd(2, "minishell: error fatal: command was not allocated properly\n");
			return(0);
		}
		if(!(parsexec(cmd)))
			return(0); //pour exit
		return(1);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ';' && s[i + 1] == ';')
		{
			ft_printf_fd(2, "minishell: syntax error near unexpected token `;;'\n");
			return (1);
		}
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
			{
				ft_printf_fd(2, "minishell: error fatal: command was not allocated properly\n");
				return(0);
			}
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
			{
				ft_printf_fd(2, "minishell: error fatal: command was not allocated properly\n");
				return(0);
			}
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
