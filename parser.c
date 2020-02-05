/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/05 19:35:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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
		printf("%s\n", ret[0]);
		free(s);
		return(ret);
	}

	i = 0;
	j = 0;
	open = 0;

	while (s[i])
	{
		if (ft_strchr(s + i, ' ') == NULL) //ou alors is_space
		{
			tmp = ft_strdup(s + j);
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
		else if (open == 1 && s[i] == quote)
			open = !open;
		if (s[i] == ' ' && open == 0)
		{
			tmp = ft_substr(s, j, i - j);
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
	ft_lstiter(list, (void (*)(void *))&ft_putstr);
	//mettre dans un *tab
	return (ret);
}









/*
	i = 0;
	j = 0;
	int open = 0;
	char c;
	while (s[i])
	{
		if ((s[i] != '\'') && (s[i] != '\"'))
		{
			j = i;
			while (s[i] != ' ' && (s[i] != '\'') && (s[i] != '\"'))
				i++;
			tmp = ft_substr(s, j, i - j);
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
				c = s[i];
				i++;
				while (s[i] != c)
					i++;
			}
			else
			{
				while ((s[i] != '\'') && (s[i] != '\"'))
					i++;
			}
			if (open && s[i] == c && ft_is_space(s[i+ 1]))
			{
				tmp = ft_substr(s, j, i - j + 1);
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
		if (!(ft_strchr(s + i, '\'')) && !(ft_strchr(s + i, '\"')))
		{
			tmp = ft_strtrim(s + i, " ");
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
*/
