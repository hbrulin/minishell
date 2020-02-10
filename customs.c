/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:23:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 17:45:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstiter_custom(t_list *lst, char *arg, int (*f)(void *, void *, int))
{
	t_list *next;
	char *tmp;
	int i = 0;

	tmp = NULL;
	while (arg[i] != '=' && arg[i])
		i++;
	if (i > 0)
		tmp = ft_substr(arg, 0, i);
	while (lst)
	{
		next = lst->next;
		if (!(f(lst->content, tmp, (int)ft_strlen(tmp))))
			return(0);
		lst = next;
	}
	if (tmp)
		free(tmp);
	return(1);
}

t_list *ft_tab_to_list_custom(t_list *lst, char **tab)
{
	t_list *temp = NULL;
	int i;

	i = 0;
	while(tab[i])
	{
		if(!(tab[i][0] == '_' && (tab[i][1] == '=')))
		{
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strdup(tab[i])))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(&lst, temp);
		}
		i++;
	}
	return(lst);
}


char **tab_cpy_custom(char **tab)
{
	int i = 0;
	int j = 0;
	int count = 0;
	char **ret = NULL;

	while (tab[i])
	{
		if(ft_strcmp(tab[i], "") != 0)
			count++;
		i++;
	}
	if (!(ret = (char**)malloc(sizeof(char *) * count + 1)))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if(ft_strcmp(tab[i], "") != 0)
		{
			ret[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return(ret);
}
