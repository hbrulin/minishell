/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:59:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/26 19:00:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_envvar(char **arg, int dr, int *i)
{
	char *tmp;
	char *key;

	tmp = ft_substr(*arg, dr + 1, (*i - 1) - dr);
	key = ft_strjoin(tmp, "=");
	free(tmp);
	if (!(tmp = get_var(g_env, key)))
	{
		g_ret = 158;
		tmp = ft_strdup(".");
	}
	free(key);
	key = ft_strnjoin(*arg, tmp, dr);
	free(tmp);
	tmp = ft_strjoin(key, &((*arg)[*i]));
	*i = !key ? -1 : (int)ft_strlen(key);
	free(key);
	key = *arg;
	*arg = tmp;
	free(key);
}

void	expand_resvar(char **arg, int *i)
{
	char *tmp;
	char *value;

	value = ft_itoa(g_ret);
	tmp = ft_strnjoin(*arg, value, *i - 1);
	free(value);
	value = ft_strjoin(tmp, &((*arg)[*i + 1]));
	*i = !tmp ? -1 : (int)ft_strlen(tmp);
	free(tmp);
	tmp = *arg;
	*arg = value;
	free(tmp);
}

int		envvar_authorized_character(char c, int first_char)
{
	if (first_char == TRUE)
		if (c == '_' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
			return (TRUE);
	if (first_char == FALSE)
		if (c == '_' || (c > 64 && c < 91) || (c > 96 && c < 123) ||
			(c > 47 && c < 58))
			return (TRUE);
	return (FALSE);
}

int		expand(char **arg, int i, int dquote)
{
	int		j;

	j = i + 1;
	if (dquote == FALSE && ((*arg)[j] == '\'' || (*arg)[j] == '"'))
	{
		ft_memmove(&((*arg)[i]), &((*arg)[j]), ft_strlen(*arg) - i);
		return (i);
	}
	else if ((*arg)[j] == '?')
		expand_resvar(arg, &j);
	else if (envvar_authorized_character((*arg)[j], TRUE) == TRUE)
	{
		j++;
		while (envvar_authorized_character((*arg)[j], FALSE) == TRUE)
			j++;
		expand_envvar(arg, i, &j);
	}
	i = j;
	return (i);
}
