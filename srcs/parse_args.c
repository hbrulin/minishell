/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/16 15:51:12 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_operand(char *s)
{
	if ((!ft_strcmp(s, "|")) || (!ft_strcmp(s, "<")) || (!ft_strcmp(s, ">")) || (!ft_strcmp(s, ">>")))
		return (1);
	return(0);
}

int		ft_is_operand(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '|')
		return(1);
	return(0);
}

int	check_error_syntax(char **args)
{
	int i = 0;

	while (args[i])
	{
		if (args[i][0] == '|' && ft_strlen(args[i]) > 1)
			return(1);
		else if ((args[i][0] == '<' || args[i][0] == '>') && (ft_strlen(args[i]) % 2 != 0) && ft_strlen(args[i]) != 1)
			return(1);
		else if ((args[i][0] == '<' || args[i][0] == '>') && ft_strlen(args[i]) > 1 && args[i][1] == '|')
			return(1);
		else if (args[i][0] == '<' && ft_strlen(args[i]) > 1 && args[i][1] == '<')
			return(1);
		if (args[i + 1])
		{
			if (check_operand(args[i]) && check_operand(args[i + 1]))
				return(1);
		}
		else if (check_operand(args[i]) && !args[i + 1])
			return (1);
		i++;
	}
	return (0);
}

char **parse_arg(char *s)
{
	char **ret = NULL;
	t_parse_tools t;
	t_list *list = NULL;
	t_list *temp = NULL;

	ft_bzero(&t, sizeof(t_parse_tools));

	while (s[t.i])
	{
		if ((ft_strchr(s + t.i, ' ') == NULL) && (ft_strchr(s + t.i, '|') == NULL)
			&& (ft_strchr(s + t.i, '>') == NULL) && (ft_strchr(s + t.i, '<') == NULL))
		{
			if(!(t.tmp = ft_strdup(s + t.j)))
				return (NULL);
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(t.tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(t.tmp);
			break;
		}
		if ((s[t.i] == '\'' || s[t.i] == '\"') && t.open == 0)
		{
			t.open = !t.open;
			t.quote = s[t.i];
		}
		else if (t.open == 1 && s[t.i] == t.quote && s[t.i - 1] != '\\')
			t.open = !t.open;
		if (s[t.i] == ' ' && t.open == 0)
		{
			if(!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
				return (NULL);
			while(ft_is_space(s[t.i]))
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
		else if ((s[t.i] == '|' || s[t.i] == '>' || s[t.i] == '<') && t.open == 0)
		{
			if (s[t.i - 1] != ' ')
			{
				if(!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
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
			if(!(t.tmp = ft_substr(s, t.j, t.i - t.j)))
					return (NULL);
			while(ft_is_space(s[t.i]))
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
