#ifndef __SORT_H
#define __SORT_H

#include <iostream>
#include <ctime>
#include <cstdlib>



typedef struct{
    int*L;
    int len;
}List;

void Init_List(List&L,int len);
void List_Copy(List L1,List&L2);
void Create_Random_List(List&L);
void Print_List(List L);
void Selection_Sort(List&L);
void Bubble_Sort(List&L);
void Insert_Sort(List&L);
void Shell_Sort(List&L);
void Quick_Sort(List&L);
void Heap_Sort(List&L);
void Merge_Sort(List&L);
void Radix_Sort(List&L);
double Clock(void(*func)(List&L),List&L);
void Print_All(List L1,List*L);

#endif // __SORT_H
