#include "minishell.h"

char	**env;

int	main(void)
{
	char arg[] = "\"\\\\\""; 
	printf("o %s\n", arg);
	if (clean_arg(arg) == 1)
		printf("c %s\n", "Syntax Error");
	else
		printf("c %s\n", arg);
}

/*
** no quotes escapes : \" \' \> \| \\ \$
** no quotes syntax error : " ' \
** single quotes syntax error : '
** double quotes escapes : \ " $ 
** double quotes syntax error : "
** DR et BS : as char if alone
*/
