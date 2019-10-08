#include "count.h"

int main(){
    int **Hash;
    clock_t BEGIN,END;
    BEGIN=clock();
    LinkList L=new LNode;
    L->index=-1;
    L->next=NULL;
    Hash=new int*[2];
    Hash[0]=new int[2579999];
    Hash[1]=new int[2579999];
    Count_phone(Hash,L);
    Create_Bill(Hash,L);
    END=clock();
    std::cout<< (double)(END-BEGIN)/CLOCKS_PER_SEC*1000;
}
