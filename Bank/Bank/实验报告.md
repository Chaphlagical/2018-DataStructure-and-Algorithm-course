

# 银行排队系统实验报告

**PB17050948        陈文博** 

## 问题描述

基本功能：模拟一个单队列、多窗口的银行排队系统一天的运行情况，随机生成顾客的到达时间和办理业务所需时间等数据。一天结束后，统计顾客的平均等待时间和窗口的平均占用率。
可选做的高级功能：(1)改变顾客办理业务所需时间或银行的窗口数，观察顾客平均等待时间和窗口平均占用率如何变化；(2)假设每位顾客有一个容忍时间，等待超过容忍时间之后顾客将离开，统计顾客的离开率；(3)假设银行有两个队列，其中一个是VIP队列，另一个是普通队列，窗口服务的规则改为：若VIP队列不空，则优先服务VIP，否则服务普通顾客，统计VIP和普通顾客的平均等待时间有多大的差别。

## 实验内容 

### 1.结构体定义 

​	顾客个体结构体：

```C++
  typedef struct {
    int id;       // 顾客编号
    int arrival;      //到达时间
    int service_time; //完成服务所需要的时间
    int waiting_time;//等待时间
    bool finish;//完成标志
    int win_id;//窗口编号
    int tol_time;//容忍时间
    bool wait;//等待状态标志
    bool at_service;//正在服务标志
    bool VIP;//VIP顾客标志
    bool leave;//离开标志
}customer;
```

​	队列结构体：

```C++
typedef struct{
    int num;//总人数
    customer*cus;//顾客线性表
    int head;//头节点
    int tail;//尾节点
}Queue;
```

​	窗口结构体：

```C++
enum status{idle,busy};//窗口状态变量
typedef struct {
    int id;//窗口编号
    status cur_status;//当前窗口状态
    int cur_start_time;//当前顾客开始服务的时间
    customer cur_customer;//窗口当前服务的顾客
    int customer_num;//已经服务的顾客数
    int using_time;//服务总时间
    float effect;//工作效率
}window;
```

以上结构体定义在bank.cpp中

### 2. 函数定义

程序中的函数包括：

**void Queue_Init(Queue&Q,int num);
void Queue_Out(Queue &Q);
void Queue_Create(Queue Q,int all_time,int max_service_time,int min_tolerant_time);
void Queue_Print(Queue Q);
void bank_simulation(Queue&Q,window*win,int BT,int nw);
void Print_Win(window *win,int nw);
void Print_ave_time(Queue Q);
void Print_Leave(Queue Q);**

#### （1）void Queue_Init(Queue&Q,int num)

1. 函数功能：初始化队列
2. 函数入口：队列Q，总人数num
3. 算法流程：创建人数为num的顾客队列
4. 算法分析：时间复杂度O（1），空间复杂度O（n）   

#### （2）void Queue_Out(Queue &Q)

1. 函数功能：出队列
2. 函数入口：队列Q
3. 算法流程：队列头节点标志head加一
4. 算法分析：时间复杂度O（1），空间复杂度O（n）

#### （3） void Queue_Create(Queue Q,int all_time,int max_service_time,int min_tolerant_time)

1. 函数功能：生成顾客队列
2. 函数入口：队列Q，银行营业总时间all_time，顾客最大服务时间max_service_time，顾客最小容忍时间min_tolerant_time
3. 算法流程：遍历队列，顾客服务时间取max_service_time/2~max_service_time之间的随机数，容忍时间取min_tolerant_time~all_time，随机设置VIP，waiting_time置-1，person.win_id置0，person.finish、person.win_id置0，person.wait，person.at_service，person.leave置0。
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （4） void Queue_Print(Queue Q)

1. 函数功能：打印队列
2. 函数入口：队列Q
3. 算法流程：遍历队列Q，打印所有顾客信息
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （5） void bank_simulation(Queue&Q,window*win,int BT,int nw)

