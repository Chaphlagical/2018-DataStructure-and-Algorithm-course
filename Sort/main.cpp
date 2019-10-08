#include "Sort.h"

int main(){
    List L1;
    char c;
    List L;
    double t;
    int MAX,index,operate;
    srand((unsigned)time(NULL));
    std::cout<<"Input the number of the original list:";
    std::cin>>MAX;
    Init_List(L1,MAX);
    Create_Random_List(L1);
    std::cout<<"Original List\n";
    Print_List(L1);
    List_Copy(L1,L);
    std::cout<<"1. Selection sort\n";
    std::cout<<"2. Bubble sort\n";
    std::cout<<"3. Insert sort\n";
    std::cout<<"4. Shell sort\n";
    std::cout<<"5. Quick sort\n";
    std::cout<<"6. Heap sort\n";
    std::cout<<"7. Merge sort\n";
    std::cout<<"8. Radix sort\n";
    std::cout<<"9. Reset the original list\n";
    std::cout<<"10. Quit\n";
    while(true){
        std::cout<<"Input index of kind of operation:";
        std::cin>>index;
        switch(index){
        case 1:
            std::cout<<"Selection sort:\n";
            t=Clock(Selection_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 2:
            std::cout<<"Bubble sort:\n";
            t=Clock(Bubble_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 3:
            std::cout<<"Insert sort:\n";
            t=Clock(Insert_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 4:
            std::cout<<"Shell sort:\n";
            t=Clock(Shell_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 5:
            std::cout<<"Quick sort:\n";
            t=Clock(Quick_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 6:
            std::cout<<"Heap sort:\n";
            t=Clock(Heap_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 7:
            std::cout<<"Merge sort:\n";
            t=Clock(Merge_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 8:
            std::cout<<"Radix sort:\n";
            t=Clock(Radix_Sort,L1);
            Print_List(L1);
            std::cout<<"Time:"<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        case 9:
            std::cout<<"Input the number of the original list:";
            std::cin>>MAX;
            Init_List(L,MAX);
            Create_Random_List(L);
            List_Copy(L,L1);
            std::cout<<"Successfully!\n";
            break;
        case 10:
            return 0;
        case 11:
            std::cout<<"Selection sort:";
            t=Clock(Selection_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            std::cout<<"Bubble sort:";
            t=Clock(Bubble_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            std::cout<<"Insert sort:";
            t=Clock(Insert_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            std::cout<<"Shell sort:";
            t=Clock(Shell_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            std::cout<<"Quick sort:";
            t=Clock(Quick_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            std::cout<<"Heap sort:";
            t=Clock(Heap_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            std::cout<<"Merge sort:";
            t=Clock(Merge_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            std::cout<<"Radix sort:";
            t=Clock(Radix_Sort,L1);
            std::cout<<t<<"ms\n";
            List_Copy(L,L1);
            break;
        default:
            std::cout<<"Please input index 1~9\n";
            break;
        }

    }
}
