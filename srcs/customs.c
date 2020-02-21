/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:23:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/21 16:08:38 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lstiter_custom(t_list *lst, char *arg)
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
		return (1);
	while (lst)
	{
		next = lst->next;
		if (!(ft_strncmp(lst->content, tmp, (int)ft_strlen(tmp))))
		{
			free(tmp);
			return (0);
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
	while (tab[i])
	{
		if (!(tab[i][0] == '_' && (tab[i][1] == '=')))
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

void	print(char *key, char *value, int equal)
{
	ft_printf_fd(1, "declare -x %s", key);
	if (equal == 1)
		ft_putstr("\"");
	ft_putstr(value);
	if (equal == 1)
		ft_putstr("\"");
	ft_putstr("\n");
}

int		ft_lstprint_export(t_list *lst)
{
	t_list	*next;
	int		k;
	char	*key;
	char	*value;

	ft_list_sort(g_export);
	while (lst)
	{
		k = 0;
		next = lst->next;
		while (lst->content[k] != '=' && lst->content[k])
			k++;
		if (!(key = ft_substr(lst->content, 0, k + 1)))
			return (ft_strerror(NULL, NULL, NULL, NULL));
		if (!(value = get_var(g_export, key)))
			return (ft_strerror(key, NULL, NULL, NULL));
		if (ft_strchr(lst->content, '='))
			print(key, value, 1);
		else
			print(key, value, 0);
		lst = next;
		free(key);
		free(value);
	}
	return (0);
}
