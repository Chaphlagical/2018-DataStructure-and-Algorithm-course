#include "count.h"

//min=510000 max=3089999 range=2579999

int string2int(std::string str){
    int sum=0;
    for(int i=3;i<11;i++)
        sum+=pow(10,10-i)*(str.data()[i]-48);
    return sum;
}

int Get_time(std::string str){
    int sum=0;
    for(int i=0;i<4;i++)
        sum+=pow(10,3-i)*(str.data()[i]-48);
    return sum;
}


int Get_Key(int number){
    int num=number-5510000;
    if(num/10000000!=0)
        num-=48000000;
    return num;
}

std::string Get_Money(int m){
    std::string s="";
    int t=10;
    //std::cout<<n;
    while(m/t){
        s=(char)(m%t*10/t+48)+s;
        t*=10;
    }
    s=(char)(m%t*10/t+48)+s;
    while(s.length()!=8)
        s="0"+s;
    return s;
}


void Count_phone(int**Hash,LinkList&L){
    std::ifstream file_in;
    std::string str="";
    std::string time="";
    std::string ad="";
    char kind;
    char buf;
    int i=0;
    int num;
    int key=0;
    file_in.open("records.txt",std::ios::in);
    while(file_in>>std::noskipws>>buf){
        if(i<11)
            str+=buf;
        else if(i==12)
            kind=buf;
        else if(i>12&&i<17)
            time+=buf;
        else if(i>=17&&i<=21)
            ad+=buf;
        i++;
        if(buf=='\n'){
            i=0;
            num=string2int(str);
            key=Get_Key(num);
            if(Hash[0][key]==0){
                Hash[0][key]=num;
                Hash[1][key]=0;
                LNode*p=new LNode;
                p->index=key;
                p->next=L->next;
                L->next=p;
            }
            if(kind=='0')
                Hash[1][key]+=(int)(40*(float)Get_time(time)/60);
            else if(kind=='1')
                Hash[1][key]+=(int)(20*(float)Get_time(time)/60);
            str=time=ad="";
        }
    }
    file_in.close();
}

void Create_Bill(int**Hash,LinkList L){
    std::ofstream file_out;
    file_out.open("bill.txt",std::ios::out);
    LNode *p=L->next;
    while(p){
        if(Hash[0][p->index]/10000000)
            file_out<<"139"<<Hash[0][p->index]<<Get_Money(Hash[1][p->index])<<"\r\n";
        else
            file_out<<"1390"<<Hash[0][p->index]<<Get_Money(Hash[1][p->index])<<"\r\n";
        p=p->next;
    }
    file_out.close();
}
