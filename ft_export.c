/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:54:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 19:16:52 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char **args)
{
	int i;
	int j;

	t_list *temp = NULL;
	ft_list_sort(export);
	if (ft_tablen(args) == 1)
	{
		ft_lstiter(export, (void (*)(void *))&ft_putstr);
		return(1);
	}
	i = 1;
	while (args[i])
	{
		if(ft_isdigit(args[i][0]))
			ft_error("export: not an identifier: %s\n", 1, NULL, args[i]); //passer un tour
		j = 0;
		while (args[i][j])
		{
			if (!(ft_isalnum(args[i][j])))
			{
				if (args[i][j] != '=')
					ft_error("export: syntax error: %s\n", 1, NULL, args[i]); //ici il faut passer un tour
			}
			j++;
		}
		if (!(ft_lstiter_custom(export, args[i], (int (*)(void *, void *, int))&ft_strncmp)))
		{
			ft_putstr("je suis trouvé\n");
		}
		else
		{
			ft_putstr("je suis pas là\n");
			if (!(temp = malloc(sizeof(t_list))))
				return (0); //il faut msg error
			if (!(temp->content = ft_strdup(args[i])))
				return (0); //idem
			temp->next = 0;
			ft_lstadd_back(&export, temp);
		}
		i++;
	}
	return (1);
}
