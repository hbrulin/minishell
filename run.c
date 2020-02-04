/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/04 13:38:20 by hbrulin          ###   ########.fr       */
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
			execve(args[0], args + 1, env);
		exit(0);
	}
	wait(&status); //le pere attend le fils pour repartir
	//il faudra prevoir si l'executable n'est pas bon ou permission denied -> check access control
	return (1); //return 1 pour que le shell continue de tourner
} 

int	run_dmc(char **args)
{
	int i;
	char **exec = NULL;
	if (!args || !*args || !**args)
		return (1);
	i = 0;
	int j = 0;
	while (args[i])
	{
		while (ft_is_space(args[i][j]))
			j++;
		/*if (ft_strcmp(*args, "echo") == 0)
			return (ft_echo(args));
		else if (ft_strcmp(*args, "cd") == 0)
			return (ft_cd(args[1])); //je ne passe que l'option
		else if (ft_strcmp(*args, "pwd") == 0)
			return (ft_pwd(args));
		else if (ft_strcmp(*args, "export") == 0)
			return (ft_export());
		else if (ft_strcmp(*args, "unset") == 0)
			return (ft_unset());
		else if (ft_strcmp(*args, "env") == 0)
			return (ft_env());*/
		if (ft_strncmp(args[i] + j, "exit", ft_strlen("exit")) == 0)
		{
			if(!(parse_exit(args[i])))
				return (0); //set status a 0 et donc quit shell
		}
		else if (ft_strncmp(args[i] + j, "./", ft_strlen("./")) == 0)
		{
			exec = parse_exe(args[i]);
			exe(exec); //si executable passe en param
		}
		else
			ft_putstr("minishell: command not found\n"); //ajouter printf pour reprint argumnt
		i++;
	}
	return(1);
}
