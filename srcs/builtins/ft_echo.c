/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:35:57 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/27 14:09:38 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write(char **args, int i)
{
	if (!(ft_strcmp(args[i], ".")) && g_ret == 0)
	{
		if (write(1, args[i], ft_strlen(args[i])) == -1)
			return (1);
		if (args[i + 1] && ft_strcmp(args[i], ""))
			if (write(1, " ", 1) == -1)
				return (1);
	}
	else if (ft_strcmp(args[i], "."))
	{
		if (write(1, args[i], ft_strlen(args[i])) == -1)
			return (1);
		if (args[i + 1] && ft_strcmp(args[i], ""))
			if (write(1, " ", 1) == -1)
				return (1);
	}
	return (0);
}

int	ft_echo(char **args)
{
	int i;
	int opt;

	if (!args || !args[0])
		return (1);
	opt = args[1] && ft_strcmp(args[1], "-n") == 0 ? TRUE : FALSE;
	i = opt;
	while (args[++i])
	{
		if (ft_write(args, i))
			return (1);
	}
	if (!opt)
		if (write(1, "\n", 1) == -1)
			return (1);
	return (0);
}
