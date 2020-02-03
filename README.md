# minishell

functions : 
malloc, free, write, open, read, close, fork, wait,
waitpid, wait3, wait4, signal, kill, exit, getcwd,
chdir, stat, lstat, fstat, execve, dup, dup2, pipe,
opendir, readdir, closedir

#fork
L'appel système fork permet le création d'un processus clône du processus courrant.
pid_t  fork(void);
DEUX valeurs de retour en cas de succès:
Dans le processus père valeur de retour = le PID du fils. A recuperer??
Dans le processus fils valeur de retour = zéro.
Sinon
Dans le processus père valeur de retour = -1.
Sert a recuperer l’environnement et le “dupliquer” pour ne pas lancer la commande recue dans le meme environnement.
Un processus n'est pas un shell?

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

#variable d'environnement
Dans un programme C, on peut accéder à la liste des variables d'environnement dans la variable environ, qui est un tableau de chaînes de caractères (terminé par un pointeur NULL pour marquer la fin de la liste).
```
extern char **environ;

int main(void)
{
   int i;
   for (i=0 ; environ[i]!=NULL ; i++)
      puts(environ[i]);
   return 0;
}
```
Pour accéder à une variable d'environnement particulière à partir de son nom, on utilise la fonction getenv, qui prend en paramètre le nom de la variable et qui retourne sa valeur sous forme de chaîne de caractère.
```
valeur = getenv("PATH");
```
putenv(char *s) -> pour assigner une variable d'environnement.

