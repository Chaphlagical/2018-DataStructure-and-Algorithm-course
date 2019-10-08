#include "bank.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(){
    int ave_time;
    srand((unsigned)time(NULL));
    int wn,cn,mst,bt,maxtt,mintt;
    std::cout<<"Input the number of windows:"<<std::endl;
    std::cin>>wn;
    std::cout<<"Input the number of customers:"<<std::endl;
    std::cin>>cn;
    std::cout<<"Input the max service time:"<<std::endl;
    std::cin>>mst;
    std::cout<<"Input the min tolerant time:"<<std::endl;
    std::cin>>mintt;
    std::cout<<"Input the bank opening time:"<<std::endl;
    std::cin>>bt;
    Queue Q;
    window*win=new window[wn];
    Queue_Init(Q,cn);
    Queue_Create(Q,bt,mst,mintt);
    std::cout<<"Customer's List:"<<std::endl;
    Queue_Print(Q);
    bank_simulation(Q,win,bt,wn);
    Queue_Print(Q);
    Print_ave_time(Q);
    Print_Win(win,wn);
    Print_Leave(Q);
    cin.get();
    return 0;
}
