//header

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
    if (count == 0)
        sub = copy_tab(args);
    else
    {
        sub = (char **)malloc(sizeof(char *) * (count * 2) + 1);
        sub[count] = 0;
        i = 0;
        count = 0;
        while (args[i])
        {
            if (args[i][0] != '<' && args[i][0] != '>' )
            {
                sub[count] = ft_strdup(args[i]);
                count++;
                i++;
            }
            else if (args[i][0] == '<' || args[i][0] == '>' )
                i++;
            i++;
        }
    }
    //ft_tab_print(sub);
    return(sub);
}