/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:30:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 14:34:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **args)
{
	int i;
	i = 0;
	if (ft_tablen(args) == 1)
		return(ft_error("unset: not enough arguments\n", 1, NULL, NULL));
	while (args[i])
	{
		del_var(export, args[i]);
		del_var(env, args[i]);
		i++;
	}
	return (1);
}
