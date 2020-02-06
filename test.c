#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int main(void)
{
	int status;
	status = 1;

	pid_t	pid;
	pid = fork();
	printf("%i\n", pid);
	wait(&status); //le pere attend le fils pour repartir
	//il faudra prevoir si l'executable n'est pas bon ou permission denied -> check access control
	//OU si command not found
	return (1); //return 1 pour que le shell continue de tourner
}
