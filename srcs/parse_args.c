/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/14 21:03:17 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_operand(char *s)
{
	if ((!ft_strcmp(s, "|")) || (!ft_strcmp(s, "<")) || (!ft_strcmp(s, ">")) || (!ft_strcmp(s, ">>")))
		return (1);
	return(0);
}

int	check_error_syntax(char **args)
{
	int i = 0;

	while (args[i])
	{
		if ((args[i][0] == '|' || args[i][0] == '<') && ft_strlen(args[i]) != 1)
			return(1);
		else if (args[i][0] == '>' && (ft_isalnum(args[i][1]) || ft_isalnum(args[i][2])))
			return(1);
		if (args[i + 1])
		{
			if (check_operand(args[i]) && check_operand(args[i + 1]))
				return(1);
		}
		i++;
	}
	return (0);
}

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

	i = 0;
	j = 0;
	open = 0;

	while (s[i])
	{
		if ((ft_strchr(s + i, ' ') == NULL) && (ft_strchr(s + i, '|') == NULL) && (ft_strchr(s + i, '>') == NULL) && (ft_strchr(s + i, '<') == NULL))
		{
			if(!(tmp = ft_strdup(s + j)))
				return (NULL);
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(tmp, " ")))
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
			while(ft_is_space(s[i]))
				i++;
			i--;
			j = i;
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(tmp);
		}
		else if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && open == 0)
		{
			if (s[i - 1] != ' ')
			{
				if(!(tmp = ft_substr(s, j, i - j)))
					return (NULL);
				j = i;
				if (!(temp = malloc(sizeof(t_list))))
					return (NULL);
				if (!(temp->content = ft_strtrim(tmp, " ")))
					return (NULL);
				temp->next = 0;
				ft_lstadd_back(&list, temp);
				free(tmp);
			}
		
			if(s[i] == '>' && s[i + 1] == '>')
			{
				if(!(tmp = ft_substr(s, i, 2)))
					return (NULL);
				i++;
			}
			else
			{
				if(!(tmp = ft_substr(s, i, 1)))
					return (NULL);
			}
			i++;
			while(ft_is_space(s[i]))
				i++;
			j = i;
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(tmp);
		}
		i++;
	}
	//ft_lstprint(list);
	ret = ft_lst_to_tab(list);
	ft_lstclear(&list, free);
	if (check_error_syntax(ret))
		return (NULL);
	return (ret);
}
