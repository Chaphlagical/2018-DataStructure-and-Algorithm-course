/*
g++ Huffman.h Huffman.cpp main.cpp -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -lpython3.6
*/
#include "Huffman.h"

int main(){
    Py_Initialize();
    int sum=0;
    Node*T=new Node[NodeNum*2-1];
    std::string code="";
    Tree_Init(T);
    Count(T);
    Huffman(T);
    Create_Dict(T,NodeNum*2-2,code);
    sum=Encode(T);
    Decode(T,sum);
    Print_Tree(T);
    Print_Compress_Ratio();
    PyRun_SimpleString("import os");
    PyRun_SimpleString("os.system('python3 draw.py')");
    Py_Finalize();
    return 0;
}
