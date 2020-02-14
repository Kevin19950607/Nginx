
#include<stdio.h>
#include <unistd.h>
#include <signal.h>
// 本程序只是为了演示用的，实际工程中是不能这样使用的


void sig_usr(int signo)
{
    if( signo == SIGUSR1)
    {
        printf("recive SIGUSR1!\n");
    }
    else if(signo == SIGUSR2)
    {
       printf("recive SIGUSR2!\n"); 
    }
    else
    {
        printf("recive signal %d\n", signo);
    }
    
}


int main()
{
    if( signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        printf("can not catch SIGUSR1 signal\n");
    }
    if( signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("can not catch SIGUSR2 signal\n");
    }
    for(;;)
    {
        sleep(1);
        printf("releax 1 second\n");
    }

    printf("goodbye\n");



    return 0;
}
