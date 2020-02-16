/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:08:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/16 15:52:51 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int ft_access(char *path)
 {
    struct stat buf;

	if ((stat(path, &buf)) == -1)
		return(ft_error(CMD_NOT_FOUND, 0, NULL, path));
    if (buf.st_mode & S_IXUSR)
        return (1);
	else
		ft_printf_fd(2, PERM_DENIED, path); 
	return (0);
 }*/

int		ft_strerror(char *befree, char **tabfree, void *param, void *param2)
{
	if (!param && !param2)
		ft_printf_fd(2, "minishell: %s\n", strerror(errno));
	else if(param && !param2)
		ft_printf_fd(2, "minishell: %s: %s\n", param, strerror(errno));
	else
		ft_printf_fd(2, "minishell: %s: %s: %s\n", param, param2, strerror(errno));
	if (befree)
		free(befree);
	if (tabfree)
		ft_tabdel((void *)befree);
	return (1);
}

int		ft_error(char *msg, char *befree, char **tab_free, void *param)
{
	if (msg && !param)
		ft_printf_fd(2, msg);
	else if (msg && param)
		ft_printf_fd(2, msg, param);
	if (befree)
		free(befree);
	if (tab_free)
		ft_tabdel((void *)tab_free);
	return (1);
}
