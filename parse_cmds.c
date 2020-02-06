/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 15:47:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsexec(char *cmd)
{
	char **args;

	args = parse_arg(cmd); 
	//interpreteur(args);
		
	if (!(run_dmc(args)))
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
	char *cmd;
	//1 cmd
	if (ft_strchr(s, ';') == NULL) //retirer en fixant erreur free si 0 ;
	{
		cmd = ft_strdup(s);
		//ft_putstr(cmd);
		if(!(parsexec(cmd)))
		{
			//free(cmd);
			return(0); //pour exit
		}
		//free(cmd); //voir pour leak
		return(1);
	}

	i = 0;
	j = 0;
	open = 0;
	//several cmds
	while (s[i])
	{
		if (ft_strchr(s + i, ';') == NULL)
		{
			cmd = ft_strdup(s + j);
			//ft_putstr(cmd);
			//ft_putstr("\n");
			if(!(parsexec(cmd)))
			{
				//free(cmd);
				return(0); //pour exit
			}
			//free(cmd);
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
			cmd = ft_substr(s, j, i - j);
			//ft_putstr(cmd);
			//ft_putstr("\n");
			i++;
			while(ft_is_space(s[i]))
				i++;
			j = i;
			if(!(parsexec(cmd)))
			{
				//free(cmd);
				return(0); //pour exit
			}
			//free(cmd);
		}
		i++;
	}
	return(1);
}
