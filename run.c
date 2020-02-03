/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/03 17:33:24 by hbrulin          ###   ########.fr       */
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
		execve(args[0], NULL, env); //revoir l'arg[0] -> tout dependra de comment est fait le parser?
		exit(0);
	}
	wait(&status); //le pere attend le fils pour repartir
	//il faudra prevoir si l'executable n'est pas bon ou permission denied -> check access control
	return (1); //return 1 pour que le shell continue de tourner
} 

int	run_dmc(char **args)
{
	
	if (!args || !*args || !**args)
		return (1);
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
	if (ft_strncmp(*args, "exit", ft_strlen("exit")) == 0)
		return (0); //set status a 0 et donc quit shell
	else
		return (exe(args)); //si executable passe en param
	return(1);
}
