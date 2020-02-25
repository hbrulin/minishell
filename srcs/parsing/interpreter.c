/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:34:22 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/25 10:00:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		escape_char(char **s, int i, int boolean_value)
{
	ft_memmove(&(*s)[i], &(*s)[i + 1], ft_strlen(*s) - i);
	return (boolean_value);
}

int		interpret_arg(char **or)
{
	t_boolean	sq;
	t_boolean	dq;
	int			i;
	char		*s;

	s = *or;
	i = 0;
	sq = FALSE;
	dq = FALSE;
	while (s && i != -1 && s[i])
	{
		if (!sq && !dq && s[i] == 92)
			i += escape_char(&s, i, TRUE);
		else if (!sq && dq && s[i] == 92 && (s[i + 1] == '\\'
				|| (s)[i + 1] == '$' || s[i + 1] == '\"'))
			i += escape_char(&s, i, TRUE);
		else if (!sq && (s)[i] == '$')
			i = expand(&s, i, dq);
		else if (!dq && (s)[i] == 39)
			sq = escape_char(&s, i, !sq);
		else if (!sq && (s)[i] == 34)
			dq = escape_char(&s, i, !dq);
		else
			i++;
	}
	*or = s;
	i = sq == TRUE || dq == TRUE || i == -1 ? 1 : 0;
	return (i);
}

int		interpreter(char **args)
{
	int i;
	int r;

	r = 0;
	i = -1;
	while (args && r != 1 && args[++i])
		r = interpret_arg(&(args[i]));
	return (r);
}
