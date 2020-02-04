#include <fcntl.h>
#include "../minishell.h"
#include "../escape_sequences.h"

int	main(int ac, char **av)
{
	(void)ac;
	t_convert crt;

	crt.pack = 28252;
	printf("%c%c", crt.tab[0], crt.tab[1]);
}
