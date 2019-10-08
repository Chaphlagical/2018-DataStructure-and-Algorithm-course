#include "TSP.h"

int random_num(int a){
    return (rand() % (a));
}

void Create_Graph(Graph&G,int n){
    srand((unsigned)time(NULL));
    G.G=new int*[n];
    G.s=new int[n];
    G.v=new int[n];
    G.path=new int[n];
    G.num=n;
    for(int i=0;i<n;i++){
        G.G[i]=new int[n];
        G.s[i]=G.v[i]=G.path[i]=-1;
    }
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++){
            if(i==j)
                G.G[i][j]=0;
            else
                G.G[j][i]=G.G[i][j]=random_num(n*n*10)+1;
        }
}

void Graph_Reset(Graph&G){
    for(int i=0;i<G.num;i++){
        G.s[i]=-1;
        G.v[i]=-1;
        G.path[i]=-1;
    }
}

void Print_Graph(Graph G){
    for(int i=0;i<G.num;i++){
        for(int j=0;j<G.num;j++)
            std::cout<<G.G[i][j]<<"     ";
        std::cout<<"\n";
    }
}

void Print_Path(Graph G){
    std::cout<<"Path: "<<G.path[0];
    for(int i=1;i<G.num;i++)
        std::cout<<" → "<<G.path[i];
    std::cout<<" → "<<G.path[0]<<std::endl;
    std::cout<<"Distance: "<<G.distance<<std::endl;
}

void Get_Distance(Graph&G){
    G.distance=0;
    for(int i=1;i<G.num;i++){
        G.distance+=G.G[G.path[i-1]][G.path[i]];
        //std::cout<<G.path[i-1]<<" "<<G.path[i]<<" "<<G.G[G.path[i-1]][G.path[i]]<<std::endl;
    }
    G.distance+=G.G[G.path[G.num-1]][G.path[0]];
}

void Swap(int&a,int&b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

void Simple_Greedy(Graph&G){
    Graph_Reset(G);
    for(int i=0;i<G.num;i++)
        G.path[i]=-1;
    int MIN=G.num*G.num*100,index=0;
    int i=0,k=0;
    G.path[0]=0;
    G.v[0]=1;
    while(G.path[G.num-1]==-1){
        MIN=G.num*G.num*100;
        for(int j=0;j<G.num;j++){
            if(MIN>G.G[i][j]&&i!=j&&G.v[j]==-1){
                index=j;
                MIN=G.G[i][j];
            }
        }
        G.path[++k]=index;
        G.v[index]=1;
        i=index;
    }
    Get_Distance(G);
    Print_Path(G);
}

void permutation(Graph &G,int*a,int k){
	int j,sum=0;
	if(k==G.num){
        for(int k=1;k<G.num;k++)
            sum+=G.G[a[k-1]][a[k]];
        sum+=G.G[a[G.num-1]][a[0]];
        if(sum<G.distance){
            for(int k=0;k<G.num;k++)
                G.path[k]=a[k];
            G.distance=sum;
        }
	}
	else{
		for(j=k;j<G.num;j++){
			Swap(a[j],a[k]);
			permutation(G,a,k+1);
			Swap(a[j],a[k]);
		}
	}
}

void Enumerate(Graph&G){
    Graph_Reset(G);
    for(int i=0;i<G.num;i++)
        G.path[i]=-1;
    int*T=new int[G.num];
    for(int i=0;i<G.num;i++){
        T[i]=i;
        G.path[i]=i;
    }
    permutation(G,T,1);
    Get_Distance(G);
    Print_Path(G);
}

int Path_Length(Graph G){
    int len=0;
    for(int i=0;i<G.num;i++){
        if(G.path[i]==-1)
            return len;
        len++;
    }
    return len;
}

void Path_Insert(Graph&G,int p,int city){
    for(int i=Path_Length(G);i>p+1;i--){
        G.path[i]=G.path[i-1];
    }
    G.path[p+1]=city;
}

void Micro_Recursive(Graph&G,int index){
    if(index==G.num)
        return;
    else{
        int p=0,MIN=G.G[0][index]+G.G[index][1]-G.G[0][1];
        for(int i=0;i<Path_Length(G)-1;i++){
            if(MIN>=G.G[i][index]+G.G[index][i+1]-G.G[i][i+1]){
                MIN=G.G[i][index]+G.G[index][i+1]-G.G[i][i+1];
                p=i;
            }
        }
        if(MIN>=G.G[Path_Length(G)-1][index]+G.G[index][0]-G.G[Path_Length(G)-1][0])
            p=Path_Length(G)-1;
        Path_Insert(G,p,index);
        Micro_Recursive(G,index+1);
    }
}


void Recursive(Graph&G){
    Graph_Reset(G);
    for(int i=0;i<G.num;i++)
        G.path[i]=-1;
    G.path[0]=0;G.path[1]=1;
    Micro_Recursive(G,2);
    Get_Distance(G);
    Print_Path(G);
}

int fvalue(Graph G,int n,int v,int MIN){
    int g=0;
    for (int i=0;i<n;i++)
        g+=G.G[G.path[i]][G.path[i+1]];
    g+=G.G[G.path[n-1]][v];
    int h=MIN*(G.num-n-1);
    return h+g;
}

void A_star(Graph&G){
    Graph_Reset(G);
    G.path[0]=0;
    G.v[0]=0;
    int v=0;
    int MIN=0;
    int F=100000000;
    for(int i=1;i<G.num;i++){

        for(int j=1;j<G.num;j++){
            //std::cout<<i<<" "<<j<<" "<<G.v[j]<<" "<<MIN<<" "<<fvalue(G,i,j,MIN)<<std::endl;
            if(G.v[j]==-1){
                if (F > fvalue(G,i,j,MIN)){
                    F=fvalue(G,i,j,MIN);
                    v=j;
                    //std::cout<<v<<std::endl;
                }
            }
        }
        G.path[i]=v;
        G.v[v]=1;
        MIN=0;
        F=100000000;
        for (int k=0;G.path[k+1]!=-1&&k+1<G.num;k++)
            MIN+=G.G[G.path[k]][G.path[k+1]];
    }
    Get_Distance(G);
    Print_Path(G);
}

