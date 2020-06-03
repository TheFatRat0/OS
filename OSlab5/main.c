#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int num=0;
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qready=PTHREAD_COND_INITIALIZER;
int flag=0;

void* add(void* arg){
	int i=(int)arg;
	while(num<=10){
		pthread_mutex_lock(&mylock);
		while(i%2==flag){
			int ret=pthread_cond_wait(&qready,&mylock);
		}
		if(flag==0)	flag=1;
		else	flag=0;
		if(num<=10)
			printf("Thread%d : number = %d\n", i, num++);
		pthread_mutex_unlock(&mylock);
		pthread_cond_broadcast(&qready);
	}
	printf("thread %d: The main function is waiting for me?\n", i);
	printf("Exit of Thread %d!\n", i);
	return ((void *)0);
}

int main(int argc, char** argv) 
{
	pthread_t tid1, tid2;
	int err;
	void *tret;
	printf("I'm the main function, Creating thread...\n");
	int i = 1;
	err = pthread_create(&tid1, NULL, add, (void *)i); 
	if (err != 0)
	{
		printf("pthread_create error:%s\n", strerror(err));
		exit(-1);
	} 
	printf("Create thread 1!\n");
	printf("thread1 : I'm thread 1\n");
	sleep(1);
	i = 2;
        err = pthread_create(&tid2, NULL, add, (void*)i);
        if (err != 0)
        {
                printf("pthread_create error:%s\n", strerror(err));
                exit(-1);
        }
        printf("Create thread 2!\n");
	printf("thread2 : I'm thread 2\n");
	printf("I'm the main function waiting for the threads to exit\n");
	err = pthread_join(tid1, &tret); 
	if (err != 0)
	{
		printf("can not join with thread1:%s\n", strerror(err));
		exit(-1);
	}
	err = pthread_join(tid2, &tret);
	if (err != 0)
	{
		printf("can not join with thread1:%s\n", strerror(err));
		exit(-1);
	}
	return 0;
}
