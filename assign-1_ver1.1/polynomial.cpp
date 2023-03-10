#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	// ToDo
	int i;
	capacity = source.capacity;
	terms = source.terms;

	termArray = new Term[capacity];

	for(i=0;i<terms;i++){
		termArray[i].coef = source.termArray[i].coef;
		termArray[i].exp = source.termArray[i].exp;
	}
	for(i=terms;i<capacity;i++){
		termArray[i].coef = 0;
		termArray[i].exp = 0;
	}
}	

// Destructor
Polynomial::~Polynomial()
{
	// ToDo
	for(int i=0;i<capacity;i++){
		termArray[i].coef = 0;
		termArray[i].exp = 0;
	}
	delete[] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
	int i;

	delete[] termArray;
	capacity = source.capacity;
	terms = source.terms;
	termArray = new Term[capacity];
	
	for(i=0;i<terms;i++){
		termArray[i].coef = source.termArray[i].coef;
		termArray[i].exp = source.termArray[i].exp;
	}
	for(i=terms;i<capacity;i++){
		termArray[i].coef = 0;
		termArray[i].exp = 0;
	}

	return *this;
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
	Polynomial c;

	int leftp = 0, rightp = 0;
	float leftcoef, rightcoef;
	int leftexp, rightexp;

	while( (leftp < terms) && (rightp < source.terms) )
	{
		leftcoef = termArray[leftp].coef;
		leftexp = termArray[leftp].exp;
		rightcoef = source.termArray[rightp].coef;
		rightexp = source.termArray[rightp].exp;
		
		if(leftexp == rightexp){
			c.CreateTerm(leftcoef + rightcoef, leftexp);
			leftp++; rightp++;
		}
		else if(leftexp > rightexp){
			c.CreateTerm(leftcoef, leftexp);
			leftp++;
		}
		else if(leftexp < rightexp){
			c.CreateTerm(rightcoef, rightexp);
			rightp++;
		}
	}
	
	while(leftp < terms){
		c.CreateTerm(termArray[leftp].coef, termArray[leftp].exp);
		leftp++;
	}
	while(rightp < source.terms){
		c.CreateTerm(source.termArray[rightp].coef, source.termArray[rightp].exp);
		rightp++;
	}

	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;

	int leftp = 0, rightp = 0, cp = 0;
	float leftcoef, rightcoef;
	int leftexp, rightexp;

	while( (leftp < terms) && (rightp < source.terms) )
	{
		leftcoef = termArray[leftp].coef;
		leftexp = termArray[leftp].exp;
		rightcoef = source.termArray[rightp].coef;
		rightexp = source.termArray[rightp].exp;
		
		if(leftexp == rightexp){
			c.CreateTerm(leftcoef - rightcoef, leftexp);
			leftp++; rightp++;
		}
		else if(leftexp > rightexp){
			c.CreateTerm(leftcoef, leftexp);
			leftp++;
		}
		else if(leftexp < rightexp){
			c.CreateTerm(-rightcoef, rightexp);
			rightp++;
		}
	}
	
	while(leftp < terms){
		c.CreateTerm(termArray[leftp].coef, termArray[leftp].exp);
		leftp++;
	}
	while(rightp < source.terms){
		c.CreateTerm(-source.termArray[rightp].coef, source.termArray[rightp].exp);
		rightp++;
	}

	return c;
	
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;
	int i, j, l;

	int exp, coef;
	bool check;
	for(i=0;i<terms;i++){
		for(j=0;j<source.terms;j++){
			exp = termArray[i].exp + source.termArray[j].exp;
			coef = termArray[i].coef * source.termArray[j].coef;
			check = true;

			for(l=0;l<c.terms;l++){
				if(c.termArray[l].exp == exp){
					c.termArray[l].coef = coef + c.termArray[l].coef;
					check = false;
					break;
				}
			}

			if(check == true){
				c.CreateTerm(coef, exp);
			}
		}
	}	

	return c;	
}

bool Polynomial::operator == (const Polynomial& right)
{
	bool ret;
	ret = true;
	
	if(terms == right.terms){
		for(int i=0;i<terms;i++){
			if(termArray[i].exp != right.termArray[i].exp || termArray[i].coef != right.termArray[i].coef){
				ret = false;
				break;
			}
		}
	}
	else{
		ret = false;
	}
	
	return ret;
}

float Polynomial::Eval(float x)
{
	float ret = 0;
	
	for(int i=0;i<terms;i++){
		ret += termArray[i].coef * pow(x, termArray[i].exp);
	}
	
	return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;
	
	int i;
	for(i=0;i<terms;i++){
		c.CreateTerm(termArray[i].coef * termArray[i].exp, termArray[i].exp -1);
	}
	
	return c;
}

void Polynomial::CreateTerm(const float coef, const int exp)
{
	// ToDo
	if(exp < 0) return;
	
	if(terms == capacity){
		Term *t;
		capacity *= 2;
		t = new Term[capacity];
		
		int i;
		for(i=0;i<terms;i++){
			t[i].coef = termArray[i].coef;
			t[i].exp = termArray[i].exp;
		}

		delete[] termArray;
		termArray = t;
	}

	int p=0;
	while(p < terms)
	{
		if(termArray[p].exp == exp){
			if(coef == 0){
				terms--;
				for(int i = p; i < terms; i++){
					termArray[i].coef = termArray[i+1].coef;
					termArray[i].exp = termArray[i+1].exp;
				}
				termArray[terms+1].coef = 0;
				termArray[terms+1].exp = 0;
				return;
			}
			
			termArray[p].coef = coef;
			return;
		}
		else if(termArray[p].exp < exp){
			if(coef == 0) return;
			for(int i = terms++; i > p; i--){
				termArray[i].coef = termArray[i-1].coef;
				termArray[i].exp = termArray[i-1].exp;
			}

			termArray[p].coef = coef;
			termArray[p].exp = exp;
			return;
		}
		p++;
	}

	if(coef != 0){
		termArray[p].coef = coef;
		termArray[p].exp = exp;
		terms++;
	}
}