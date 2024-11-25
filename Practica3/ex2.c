#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int fd[2];
    char buffer[10];
    pid_t pid;
    char mensaje[] = "Hola papa\n\0";

    pipe(fd);
    pid = fork();

    if (pid < 0)
    {
        perror("Error");
    }
    else if (pid == 0)
    {
        printf("Soy el hijo y escribo en el pipe. Mi ID es %d y el de mi padre es %d\n", getpid(), getppid());
        // Escribir en el pipe
        write(fd[1], mensaje, strlen(mensaje));
    }
    else
    {
        wait(NULL);
        printf("Soy el padre y leo desde el pipe. Mi ID es %d y el de mi padre es %d\n", getpid(), pid);
        // Leer desde el pipe
        read(fd[0], buffer, strlen(mensaje));
        printf("%s", buffer);
    }

}