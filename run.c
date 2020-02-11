/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/11 17:31:24 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsexec(char *cmd)
{
	if (!cmd)
		return(1);
	char **args = NULL;

	if(!(args = parse_arg(cmd)))
		return(ft_error("minishell: error fatal: command was not allocated properly\n", 0, cmd, NULL));
	free(cmd);
	//ft_printf_fd(1, "2");
	if (interpreter(args) == 1)
	{
		ft_tabdel((void *)args); 
		return(ft_error("minishell: error syntax\n", 1, NULL, NULL));
	}
	//ft_printf_fd(1, "3");
	if (!(run_dmc(args)))
	{
		ft_tabdel((void *)args); 
		return(0); 
	}
	//ft_printf_fd(1, "4");
	ft_tabdel((void *)args); 
	return(1);
}


int	run_dmc(char **args)
{
	if (!args || !*args || !**args)
		return (1);
	if ((ft_strcmp(args[0], "exit") == 0))
		return(ft_exit(args));
	else if ((ft_strcmp(args[0], "export") == 0))
		return(ft_export(args));
	else if ((ft_strcmp(args[0], "unset") == 0))
		return(ft_unset(args));
	else if ((ft_strcmp(args[0], "env") == 0))
		return(ft_env(args));
	else if ((ft_strcmp(args[0], "pwd") == 0))
		return(ft_pwd(args));
	else if ((ft_strcmp(args[0], "cd") == 0))
		return(ft_cd(args));
	else
		return (ft_execve(args));
	return(1);
}
