/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:54:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 17:00:51 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_error(char *arg, int *err)
{
	int i;

	i = 0;
	if (envvar_authorized_character(arg[i], TRUE) == FALSE)
		return (*err = ft_error(INVALID_ID_X, NULL, NULL, arg));
	while (arg[++i] && arg[i] != '=')
	{
		if (envvar_authorized_character(arg[i], FALSE) == FALSE)
			return (*err = ft_error(INVALID_ID_X, NULL, NULL, arg));
	}
	return (0);
}

int		add_var(char *s, t_list **list)
{
	t_list	*temp;

	temp = NULL;
	if (!(temp = malloc(sizeof(t_list))))
		return (1);
	if (!(temp->content = ft_strdup(s)))
		return (1);
	temp->next = 0;
	ft_lstadd_back(list, temp);
	return (0);
}

int		ft_replace(char *s, int k)
{
	if (ft_strchr(s, '='))
	{
		if (set_var_full(export, ft_substr(s, 0, k + 1), s) == -1)
			return (ft_strerror(NULL, NULL, NULL, NULL));
		if (set_var_full(env, ft_substr(s, 0, k + 1), s) == -1)
			return (ft_strerror(NULL, NULL, NULL, NULL));
	}
	return (0);
}

int		add_to_list(char *s)
{
	if (add_var(s, &export))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	if (ft_strchr(s, '='))
	{
		if (add_var(s, &env))
			return (ft_strerror(NULL, NULL, NULL, NULL));
	}
	return (0);
}

int		ft_export(char **args)
{
	int		i;
	int		err;
	int		k;

	if (ft_tablen(args) == 1)
		return (ft_lstprint_export(export));
	i = 1;
	err = 0;
	while (args[i] && !(export_error(args[i], &err)))
	{
		k = 0;
		while (args[i][k] != '=' && args[i][k])
			k++;
		if (!(ft_lstiter_custom(export, args[i])))
		{
			if (ft_replace(args[i], k))
				return (1);
		}
		else if (add_to_list(args[i]))
			return (1);
		i++;
	}
	return (err);
}
