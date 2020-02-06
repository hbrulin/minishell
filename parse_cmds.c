/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 13:34:13 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	parsexec(char *cmd)
{
	char **args;
	//char **inter; pas besoin, modif de args

	args = parse_arg(cmd); //renvoie arg separes pour UNE commande
	//inter = interpreteur(args);
	ft_tabdel((void *)args);
	
	/*if (!(run_dmc(inter)))
	{
		ft_tabdel(inter);
		return(0); //pour exit
	}
	ft_tabdel(inter);*/
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



/*
int		exe(char **args)
{
	int status;
	status = 1;

	pid_t	pid;
	pid = fork();
	if (pid == 0) //pour dire que je suis dans le processus fils. Quid si erreur de fork?
	{
		if (ft_tablen(args) == 1)
			execve(args[0], NULL, env);
		else if (ft_tablen(args) > 1)
			execve(args[0], args + 1, env); //controler si parametre passes au programme 
		exit(0);
	}
	wait(&status); //le pere attend le fils pour repartir
	//il faudra prevoir si l'executable n'est pas bon ou permission denied -> check access control
	//OU si command not found
	return (1); //return 1 pour que le shell continue de tourner
} 


*/
