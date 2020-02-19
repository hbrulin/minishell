/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:39:23 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 18:39:52 by hbrulin          ###   ########.fr       */
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
