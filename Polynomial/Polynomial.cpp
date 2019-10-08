#include"Polynomial.h"

void Poly_Init(Poly&P) {//Initialize Polynomial
	P = new Node;
	P->expo = -1;
	P->coef = 0;
	P->next = NULL;
}

void Poly_Print(Poly&P) {//Print Polynomial
	Node*p=P->next;
	if (!p){
        std::cout<<"0";
        return;
	}
	if (!(p->expo)) {
		std::cout << p->coef;
		if (p->next!=NULL) {
			p = p->next;
		}
		else {
            return;
		}
	}
	else {
		std::cout << p->coef << "*x^" << p->expo;
		p = p->next;
	}
	while (p) {
		if(p->coef>0)
			std::cout << '+' << p->coef << "*x^" << p->expo;
		else if(p->coef<0)
			std::cout << p->coef << "*x^" << p->expo;
		p = p->next;
	}
}

void Poly_Clear(Poly&P) {//CLear Polynomial
	Node*p=P->next;
	if (!p)return;
	Node*q = p->next;
	while (q) {
		delete p;
		p = q;
		q = q->next;
	}
	P->next = NULL;
}

void Poly_Destroy(Poly&P){
    if(!P)return;
    Poly_Clear(P);
    delete P;
}

void Poly_Copy(Poly&P, Poly&Q) {//Copy Polynomials
	Node*p,*q,*temp;
	Poly_Clear(Q);
	p = P; q = Q;
	while (p->next) {
		temp = new Node;
		*temp = *p->next;
		temp->next=NULL;
		q->next = temp;
		q = q->next;
		p = p->next;
	}
}

void Poly_Add(Poly&P, Poly&Q, Poly&R) {//Polynomial Addition P+Q=R
	Node*p, *q, *r,*temp=NULL;
	Poly Rt;
	Poly_Init(Rt);
	p = P->next; q = Q->next; r = Rt;
	while (p&&q) {
		if (p->expo > q->expo) {
			temp = new Node;
			*temp = *q;
			temp->next=NULL;
			r->next = temp;
			r = r->next;
			q = q->next;
		}
		else if (p->expo < q->expo) {
			temp = new Node;
			*temp = *p;
			temp->next=NULL;
			r->next = temp;
			r = r->next;
			p = p->next;
		}
		else {
			float sum = p->coef + q->coef;
			if (fabs(sum) > 1e-9) {
				temp = new Node;
				*temp = *p;
				r->next = temp;
				r = r->next;
				r->coef = sum;
			}
			p = p->next; q = q->next;
		}
	}
	if (q) {
		while (q) {
			if (q->coef) {
				temp = new Node;
				*temp = *q;
				r->next = temp;
				r = r->next;
			}
			q = q->next;
		}
	}
	if (p) {
		while (p) {
			if (p->coef) {
				temp = new Node;
				*temp = *p;
				r->next = temp;
				r = r->next;
			}
			p = p->next;
		}
	}
	Poly_Clear(R);
	R=Rt;
}

void Poly_Minus(Poly&P, Poly&Q, Poly&R) {//Polynomial Subtraction P-Q=R
	Node*p, *q, *r,*temp = NULL;
	Poly Rt;
	Poly_Init(Rt);
	p = P->next; q = Q->next; r = Rt;
	while (p&&q) {
        if (p->expo > q->expo) {
			temp = new Node;
			*temp = *q;
            temp->next=NULL;
			r->next = temp;
			r = r->next;
			r->coef = 0 - r->coef;
			q = q->next;
		}
		else if (p->expo < q->expo) {
			temp = new Node;
			*temp = *p;
			temp->next=NULL;
			r->next = temp;
			r = r->next;
			p = p->next;
		}
		else {
			float sum = p->coef - q->coef;
			if (fabs(sum) > 1e-9) {
				temp = new Node;
				*temp = *p;
				temp->next=NULL;
				r->next = temp;
				r = r->next;
				r->coef = sum;
			}

			p = p->next; q = q->next;
		}

	}
	if (p) {
		while (p) {
			temp = new Node;
			*temp = *p;
			r->next = temp;
			r = r->next;
			p = p->next;
		}
	}
	if (q) {
		while (q) {
			temp = new Node;
			*temp = *q;
			r->next = temp;
			r = r->next;
			r->coef = 0 - r->coef;
			q = q->next;
		}
	}
	Poly_Clear(R);
	R=Rt;
}

void Poly_Mutiply(Poly&P, Poly&Q, Poly&R) {//Polynomials multiplication P*Q=R
	Node*p, *q, *temp, *r1, *r2, *r3, *h, *e;
	Poly Rt;
	Poly_Init(Rt);
	p = P; r1 = p->next;
	q = Q; r2 = q->next;
	while (r1) {
		Poly_Init(h);
		r3 = h;
		Poly_Init(e);
		while (r2) {
			temp = new Node;
			temp->coef = r1->coef*r2->coef;
			temp->expo = r1->expo + r2->expo;
			r3->next = temp;
			r3 = r3->next;
			r2 = r2->next;
		}
		r3->next = NULL;
		r1 = r1->next;
		r2 = Q->next;
		Poly_Add(Rt, h, e);
		Poly_Clear(h);
		Poly_Clear(Rt);
		Rt = e;
	}
	Poly_Clear(R);
	R=Rt;
}

void Poly_Power(Poly&P, int n, Poly&R) {//Polynomial involution R=P^n
	Poly Q, Rt;
	Q = P;
	Poly_Init(Rt);
	if (!n) {
		Node*temp = new Node;
		temp->expo = 0;
		temp->coef = 1;
		temp->next = NULL;
		Rt->next = temp;
	}
	else if (n == 1)Rt = P;
	for (int i = 0; i < n-1; i++) {
		Poly_Init(Rt);
		Poly_Mutiply(P, Q, Rt);
		Q = Rt;
	}
	Poly_Clear(R);
	R=Rt;
}

