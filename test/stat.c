 #include <sys/stat.h>
 #include <stdio.h>

 int main(void)
 {
     struct stat *buf;

     stat("minishell", buf);
     printf("%hu\n", buf->st_mode);
 }