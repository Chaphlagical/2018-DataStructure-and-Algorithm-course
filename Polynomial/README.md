# 多项式运算实验报告

**PB17050948        陈文博** 

## 题目描述

 实现一元多项式运算器的基本功能：(1)创建多项式；(2)打印显示多项式；(3)销毁多项式；(4)复制多项式；(5)求两个多项式的和；(6)求两个多项式的差；(7)求两个多项式的积；(8)求一个多项式的n次幂；(9)计算一个多项式在x=a处的值。

 可选做的高级功能：(1)求两个多项式的商和余式；(2)求两个多项式的最大公约式和最小公倍式；(3)求一个多项式的n阶导函数；(4)求一个多项式的不定积分；(5)求一个多项式在区间[a, b]上的定积分。

## 实验内容 

### 1.结构体定义 

​	本实验使用带头节点的单链表作为多项式的储存结构，定义于头文件Polynomial.h中（该实验默认多项式指数按升序排列），结构体定义如下： 

```C++
  typedef struct Node {//节点定义
	float coef;//系数
	float expo;//指数
	struct Node*next;//指向下一项的结构体指针
}Node, *Poly;
```

### 2. 函数定义

程序中的函数包括：

**void Poly_Init(Poly&P);
void Poly_Print(Poly&P);
void Poly_Clear(Poly&P);
void Poly_Destroy(Poly&P);
void Poly_Add(Poly&P, Poly&Q,Poly&R);
void Poly_Minus(Poly&P, Poly&Q, Poly&R);
void Poly_Copy(Poly&P, Poly&Q);
void Poly_Mutiply(Poly&P, Poly&Q, Poly&R);
void Poly_MutiplyNum(Poly&P,float num,Poly&Q);
void Poly_Power(Poly&P,int n, Poly&R);
void Poly_Calculate(Poly&P, float a, float&sum);
void Poly_Derivative(Poly&P, int n, Poly&R);
bool Poly_Division(Poly&P, Poly&Q, Poly&Quo, Poly&Re);
void Poly_indefinite_integral(Poly&P, int n, Poly&R);
void Poly_definite_integral(Poly&P, float a, float b, float&sum);
void Poly_GCD(Poly&P,Poly&Q,Poly&R);
void Poly_LCM(Poly&P,Poly&Q,Poly&R);**

定义在Polynomial.cpp中，在Polynomial.h中声明。

#### （1）void Poly_Init(Poly&P)

1. 函数功能：初始化多项式P
2. 函数入口：多项式P
3. 算法流程：给多项式头节点P分配空间并赋值P->expo=-1,P->coef=0,P->next=NULL
4. 算法分析：时间复杂度O（1），空间复杂度O（1）   

#### （2）void Poly_Print(Poly&P)

1. 函数功能：打印多项式P
2. 函数入口：多项式P
3. 算法流程：遍历多项式每一个节点并打印出来
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （3） void Poly_Clear(Poly&P)

1. 函数功能：清空多项式P
2. 函数入口：多项式P
3. 算法流程：遍历多项式每一个节点并删除（保留头节点）
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （4） void Poly_Destroy(Poly&P)

1. 函数功能：销毁多项式P
2. 函数入口：多项式P
3. 算法流程：清空多项式P并销毁头节点
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （5） void Poly_Add(Poly&P, Poly&Q,Poly&R)

1. 函数功能：多项式加法P+Q=R
2. 函数入口：多项式P、Q、R
3. 算法流程：分别从P和Q的头节点开始遍历P和Q，选取指数小的项复制节点连接到R的末尾，若指数相等则系数相加再连接
4. 算法分析：时间复杂度O（n），空间复杂度O（m+n） 

#### （6）Poly_Minus(Poly&P, Poly&Q, Poly&R)

1. 函数功能：多项式减法P-Q=R
2. 函数入口：多项式P、Q、R
3. 算法流程：分别从P和Q的头节点开始遍历P和Q，选取指数小的项（Q的项需要将系数取相反数）复制节点连接到R的末尾，若指数相等则系数相减再连接
4. 算法分析：时间复杂度O（n），空间复杂度O（m+n）

#### （7）void Poly_Copy(Poly&P, Poly&Q)

1. 函数功能：多项式复制Q=P
2. 函数入口：多项式P、Q
3. 算法流程：遍历P，不断为Q开辟新节点并将P节点的值赋给Q的节点
4. 算法分析：时间复杂度O（n），空间复杂度O（n） 

#### （8）void Poly_Mutiply(Poly&P, Poly&Q, Poly&R)

