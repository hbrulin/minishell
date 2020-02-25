/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:34:22 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/25 12:41:19 by hbrulin          ###   ########.fr       */
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
	t_interp_tools t;

	t.s = *or;
	t.i = 0;
	t.sq = FALSE;
	t.dq = FALSE;
	while (t.s && t.i != -1 && t.s[t.i])
	{
		if (!t.sq && !t.dq && t.s[t.i] == 92)
			t.i += escape_char(&t.s, t.i, TRUE);
		else if (!t.sq && t.dq && t.s[t.i] == 92 && (t.s[t.i + 1] == '\\'
				|| (t.s)[t.i + 1] == '$' || t.s[t.i + 1] == '\"'))
			t.i += escape_char(&t.s, t.i, TRUE);
		else if (!t.sq && (t.s)[t.i] == '$')
			t.i = expand(&t.s, t.i, t.dq);
		else if (!t.dq && (t.s)[t.i] == 39)
			t.sq = escape_char(&t.s, t.i, !t.sq);
		else if (!t.sq && (t.s)[t.i] == 34)
			t.dq = escape_char(&t.s, t.i, !t.dq);
		else
			t.i++;
	}
	*or = t.s;
	t.i = t.sq == TRUE || t.dq == TRUE || t.i == -1 ? 1 : 0;
	return (t.i);
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
