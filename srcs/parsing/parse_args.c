/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:41:46 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 18:00:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		delim_is_space(t_list **list, char *s, t_parse_tools *t)
{
	if (set_node(list, s, t, 2))
		return (1);
	while (ft_is_space(s[t->i]))
		t->i++;
	t->i--;
	t->j = t->i;
	return (0);
}

int		delim_is_operand(t_list **list, char *s, t_parse_tools *t)
{
	if (!ft_is_space(s[t->i - 1]))
	{
		if (set_node(list, s, t, 2))
			return (1);
		t->j = t->i;
		t->i++;
	}
	while (ft_is_operand(s[t->i]))
		t->i++;
	if (set_node(list, s, t, 2))
		return (1);
	while (ft_is_space(s[t->i]))
		t->i++;
	t->j = t->i;
	return (0);
}

int		loop_list_cases(t_list **list, char *s, t_parse_tools *t)
{
	if (ft_is_space(s[t->i]) && t->open == 0)
	{
		if (delim_is_space(list, s, t))
			return (1);
	}
	if (ft_is_operand(s[t->i]) && t->open == 0)
	{
		if (delim_is_operand(list, s, t))
			return (1);
	}
	if (s[t->i + 1] == '\0')
	{
		if (set_node2(list, s, t, 3))
			return (1);
	}
	return (0);
}

int		loop_list(t_list **list, char *s, t_parse_tools *t)
{
	while (s[t->i])
	{
		if (!ft_strchr(s + t->i, ' ') && !ft_strchr(s + t->i, '|') &&
			!ft_strchr(s + t->i, '>') && !ft_strchr(s + t->i, '<'))
		{
			if (set_node(list, s, t, 1))
				return (1);
			break ;
		}
		set_quote(s[t->i], t);
		if (loop_list_cases(list, s, t))
			return (1);
		t->i++;
	}
	return (0);
}

char	**parse_args(char *s)
{
	char			**ret;
	char			**ret2;
	t_parse_tools	t;
	t_list			*list;

	ft_bzero(&t, sizeof(t_parse_tools));
	list = NULL;
	ret = NULL;
	if (loop_list(&list, s, &t))
		return (NULL);
	ret = ft_lst_to_tab(list);
	ft_lstclear(&list, free);
	ret2 = copy_tab_void(ret);
	ft_tabdel((void *)ret);
	if (check_error_syntax(ret2))
		return (NULL);
	return (ret2);
}
