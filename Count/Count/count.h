#ifndef __COUNT_H
#define __COUNT_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <ctime>

typedef struct LNode{
    int index;
    LNode*next;
}LNode,*LinkList;

void Count_phone(int**Hash,LinkList&L);
void Create_Bill(int**Hash,LinkList L);

#endif // __COUNT_H
