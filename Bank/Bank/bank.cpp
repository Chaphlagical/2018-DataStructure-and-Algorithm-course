#include "bank.h"

int random_num(int a,int b){
    //srand((unsigned)time(NULL));
    return (rand() % (b-a))+a;
}

void Queue_Init(Queue&Q,int num){
    Q.cus=new customer[num];
    Q.head=0;
    Q.tail=num-1;
    Q.num=num;
}

void Queue_Out(Queue &Q){
    if(Q.head==Q.num){
    }
        Q.head+=1;
}

int Queue_length(Queue&Q){
    return Q.tail-Q.head+1;
}

customer random_customer(int all_time,int max_service_time,int min_tolerant_time){
    customer person;
    person.service_time=random_num((int)(max_service_time/2),max_service_time);
    person.arrival=random_num(0,all_time);
    person.waiting_time=-1;
    person.finish=false;
    person.win_id=0;
    person.tol_time=random_num(min_tolerant_time,max_service_time);
    person.wait=false;
    person.at_service=false;
    person.leave=false;
    if(random_num(0,2))
        person.VIP=true;
    else person.VIP=false;
    return person;
}

void Queue_Create(Queue Q,int all_time,int max_service_time,int min_tolerant_time){
    for(int i=0;i<Q.num;i++)
        Q.cus[i]=random_customer(all_time,max_service_time,min_tolerant_time);
    for(int i=0;i<Q.num-1;i++)
        for(int j=i+1;j<Q.num;j++)
            if(Q.cus[i].arrival>Q.cus[j].arrival){
                customer t=Q.cus[i];
                Q.cus[i]=Q.cus[j];
                Q.cus[j]=t;
            }
    for(int i=0;i<Q.num;i++)
        Q.cus[i].id=i+1;
}

void Queue_Print(Queue Q){
    for(int i=0;i<Q.num;i++){
        std::cout<<std::endl<<"Customer's ID:"<<Q.cus[i].id<<std::endl;
        std::cout<<"Arrival time:"<<Q.cus[i].arrival<<std::endl;
        std::cout<<"Service time:"<<Q.cus[i].service_time<<std::endl;
        std::cout<<"Tolerant time:"<<Q.cus[i].tol_time<<std::endl;
        std::cout<<"Rank:";
        if(Q.cus[i].VIP)std::cout<<"VIP"<<std::endl;
        else std::cout<<"Not VIP"<<std::endl;
        std::cout<<"Finishing status:";
        if(Q.cus[i].finish)std::cout<<"Finish"<<std::endl;
        else std::cout<<"Not finish"<<std::endl;
        if(Q.cus[i].waiting_time!=-1)std::cout<<"Waiting time:"<<Q.cus[i].waiting_time<<std::endl;
        if(Q.cus[i].win_id)std::cout<<"Windows id:"<<Q.cus[i].win_id<<std::endl;
    }
}

void Init_Win(window*win,int num,status s){
    for(int i =0;i<num;i++){
        win[i].cur_status=s;
        win[i].customer_num=0;
        win[i].id=i+1;
        win[i].using_time=0;
        win[i].effect=0;
    }
}

void VIP_Line_Init(Queue&VIP,int n){
    VIP.head=VIP.tail=VIP.num=0;
    VIP.cus=new customer[n];
}

void In_VIP(Queue&VIP,customer c){
    if(VIP.num==0){
        VIP.cus[0]=c;
        VIP.num++;
    }
    else{
        VIP.tail++;
        VIP.num++;
        VIP.cus[VIP.tail]=c;
    }
}


