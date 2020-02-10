/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 18:26:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_dmc(char **args)
{
	if (!args || !*args || !**args)
		return (1);
	if ((ft_strcmp(args[0], "exit") == 0))
		return(ft_exit(args));
	if ((ft_strcmp(args[0], "export") == 0))
		return(ft_export(args));
	if ((ft_strcmp(args[0], "unset") == 0))
		return(ft_unset(args));
	if ((ft_strcmp(args[0], "env") == 0))
		return(ft_env(args));
	if ((ft_strcmp(args[0], "pwd") == 0))
		return(ft_pwd(args));
	if ((ft_strcmp(args[0], "cd") == 0))
		return(ft_cd(args));
	else
		return (ft_execve(args));
	return(1);
}
