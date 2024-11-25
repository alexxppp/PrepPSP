#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int fd[2];
    char mensaje[] = "Hola hijo, como estas?\n\0";
    char buffer[strlen(mensaje) + 1];

    pipe(fd);
    pid = fork();

    if (pid < 0)
    {
        perror("Error");
    }
    else if (pid == 0)
    {
        close(fd[1]); // Cerrar escritura ya que no la necesitamos
        printf("Soy el hijo, mi ID es %d y el de mi padre es %d y voy a leer del pipe.\n", getpid(), getppid());
        read(fd[0], buffer, strlen(mensaje));
        printf("%s", buffer);
    }
    else
    {
        close(fd[0]); // Cerrar lectura ya que no la necesitamos
        printf("Soy el padre, mi ID es %d y el de mi hijo es %d y voy a escribir en el pipe.\n", getpid(), pid);
        write(fd[1], mensaje, strlen(mensaje));
        wait(NULL);
    }

    return 0;

}