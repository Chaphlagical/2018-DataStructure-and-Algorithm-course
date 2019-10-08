#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "/usr/include/python3.6/Python.h"
#define Target_File "stdio.h"
#define NodeNum 127

typedef struct Node{
    char data;
    int lchild;
    int rchild;
    int parent;
    int weight;
    std::string code="";
}Node;

void Tree_Init(Node*T);
void Count(Node*T);
void Huffman(Node*T);
void Create_Dict(Node*T,int t,std::string code);
int Encode(Node*T);
void Decode(Node*T,int sum);
void Print_Tree(Node*T);
void Print_Compress_Ratio();

#endif // __HUFFMAN_H
