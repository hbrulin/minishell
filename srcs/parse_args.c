/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:41:46 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 11:43:25 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_node(t_parse_tools *t, t_list **list)
{
	t_list	*temp;

	temp = NULL;
	if (!(temp = malloc(sizeof(t_list))))
		return (1);
	if (!(temp->content = ft_strtrim(t->tmp, " ")))
		return (1);
	temp->next = 0;
	ft_lstadd_back(list, temp);
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
	while (s[t.i])
	{
		if (!ft_strchr(s + t.i, ' ') && !ft_strchr(s + t.i, '|') &&
			!ft_strchr(s + t.i, '>') && !ft_strchr(s + t.i, '<'))
		{
			if (!(t.tmp = ft_strdup(s + t.j)))
				return (NULL);
			if (add_node(&t, &list))
				return (NULL);
			free(t.tmp);
			break ;
		}
		set_quote(s[t.i], &t);
		if (s[t.i] == ' ' && t.open == 0)
		{
			if (!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
				return (NULL);
			if (add_node(&t, &list))
				return (NULL);
			free(t.tmp);
			while (ft_is_space(s[t.i]))
				t.i++;
			t.i--;
			t.j = t.i;
		}
		else if (ft_is_operand(s[t.i]) && t.open == 0)
		{
			if (s[t.i - 1] != ' ')
			{
				if (!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
					return (NULL);
				if (add_node(&t, &list))
					return (NULL);
				free(t.tmp);
				t.j = t.i;
				t.i++;
			}
			while (ft_is_operand(s[t.i]))
				t.i++;
			if (!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
				return (NULL);
			while (ft_is_space(s[t.i]))
				t.i++;
			t.j = t.i;
			if (add_node(&t, &list))
				return (NULL);
			free(t.tmp);
		}
		t.i++;
	}
	ret = ft_lst_to_tab(list);
	ft_lstclear(&list, free);
	if (check_error_syntax(ret))
		return (NULL);
	return (ret);
}