1. 函数功能：多项式乘法P*Q=R
2. 函数入口：多项式P、Q、R
3. 算法流程：遍历P，将P的每一个节点与Q的每一项系数相乘、指数相加复制到临时链表temp，每次执行R=R+temp直到P遍历完毕得到乘法结果R
4. 算法分析：时间复杂度O（mn），空间复杂度O（mn）

#### （9）void Poly_MutiplyNum(Poly&P,float num,Poly&Q)

1. 函数功能：多项式数乘P*num=Q
2. 函数入口：多项式P、Q，浮点数num
3. 算法流程：遍历P，将P的每个节点的系数与num相乘复制连接到Q
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （10）void Poly_Power(Poly&P,int n, Poly&R)

1. 函数功能：多项式的n次方P^n=R
2. 函数入口：多项式P、R，整数n
3. 算法流程：将P进行n次乘法复制给R
4. 算法分析：时间复杂度O（m^n），空间复杂度O（m^n） 

#### （11）void Poly_Calculate(Poly&P, float a, float&sum)

1. 函数功能：计算多项式在x=a处的值
2. 函数入口：多项式P，浮点数a、sum
3. 算法流程：sum赋初始值0，遍历P，计算每个节点的coef*a^expo并累加到sum
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （12） void Poly_Derivative(Poly&P, int n, Poly&R)

1. 函数功能：对多项式求n阶导数R=d^n P/d R^n
2. 函数入口：多项式P、R，整数n
3. 算法流程：遍历P，对每一节点，若expo>n，直接跳过，若expo<=n，则按照求导法则赋值R的新节点，得到P的导数R
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （13）bool Poly_Division(Poly&P, Poly&Q, Poly&Quo, Poly&Re)

1. 函数功能：多项式除法P/Q=Quo…………Re
2. 函数入口：多项式P，Q，Quo，Re
3. 算法流程：若Q=0，则直接返回false。否则复制Re=P，每次取Re最大项，求Re最大项与Q最大项之商temp，temp作为Quo的新项，更新Re=Re-Q*temp，直到Re最大项小于Q的最大项为止，返回true。Quo即为商式，Re即为余式。
4. 算法分析：时间复杂度O（n^2-nm），空间复杂度O（n+m）

#### （14）void Poly_indefinite_integral(Poly&P, int n, Poly&R)

1. 函数功能：求多项式P的n次不定积分（默认每次积分的常数项为0）
2. 函数入口：多项式P、R，整数n
3. 算法流程：遍历P，对每一节点，则按照积分法则赋值R的新节点，得到P的不定积分R
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （15）void Poly_definite_integral(Poly&P, float a, float b, float&sum)

1. 函数功能：求多项式P从a到b的定积分sum

2. 函数入口：多项式P，积分下限a，积分下限b，积分值sum
3. 算法流程：对P进行不定积分一次，再对结果赋值相减得到sum
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （16） void Poly_GCD(Poly&P,Poly&Q,Poly&R) 

1. 函数功能：求多项式P和Q的最大公约数R
2. 函数入口：多项式P、Q、R
3. 算法流程：辗转相除法

#### （17） void Poly_LCM(Poly&P,Poly&Q,Poly&R) 

1. 函数功能：求多项式P和Q的最小公倍数R
2. 函数入口：多项式P、Q、R
3. 算法流程：求P与Q的最大公约数temp，R=P*Q/temp 

### 实验结果

输入数据：**P= -3-x+3*x^2+x^3       Q=2+3*x+x^2**

输出结果（单个多项式的操作默认操作P）：

**(1)多项式加法：** -1+2\*x^1+4\*x^2+1*x^3  

**(2)多项式减法：** -5-4\*x^1+2\*x^2+1\*x^3

**(3)多项式乘法：** -6-11\*x^1+10\*x^3+6\*x^4+1\*x^5

**(4)多项式除法：** 1\*x^1......................-3-3*x^1

**(5)多项式乘方（以二次方为例）：** 9+6\*x^1-17\*x^2-12\*x^3+7\*x^4+6\*x^5+1\*x^6

**(6)多项式不定积分（以一次为例）：** -0.5\*x^2+1\*x^3+0.25\*x^4

**(7)多项式定积分（从1积分到3）：** 36

**(8)多项式求导（以一次为例）：** -1+6\*x^1+3\*x^2

**(9)多项式最大公约数：** -3-3\*x^1

**(4)多项式最小公倍数：** 2+1.66667\*x^1-1.66667\*x^2-1.66667\*x^3-0.333333\*x^4 

### 讨论与结论

本次实验采用参数传递来得到结果链表，好处是原链表得到保留，某些算法更加利于理解，但也消耗更多内存，在复合操作时销毁链表也浪费了一些时间






