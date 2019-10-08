#include "TSP.h"


int main(){
    Graph G;
    int n;
    std::cin>>n;
    Create_Graph(G,n);
    Print_Graph(G);
    std::cout<<"Enumerate:\n";
    Enumerate(G);
    std::cout<<"Simple_Greedy:\n";
    Simple_Greedy(G);
    std::cout<<"Recursive:\n";
    Recursive(G);
    std::cout<<"A-star:\n";
    A_star(G);
}
