#include "../minishell.h"

/*
** echo test = "test"
** echo test | echo = ""
** echo test | $? = 0
** le stdout de echo est toujours un int donc un int alimentera le pipe
** un fd different de 1 devra etre passe en cas de redirection
** > ecrit en ecrasant (write mode)
** >> ecrit en fin de fichier (append mode)
** 1 si pas d'option 0 si option
*/

int	echo_wrap(char **args)
{
			
}

int	echo(const char *input, const char *filepath, int wmode, int option)
{
	int fd;
	int n;

	fd = 1;
	if (filepath)
		fd = open(filepath, O_CREAT | wmode | O_WRONLY, S_IRWXU);
	n = ft_strlen(input);
	write(fd, input, n) == -1;
	write(fd, "\n", option) == -1;
		close(fd);
		return (1);
	return (0);
}
