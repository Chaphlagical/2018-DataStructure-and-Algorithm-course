#ifndef __TSP_H
#define __TSP_H

#include <iostream>
#include <ctime>

typedef struct{
    int**G;
    int *s;//side
    int *v;//vertex
    int *path;
    int num;
    int distance;
}Graph;

void Create_Graph(Graph&G,int n);
void Print_Graph(Graph G);
void Simple_Greedy(Graph&G);
void Print_Path(Graph G);
void Swap(int&a,int&b);
void Enumerate(Graph&G);
void Recursive(Graph&G);
void A_star(Graph&G);

#endif // __TSP_H
