/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:08:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/08 11:27:31 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_access(char *path)
 {
    struct stat buf;

	if ((stat(path, &buf)) == -1)
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", path);
		return(0);
	}
    if (buf.st_mode & S_IXUSR)
        return (1);
	else
		ft_printf_fd(2, "minishell: %s: permission denied\n", path);
	return (0);
	
 }
