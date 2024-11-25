#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int status1, status2;

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
            printf("Soy el nieto, mi ID es %d y el de mi padre es %d\n", getpid(), getppid());
        }
        else
        {
            waitpid(pid, &status2, 0);
            printf("Soy el padre, mi ID es %d, el ID de mi hijo es %d y el ID de mi padre es %d\n", getpid(), pid, getppid());
        }
    }
    else
    {
        waitpid(pid, &status1, 0);
        printf("Soy el abuelo, mi ID es %d y el ID de mi hijo es %d\n", getpid(), pid);
    }
    return 0;
}
