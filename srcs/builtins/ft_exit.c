/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:41:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/01 11:04:28 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(char **args)
{
	int				i;
	unsigned int	j;

	i = 0;
	ft_putstr("exit\n");
	if (ft_tablen(args) == 1)
		exit(0);
	if (args[1][i] == '+' || args[1][i] == '-')
		i++;
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i])))
		{
			ft_error(EXIT_NUM, NULL, NULL, args[1]);
			exit(255);
		}
		i++;
	}
	if (ft_tablen(args) > 2)
		return (ft_error(MANY_ARGS, NULL, NULL, args[0]));
	if ((i = ft_atoi(args[1])) < 0)
		j = (unsigned char)i;
	else
		j = i;
	exit(j);
}
