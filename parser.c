/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/05 17:32:26 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char **parse_arg(char *args)
{
	char **ret = NULL;
	char *trim;
	t_list *list = NULL;
	t_list *temp = NULL;
	int i;
	int j;
	char *tmp;
	
	trim = ft_strtrim(args, " ");

	if (ft_strchr(trim, '\'') == NULL && ft_strchr(trim, '\"') == NULL)
	{
		ret = ft_split(trim, ' '); 
		free(trim);
		return(ret);
	}

	i = 0;
	j = 0;
	int open = 0;
	char c;
	while (trim[i])
	{
		if ((trim[i] != '\'') && (trim[i] != '\"'))
		{
			j = i;
			while (trim[i] != ' ' && (trim[i] != '\'') && (trim[i] != '\"'))
				i++;
			tmp = ft_substr(trim, j, i - j);
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(tmp);
		}
		else
		{
			j = i;
			open = !open;
			if (open)
			{
				c = trim[i];
				i++;
				while (trim[i] != c)
					i++;
			}
			else
			{
				while ((trim[i] != '\'') && (trim[i] != '\"'))
					i++;
			}
			if (open && trim[i] == c)
			{
				tmp = ft_substr(trim, j, i - j + 1);
				if (!(temp = malloc(sizeof(t_list))))
					return (NULL);
				if (!(temp->content = ft_strtrim(tmp, " ")))
					return (NULL);
				temp->next = 0;
				ft_lstadd_back(&list, temp);
				free(tmp);
				i++;
				open = !open;
			}
		}
		if (!(ft_strchr(trim + i, '\'')) && !(ft_strchr(trim + i, '\"')))
		{
			tmp = ft_strtrim(trim + i, " ");
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(tmp);
			break;
		}
		i++;
	}
	ft_lstiter(list, (void (*)(void *))&ft_putstr);
	//mettre dans un *tab
	return (ret);
}
