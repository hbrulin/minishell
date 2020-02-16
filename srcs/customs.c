/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:23:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/16 15:59:11 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lstiter_custom(t_list *lst, char *arg, int (*f)(void *, void *, int))
{
	t_list	*next;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	if (i > 0)
		tmp = ft_substr(arg, 0, i);
	else
		return(1);
	while (lst)
	{
		next = lst->next;
		if (!(f(lst->content, tmp, (int)ft_strlen(tmp))))
		{
			free(tmp);
			return(0);
		}
		lst = next;
	}
	if (tmp)
		free(tmp);
	return (1);
}

t_list	*ft_tab_to_list_custom(t_list **lst, char **tab)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while(tab[i])
	{
		if(!(tab[i][0] == '_' && (tab[i][1] == '=')))
		{
			if (!(temp = malloc(sizeof(t_list))))
				return (NULL);
			if (!(temp->content = ft_strdup(tab[i])))
				return (NULL);
			temp->next = 0;
			ft_lstadd_back(lst, temp);
		}
		i++;
	}
	return (*lst);
}


void	ft_lstprint_export(t_list *lst)
{
	t_list	*next;
	int		k;
	char	*key;
	char	*value;

	k = 0;
	if (!lst)
		return ;
	while (lst)
	{
		k = 0;
		next = lst->next;
		while (lst->content[k] != '=' && lst->content[k])
			k++;
		key = ft_substr(lst->content, 0, k + 1);
		value = get_var(export, key);
		ft_putstr("declare -x ");
		ft_putstr(key);
		if (ft_strchr(lst->content, '='))
			ft_putstr("\"");
		ft_putstr(value);
		ft_putstr("\"\n");
		lst = next;
		free(key);
		free(value);
	}
}
