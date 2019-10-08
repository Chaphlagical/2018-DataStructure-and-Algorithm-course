

# 排序算法实验报告

**PB17050948        陈文博** 

## 问题描述

应该使用同一个无序序列作为输入，来测量不同排序算法的运行时间。那么无序序列如何得到？一种方法是，先生成一个长度为N的有序序列，再将该序列随机重排(random shuffle)，从而得到一个长度为N的无序序列。
测量程序的运行时间，我们可以使用C/C++语言提供的计时器。需要注意的是，该计时器的灵敏度比较低，在Windows系统中，一般只有当两组运行时间相差0.1秒以上时，才能认为这两组时间是有差别的。
本实验要求编程实现至少5种排序算法（快速、堆、归并必做，其他选做），并在不同N值（如10000、100000、1000000）的条件下多次运行程序计算平均运行时间。实验报告应对不同算法的运行时间进行比较分析。

## 实验内容 

### 1.结构体定义 

待排序数组结构体：

```c++
typedef struct{
    int*L;
    int len;
}List;
```

在Sort.h中声明

### 2. 函数定义

程序中的函数包括：

**void Init_List(List&L,int len)
void Create_Random_List(List&L)
void Selection_Sort(List&L)
void Bubble_Sort(List&L)
void Insert_Sort(List&L)
void Shell_Sort(List&L)
void Quick_Sort(List&L)
void Heap_Sort(List&L)
void Merge_Sort(List&L)
void Radix_Sort(List&L)
double Clock(void(*func)(List&L),List&L)**

#### （1）void Init_List(List&L,int len)

1. 函数功能：初始化数组
2. 函数入口：数组L，长度len
3. 算法流程：给数组L创建内存
4. 算法分析：时间复杂度O（1），空间复杂度O（n）   

#### （2）void Create_Random_List(List&L)

1. 函数功能：随机给数组赋值
2. 函数入口：数组L
3. 算法流程：给每一个地址随机赋值
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

#### （3）void Selection_Sort(List&L)

1. 函数功能：选择排序算法
2. 函数入口：数组L
3. 算法流程：选择排序第i次遍历L记录第i小的数，并最后与第i个位置的数交换
4. 算法分析：时间复杂度O（n^2），空间复杂度O（1）

#### （4） void Insert_Sort(List&L)

1. 函数功能：简单插入排序算法
2. 函数入口：数组L
3. 算法流程：逐个处理待排序的记录，每个新纪录与前面已经实现的子序列进行比较，将它插入到子序列中正确的位置
4. 算法分析：时间复杂度O（n^2），空间复杂度O（1）

#### （5） void Bubble_Sort(List&L)

1. 函数功能：冒泡排序
2. 函数入口：数组L
3. 算法流程：双重for循环，从数组底部比较到顶部，交换相邻顺序不合要求的关键码
4. 算法分析：时间复杂度O（n^2），空间复杂度O（1） 

#### （6）void Shell_Sort(List&L)

1. 函数功能：希尔排序
2. 函数入口：数组L
3. 算法流程：将数组用一定间隔分成子序列，用插入排序算法进行排序，缩短间隔，继续排序，以此类推
4. 算法分析：时间复杂度不确定，空间复杂度O（1）

#### （7）void Quick_Sort(List&L)

1. 函数功能：快速排序
2. 函数入口：数组L
3. 算法流程：通过一趟“划分”，将整个序列分为两块，保证后一块的任一关键字都比前一块的任一关键字大，再对两块分别进行进一步“划分”，以递归形式进行，直到不能再细分为止
4. 算法分析：时间复杂度O（nlogn~n^2），空间复杂度O（logn） 

#### （8）void Heap_Sort(List&L)

1. 函数功能：堆排序
2. 函数入口：数组L
3. 算法流程：初始化大顶堆，将第一个数和最后交换后，将第一个数与第n-1个数组成的子序列调整为大顶堆，第一个数与最后一个数交换，以此类推，直至有序。
4. 算法分析：时间复杂度O（nlogn），空间复杂度O（1）

#### （9）void Merge_Sort(List&L)

1. 函数功能：归并排序
2. 函数入口：数组L
3. 算法流程：将数组分成若干个长度相等的子数组，把每个子数组排序后两两合并后再排序，直到不能再合并、有序为止
4. 算法分析：时间复杂度O（nlogn），空间复杂度O（n）

#### （9）void Radix_Sort(List&L)

1. 函数功能：基数排序
2. 函数入口：数组L
3. 算法流程：根据关键字进行收集，在将各个关键字的元素进行排序最后合并
4. 算法分析：时间复杂度O（n），空间复杂度O（n）

### 实验结果

n=10000

```
Selection sort:102.167ms
Bubble sort:263.396ms
Insert sort:55.382ms
Shell sort:2.376ms
Quick sort:0.933ms
Heap sort:1.527ms
Merge sort:92.359ms
Radix sort:1.11ms
```

n=100000

```
Selection sort:9323.66ms
Bubble sort:32556.4ms
Insert sort:5848.63ms
Shell sort:34.391ms
Quick sort:11.527ms
Heap sort:18.235ms
Merge sort:9686.35ms
Radix sort:13.114ms
```

n=1000000

```
Selection sort:921186ms
Bubble sort:3.35492e+06ms
Insert sort:595005ms
Shell sort:512.956ms
Quick sort:139.345ms
Heap sort:228.163ms
Merge sort:1.00058e+06ms
Radix sort:151.655ms
```



### 讨论与结论

归并排序的辅助数组注意要释放内存否则可能造成栈溢出





