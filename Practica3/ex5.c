#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int fd1[2], fd2[2];
    char buffer[10];
    pid_t pid;

    char mensajeNietoAbuelo[] = "Hola abuelo soy tu nieto, el nieto\n\0";
    char mensajeNietoPadre[] = "Hola papa, soy tu hijo, el nieto\n\0";
    char mensajePadreHijo[] = "Hola hijo soy tu padre, el padre\n\0";
    char mensajePadreAbuelo[] = "Hola papa soy tu hijo, el padre\n\0";
    char mensajeAbueloPadre[] = "Hola hijo soy tu padre, el abuelo\n\0";
    char mensajeAbueloHijo[] = "Hola nieto soy el abuelo, el abuelo\n\0";

    char bufferAbuelo[10];
    char bufferPadre[10];
    char bufferNieto[10];

    pipe(fd1);
    pipe(fd2);
    pid = fork();

    if (pid < 0)
    {
        perror("Error");
    }
    else if (pid == 0)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("Error");
        }
        else if (pid == 0)
        {
            printf("Soy el nieto, mi ID es %d y el de mi padre es %d", getpid(), getppid());
        }
        else
        {
            
            printf("Soy el padre, mi id es %d, el de mi hijo es %d y el de mi padre es %d", getpid(), pid, getppid());
        }
    }
    else
    {
        printf("Soy el abuelo, mi id es %d y el de mi hijo es %d", getpid(), pid);
        read(fd2[0], bufferAbuelo, strlen(mensajeNietoAbuelo));
        printf("Mensaje Nieto a Abuelo: %s", buffer);
        read(fd2[0], bufferAbuelo, strlen(mensajePadreAbuelo));
    }
}