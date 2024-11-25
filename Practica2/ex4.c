#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int contador = 6;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("Error");
    }
    else if (pid == 0)
    {
        printf("Soy el hijo: %i\n", contador - 5);
    }
    else
    {
        waitpid(pid, &status, 0);
        printf("Soy el padre: %i\n", contador + 5);
    }
    return 0;
    
}