/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/18 14:07:53 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(char **args)
{
	int i;

	i = 0;
	if (ft_tablen(args) > 2)
		return (ft_error(MANY_ARGS, NULL, NULL, args[0]));
	if (ft_tablen(args) == 1)
		exit(0);
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i])))
		{
			ft_error(EXIT_NUM, NULL, NULL, args[1]);
			exit(0);
		}
		i++;
	}
	i = ft_atoi(args[1]);
	exit(i);
}
