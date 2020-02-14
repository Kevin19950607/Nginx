
#include<stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>



//信号处理函数
void sig_usr(int signo)
{   
    printf("收到了SIGUSR1信号，进程id=%d!\n",getpid());   
}


int main()
{
    pid_t pid;

    printf("进程开始执行!\n");

    //
    if( signal(SIGUSR1, sig_usr) == SIG_ERR) // 参数2 是函数指针
    {
        printf("无法捕捉SIGUSR1信号!\n");
        exit(1);
    }

    pid = fork();

    if(pid < 0)
    {
        printf("子进程创建失败，很遗憾!\n");
        exit(1);
    }

    //现在，父进程和子进程同时开始 运行了 
    for(;;)
    {        
        sleep(1); //休息1秒
        printf("休息1秒，进程id=%d!\n",getpid());
    }
    printf("再见了!\n");


    return 0;
}

