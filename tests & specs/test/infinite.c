#include <stdio.h>
#include <signal.h>
void unkillable(int sig)
{
	sig = 0;
	printf("I can't be killed muahaha >:D\n");
}
int main()
{
	signal(SIGINT, &unkillable);
	printf("Hello World!\n");
	while (1)
		;
	return (0);
}
