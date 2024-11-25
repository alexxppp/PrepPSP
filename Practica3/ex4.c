#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd[2];
    pid_t pid;
    char mensaje[] = "Hola papa soy tu hijo\n\0";
    char buffer[strlen(mensaje)];

    pipe(fd);

    pid = fork();

    if (pid < 0)
    {
        perror("Error");
    }
    else if (pid == 0)
    {
        close(fd[0]); // Cerrar lectura ya que no lo necesitamos
        printf("Soy el hijo, mi ID es %d, y el de mi padre es %d\n", getpid(), getppid());
        write(fd[1], mensaje, strlen(mensaje));
    }
    else
    {
        wait(NULL);
        close(fd[1]); // Cerrar escritura ya que no lo necesitamos
        printf("Soy el padre, mi ID es %d y el de mi hijo es %d\n", getpid(), pid);
        read(fd[0], buffer, strlen(mensaje));
        printf("%s", buffer);
    }

    return 0;

}