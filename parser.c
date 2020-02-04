/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/04 13:35:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
//error checking si pas d'espace entre une cmd et option par ex
//char **parse_echo
//->strtrim '’' et '"' doivent marcher comme dans bash, à l’exception du multiligne.*/ 

int		ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char **parse_exe(char *args)
{
	char **exec = ft_split(args, ' ');
	return(exec);
}

int		parse_exit(char *args)
{
	char *exit;
	int i = 4;
	exit = ft_strtrim(args, " ");
	int len = ft_strlen(exit);
	if (len == i)
		return(0);
	else if (ft_isprint(exit[i]) && !(ft_is_space(exit[i])))
	{
		ft_putstr("minishell: command not found\n"); //ajouter printf ici
		free(exit);
		return(1);
	}
	while (ft_is_space(exit[i]) && exit[i])
		i++;
	if (ft_isprint(exit[i]))
	{
		ft_putstr("minishell: exit: unknown argument\n"); //ajouter printf ici pour l'argment inconnu
		free(exit);
	}
	return(0);
}


char **parser(char *input)
{
	char **argv;

	if (!input || !*input)
		return (NULL);
	argv = ft_split(input, ';');
	return(argv);
}
