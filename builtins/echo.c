/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 09:44:12 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/05 15:29:01 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char **args)
{
	int i;
	int s;
	int opt;

	s = 1;
	opt = ft_strcmp(args[0], "-n") == 0 ? 0 : -1;
	i = opt;
	while (args[++i])
	{
		if (write(1, args[i], ft_strlen(args[i])) == -1)
			return (-1);
		// last space should'nt be printed
		if (s && write(1, " ", 1) == -1 && (s = args[i + 1] ? 1 : 0))
			return (-1);
	}
	if (opt)
		if (write(1, "\n", 1) == -1)
			return (-1);
	return (0);
}
