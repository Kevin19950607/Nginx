
#include<stdio.h>
#include <unistd.h>
#include <signal.h>


int main()
{
    pid_t pid;
    printf("welcome to learn Linux C++\n");

    //signal(SIGHUP, SIG_IGN); //SIG_IGN标志，要求忽略这个信号

    pid = fork();

    if(pid < 0)
    {
        printf("fork error");
        return 0;
    }
    if(pid == 0)
    {
        for(;;)
        {
            sleep(1);
            printf("child releax 1 second\n");
        }

    }
    else
    {
        for(;;)
        {
            sleep(1);
            printf("falther releax 1 second\n");
        }

    }

    printf("exit\n");

    return 0;
}
