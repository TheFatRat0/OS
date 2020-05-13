
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#define BUFNUM 60
int main() {
	int n;
	int fd[2];
	pid_t pid;
	char buf[BUFNUM];
	signal(SIGPIPE, SIG_IGN);
	pipe(fd);
	close(fd[0]);
	if((n = write(fd[1], "I'm your father.\n", 17)) < 0) {
		printf("%d\n",errno);//输出对应的错误编号
		printf("%s\n",strerror(errno));//返回关于错误编号的描述
	}
	printf("%d\n",n);
}

