/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 21:04:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/11 21:39:27 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_rm(char **args)
{
	t_rm_var_tools	t;

	ft_bzero(&t, sizeof(t_rm_var_tools));
	while (args[t.i])
	{
		t.j = 0;
		if (args[t.i][t.j] == '$')
		{
			t.k = t.j + 1;
			while (args[t.i][t.k] != '\"' && args[t.i][t.k])
				t.k++;
			if (!(t.key = ft_substr(args[t.i], t.j + 1, t.k - 1)))
				return (-1);
			if ((t.tmp = get_var(g_env, t.key)) != NULL)
				t.count++;
			free(t.tmp);
			free(t.key);
		}
		else
			t.count++;
		t.i++;
	}
	return (t.count);
}

int		copy_if(t_rm_var_tools *t, char **args)
{
	t->k = t->j + 1;
	while (args[t->i][t->k] != '\"' && args[t->i][t->k])
		t->k++;
	if (!(t->key = ft_substr(args[t->i], t->j + 1, t->k - 1)))
		return (-1);
	if ((t->tmp = get_var(g_env, t->key)) != NULL)
	{
		if (!(t->cpy[t->l] = ft_strdup(args[t->i])))
			return (-1);
		t->l++;
	}
	free(t->tmp);
	free(t->key);
	return (0);
}

char	**rm_wrong_var(char **args)
{
	t_rm_var_tools	t;

	ft_bzero(&t, sizeof(t_rm_var_tools));
	if ((t.count = count_rm(args)) == -1)
		return (NULL);
	if (!(t.cpy = (char **)malloc(sizeof(char *) * (t.count + 1))))
		return (NULL);
	t.cpy[t.count] = NULL;
	while (args[t.i])
	{
		t.j = 0;
		if (args[t.i][t.j] == '$')
		{
			if ((copy_if(&t, args)) == -1)
				return (NULL);
		}
		else
		{
			if (!(t.cpy[t.l] = ft_strdup(args[t.i])))
				return (NULL);
			t.l++;
		}
		t.i++;
	}
	return (t.cpy);
}