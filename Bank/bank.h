#ifndef __BANK_H
#define __BANK_H

#include <iostream>
#include <cstdlib>
#include <ctime>

typedef struct {
    int id;       // customer's id
    int arrival;      // the time that customer arrived
    int service_time; // the service time the customer need
    int waiting_time;
    bool finish;
    int win_id;
    int tol_time;
    bool wait;
    bool at_service;
    bool VIP;
    bool leave;
}customer;

typedef struct{
    int num;
    customer*cus;
    int head;
    int tail;
}Queue;

enum status{idle,busy};

typedef struct {
    int id;
    status cur_status;// the current status of the window
    int cur_start_time;//if busy,the current service starts time
    customer cur_customer;//if busy,the current customer
    int customer_num;
    int using_time;
    float effect;
}window;

void Queue_Init(Queue&Q,int num);
void Queue_Out(Queue &Q);
void Queue_Create(Queue Q,int all_time,int max_service_time,int min_tolerant_time);
void Queue_Print(Queue Q);
void bank_simulation(Queue&Q,window*win,int BT,int nw);
void Print_Win(window *win,int nw);
void Print_ave_time(Queue Q);
void Print_Leave(Queue Q);

#endif // __BANK_H
