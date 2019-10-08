#include "Sort.h"

bool sure(List L){
    for (int i=0;i<L.len-1;i++)
        if(L.L[i]>L.L[i+1])
            return false;
    return true;
}

void Destory_List(List&L){
    if(L.len!=0){
        delete(L.L);
        L.len=0;
    }
}

void Init_List(List&L,int len){
    Destory_List(L);
    L.L=new int[len];
    L.len=len;
}

void List_Copy(List L1,List&L2){
    L2.L=new int[L1.len];
    for(int i=0;i<L1.len;i++)
        L2.L[i]=L1.L[i];
    L2.len=L1.len;
}

int random_num(int a){
    return (rand() % (a));
}

void Create_Random_List(List&L){
    for(int i=0;i<L.len;i++)
        L.L[i]=random_num(100*L.len);
}

void Print_List(List L){
    for(int i=0;i<L.len;i++)
        std::cout<<L.L[i]<<" ";
    std::cout<<std::endl;
}

void Swap(int&a,int&b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

void Selection_Sort(List&L){
    int min_index=0;
    for(int i=0;i<L.len;i++){
        for(int j=i;j<L.len;j++){
            if(L.L[min_index]>=L.L[j])
                min_index=j;
        }
        Swap(L.L[min_index],L.L[i]);
        min_index=i+1;
    }
}

void Bubble_Sort(List&L){
    for(int i=0;i<L.len;i++)
        for(int j=L.len-1;j>i;j--)
            if(L.L[j]<L.L[j-1])
                Swap(L.L[j],L.L[j-1]);
}

void Insert_Sort(List&L){
    int temp,j;
    for(int i=1;i<L.len;i++){
        if(L.L[i]>L.L[i-1])
            continue;
        temp=L.L[i];
        for(j=i-1;temp<L.L[j];j--)
            L.L[j+1]=L.L[j];
        L.L[j+1]=temp;
        //Print_List(L);
    }
    //std::cout<<sure(L)<<"\n\n\n\n";
}

void micro_sort(int L[],int n,int a){
    for(int i=a;i<=n;i+=a)
        for(int j=i;(j>a)&&(L[j-1]<L[j-a-1]);j-=a)
            Swap(L[j-1],L[j-a-1]);
}

void Shell_Sort(List&L){
    for(int i=L.len/2;i>2;i/=2)
        for(int j=1;j<=i;j++)
            micro_sort(&L.L[j],L.len+1-j,i);
    micro_sort(&L.L[0],L.len,1);
}

void Qsort(List&L,int left,int right){
    int i=left;
    int j=right;
    int temp=L.L[left];
    if(left>=right)return;
    while(i<j){
        while(i<j&&L.L[j]>=temp)j--;
        if(j>i)L.L[i]=L.L[j];
        while(i<j&&L.L[i]<=temp)i++;
        if(i<j)L.L[j]=L.L[i];
    }
    L.L[i]=temp;
    if(left<(i-1))Qsort(L,left,i-1);
    if(right>(j+1))Qsort(L,i+1,right);
}

void Quick_Sort(List&L){
    Qsort(L,0,L.len-1);
}

void HeapAdjust(List&L,int s,int t){
    int w=L.L[s];
    for(int i=2*s;i<=t;i*=2){
        if(i<t)i=(L.L[i]>L.L[i+1])?i:i+1;
        if(w>=L.L[i])break;
        L.L[s]=L.L[i];
        s=i;
    }
    L.L[s]=w;
}

void Heap_Sort(List&L){
    for(int i=L.len/2;i>=0;i--)
        HeapAdjust(L,i,L.len);
    for(int i=L.len;i>0;i--){
        Swap(L.L[0],L.L[i]);
        HeapAdjust(L,0,i-1);
    }
}

void Merge(int *T,int s,int m,int t){
    int *L=new int[t+1];
    int i=0,j=0,k=0;
    for(int m=0;m<t+1;m++)
        L[m]=T[m];
    for(i=s,j=m+1,k=i;i<=m&&j<=t;k++){
        if(L[i]<=L[j])T[k]=L[i++];
        else T[k]=L[j++];
    }

    for(;i<=m;)T[k++]=L[i++];
    for(;j<=t;)T[k++]=L[j++];
    delete L;
    //Print_List(L);
}

void MSort(List L,int*T,int s,int t){
    if(s==t){T[t]=L.L[t];return;}
    int m=(s+t)/2;
    MSort(L,L.L,s,m);
    MSort(L,L.L,m+1,t);
    Merge(L.L,s,m,t);
}

void Merge_Sort(List&L){
    MSort(L,L.L,0,L.len-1);
}

int Get_max(List L,int n){
    int MAX=0;
    for(int i=0;i<n;i++)
        if(MAX<L.L[i])
            MAX=L.L[i];
    return MAX;
}

void countSort(List&L, int n, int exp)
{
    int output[n];
    int buckets[10]={0};
    for (int i=0;i<n;i++)
        buckets[(L.L[i]/exp)%10]++;
    for (int i=1;i<10;i++)
        buckets[i]+=buckets[i-1];
    for (int i=n-1;i>=0;i--){
        output[buckets[(L.L[i]/exp)%10]-1]=L.L[i];
        buckets[(L.L[i]/exp)%10]--;
    }
    for (int i=0;i<n;i++)
        L.L[i]=output[i];
}

void Radix_Sort(List&L){
    int MAX=Get_max(L,L.len);
    for (int exp=1;MAX/exp>0;exp*=10)
        countSort(L,L.len,exp);
}

double Clock(void(*func)(List&L),List&L){
    clock_t BEGIN,END;
    BEGIN=clock();
    (*func)(L);
    END=clock();
    return (double)(END-BEGIN)/CLOCKS_PER_SEC*1000;
}

void Print_All(List L1,List*L){
    double t;
    std::cout<<"Original list : ";
    Print_List(L1);
    std::cout<<"Selection sort: ";
    t=Clock(Selection_Sort,L[0]);
   // Print_List(L[0]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
    std::cout<<"Bubble sort   : ";
    t=Clock(Bubble_Sort,L[1]);
 //   Print_List(L[1]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
    std::cout<<"Insert sort   : ";
    t=Clock(Insert_Sort,L[2]);
  //  Print_List(L[2]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
    std::cout<<"Shell sort   : ";
    t=Clock(Shell_Sort,L[3]);
  //  Print_List(L[3]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
    std::cout<<"Quick sort   : ";
    t=Clock(Quick_Sort,L[4]);
 //   Print_List(L[4]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
    std::cout<<"Heap sort   : ";
    t=Clock(Heap_Sort,L[5]);
  //  Print_List(L[5]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
    std::cout<<"Merge sort   : ";
    t=Clock(Merge_Sort,L[6]);
  //  Print_List(L[6]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
    std::cout<<"Radix sort   : ";
    t=Clock(Merge_Sort,L[7]);
  //  Print_List(L[7]);
    std::cout<<"Time: "<<t<<" ms"<<std::endl;
}

