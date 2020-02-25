/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:08:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/25 16:48:02 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_ret_errno(char *befree, char **tabfree, void *param)
{
	ft_printf_fd(2, "minishell: %s: %s\n", param, strerror(errno));
	if (befree)
		free(befree);
	if (tabfree)
		ft_tabdel((void *)befree);
	if (errno == 13)
		errno = 126;
	return (errno);
}

int		ft_strerror(char *befree, char **tabfree, void *param, void *param2)
{
	if (!param && !param2)
		ft_printf_fd(2, "minishell: %s\n", strerror(errno));
	else if (param && !param2)
		ft_printf_fd(2, "minishell: %s: %s\n", param, strerror(errno));
	else
		ft_printf_fd(2, "minishell: %s: %s: %s\n", param, param2,
			strerror(errno));
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
