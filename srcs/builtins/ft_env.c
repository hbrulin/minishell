/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:41:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/21 16:09:59 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **args)
{
	if (ft_tablen(args) > 1)
		return (ft_error(MANY_ARGS, NULL, NULL, args[0]));
	ft_lstprint(g_env);
	return (0);
}
