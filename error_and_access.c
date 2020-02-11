/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:08:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/11 13:01:21 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_access(char *path)
 {
    struct stat buf;

	if ((stat(path, &buf)) == -1)
		return(ft_error("minishell: %s: command not found\n", 0, NULL, path));
    if (buf.st_mode & S_IXUSR)
        return (1);
	else
		ft_printf_fd(2, "minishell: %s: permission denied\n", path); 
	return (0);
	
 }

int		ft_error(char *msg, int ret, char *befree, void *param)
{
	if (msg && !param)
		ft_printf_fd(2, msg);
	else if (msg && param)
		ft_printf_fd(2, msg, param);
	if (befree)
		free(befree);
	return(ret);
}

