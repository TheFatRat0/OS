#include "ipc.h"

int main(int argc,char* argv[])
{
	int rate;
	if(argv[1]!=NULL) rate=atoi(argv[1]);
	else rate=3;

	buff_key=101;
	buff_num=3;
	pput_key=102;
	pput_num=1;

	shm_flg=IPC_CREAT|0644;

	buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg);
	pput_ptr = (int *)set_shm(pput_key,pput_num,shm_flg);	

	prod_key=201;//生产者同步信号灯键值
	pmtx_key=202;//生产者互斥信号灯键值
	TP_key = 301;//消费者同步信号灯键值
    PG_key = 302;//消费者互斥信号灯键值
    TG_key = 303;//消费者互斥信号灯键值	

	sem_flg=IPC_CREAT|0644;	
	sem_val=1;
	prod_sem=set_sem(prod_key,sem_val,sem_flg);
	sem_val=0;

	PG_sem=set_sem(PG_key,sem_val,sem_flg);
	TP_sem=set_sem(TP_key,sem_val,sem_flg);
	TG_sem=set_sem(TG_key,sem_val,sem_flg);
	
	sem_val=1;
	pmtx_sem=set_sem(pmtx_key,sem_val,sem_flg);

	int pid;
	int i=0;
	while(1){
		int r=(i++)%3;
		if(r==0){
			down(prod_sem);
			down(pmtx_sem);
			buff_ptr[*pput_ptr]='T';
			buff_ptr[*pput_ptr+2]='G';
			sleep(rate);
			printf("%d producer put: tobacoo%c,glue%c\n",getpid(),buff_ptr[*pput_ptr],buff_ptr[*pput_ptr+2]);

			up(pmtx_sem);
			up(TG_sem);
		}
		else if(r==1){
			down(prod_sem);
			down(pmtx_sem);
			buff_ptr[*pput_ptr+1]='P';
			buff_ptr[*pput_ptr+2]='G';
			sleep(rate);
	                printf("%d producer put: paper%c,glue%c\n",getpid(),buff_ptr[*pput_ptr+1],buff_ptr[*pput_ptr+2]);

          		up(pmtx_sem);
          		up(PG_sem);
		}
		else{
			down(prod_sem);
			down(pmtx_sem);
			buff_ptr[*pput_ptr]='T';
			buff_ptr[*pput_ptr+1]='P';
			sleep(rate);
			printf("%d producer put: tobacoo%c,paper%c\n",getpid(),buff_ptr[*pput_ptr],buff_ptr[*pput_ptr+1]);

            		up(pmtx_sem);
            		up(TP_sem);
		}
	}
	return EXIT_SUCCESS;
}