1. 函数功能：银行排队系统仿真
2. 函数入口：队列Q，窗口数组win，银行营业时间BT，窗口数nw
3. 算法流程：生成VIP队列，仿真开始，遍历队列，将满足到达时间等于当前时间的顾客填入相应的队列，将当前时间减去到达时间等于容忍时间且处于等待状态的顾客移出队列。遍历窗口数组，若有窗口服务的顾客到达时间加服务时间等于当前时间，送出窗口。遍历窗口数组，遍历VIP队列若有等待的顾客，送入窗口服务，否则遍历普通顾客队列，选择等待的顾客送入队列。
4. 算法分析：时间复杂度O（n），空间复杂度O（n） 

#### （6）void Print_Win(window *win,int nw)

1. 函数功能：打印窗口数组
2. 函数入口：窗口数组win，窗口数nw
3. 算法流程：遍历窗口数组，打印窗口的工作效率和总效率
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （7）void Print_ave_time(Queue Q)

1. 函数功能：打印平均等待时间
2. 函数入口：队列Q
3. 算法流程：遍历队列，分别计算打印VIP和普通顾客的平均等待时间
4. 算法分析：时间复杂度O（n），空间复杂度O（n） 

#### （8）void Print_Leave(Queue Q)

1. 函数功能：打印提前离开银行的人数
2. 函数入口：队列Q
3. 算法流程：遍历队列，累加提前离开的人数并打印
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

### 实验结果

Input the number of windows:
（输入）3
Input the number of customers:
（输入）20
Input the max service time:
（输入）40
Input the min tolerant time:
（输入）50
Input the bank opening time:
（输入）100
Customer's List:

Customer's ID:1
Arrival time:0
Service time:27
Tolerant time:56
Rank:VIP
Finishing status:Not finish

Customer's ID:2
Arrival time:1
Service time:25
Tolerant time:51
Rank:VIP
Finishing status:Not finish

Customer's ID:3
Arrival time:18
Service time:38
Tolerant time:57
Rank:VIP
Finishing status:Not finish

Customer's ID:4
Arrival time:25
Service time:31
Tolerant time:51
Rank:Not VIP
Finishing status:Not finish

Customer's ID:5
Arrival time:26
Service time:33
Tolerant time:50
Rank:Not VIP
Finishing status:Not finish

Customer's ID:6
Arrival time:27
Service time:35
Tolerant time:53
Rank:Not VIP
Finishing status:Not finish

Customer's ID:7
Arrival time:27
Service time:23
Tolerant time:59
Rank:VIP
Finishing status:Not finish

Customer's ID:8
Arrival time:29
Service time:26
Tolerant time:59
Rank:VIP
Finishing status:Not finish

Customer's ID:9
Arrival time:30
Service time:27
Tolerant time:52
Rank:Not VIP
Finishing status:Not finish

Customer's ID:10
Arrival time:31
Service time:20
Tolerant time:54
Rank:Not VIP
Finishing status:Not finish

Customer's ID:11
Arrival time:42
Service time:31
Tolerant time:58
Rank:Not VIP
Finishing status:Not finish

Customer's ID:12
Arrival time:43
Service time:38
Tolerant time:56
Rank:VIP
Finishing status:Not finish

Customer's ID:13
Arrival time:69
Service time:31
Tolerant time:55
Rank:VIP
Finishing status:Not finish

Customer's ID:14
Arrival time:73
Service time:26
Tolerant time:53
Rank:VIP
Finishing status:Not finish

Customer's ID:15
Arrival time:73
Service time:36
Tolerant time:56
Rank:VIP
Finishing status:Not finish

Customer's ID:16
Arrival time:74
Service time:35
Tolerant time:51
Rank:Not VIP
Finishing status:Not finish

Customer's ID:17
Arrival time:79
Service time:31
Tolerant time:51
Rank:Not VIP
Finishing status:Not finish

Customer's ID:18
Arrival time:82
Service time:38
Tolerant time:53
Rank:Not VIP
Finishing status:Not finish

