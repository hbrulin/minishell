/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:11:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 14:13:22 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_rmfd(char **args, int count)
{
    int i;
    int len;
    char **sub = NULL;

    i = 0;
	len = ft_tablen(args) - (count * 2);
    if((sub = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
    sub[len] = 0;
    count = 0;
    while (args[i])
    {
        if (args[i][0] == '<' || args[i][0] == '>' )
            i++;
        else if (args[i][0] != '<' && args[i][0] != '>' )
        {
            if((sub[count] = ft_strdup(args[i])))
				return (NULL);
            count++;
        }
        i++;

    }
    //ft_tab_print(sub);
    return(sub);
}
