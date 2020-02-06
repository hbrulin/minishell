/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:32:25 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/06 16:14:24 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Needs escape_sequences header
**	Receive splitted arguments.
**	args[0] = cmd name
**	DR replace by corresponding env variable
**	BS replace by corresponding char
**	Check for syntax error
*/

// hello"hello\"""hello"
// 012345678911111111112
//	     01234567890

int seq[7] = {'\\', '$', '\"', '\'', '|', '<', '>'};

int	clean_arg(char *s)
{
	t_boolean sq;
	t_boolean dq;
	int i;
	int j;

	i = 0;
	sq = FALSE;
	dq = FALSE;
	while (s[i])
	{
		if (!sq && !dq && s[i] == 92) // si no mod et escape char escape all
		{
			j = 0;
			while (j < 7 && seq[j] != s[i + 1])
				j++;
			if (j != 7)
				ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
			i++;
		}
		else if (!sq && dq && s[i] == 92) // si dq et escape char escape all
		{
			j = 0;
			while (j < 3 && seq[j] != s[i + 1])
				j++;
			if (j != 3)
				ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
			i = j == 0 ? i + 2 : i + 1;
		}
		else if (!sq && !dq && s[i] == 39) // si dq FALSE, sq FALSE, on active et on clear, l'escape n'existe pas en sq mode 
		{
			sq = TRUE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else if (sq && !dq && s[i] == 39) // si sq TRUE, dq FALSE, on desactive et on clear, l'escape n'existe pas en sq mode
		{
			sq = FALSE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else if (!sq && !dq && s[i] == 34) // si sqdq FALSE et single quotes et index = 0 ou index -1 diff de escapechar, on active et on clear 
		{
			dq = TRUE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else if (dq && !sq && s[i] == 34) // si sq TRUE et dq FALSE et pas d'escape derriere on desactive et on clear
		{
			dq = FALSE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else
			i++;
	}
	if (sq || dq) // si sq ou dq TRUE la matching quote n'as pas ete trouvee donc syntx error
		return (1);
	return (0);
}

int	foreach_escape(char **args)
{
	int i;

	i = 0;
	while (args[++i])
		clean_arg(args[i]);
	return (0);
}
