/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:03 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 16:14:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(char **args)
{
	int i;
	i = 0;
	if (ft_tablen(args) > 2)
	{
		ft_putstr("minishell: exit: too many arguments\n");
		return(1);
	}
	if (ft_tablen(args) == 1)
		return(0);
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i])))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
			return (0);
		}
		i++;
	}
	g_ret = ft_atoi(args[1]);
	return (0);
}
