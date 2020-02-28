/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:59:16 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 18:00:15 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_node2(t_list **list, char *s, t_parse_tools *t, int flag)
{
	if (flag == 3)
	{
		if (!(t->tmp = ft_substr(s, t->j, t->i - t->j + 1)))
			return (1);
		if (add_node(t, list))
			return (1);
		free(t->tmp);
		return (0);
	}
	return (1);
}

int		set_node(t_list **list, char *s, t_parse_tools *t, int flag)
{
	if (flag == 1)
	{
		if (!(t->tmp = ft_strdup(s + t->j)))
			return (1);
		if (add_node(t, list))
			return (1);
		free(t->tmp);
		return (0);
	}
	if (flag == 2)
	{
		if (!(t->tmp = ft_substr(s, t->j, t->i - t->j)))
			return (1);
		if (add_node(t, list))
			return (1);
		free(t->tmp);
		return (0);
	}
	return (1);
}
