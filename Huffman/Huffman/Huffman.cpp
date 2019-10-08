#include "Huffman.h"

void Tree_Init(Node*T){
    for(int i=0;i<NodeNum*2-1;i++){
        if(i<NodeNum){
            T[i].data=i;
            T[i].weight=0;
        }
        else{
            T[i].data=128;
            T[i].weight=0;
        }
        T[i].lchild=T[i].rchild=T[i].parent=-1;
    }
}

void Count(Node*T){
    std::ifstream file;
    file.open(Target_File,std::ios::in);
    char buf;
    int a=0;
    while(!file.eof()){
        file.get(buf);
        T[(int)buf].weight++;
        if(a<(int)buf)
            a=(int)buf;
    }
    file.close();
}

void Huffman(Node*T){
    int L=0,R=0;
    int flag=NodeNum;
    while(flag<NodeNum*2-1){
        for(int i=0;i<flag;i++)
            if(T[i].parent==-1){
                R=L=i;
                break;
            }
        for(int i=0;i<flag;i++)
            if(T[L].weight>=T[i].weight&&T[i].parent==-1){
                R=L;
                L=i;
            }
        if(R==L){
            for(int i=0;i<flag;i++)
                if(i!=L&&T[i].parent==-1)
                    R=i;
            for(int i=0;i<flag;i++)
                if(T[R].weight>=T[i].weight&&T[i].parent==-1&&i!=L)
                    R=i;
        }
        T[flag].weight=T[L].weight+T[R].weight;
        T[flag].lchild=L;T[flag].rchild=R;
        T[L].parent=flag;
        T[R].parent=flag;
        flag++;
    }
}


void Create_Dict(Node*T,int t,std::string code){
    if((int)T[t].data!=(int)T[NodeNum*2-2].data){
        T[t].code=code;
        return;
    }
    else{
        Create_Dict(T,T[t].lchild,code+"0");
        Create_Dict(T,T[t].rchild,code+"1");
    }
}

int char2int(char c){
    return (int)c-48;
}

void str2uchar(unsigned char&c,std::string str){
    c=(unsigned char)(128*char2int(str[0])+64*char2int(str[1])+32*char2int(str[2])+16*char2int(str[3])+8*char2int(str[4])+4*char2int(str[5])+2*char2int(str[6])+char2int(str[7]));
}

int Encode(Node*T){
    std::ifstream file_in;
    std::ofstream file_out;
    char buf;
    unsigned char c=0;
    std::string str;
    int flag=0;
    int sum=0;
    file_in.open(Target_File,std::ios::in);
    file_out.open("stdio_encode_temp.txt",std::ios::out);
    while(file_in>>std::noskipws>>buf ){
        file_out<<T[(int)buf].code;
        sum+=T[(int)buf].code.length();
    }
    file_in.close();
    file_out.close();
    file_in.open("stdio_encode_temp.txt",std::ios::in);
    file_out.open("stdio_encode",std::ios::out);
    while(file_in>>std::noskipws>>buf ){
            flag++;
            str+=buf;
            if(flag==8){
                str2uchar(c,str);
                file_out<<c;
                str="";
                flag=0;
            }
    }

        for(int i=0;i<8-flag;i++)
            str+='0';
        str2uchar(c,str);
        file_out<<c;
        file_in.close();
        file_out.close();
        remove("stdio_encode_temp.txt");
        return sum;
    }



void uchar2str(char c,std::string&str){
        str="";
        str=(char)((c&128)/128+48);
        str+=(char)((c&64)/64+48);
        str+=(char)((c&32)/32+48);
        str+=(char)((c&16)/16+48);
        str+=(char)((c&8)/8+48);
        str+=(char)((c&4)/4+48);
        str+=(char)((c&2)/2+48);
        str+=(char)((c&1)+48);
}

void Decode(Node*T,int sum){
    std::ifstream file_in;
    std::ofstream file_out;
    int t=NodeNum*2-2;
    int counting=0;
    char buf;
    std::string str;
    file_in.open("stdio_encode",std::ios::in);
    file_out.open("stdio_decode_temp.txt",std::ios::out);
    while(file_in>>std::noskipws>>buf ){
            uchar2str(buf,str);
            for(int i=0;i<str.length()&&counting<sum;i++){
                file_out<<str.data()[i];
                counting++;
            }
    }
    file_in.close();
    file_out.close();
    file_in.open("stdio_decode_temp.txt",std::ios::in);
    file_out.open("stdio_decode.txt",std::ios::out);
    while(file_in>>std::noskipws>>buf ){
            if(buf=='0')
                t=T[t].lchild;
            else if(buf=='1')
                t=T[t].rchild;
            if((int)T[t].data!=(int)T[NodeNum*2-2].data){
                file_out<<T[t].data;
                t=NodeNum*2-2;
            }

    }
    file_in.close();
    file_out.close();
    remove("stdio_decode_temp.txt");

}

void Print_Tree(Node*T){
    std::ofstream file_out;
    file_out.open("Tree.txt",std::ios::out);
    for(int i=0;i<NodeNum*2-1;i++){
        std::cout<<i<<"  data="<<T[i].data<<"  code="<<T[i].code<<"  lchild="<<T[i].lchild<<"  rchild="<<T[i].rchild<<"  weight="<<T[i].weight<<"  parent="<<T[i].parent<<std::endl;
        file_out<<i<<" "<<T[i].code<<std::endl;
    }

    file_out.close();

}

void Print_Compress_Ratio(){
    std::ifstream file1;
    std::ifstream file2;
    char buf;
    float Ratio,sum1,sum2;
    file1.open("stdio.h",std::ios::in);
    file2.open("stdio_encode",std::ios::in);
    while(file1>>std::noskipws>>buf ){
        sum1++;
    }
    while(file2>>std::noskipws>>buf ){
        sum2++;
    }
    Ratio=sum1/sum2;
    std::cout<<"Compression Ratio:"<<Ratio<<std::endl;
}


