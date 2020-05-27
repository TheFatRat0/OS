#include "ipc.h"

int main(int argc,char * argv[])
{
        int rate;
        if(argv[1]!=NULL)  rate=atoi(argv[1]);
        else rate=3;

        buff_key=101;
        buff_num=3;

        cget_key = 103;

        cget_num = 1;

        shm_flg=IPC_CREAT|0644;

        buff_ptr=(char *)set_shm(buff_key,buff_num,shm_flg);

        cget_ptr=(int*)set_shm(cget_key,cget_num,shm_flg);

        prod_key = 201; //生产者同步信号灯键值
        pmtx_key = 203; //生产者互斥信号灯键值
        TP_key = 301;//消费者同步信号灯键值
        PG_key = 302;//消费者互斥信号灯键值
        TG_key = 303;//消费者互斥信号灯键值

        sem_flg = IPC_CREAT | 0644;
        sem_val=1;
        prod_sem=set_sem(prod_key,sem_val,sem_flg);
        sem_val=0;

        PG_sem=set_sem(PG_key,sem_val,sem_flg);
        TP_sem=set_sem(TP_key,sem_val,sem_flg);
        TG_sem=set_sem(TG_key,sem_val,sem_flg);

        sem_val=1;

        pmtx_sem=set_sem(pmtx_key,sem_val,sem_flg);

        while(1){
  		down(PG_sem);
		down(pmtx_sem);
		sleep(rate);
		printf("%d consumer get: paper%c,glue%c\n",getpid(),buff_ptr[*cget_ptr+1],buff_ptr[*cget_ptr+2]);
		up(pmtx_sem);
		up(prod_sem);
        }

        return EXIT_SUCCESS;
}