Customer's ID:19
Arrival time:93
Service time:21
Tolerant time:55
Rank:Not VIP
Finishing status:Not finish

Customer's ID:20
Arrival time:96
Service time:25
Tolerant time:57
Rank:VIP
Finishing status:Not finish

Bank Open Now!

Time:0
Customer with ID 1 enter the line
Customer with ID 1 begin to get service at 3 windows

Time:1
Customer with ID 2 enter the line
Customer with ID 1 is having service
Customer with ID 2 begin to get service at 2 windows

Time:2
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:3
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:4
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:5
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:6
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:7
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:8
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:9
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:10
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:11
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:12
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:13
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:14
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:15
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:16
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:17
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:18
Customer with ID 3 enter the line
Customer with ID 2 is having service
Customer with ID 1 is having service
Customer with ID 3 begin to get service at 1 windows

Time:19
Customer with ID 3 is having service
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:20
Customer with ID 3 is having service
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:21
Customer with ID 3 is having service
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:22
Customer with ID 3 is having service
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:23
Customer with ID 3 is having service
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:24
Customer with ID 3 is having service
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:25
Customer with ID 4 enter the line
Customer with ID 3 is having service
Customer with ID 2 is having service
Customer with ID 1 is having service

Time:26
Customer with ID 5 enter the line
Customer with ID 3 is having service
Customer with ID 2 finishes service
Customer with ID 1 is having service
Customer with ID 4 begin to get service at 2 windows

Time:27
Customer with ID 6 enter the line
Customer with ID 7 enter the line
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 1 finishes service
Customer with ID 7 begin to get service at 3 windows

Time:28
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:29
Customer with ID 8 enter the line
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:30
Customer with ID 9 enter the line
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:31
Customer with ID 10 enter the line
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:32
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:33
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:34
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:35
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:36
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:37
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:38
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:39
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:40
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:41
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:42
Customer with ID 11 enter the line
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:43
Customer with ID 12 enter the line
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:44
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:45
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:46
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:47
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:48
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:49
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 is having service

Time:50
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 7 finishes service
Customer with ID 8 begin to get service at 3 windows

Time:51
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 8 is having service

Time:52
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 8 is having service

Time:53
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 8 is having service

Time:54
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 8 is having service

Time:55
Customer with ID 3 is having service
Customer with ID 4 is having service
Customer with ID 8 is having service

Time:56
Customer with ID 3 finishes service
Customer with ID 4 is having service
Customer with ID 8 is having service
Customer with ID 12 begin to get service at 1 windows

Time:57
Customer with ID 12 is having service
Customer with ID 4 finishes service
Customer with ID 8 is having service
Customer with ID 5 begin to get service at 2 windows

Time:58
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:59
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:60
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:61
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:62
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:63
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:64
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:65
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:66
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:67
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:68
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:69
Customer with ID 13 enter the line
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:70
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:71
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:72
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:73
Customer with ID 14 enter the line
Customer with ID 15 enter the line
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:74
Customer with ID 16 enter the line
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:75
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 is having service

Time:76
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 8 finishes service
Customer with ID 13 begin to get service at 3 windows

Time:77
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:78
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:79
Customer with ID 17 enter the line
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:80
Customer with ID 6 leaving the bank
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:81
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:82
Customer with ID 18 enter the line
Customer with ID 9 leaving the bank
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:83
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:84
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:85
Customer with ID 10 leaving the bank
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:86
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:87
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:88
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:89
Customer with ID 12 is having service
Customer with ID 5 is having service
Customer with ID 13 is having service

Time:90
Customer with ID 12 is having service
Customer with ID 5 finishes service
Customer with ID 13 is having service
Customer with ID 14 begin to get service at 2 windows

Time:91
Customer with ID 12 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:92
Customer with ID 12 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:93
Customer with ID 19 enter the line
Customer with ID 12 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:94
Customer with ID 12 finishes service
Customer with ID 14 is having service
Customer with ID 13 is having service
Customer with ID 15 begin to get service at 1 windows

