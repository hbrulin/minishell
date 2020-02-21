# minishell

#fork
L'appel système fork permet le création d'un processus clône du processus courrant.
pid_t  fork(void);
DEUX valeurs de retour en cas de succès:
Dans le processus père valeur de retour = le PID du fils. A recuperer??
Dans le processus fils valeur de retour = zéro.
Sinon
Dans le processus père valeur de retour = -1.

test fork: 

```c
pid_t pid;

//va print deux fois, une fois par processus. Pere id fils, et fils 0.
pid = fork();
printf("%i\n", pid);

exit(0);
```

#wait
pid_t wait(int *ptr_etat)
Le processus pere attend son fils.
Donne comme valeur de retour le pid du fils qui a terminé, et le code de fin est stocké dans ptr_etat. A recuperer &ptr_etat.
```c
pid = fork();
if (pid == 0)  //execution par le fils
        execve(path, args, g_env);
else if (pid > 0) //execution par le pere
{
	wpid = wait(&status); //pere attend fils, valeur retour dans wpid
	while (wpid != pid)
		wpid = wait(&status); //on attend tant que le pid du fils n'est pqs retourne
	if (wpid == pid) //If wait() returns due to a stopped or terminated child process, the process ID of                    the child is returned to the calling process.
	{
		free(path);
		return(1);
	}
```

#waitpid
On peut également attendre la fin du fils grâce à son pid : pid_t waitpid(pid_t pid, int *ptr_etat, int options).

#exit 
prend un etat/status en parametre -> exit le processus

#dup
int dup(int oldfd);
int dup2(int oldfd, int newfd);
Créent une copie du descripteur de fichier oldfd.

#signal
signal() installe le gestionnaire handler pour le signal signum. handler peut être SIG_IGN, SIG_DFL ou l'adresse d'une fonction définie par le programmeur (un « gestionnaire de signal »).
La fonction signal permet de spécifier ou de connaître le comportement du processus à la réception d'un signal donné, il faut donner en paramètre à la fonction le numéro du signal sig que l'on veut détourner et la fonction de traitement action à réaliser à la réception du signal.
http://www-igm.univ-mlv.fr/~dr/NCSPDF/chapitre11.pdf
https://fr.wikipedia.org/wiki/Signal_(informatique) 

#getcwd
The getcwd() function copies the absolute pathname of the current working directory into the memory referenced by buf and returns a pointer to buf.  The size argument is the size, in bytes, of the array referenced by buf.
If buf is NULL, space is allocated as necessary to store the pathname and size is ignored.  -> MALLOC tout seul, pas de size necessaire

#Background, foreground
Ctrl-Z - processus en background - fg pour le ramener en foreground. On peut voir les numéros de job a gauche entre [].
Ctrl -C tells the terminal to send a SIGINT to the current foreground process, which by default translates into terminating the application.
Ctrl -D tells the terminal that it should register a EOF on standard input, which bash interprets as a desire to exit. Ctrl -D means end of file. It only works at the beginning of a line (I'm simplifying a little), and has no effect if the program isn't reading input from the terminal. In your experiment, ^D told the shell that you weren't going to type any more commands, so it exited; then the terminal exited because its subprogram had terminated. -> ctrl-D n'est pas un signal, mais un retour de read.
Ctrl -\ : This sends the QUIT signal, which by default terminates an application.

#path
https://www.alsacreations.com/astuce/lire/78-quelle-est-la-diffrence-entre-les-chemins-relatifs-et-absolus.html

#expand 
https://www.commentcamarche.net/faq/5444-bash-les-arguments-parametres

#dirent.h
DIR : type representing a directory stream : rdered sequence of all the directory entries in a particular directory.
char d_name[] : name of an entry
struct dirent * > returned by readdir.
The readdir() function returns a pointer to a structure representing the directory entry at the current position in the directory stream specified by the argument dirp, and positions the directory stream at the next entry. 
It returns a null pointer upon reaching the end of the directory stream. The structure dirent defined by the dirent.h header describes a directory entry.

```c
struct dirent *readdir(DIR *dirp);
```

opendir : The opendir() function opens a directory stream corresponding to the directory named by the dirname argument. The directory stream is positioned at the first entry. Upon successful completion, opendir() returns a pointer to an object of type DIR. Otherwise, a null pointer is returned and errno is set to indicate the error.

```c
DIR *opendir(const char *dirname);
```

#stat
http://manpagesfr.free.fr/man/man2/stat.2.html
retourne un struct stat *buf, le remplit avec plusieurs champ, donc un champ st_mode, qui se compare avec des valeurs ENUM comme un flagbit -> permet de connaitre les droits.
```c
if (buf.st_mode & S_IXUSR)
        return (1);
```

#pipe
```c
int pipe(int fildes[2]);
```
The pipe() function creates a pipe (an object that allows unidirectional data flow) and allocates a pair of file descriptors.  The first descriptor connects to the read end of the pipe; the second connects to the write end.
Data written to fildes[1] appears on (i.e., can be read from) fildes[0].

#dup, dup2, 
 dup() duplicates an existing object descriptor and returns its value to the calling process (fildes2 = dup(fildes))
 In dup2(), the value of the new descriptor fildes2 is specified.  If fildes and fildes2 are equal, then dup2() just returns fildes2; no other changes are made to the existing descriptor.
 ```c
 int dup2(int fildes, int fildes2);
 ```

#Detecter les fuites de fd :
- ps aux | grep minishell -> recuperer le pid du processus
- lsof -a -p PID -> si la liste ne grandit pas, pas de leak
- ls -l | wc -l -> count open files
- https://www.cyberciti.biz/tips/linux-procfs-file-descriptors.html 
- https://stackoverflow.com/questions/6842113/how-to-detect-file-leak-and-the-corresponding-code-in-solaris 
