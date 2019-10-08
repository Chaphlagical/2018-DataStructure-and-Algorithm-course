#include <string.h>
#include <iostream>
#include "Polynomial.h"

int main() {
	Poly P,Q,R,Quo,Re;
	Node*p,*q,*temp;
	int index=0,n=0;
	float a=0,b=0,sum=0;
    Poly_Init(P);
    Poly_Init(Q);
    Poly_Init(R);
    Poly_Init(Quo);
    Poly_Init(Re);
    for(int i=0;i<70;i++)
        std::cout<<'*';
    std::cout<<std::endl;
    std::cout<<"(1) Input Polynomial P by order \"coefficient exponential...\" "<<std::endl;
    std::cout<<"(2) Input Polynomial Q by order \"coefficient exponential...\" "<<std::endl;
    std::cout<<"(3) Print P"<<std::endl;
    std::cout<<"(4) Print Q"<<std::endl;
    std::cout<<"(5) Polynomial Addition P+Q"<<std::endl;
    std::cout<<"(6) Polynomial Subtraction P-Q"<<std::endl;
    std::cout<<"(7) Polynomials multiplication P*Q"<<std::endl;
    std::cout<<"(8) Polynomial division P/Q"<<std::endl;
    std::cout<<"(9) Polynomial involution P^n"<<std::endl;
    std::cout<<"(10) Polynomial indefinite integral with C=0"<<std::endl;
    std::cout<<"(11) Polynomial definite integral from a to b"<<std::endl;
    std::cout<<"(12) Polynomial division d^nP/dx^n"<<std::endl;
    std::cout<<"(13) Calculate polynomial's greatest common divisor"<<std::endl;
    std::cout<<"(14) Calculate polynomial's least common multiple"<<std::endl;
    std::cout<<"(15) polynomial copy"<<std::endl;
    std::cout<<"(16) Quit"<<std::endl;
    for(int i=0;i<70;i++)
        std::cout<<'*';
    std::cout<<std::endl;
    while(true){
        p=P;q=Q;
        std::cout<<"Please input index to select your operation:"<<std::endl;
        std::cin>>index;
        switch (index){
            case 1:{
                std::cout<<"Input the number of item:";
                std::cin>>n;
                for(int i=0;i<n;i++){
                    temp=new Node;
                    std::cin>>temp->coef;
                    std::cin>>temp->expo;
                    temp->next=NULL;
                    p->next=temp;
                    p=p->next;
                }
                std::cout<<"P=";
                Poly_Normalize(P);
                Poly_Print(P);
                std::cout<<std::endl;
                break;
            }
            case 2:{
                std::cout<<"Input the number of item:";
                std::cin>>n;
                for(int i=0;i<n;i++){
                    temp=new Node;
                    std::cin>>temp->coef;
                    std::cin>>temp->expo;
                    temp->next=NULL;
                    q->next=temp;
                    q=q->next;
                }
                std::cout<<"Q=";
                Poly_Normalize(Q);
                Poly_Print(Q);
                std::cout<<std::endl;
                break;
            }
            case 3:{
                std::cout<<"P=";
                Poly_Print(P);
                std::cout<<std::endl;
                break;
            }
            case 4:{
                std::cout<<"Q=";
                Poly_Print(Q);
                std::cout<<std::endl;
                break;
            }
            case 5:{
                Poly_Add(P,Q,R);
                std::cout<<"P+Q=";
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 6:{
                std::cout<<"P-Q=";
                Poly_Minus(P,Q,R);
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 7:{
                std::cout<<"P*Q=";
                Poly_Mutiply(P,Q,R);
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 8:{
                if(Poly_Division(P,Q,Quo,Re)){
                    std::cout<<"P/Q=";
                    Poly_Print(Quo);
                    std::cout<<"..........";
                    Poly_Print(Re);
                    std::cout<<std::endl;
                }
                else std::cout<<"Error!"<<std::endl;
                break;
            }
            case 9:{
                std::cout<<"Input power:";
                std::cin>>n;
                Poly_Power(P,n,R);
                std::cout<<"P^n=";
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 10:{
                std::cout<<"Input times:";
                std::cin>>n;
                std::cout<<"∫P=";
                Poly_indefinite_integral(P,n,R);
                Poly_Print(R);
                std::cout<<"+C";
                std::cout<<std::endl;
                break;
            }
            case 11:{
                std::cout<<"Input a and b:";
                std::cin>>a>>b;
                std::cout<<"∫P(b-a)=";
                Poly_definite_integral(P,a,b,sum);
                std::cout<<sum;
                std::cout<<std::endl;
                break;
            }
            case 12:{
                std::cout<<"Input times:";
                std::cin>>n;
                std::cout<<"d^nP/dx^n=";
                Poly_Derivative(P,n,R);
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 13:{
                std::cout<<"GCD(P,Q)=";
                Poly_GCD(P,Q,R);
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 14:{
                std::cout<<"LCM(P,Q)=";
                Poly_LCM(P,Q,R);
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 15:{
                std::cout<<"Copy P to R,R=";
                Poly_Copy(P,R);
                Poly_Print(R);
                std::cout<<std::endl;
                break;
            }
            case 16:{
                std::cout<<"Quit!";
                return 0;
            }
            default:{
                std::cout<<"Please input number between 1~15"<<std::endl;
                break;
            }

        }
    }
}
