/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:32:25 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/05 19:23:36 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Needs escape_sequences header
**	Receive splitted arguments.
**	args[0] = cmd name
**	DR replace by corresponding env variable
**	BS replace by corresponding char
*/

int	expand_and_escape(char **arg)
{
	t_boolean sq;
	t_boolean dq;
	int i;
	int j;

	j = 0;
	sq = FALSE;
	dq = FALSE;
	while (args[++j])
	{
		while (arg[j][i])
		{
			i = 0;
			sq = arg[j][i] == '\'' ? !sq : sq;
			dq = arg[j][i] == '"' ? !dq : dq;
			if (arg[j][i] == '\\')
				escape_char(&arg[j][0], &arg[j][i], sq, dq);
//			else if (*arg[i] == '$')
//				expand_var(sq, dq);
			i++;
		}
	}
	return (0);
}
