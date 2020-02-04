/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/04 15:50:59 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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

int	run_dmc(char **args)
{
	int i;
	int j;
	char **param = NULL;
	if (!args || !*args || !**args)
		return (1);
	i = 0;
	while (args[i])
	{
		j = 0;
		while (ft_is_space(args[i][j]))
			j++;
		if ((ft_strncmp(args[i] + j, "echo", ft_strlen("echo")) == 0)) //regler si jamais echop - faire ft command not found
		{
			param = parse_arg(args[i]);
			//ft_echo(param);
		}
		else if (ft_strncmp(args[i] + j, "exit", ft_strlen("exit")) == 0)
		{
			if(!(parse_exit(args[i])))
				return (0); //set status a 0 et donc quit shell, sauf si command inconnue
		}
		else
		{
			param = parse_arg(args[i]);
			exe(param); //si executable passe en param
		}
		i++;
		ft_tabdel((void *)param);
	}
	return(1);
}
