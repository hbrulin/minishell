/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 16:06:03 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parse_arg(char *s)
{
	char **ret = NULL;
	t_list *list = NULL;
	t_list *temp = NULL;
	int i;
	int j;
	int open;
	char quote;
	char *tmp;
	
	if (ft_strchr(s, '\'') == NULL && ft_strchr(s, '\"') == NULL)
	{
		ret = ft_split(s, ' '); 
		return(ret);
	}

	i = 0;
	j = 0;
	open = 0;

	while (s[i])
	{
		if (ft_strchr(s + i, ' ') == NULL) //ou alors is_space
		{
			if(!(tmp = ft_strdup(s + j)))
				return (NULL);
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strdup(tmp)))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(tmp);
			break;
		}
		if ((s[i] == '\'' || s[i] == '\"') && open == 0)
		{
			open = !open;
			quote = s[i];
		}
		else if (open == 1 && s[i] == quote && s[i - 1] != '\\')
			open = !open;
		if (s[i] == ' ' && open == 0)
		{
			if(!(tmp = ft_substr(s, j, i - j)))
				return (NULL);
			i++;
			while(ft_is_space(s[i]))
				i++;
			j = i;
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strdup(tmp)))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(tmp);
		}
		i++;
	}
	ret = ft_lst_to_tab(list);
	ft_lstclear(&list, free);
	return (ret);
}