void Poly_Calculate(Poly&P, float a,float&sum) {//Calculate the value of polynomial P(x=a)
	Node*p = P->next;
	sum = 0;
	while (p) {
		sum += p->coef*pow(a, p->expo);
		p = p->next;
	}
}

void Poly_Derivative(Poly&P, int n,Poly&R) {//Polynomial derivation
	Node*p,*r;
	Poly Rt;
	Poly_Init(Rt);
	p = P; r = Rt;
	while (p) {
		if (n <= p->expo) {
			Node*temp = new Node;
			float expo = p->expo;
			temp->expo = p->expo - n;
			temp->coef = p->coef;
			for (int i = 0; i < n; i++) {
				temp->coef *= expo;
				expo--;
			}
			r->next = temp; r = r->next;
		}
		p = p->next;
	}
	r->next = NULL;
	Poly_Clear(R);
	R=Rt;
}

Node*Poly_Max(Poly&P) {
	Node*p = P;
	while (p->next)
		p = p->next;
	return p;
}

Node*Poly_Min(Poly&P) {
	Node*p = P->next;
	int min=0;
	while (p){
        if(p->expo<=min){
            min=p->expo;
        }
        p=p->next;
	}
	return p;
}

void Poly_MutiplyNum(Poly&P,float num,Poly&Q) {//
	Node*q=Q;
	Poly_Copy(P, Q);
	while (q->next) {
		q->coef *= num;
		q = q->next;
	}
}

bool Poly_Division(Poly&P, Poly&Q, Poly&Quo, Poly&Re) {
    Node*Max_P,*Max_Q,*temp;
    Poly tpoly;
    Poly_Init(tpoly);
    Poly_Clear(Quo);
    Poly_Clear(Re);
    Poly_Init(Quo);
    Poly_Init(Re);
    Poly_Copy(P,Re);
    Max_P=Poly_Max(Re);
    Max_Q=Poly_Max(Q);
    if(!Q->next){
        return false;
	}
    while(Max_P->expo>=Max_Q->expo){
        temp=new Node;
        temp->coef=Max_P->coef/Max_Q->coef;
        temp->expo=Max_P->expo-Max_Q->expo;
        temp->next=NULL;
        tpoly->next=temp;
        Poly_Add(Quo,tpoly,Quo);
        Poly_Mutiply(tpoly,Q,tpoly);
        Poly_Minus(Re,tpoly,Re);
        Poly_Clear(tpoly);
        delete temp;
        Max_P=Poly_Max(Re);
    }
    return true;
}

void Poly_indefinite_integral(Poly&P, int n, Poly&R){
    Node*p,*r;
	p = P; r = R;
	while (p) {
		if (n <= p->expo+1) {
			Node*temp = new Node;
			float expo = p->expo;
			temp->expo = p->expo + n;
			temp->coef = p->coef;
			for (int i = 0; i < n; i++) {
				temp->coef /= expo+1;
				expo++;
			}
			r->next = temp; r = r->next;
		}
		p = p->next;
	}
	r->next = NULL;
}

void Poly_definite_integral(Poly&P, float a, float b, float&sum){
    float sum1,sum2;
    Poly Q;
    Poly_Init(Q);
    Poly_indefinite_integral(P,1,Q);
    Poly_Calculate(Q,a,sum1);
    Poly_Calculate(Q,b,sum2);
    sum=sum2-sum1;
}

void Poly_GCD(Poly&P,Poly&Q,Poly&R){
    Poly_Clear(R);
    Poly Re,Quo,Qt,Ret;
    Poly_Init(Re);
    Poly_Init(Quo);
    Poly_Init(Qt);
    Poly_Init(Ret);
    if(Poly_Max(P)->expo>Poly_Max(Q)->expo){
        Poly_Division(P,Q,Quo,Re);
        if(!Re->next){
            Poly_Copy(Q,R);
            return;
        }
        Poly_Copy(Q,Qt);
    }
    else {
        Poly_Division(Q,P,Quo,Re);
        if(!Re->next){
            Poly_Copy(P,R);
            return;
        }
        Poly_Copy(P,Qt);
    }
    Poly_Copy(Re,Ret);
    while(Re->next){
        Poly_Division(Qt,Ret,Quo,Re);
        Poly_Copy(Ret,Qt);
        Poly_Copy(Re,Ret);
    }

    Poly_Copy(Qt,R);
    Poly_Destroy(Qt);
    Poly_Destroy(Ret);
    Poly_Destroy(Quo);
    Poly_Destroy(Re);

}



void Poly_LCM(Poly&P,Poly&Q,Poly&R){
    Poly Re,Quo,GCD;
    Poly_Init(Re);
    Poly_Init(Quo);
    Poly_Init(GCD);
    Poly_GCD(P,Q,GCD);
    Poly_Mutiply(P,Q,Quo);
    Poly_Division(Quo,GCD,R,Re);
    Poly_Destroy(GCD);
    Poly_Destroy(Re);
    Poly_Destroy(Quo);
}

bool Normal(Poly P){
    Node*p;
    p=P->next;
    while(p){
        if(p->expo>=p->next->expo)
            return true;
        p=p->next;
    }
    return false;

}

void Poly_Normalize(Poly&P){
    Node*p,*q;
    p=P->next;
    q=p->next;
    float a;
    int b;
    while(p->next){
        while(q){
            if(q->expo<p->expo){
                a=q->coef;b=q->expo;
                q->coef=p->coef;q->expo=p->expo;
                p->coef=a;p->expo=b;
            }
            q=q->next;
        }

        p=p->next;
        q=p->next;
    }

}
