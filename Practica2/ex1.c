#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("Error");
    }
    else if (pid == 0)
    {
        printf("Soy el hijo. Mi ID es %d y el ID de mi padre es %d\n", getpid(), getppid());
    }
    else
    {
        printf("Soy el padre. Mi ID es %d y el ID de mi hijo es %d y el de mi padre es %d\n", getpid(), pid, getppid());
    }
    return 0;
}