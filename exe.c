/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 16:14:40 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_dmc(char **args)
{
	if (!args || !*args || !**args)
		return (1);
	if ((ft_strcmp(args[0], "exit") == 0))
		return(ft_exit(args));
	else
		ft_printf("minishell: %s: command not found\n", args[0]);
	return(1);
}
