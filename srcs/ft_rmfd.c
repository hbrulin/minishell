/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:11:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 14:29:47 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_rmfd(char **args)
{
    int i;
    int len;
    int count;
    char **sub;

    i = 0;
    count = 0;
    while (args[i])
    {
         if (args[i][0] == '<' || args[i][0] == '>' )
            count++;
        i++;
    }
    len = ft_tablen(args) - (count * 2);
    if (count == 0)
        sub = copy_tab(args);
    else
    {
        sub = (char **)malloc(sizeof(char *) * (len + 1));
        sub[len] = 0;
        i = 0;
        count = 0;
        while (args[i])
        {
            if (args[i][0] == '<' || args[i][0] == '>' )
                i++;
            else if (args[i][0] != '<' && args[i][0] != '>' )
            {
                sub[count] = ft_strdup(args[i]);
                count++;
            }
            i++;
        }
    }
    //ft_tab_print(sub);
    return(sub);
}
