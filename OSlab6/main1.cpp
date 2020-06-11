#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
class PCB{
public:
	int ID;//����ID
	double arr_time;
	double ser_time;
	double str_time;
	double fin_time;
	double cyc_time;//��תʱ��
	double w_cyc_time;//��Ȩ��תʱ��

	PCB(int p_id=0,double arrTime=0,double serTime=0)
	:ID(p_id),arr_time(arrTime),ser_time(serTime){}

	~PCB(){}
};

bool cmp_arr(const PCB& p1,const PCB& p2){
	return p1.arr_time<p2.arr_time;//�Ƚϵ���ʱ��
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
	printf("\n��SJF��������ʾ\n");
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
    cout<<"����ID,����ʱ��,��ʼʱ��,����ʱ��,��תʱ��,��Ȩ��תʱ��ֱ�������ʾ"<<endl;
    for(int i = 0; i < pnum; ++i){
        cout<<plist[i].ID<<","<<plist[i].arr_time<<","<<plist[i].str_time<<","<<plist[i].fin_time<<","<<plist[i].cyc_time<<","<<plist[i].w_cyc_time<<endl;
    }
    cout<<"���̵���˳��Ϊ:";
    for(int i=0;i<pnum;i++){
            cout<<plist[i].ID;
            if(i!=pnum-1)
                    cout<<"-->";
    }
    cout<<endl;
    cout<<"ƽ����תʱ��Ϊ "<<get_avg_cyc_time(plist,pnum)<<" ƽ����Ȩ��תʱ��Ϊ "<<get_w_avg_cyc_time(plist,pnum)<<endl;
}

void FCFS(PCB* plist,int pnum){
	int time=0;
        cout<<"\n��FCFS��������ʾ"<<endl;
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
    cout<<"����ID,����ʱ��,��ʼʱ��,����ʱ��,��תʱ��,��Ȩ��תʱ��ֱ�������ʾ"<<endl;
    for(int i = 0; i < pnum; ++i){
    cout<<plist[i].ID<<","<<plist[i].arr_time<<","<<plist[i].str_time<<","<<plist[i].fin_time<<","<<plist[i].cyc_time<<","<<plist[i].w_cyc_time<<endl;

    }
    cout<<"���̵���˳��Ϊ:";
    for(int i=0;i<pnum;i++){
            cout<<plist[i].ID;
            if(i!=pnum-1)
                    cout<<"-->";
    }
    cout<<endl;
    cout<<"ƽ����תʱ��Ϊ "<<get_avg_cyc_time(plist,pnum)<<" ƽ����Ȩ��תʱ��Ϊ "<<get_w_avg_cyc_time(plist,pnum)<<endl;
}

int main(){
	int pnum=0;
	cout<<"��������";
	cin>>pnum;
	PCB* plist=new PCB[pnum];
	for(int i=0;i<pnum;i++){
		cout<<"��"<<i<<"������"<<"����ʱ�䣬����ʱ��:"<<endl;
		cin>>plist[i].arr_time>>plist[i].ser_time;
		plist[i].ID = i;
	}
	SJF(plist,pnum);
	FCFS(plist,pnum);
	return 0;
}


