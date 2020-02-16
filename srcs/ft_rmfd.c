//HEADER

#include "minishell.h"

char **ft_rmfd(char **args)
{
    int i = 0;
    int count = 0;
    char **sub;
    while (args[i])
    {
         if (args[i][0] == '<' || args[i][0] == '>' )
            count++;
        i++;
    }
    int len = ft_tablen(args) - (count * 2);
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