Time:95
Customer with ID 15 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:96
Customer with ID 20 enter the line
Customer with ID 15 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:97
Customer with ID 15 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:98
Customer with ID 15 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:99
Customer with ID 15 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service

Time:100
Customer with ID 11 leaving the bank
Customer with ID 15 is having service
Customer with ID 14 is having service
Customer with ID 13 is having service
Bank Closed Down!

Customer's ID:1
Arrival time:0
Service time:27
Tolerant time:56
Rank:VIP
Finishing status:Finish
Waiting time:0
Windows id:3

Customer's ID:2
Arrival time:1
Service time:25
Tolerant time:51
Rank:VIP
Finishing status:Finish
Waiting time:0
Windows id:2

Customer's ID:3
Arrival time:18
Service time:38
Tolerant time:57
Rank:VIP
Finishing status:Finish
Waiting time:0
Windows id:1

Customer's ID:4
Arrival time:25
Service time:31
Tolerant time:51
Rank:Not VIP
Finishing status:Finish
Waiting time:1
Windows id:2

Customer's ID:5
Arrival time:26
Service time:33
Tolerant time:50
Rank:Not VIP
Finishing status:Finish
Waiting time:31
Windows id:2

Customer's ID:6
Arrival time:27
Service time:35
Tolerant time:53
Rank:Not VIP
Finishing status:Not finish
Waiting time:74

Customer's ID:7
Arrival time:27
Service time:23
Tolerant time:59
Rank:VIP
Finishing status:Finish
Waiting time:0
Windows id:3

Customer's ID:8
Arrival time:29
Service time:26
Tolerant time:59
Rank:VIP
Finishing status:Finish
Waiting time:21
Windows id:3

Customer's ID:9
Arrival time:30
Service time:27
Tolerant time:52
Rank:Not VIP
Finishing status:Not finish
Waiting time:71

Customer's ID:10
Arrival time:31
Service time:20
Tolerant time:54
Rank:Not VIP
Finishing status:Not finish
Waiting time:70

Customer's ID:11
Arrival time:42
Service time:31
Tolerant time:58
Rank:Not VIP
Finishing status:Not finish
Waiting time:59

Customer's ID:12
Arrival time:43
Service time:38
Tolerant time:56
Rank:VIP
Finishing status:Finish
Waiting time:13
Windows id:1

Customer's ID:13
Arrival time:69
Service time:31
Tolerant time:55
Rank:VIP
Finishing status:Not finish
Waiting time:7
Windows id:3

Customer's ID:14
Arrival time:73
Service time:26
Tolerant time:53
Rank:VIP
Finishing status:Not finish
Waiting time:17
Windows id:2

Customer's ID:15
Arrival time:73
Service time:36
Tolerant time:56
Rank:VIP
Finishing status:Not finish
Waiting time:21
Windows id:1

Customer's ID:16
Arrival time:74
Service time:35
Tolerant time:51
Rank:Not VIP
Finishing status:Not finish
Waiting time:27

Customer's ID:17
Arrival time:79
Service time:31
Tolerant time:51
Rank:Not VIP
Finishing status:Not finish
Waiting time:22

Customer's ID:18
Arrival time:82
Service time:38
Tolerant time:53
Rank:Not VIP
Finishing status:Not finish
Waiting time:19

Customer's ID:19
Arrival time:93
Service time:21
Tolerant time:55
Rank:Not VIP
Finishing status:Not finish
Waiting time:8

Customer's ID:20
Arrival time:96
Service time:25
Tolerant time:57
Rank:VIP
Finishing status:Not finish
Waiting time:5

Average waiting time for normal customers :38
Average waiting time for VIP customers :8
Window1's effect:0.811881
Window2's effect:0.980198
Window3's effect:0.990099
Windows average effect:0.927393
4 customers leave

### 讨论与结论

本实验将顾客数组和队列放在同一内存下，在生成顾客数组时需要进行排序操作，VIP队列实际可以只存储VIP顾客的ID，银行窗口的使用最好能够实现随机选择。





