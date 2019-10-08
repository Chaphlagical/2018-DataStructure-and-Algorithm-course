#include "Railway.h"


int main(){
    railway R={new int*[MAXSIZE],new int*[MAXSIZE],new std::string[MAXSIZE],new std::string*[MAXSIZE]};
    int index;
    std::string A,B;
    Get_city(R);
    Create_Graph(R.G);
    Create_Graph(R.D);
    Path_Init(R);
    Floyd(R);
    while(true){
        std::cout<<std::endl;
        std::cout<<"1. Get shortest path"<<std::endl;
        std::cout<<"2. Delete city"<<std::endl;
        std::cout<<"3. Quit"<<std::endl;
        std::cout<<"Input index to select operation: ";
        std::cin>>index;
        switch(index){
        case 1:
            std::cout<<"Input two cities:";
            std::cin>>A;
            std::cin>>B;
            if(Get_index(R,A)!=-1&&Get_index(R,B)!=-1){
                if(R.D[Get_index(R,A)][Get_index(R,B)]==INF)
                    std::cout<<"There is no way to go from "<<A<<" to "<<B<<std::endl;
                else{
                    std::cout<<"Path:"<<R.path[Get_index(R,A)][Get_index(R,B)]<<std::endl;
                    std::cout<<"Distance:"<<R.D[Get_index(R,A)][Get_index(R,B)]<<std::endl;
                }
            }
            else{
                if(Get_index(R,A)==-1)
                    std::cout<<"Couldn't find "<<A<<"!  ";
                if(Get_index(R,B)==-1)
                    std::cout<<"Couldn't find "<<B<<"!  ";
                std::cout<<std::endl;
            }
            break;
        case 2:
            std::cout<<"Input the city you want to delete:";
            std::cin>>A;
            if(!Delete_City(R,A))
                break;
            else{
                Reset(R);
                Floyd(R);
                std::cout<<"Delete successfully!"<<std::endl;
            }
            break;
        case 3:
            std::cout<<"Goodbye!"<<std::endl;
            return 1;
        default:
            break;
        }
    }
}
