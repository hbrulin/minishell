/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:08:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/14 12:54:35 by pmouhali         ###   ########.fr       */
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

int		ft_strerror(int ret, char *befree, char **tabfree, void *param)
{
	if (!param)
		ft_printf_fd(2, "minishell: %s\n", strerror(errno));
	else
		ft_printf_fd(2, "minishell: %s: %s\n", param, strerror(errno));
	if (befree)
		free(befree);
	if (tabfree)
		ft_tabdel((void *)befree);
	return(ret);
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

int		ft_error_tab(char *msg, int ret, char **befree, void *param)
{
	if (msg && !param)
		ft_printf_fd(2, msg);
	else if (msg && param)
		ft_printf_fd(2, msg, param);
	if (befree)
		ft_tabdel((void *)befree);
	return(ret);
}
