// HEADER

#include "minishell.h"

int	ft_echo(char **args)
{
	int i;
	int opt;

	if (!args || !args[0])
		return (1);
	opt = args[1] && ft_strcmp(args[1], "-n") == 0 ? TRUE : FALSE;
	i = opt;
	while (args[++i])
	{
		if (write(1, args[i], ft_strlen(args[i])) == -1)
			return (1);
		if (args[i + 1])
			if (write(1, " ", 1) == -1)
				return (1);
	}
	if (!opt)
		if (write(1, "\n", 1) == -1)
			return (1);
	return (0);
}
