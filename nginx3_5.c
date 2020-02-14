
#include<stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>



//信号处理函数
void sig_quit(int signo)
{   
    printf("收到了SIGQUIT信号!\n");
    // if(signal(SIGQUIT,SIG_DFL) == SIG_ERR)
    // {
    //     printf("无法为SIGQUIT信号设置缺省处理(终止进程)!\n");
    //     exit(1);
    // }
}


int main()
{
    sigset_t  newmask, oldmask;

    if(signal(SIGQUIT, sig_quit) == SIG_ERR) // 注册 SIGQUT 信号
    {
        printf("无法捕捉 SIGQUIT 信号");
        exit(1);
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        printf("sigprocmask(SIG_BLOCK) 失败！\n"); 
        exit(1);
    }

    printf("我要开始休息10秒了--------begin-----，此时我无法接收SIGQUIT信号!\n");
    sleep(10);   //这个期间无法收到SIGQUIT信号的；
    printf("我已经休息了10秒了--------end----!\n");

    if(sigismember(&newmask,SIGQUIT))  //测试一个指定的信号位是否被置位(为1)，测试的是newmask
    {
        printf("SIGQUIT信号被屏蔽了!\n");
    }
    else
    {
        printf("SIGQUIT信号没有被屏蔽!!!!!!\n");
    }

    if(sigismember(&newmask,SIGHUP))  //测试另外一个指定的信号位是否被置位,测试的是newmask
    {
        printf("SIGHUP信号被屏蔽了!\n");
    }
    else
    {
        printf("SIGHUP信号没有被屏蔽!!!!!!\n");
    }
    
    //现在我要取消对SIGQUIT信号的屏蔽(阻塞)--把信号集还原回去
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0) //第一个参数用了SIGSETMASK表明设置 进程  新的信号屏蔽字为 第二个参数 指向的信号集，第三个参数没用
    {
        printf("sigprocmask(SIG_SETMASK)失败!\n");
        exit(1);
    }

    printf("sigprocmask(SIG_SETMASK)成功!\n");

    if(sigismember(&oldmask,SIGQUIT))  //测试一个指定的信号位是否被置位,这里测试的当然是oldmask
    {
        printf("SIGQUIT信号被屏蔽了!\n");
    }
    else
    {
        printf("SIGQUIT信号没有被屏蔽，您可以发送SIGQUIT信号了，我要sleep(10)秒钟!!!!!!\n");
        int mysl = sleep(10);
        if(mysl > 0)
        {
            printf("sleep还没睡够，剩余%d秒\n",mysl);
        }
    }   

    return 0;
}

