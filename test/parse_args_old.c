/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:41:46 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 18:10:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_args(char *s)
{
	char			**ret;
	t_parse_tools	t;
	t_list			*list;
	t_list			*temp;

	ft_bzero(&t, sizeof(t_parse_tools));
	list = NULL;
	temp = NULL;
	ret = NULL;
	while (s[t.i])
	{
		if ((ft_strchr(s + t.i, ' ') == NULL) && (ft_strchr(s + t.i, '|') == NULL)
			&& (ft_strchr(s + t.i, '>') == NULL) && (ft_strchr(s + t.i, '<') == NULL))
		{
			if (!(t.tmp = ft_strdup(s + t.j)))
				return (NULL);
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(t.tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(t.tmp);
			break ;
		}
		set_quote(s[t.i], &t);
		if (s[t.i] == ' ' && t.open == 0)
		{
			if (!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
				return (NULL);
			while (ft_is_space(s[t.i]))
				t.i++;
			t.i--;
			t.j = t.i;
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(t.tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(t.tmp);
		}
		else if (ft_is_operand(s[t.i]) && t.open == 0)
		{
			if (s[t.i - 1] != ' ')
			{
				if (!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
					return (NULL);
				t.j = t.i;
				if (!(temp = malloc(sizeof(t_list))))
					return (NULL);
				if (!(temp->content = ft_strtrim(t.tmp, " ")))
					return (NULL);
				temp->next = 0;
				ft_lstadd_back(&list, temp);
				free(t.tmp);
				t.i++;
			}
			while (ft_is_operand(s[t.i]))
				t.i++;
			if (!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
				return (NULL);
			while (ft_is_space(s[t.i]))
				t.i++;
			t.j = t.i;
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(t.tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
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
