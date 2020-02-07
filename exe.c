/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 17:24:10 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_dmc(char **args)
{
	if (!args || !*args || !**args)
		return (1);
	if ((ft_strcmp(args[0], "exit") == 0))
		return(ft_exit(args));
	if ((ft_strcmp(args[0], "env") == 0))
		return(ft_env(args));
	if ((ft_strcmp(args[0], "pwd") == 0))
		return(ft_pwd(args));
	else if (ft_execve(args))
		return (1);
	else
		ft_printf("minishell: %s: command not found\n", args[0]);
	return(1);
}
