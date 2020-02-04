/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/04 18:09:53 by hbrulin          ###   ########.fr       */
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
	while (trim[i])
	{
		while (trim[i] != '\'' && trim[i] != '\"')
			i++;
		if (i != 0)
		{
			tmp = ft_substr(trim, j, i - j + 1);
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strtrim(tmp, " ")))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&list, temp);
			free(tmp);
			j = i + 1;
			i++;
			while (ft_is_space(trim[i]))
				i++;
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
		}
		i++;
	}
	ft_lstiter(list, (void (*)(void *))&ft_putstr);
	return (ret);
}

int		parse_exit(char *args)
{
	char *exit;
	int i = 4;
	exit = ft_strtrim(args, " ");
	int len = ft_strlen(exit);
	if (len == i)
		return(0);
	else if (ft_isprint(exit[i]) && !(ft_is_space(exit[i])))
	{
		ft_putstr("minishell: command not found\n"); //ajouter printf ici
		free(exit);
		return(1);
	}
	while (ft_is_space(exit[i]) && exit[i])
		i++;
	if (ft_isprint(exit[i]))
	{
		ft_putstr("minishell: exit: unknown argument\n"); //ajouter printf ici pour l'argment inconnu
		free(exit);
	}
	return(0);
}


char **parser(char *input)
{
	char **argv;

	if (!input || !*input)
		return (NULL);
	argv = ft_split(input, ';');
	return(argv);
}
