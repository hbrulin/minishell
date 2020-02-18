/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:05:31 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/18 14:05:34 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(char **args)
{
	char *dir;

	dir = NULL;
	(void)args;
	if (ft_tablen(args) > 1)
		return (ft_error(MANY_ARGS, NULL, NULL, args[0]));
	if (!(dir = getcwd(dir, 0)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	ft_printf_fd(1, "%s\n", dir);
	free(dir);
	return (0);
}
