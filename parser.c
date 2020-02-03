/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:31:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/03 16:38:35 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*; doit pouvoir separer les commandes
'’' et '"' doivent marcher comme dans bash, à l’exception du multiligne.*/ 

char **parser(char *input)
{
	char **argv;

	if (!input || !*input)
		return (NULL);
	
	argv = ft_split(input, ' '); //; doit pouvoir separer les commandes, faire un parser selon commandes, puis selon espace pour differents param + error checking si pas d'espace entre une cmd et option par ex
	return(argv);
}
