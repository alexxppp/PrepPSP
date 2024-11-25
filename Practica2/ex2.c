#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    pid_t pid1, pid2;

    int status1, status2;

    pid1 = fork();

    if (pid1 < 0)
    {
        perror("Error");
    }
    else if (pid1 == 0)
    {
        printf("Soy el primer hijo, mi ID es %d y el ID de mi padre es %d\n", getpid(), getppid());
    }
    else
    {
        pid2 = fork();
        if (pid2 < 0)
        {
            perror("Error");
        }
        else if (pid2 == 0)
        {
            printf("Soy el segundo hijo, mi ID es %d y el ID de mi padre es %d\n", getpid(), getppid());
        }
        else
        {
            waitpid(pid1, &status1, 0); // Esperar al hijo 1
            waitpid(pid2, &status2, 0); // Esperar al hijo 2
            printf("Soy el padre, , mi ID es %d y el ID de mis hijos son %d y %d\n", getpid(), pid1, pid2);
        }
    }
}