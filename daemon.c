
//功能：守护进程
// 执行失败:返回-1
// 子进程：返回0，父进程：返回1
int daemon()
{
	switch( fork() )
	{
		case -1:
		// 创建子进程失败
			// 记录日志 ...
			return -1;
		case 0:
		// 子进程，这里直接 break
			break;
		default:
		// 父进程直接返回1
			return 1;
	}
	
	// 只有子进程才能执行下面的代码
	// 脱离终端，终端关闭，讲跟此子进程无关
	if( setsid() == -1 )
	{
		// 记录日志 ...
		return -1;
	}
	
	//设置为 0 ，不要让它来限制文件权限，以免引起混乱
	umask(0);
	
	// 打开黑洞文件，以读写方式打开
	int fd = open("/dev/null", O_RDWR);
	if(fd == -1)
	{
		// 记录日志 ...
		return -1;
	}
	if(dup2(fd, STDIN_FILENO) == -1) // 让 /dev/null 成为标准输入
	{
		// 记录日志 ...
		return -1;
	}
	if(dup2(fd, STDOUT_FILENO) == -1)// 让 /dev/null 成为标准输出
	{
		// 记录日志 ...
		return -1;
	}
	if(fd > STDERR_FILENO)
	{
		if(close(fd) == -1) //释放资源这样这个文件描述符就可以被复用，不然这个数字(文件描述符)会被一直占着
		{
			// 记录日志 ...
			return -1;
		}
	}
	
	return 0; // 子进程返回 0
	
	
}