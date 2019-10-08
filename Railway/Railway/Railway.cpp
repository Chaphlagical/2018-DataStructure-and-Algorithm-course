#include "Railway.h"

int char2int(char c){
    return (int)(c-48);
}

int str2int(std::string str){
    int a=0;
    for(unsigned int i=0;i<str.length();i++){
        a+=char2int(str.data()[i])*pow(10,str.length()-i-1);
    }
    return a;
}

void Create_Graph(int **G){
    for(int i=0;i<MAXSIZE;i++)
        G[i]=new int[MAXSIZE];
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++){
            if(i==j)
                G[i][j]=0;
            else
                G[i][j]=INF;
        }
    std::ifstream file_in;
    std::string str[3]={"","",""};
    int counting=0;
    char buf;
    file_in.open("railway/dist.txt",std::ios::in);
    while(file_in>>std::noskipws>>buf){
        if(buf==' ')
            counting++;
        else if(buf=='\n'||buf=='\r'){
            G[str2int(str[0])][str2int(str[1])]=str2int(str[2]);
            G[str2int(str[1])][str2int(str[0])]=str2int(str[2]);
            //std::cout<<str2int(str[0].data())<<" "<<str2int(str[1].data())<<" "<<str2int(str[2].data())<<std::endl;
            counting=0;
            str[0]=str[1]=str[2]="";
        }
        else
            str[counting]+=buf;
    }
    file_in.close();
}

void Reset(railway&R){
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++)
            R.D[i][j]=R.G[i][j];
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++){
            if(R.G[i][j]!=-1)
                R.path[i][j]=R.city[i]+" → "+R.city[j];
            else
                R.path[i][j]="None";
        }
}

void Path_Init(railway R){
    for(int i=0;i<MAXSIZE;i++)
        R.path[i]=new std::string[MAXSIZE];
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++){
            if(R.G[i][j]!=-1)
                R.path[i][j]=R.city[i]+" → "+R.city[j];
            else
                R.path[i][j]="None";
        }
}

std::string get_tail(std::string s){
    std::string s1="";
    unsigned int flag;
    for(flag=0;flag<s.length();flag++){
        if(s[flag]==' ')
            break;
    }
    for(unsigned int i=flag;i<s.length();i++){
        s1+=s[i];
    }
    return s1;
}

void Floyd(railway&R){
    for(int k=0;k<MAXSIZE;k++)
        for(int i=0;i<MAXSIZE;i++)
            for(int j=0;j<MAXSIZE;j++)
                if(R.D[i][j]>R.D[i][k]+R.D[k][j]&&R.D[i][j]!=-1&&R.D[i][k]!=-1&&R.D[k][j]!=-1){
                    R.D[i][j]=R.D[i][k]+R.D[k][j];
                    R.path[i][j]=R.path[i][k]+get_tail(R.path[k][j]);
                }
}

void Get_city(railway&R){
    std::ifstream file_in;
    int index=0;
    char buf;
    file_in.open("railway/city.txt",std::ios::in);
    for(int i=0;i<MAXSIZE;i++)
        R.city[i]="";
    while(file_in>>std::noskipws>>buf){
        if(buf=='\n')
            index++;
        else if((buf<'0'||buf>'9')&&buf!=' '&&buf!='\r'){
            R.city[index]+=buf;
        }
    }
    file_in.close();
}

bool Delete_City(railway&R,std::string city){
    int x;
    for(x=0;x<MAXSIZE;x++)
        if(R.city[x]==city)
            break;
    if(x==MAXSIZE&&R.city[x]!=city){
        std::cout<<"Couldn't find "<<city<<std::endl;
        return false;
    }
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++)
            if(i==x||j==x)
                R.G[i][j]=-1;
    return true;
}

int Get_index(railway R,std::string city){
    for(int i=0;i<MAXSIZE;i++)
        if(R.city[i]==city&&R.G[i][i]!=-1)
            return i;
    return -1;
}
