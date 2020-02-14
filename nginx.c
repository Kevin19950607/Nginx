
#include<stdio.h>
#include <unistd.h>
#include <signal.h>


int main()
{
    
    printf("welcome to learn Linux C++\n");

    //signal(SIGHUP, SIG_IGN); //SIG_IGN标志，要求忽略这个信号

    for(;;)
    {
        sleep(1);
        printf("child releax 1 second\n");
    }


    printf("exit\n");

    return 0;
}
