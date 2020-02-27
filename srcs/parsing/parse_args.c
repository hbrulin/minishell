/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:41:46 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/27 14:14:16 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (set_node(list, s, t, 3))
				return (1);
		}
		t->i++;
	}
	return (0);
}

char	**parse_args(char *s)
{
	char			**ret;
	t_parse_tools	t;
	t_list			*list;

	ft_bzero(&t, sizeof(t_parse_tools));
	list = NULL;
	ret = NULL;
	if (loop_list(&list, s, &t))
		return (NULL);
	ret = ft_lst_to_tab(list);
	ft_lstclear(&list, free);
	char **ret2 = copy_tab_void(ret);
	ft_tabdel((void *)ret);
	//ft_tab_print(ret2);
	//ft_lstprint(list);
	if (check_error_syntax(ret2))
		return (NULL);
	return (ret2);
}
