#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int 	main(int ac, char **av, char **envp)
{
	(void)ac;
	char *buf = "HE";

	int s = buf ? 1 : 0;
	printf("%d\n", s);
}
