# minishell

#fork
L'appel système fork permet le création d'un processus clône du processus courrant.
pid_t  fork(void);
DEUX valeurs de retour en cas de succès:
Dans le processus père valeur de retour = le PID du fils. A recuperer??
Dans le processus fils valeur de retour = zéro.
Sinon
Dans le processus père valeur de retour = -1.

/*
	fork s utilise si executable, avec execve
	test fork
	pid_t pid;

	//va print deux fois, une fois par processus. Pere id fils, et fils 0.
	pid = fork();
	printf("%i\n", pid);

	exit(0);*/


#wait
pid_t wait(int *ptr_etat)
Le processus pere attend son fils.
Donne comme valeur de retour le pid du fils qui a terminé, et le code de fin est stocké dans ptr_etat. A recuperer &ptr_etat.

#waitpid
On peut également attendre la fin du fils grâce à son pid : pid_t waitpid(pid_t pid, int *ptr_etat, int options).

#exit 
prend un etat/status en parametre

#dup
int dup(int oldfd);
int dup2(int oldfd, int newfd);
Créent une copie du descripteur de fichier oldfd.

#signal
signal() installe le gestionnaire handler pour le signal signum. handler peut être SIG_IGN, SIG_DFL ou l'adresse d'une fonction définie par le programmeur (un « gestionnaire de signal »).
La fonction signal permet de spécifier ou de connaître le comportement du processus à la réception d'un signal donné, il faut donner en paramètre à la fonction le numéro du signal sig que l'on veut détourner et la fonction de traitement action à réaliser à la réception du signal.


#pwd
The getcwd() function copies the absolute pathname of the current working directory into
     the memory referenced by buf and returns a pointer to buf.  The size argument is the
     size, in bytes, of the array referenced by buf.

     If buf is NULL, space is allocated as necessary to store the pathname and size is
     ignored.  -> MALLOC tout seul, pas de size necessaire
