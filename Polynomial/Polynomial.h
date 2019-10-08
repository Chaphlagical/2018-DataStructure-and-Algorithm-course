#ifndef __POLYNOMIAL_H
#define __POLYNOMIAL_H

#include <iostream>
#include<cmath>

typedef struct Node {//Link list with head node
	float coef;//Polynomial Coefficient
	float expo;//Polynomial Exponent
	struct Node*next;
}Node, *Poly;

void Poly_Init(Poly&P);//Initialize Polynomial
void Poly_Print(Poly&P);//Print Polynomial
void Poly_Clear(Poly&P);//CLear Polynomial
void Poly_Destroy(Poly&P);//Destroy Polynomial
void Poly_Add(Poly&P, Poly&Q,Poly&R);//Polynomial Addition
void Poly_Minus(Poly&P, Poly&Q, Poly&R);//Polynomial Subtraction
void Poly_Copy(Poly&P, Poly&Q);//Copy Polynomials
void Poly_Mutiply(Poly&P, Poly&Q, Poly&R);//Polynomials multiplication
void Poly_MutiplyNum(Poly&P,float num,Poly&Q);//Polynomials multiply a number
void Poly_Power(Poly&P,int n, Poly&R);//Polynomial involution
void Poly_Calculate(Poly&P, float a, float&sum);//Calculate the value of polynomial
void Poly_Derivative(Poly&P, int n, Poly&R);//Polynomial derivation
bool Poly_Division(Poly&P, Poly&Q, Poly&Quo, Poly&Re);//Polynomial division
void Poly_indefinite_integral(Poly&P, int n, Poly&R);//Polynomial indefinite integral with C=0
void Poly_definite_integral(Poly&P, float a, float b, float&sum);//Polynomial definite integral
void Poly_GCD(Poly&P,Poly&Q,Poly&R);//Greatest common divisor
void Poly_LCM(Poly&P,Poly&Q,Poly&R);//Least Common Multiple
void Poly_Normalize(Poly&P);
#endif
