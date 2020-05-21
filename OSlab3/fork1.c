#include <sys/types.h>
#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>

int value=5;     //where?

int main(){
	
	int i;     //where?
	
	pid_t pid;
	
	for(i=0;i<2;i++){    // How many new processes and printfs£¿   4
		
	
		pid=fork();
	
		if(pid==0){
			value += 15;
			printf("Child: value = %d i = %d id = %d\n",value,i,getpid());
		}
		else if(pid>0){
			wait(NULL);
			printf("PARNET: value = %d i = %d id = %d\n",value,i,getpid());
			exit(0);   //Notice£ºWhat will happen with or without this line?
		}
	}
}
