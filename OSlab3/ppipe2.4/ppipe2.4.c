#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pid1,pid2,pid3,x,y,fx,fy,fz;

	int pipe1[2];
	int pipe2[2];
	int pipe3[2];
	int pipe4[2];


	printf("x  y you should put in:\n");
	scanf("%d%d",&x,&y);

	int y1[y];

	if(pipe(pipe1)<0){
		perror("pipe not create");
		exit(EXIT_FAILURE);
	}
	if(pipe(pipe2)<0){
                perror("pipe not create");
                exit(EXIT_FAILURE);
        }
	if(pipe(pipe3)<0){
                perror("pipe not create");
                exit(EXIT_FAILURE);
        }
	if(pipe(pipe4)<0){
                perror("pipe not create");
                exit(EXIT_FAILURE);
        }
	
	if((pid3=fork())<0){
                perror("process not create");
                exit(EXIT_FAILURE);
        }
	if((pid1=fork())==0){
		close(pipe1[1]);
		close(pipe2[0]);
		read(pipe1[0],&x,sizeof(int));
		if(x==1){
			fx=1;
		}
		else{
			int i=1;
			int j;
			for(j=1;j<=x;j++)
			{
				i=i*j;
			}
			fx=i;
		}
		printf("id1=%d x=%d\n",getpid(),fx);
		write(pipe2[1],&fx,sizeof(int));
		close(pipe1[0]);
                close(pipe2[1]);
		exit(EXIT_SUCCESS);
	}
	else{
	if ((pid2=fork())==0){
		close(pipe3[1]);
		close(pipe4[0]);
		read(pipe3[0],&y,sizeof(int));
		
		if(y==1||y==2){
			fy=1;
		}
		else{
			y1[1]=1;
			y1[2]=1;
			int i;
			for(i=3;i<=y;i++)
				y1[i]=y1[i-1]+y1[i-2];
				fy=y1[y];
		}

		printf("id2=%d y=%d\n",getpid(),fy);
		write(pipe4[1],&fy,sizeof(int));
		close(pipe3[0]);
		close(pipe4[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipe1[0]);
	close(pipe2[1]);
	close(pipe3[0]);
        close(pipe4[1]);

	write(pipe1[1],&x,sizeof(int));
	read(pipe2[0],&fx,sizeof(int));
	write(pipe3[1],&y,sizeof(int));
	read(pipe4[0],&fy,sizeof(int));
	fz=fx+fy;
	printf("id3=%d f(x,y)=%d\n",getpid(),fz);
	
	close(pipe1[1]);
        close(pipe2[0]);
	close(pipe3[0]);
        close(pipe4[1]);

	exit(EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;
 }
