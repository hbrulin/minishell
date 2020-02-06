/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 16:47:30 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **args)
{
	int i;
	if (ft_tablen(args) > 1)
	{
		ft_putstr("minishell: env: too many arguments\n");
		return (1);
	}
	i = 0;
	while(g_env[i])
	{
		ft_putstr(g_env[i]);
		ft_putstr("\n");
		i++;
	}
	return (1);
}