void bank_simulation(Queue&Q,window*win,int BT,int nw) {
    int t=0,idw=nw,c,w,i=0;
    Queue VIP;
    VIP_Line_Init(VIP,Q.num);

    std::cout<<std::endl<<"Bank Open Now!"<<std::endl;
    Init_Win(win,nw,idle);
    while(t<=BT){
        std::cout<<std::endl<<"Time:"<<t<<std::endl;
        for(i=0;i<Q.num;i++)
            if(Q.cus[i].arrival==t){
                std::cout<<"Customer with ID "<<Q.cus[i].id<<" enter the line"<<std::endl;
                Q.cus[i].wait=true;
                if(Q.cus[i].VIP)
                    In_VIP(VIP,Q.cus[i]);
            }

        for(int j=0;j<Q.num;j++)
            if(t-Q.cus[j].arrival==Q.cus[j].tol_time&&Q.cus[j].wait){
                Queue_Out(Q);
                Q.cus[j].leave=true;
                std::cout<<"Customer with ID "<<Q.cus[j].id<<" leaving the bank"<<std::endl;
            }



        for(w=0;w<nw;++w)
            if(win[w].cur_status==busy){
                win[w].using_time++;
                    //std::cout<<"aa"<<std::endl;
                if(t-win[w].cur_start_time==win[w].cur_customer.service_time){
                  //  std::cout<<std::endl<<"Time:"<<t<<std::endl;
                    std::cout<<"Customer with ID "<<win[w].cur_customer.id<<" finishes service"<<std::endl;
                    win[w].cur_status=idle;
                    Q.cus[win[w].cur_customer.id-1].finish=true;
                    Q.cus[win[w].cur_customer.id-1].wait=false;
                    Q.cus[win[w].cur_customer.id-1].at_service=false;
                    //win[w].cur_start_time=t;
                    ++idw;
                }
                else
                    std::cout<<"Customer with ID "<<win[w].cur_customer.id<<" is having service"<<std::endl;
            }

        for(w=nw-1;w>=0;--w){
                //std::cout<<"aa"<<std::endl;
            if(win[w].cur_status==idle&&Queue_length(VIP)>0&&t>=VIP.cus[VIP.head].arrival&&VIP.cus[VIP.head].id!=0){
                c=VIP.head;
                Queue_Out(VIP);
                //std::cout<<std::endl<<"Time:"<<t<<std::endl;
                std::cout<<"Customer with ID "<<VIP.cus[c].id<<" begin to get service at "<<win[w].id<<" windows"<<std::endl;
                win[w].cur_status=busy;
                win[w].cur_start_time=t;
                win[w].cur_customer=VIP.cus[c];
                win[w].customer_num++;
                VIP.cus[c].waiting_time=t-VIP.cus[c].arrival;
                VIP.cus[c].at_service=true;
                VIP.cus[c].wait=false;
                VIP.cus[c].win_id=win[w].id;
                Q.cus[win[w].cur_customer.id-1].win_id=win[w].id;
                Q.cus[win[w].cur_customer.id-1].wait=false;
                Q.cus[win[w].cur_customer.id-1].at_service=true;
                Q.cus[win[w].cur_customer.id-1].waiting_time=t-VIP.cus[c].arrival;
            }
            while(Q.cus[Q.head].VIP)
                Queue_Out(Q);
            if(win[w].cur_status==idle&&Queue_length(Q)>0&&t>=Q.cus[Q.head].arrival){
                c=Q.head;
                Queue_Out(Q);
                //std::cout<<std::endl<<"Time:"<<t<<std::endl;
                std::cout<<"Customer with ID "<<Q.cus[c].id<<" begin to get service at "<<win[w].id<<" windows"<<std::endl;
                win[w].cur_status=busy;
                win[w].cur_start_time=t;
                win[w].cur_customer=Q.cus[c];
                win[w].customer_num++;
                Q.cus[c].waiting_time=t-Q.cus[c].arrival;
                Q.cus[c].at_service=true;
                Q.cus[c].wait=false;
                Q.cus[c].win_id=win[w].id;
            }
        }
        ++t;
    }
    for(int j=0;j<nw;j++)
        win[j].effect=(float)win[j].using_time/t;
    for(int j=0;j<Q.num;j++)
        if(Q.cus[j].wait)
            Q.cus[j].waiting_time=t-Q.cus[j].arrival;
    std::cout<<"Bank Closed Down!"<<std::endl;
}

void Print_ave_time(Queue Q){
    int time=0,time_VIP=0,n=0,n_VIP=0;
    for(int i=0;i<Q.num;i++){
        if(Q.cus[i].VIP){
            time_VIP+=Q.cus[i].waiting_time;
            n_VIP++;
        }
        else{
            time+=Q.cus[i].waiting_time;
            n++;
        }
    }
    std::cout<<"Average waiting time for normal customers :"<<time/n<<std::endl;
    std::cout<<"Average waiting time for VIP customers :"<<time_VIP/n_VIP<<std::endl;
}

void Print_Win(window *win,int nw){
    float sum=0;
    for(int i=0;i<nw;i++){
        std::cout<<"Window"<<i+1<<"'s effect:"<<win[i].effect<<std::endl;
        sum+=win[i].effect;
    }
    std::cout<<"Window"<<"average effect:"<<sum/nw<<std::endl;
}
void Print_Leave(Queue Q){
    int num=0;
    for(int i=0;i<Q.num;i++)
        if(Q.cus[i].leave)
            num++;
    std::cout<<num<<" customers leave"<<std::endl;
}

