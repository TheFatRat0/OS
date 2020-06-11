#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
class PCB{
public:
	int ID;//进程ID
	double arr_time;
	double ser_time;
	double str_time;
	double fin_time;
	double cyc_time;//周转时间
	double w_cyc_time;//带权周转时间

	PCB(int p_id=0,double arrTime=0,double serTime=0)
	:ID(p_id),arr_time(arrTime),ser_time(serTime){}

	~PCB(){}
};

bool cmp_arr(const PCB& p1,const PCB& p2){
	return p1.arr_time<p2.arr_time;//比较到达时间
}

double get_avg_cyc_time(PCB* plist,int pnum){
	double sum=0;
	for(int i=0;i<pnum;i++){
		sum+=plist[i].cyc_time;
	}
	return sum/pnum;
}

double get_w_avg_cyc_time(PCB* plist,int pnum){
        double sum=0;
        for(int i=0;i<pnum;i++){
                sum+=plist[i].w_cyc_time;
        }
        return sum/pnum;
}

void SJF(PCB* plist,int pnum){
	int time=0;
	printf("\n（SJF）如下所示\n");
	sort(plist,plist+pnum,cmp_arr);
	int i=0;
	for(i=0;i<pnum;i++){
		for(int j=i+1;j<pnum;j++){
			if(plist[j].arr_time<=time&&plist[j].ser_time<plist[i].ser_time)
				swap(plist[i],plist[j]);
		}
		if(plist[i].arr_time<=time){
			plist[i].str_time=time;
			plist[i].fin_time=time+plist[i].ser_time;
			time=plist[i].fin_time;
			plist[i].cyc_time=plist[i].fin_time-plist[i].arr_time;
			plist[i].w_cyc_time=plist[i].cyc_time/plist[i].ser_time;
		}
		else{
			time+=1;
			i--;
		}
	}
    cout<<"进程ID,到达时间,开始时间,结束时间,周转时间,带权周转时间分别如下所示"<<endl;
    for(int i = 0; i < pnum; ++i){
        cout<<plist[i].ID<<","<<plist[i].arr_time<<","<<plist[i].str_time<<","<<plist[i].fin_time<<","<<plist[i].cyc_time<<","<<plist[i].w_cyc_time<<endl;
    }
    cout<<"进程调度顺序为:";
    for(int i=0;i<pnum;i++){
            cout<<plist[i].ID;
            if(i!=pnum-1)
                    cout<<"-->";
    }
    cout<<endl;
    cout<<"平均周转时间为 "<<get_avg_cyc_time(plist,pnum)<<" 平均带权周转时间为 "<<get_w_avg_cyc_time(plist,pnum)<<endl;
}

void FCFS(PCB* plist,int pnum){
	int time=0;
        cout<<"\n（FCFS）如下所示"<<endl;
        sort(plist,plist+pnum,cmp_arr);
	int i=0;
	for (i=0;i<pnum;i++){
		if(plist[i].arr_time<=time){
                  	plist[i].str_time=time;
			plist[i].fin_time=time+plist[i].ser_time;
                        time=plist[i].fin_time;
                        plist[i].cyc_time=plist[i].fin_time-plist[i].arr_time;
                        plist[i].w_cyc_time=plist[i].cyc_time/plist[i].ser_time;
		}
		else{
			time+=1;
                        i--;
                }
	}
    cout<<"进程ID,到达时间,开始时间,结束时间,周转时间,带权周转时间分别如下所示"<<endl;
    for(int i = 0; i < pnum; ++i){
    cout<<plist[i].ID<<","<<plist[i].arr_time<<","<<plist[i].str_time<<","<<plist[i].fin_time<<","<<plist[i].cyc_time<<","<<plist[i].w_cyc_time<<endl;

    }
    cout<<"进程调度顺序为:";
    for(int i=0;i<pnum;i++){
            cout<<plist[i].ID;
            if(i!=pnum-1)
                    cout<<"-->";
    }
    cout<<endl;
    cout<<"平均周转时间为 "<<get_avg_cyc_time(plist,pnum)<<" 平均带权周转时间为 "<<get_w_avg_cyc_time(plist,pnum)<<endl;
}

int main(){
	int pnum=0;
	cout<<"进程数：";
	cin>>pnum;
	PCB* plist=new PCB[pnum];
	for(int i=0;i<pnum;i++){
		cout<<"第"<<i<<"个进程"<<"到达时间，服务时间:"<<endl;
		cin>>plist[i].arr_time>>plist[i].ser_time;
		plist[i].ID = i;
	}
	SJF(plist,pnum);
	FCFS(plist,pnum);
	return 0;
}


