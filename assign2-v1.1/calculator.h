#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"


Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators

int Num_alloc(char a)
{
	if(a == '#') return -1;
	if(a == '(') return 0;
	if(a == '+' || a == '-') return 1;
	if(a == '*' || a == '/') return 2;
	if(a == ')') return 3;
}

bool Compare(char prev, char cur)
{
	int a, b;
	a = Num_alloc(prev);
	b = Num_alloc(cur);

	return (a < b);
}
//
// Modify Eval() below to evaluate the given expression
//
double Eval(char* in)
{
	double out = 0;
	
	char buf[1000]; // temp buffer
	char lastToken = '#';
	
	double operand;
	int i = 0, bi = 0;

	int n_opr = 0, n_opt = 0;
	bool check_negative = 0;

	opt.Push('#');
	
	while(in[i] != '\0')
	{
		char c = in[i];
		
		// Operators
		if(bi == 0 && c == '-' && (n_opr != n_opt+1)){
			check_negative = 1;
		}
		else if(c == '+' || c == '-' ||
			   c == '*' || c == '/' ||
			   c == '(' || c == ')')
		{
			if(bi > 0)
			{
				buf[bi++] = '\0';
				operand = atof(buf);				
				bi = 0;
				if(check_negative){
					operand *= -1;
					check_negative = 0;
				}
				
				// push operand
				std::cout << "New operand : " << operand << std::endl;
				opr.Push(operand);
				n_opr ++;
			}

			// push operator
			std::cout << "New operator : " << c << std::endl;
			char prev = opt.Top();
			opt.Push(c);
			if(c == '+' || c == '-' || c == '*' || c == '/'){
				n_opt++;
			}
			double a, b;
			while(1){
				if(c == lastToken) break;
				if(c == '('){
					break;
				}
				if(c == ')'){
					opt.Pop();
					while(opt.Top() != '('){
						a = opr.Top();
						opr.Pop();
						b = opr.Top();
						opr.Pop();

						if(opt.Top() == '+'){
							opr.Push(b + a);
						}
						else if(opt.Top() == '-'){
							opr.Push(b - a);
						}
						else if(opt.Top() == '*'){
							opr.Push(b * a);
						}
						else if(opt.Top() == '/'){
							opr.Push(b / a);
						}
						opt.Pop();

						n_opr--;
						n_opt--;
					}
					opt.Pop();
					break;
				}
				
				if( Compare( prev, c ) ) break; //이전 게 우선순위가 같거나 더 낮다면 ex) a + b * c
				
				else{
					opt.Pop();
					while( opt.Top() != lastToken && opt.Top() != '('){ // 어차피 c보다 우선순위가 다 낮을 거니까 쭉 계산 
						a = opr.Top();
						opr.Pop();
						b = opr.Top();
						opr.Pop();

						if(opt.Top() == '+'){
							opr.Push(b + a);
						}
						else if(opt.Top() == '-'){
							opr.Push(b - a);
						}
						else if(opt.Top() == '*'){
							opr.Push(b * a);
						}
						else if(opt.Top() == '/'){
							opr.Push(b / a);
						}

						n_opr--;
						n_opt--;
						opt.Pop();
					}
					opt.Push(c);
					break;
				}
			}
		}
		// Operands
		else if(c == '0' || c == '1' ||
				c == '2' || c == '3' ||
				c == '4' || c == '5' ||
				c == '6' || c == '7' ||
				c == '8' || c == '9' ||
				c == '.')
		{
			buf[bi++] = c;
		}
		else {}
	
		i++;
	}
	
	// push the very last operand if exists
	if(bi > 0)
	{
		buf[bi++] = '\0';
		operand = atof(buf);
		bi = 0;

		if(check_negative){
			operand *= -1;
			check_negative = 0;
		}

		// push operand
		std::cout << "New operand : " << operand << std::endl;
		opr.Push(operand);
	}
	double a, b;

	while( opt.Top() != lastToken ){ // 어차피 c보다 우선순위가 다 낮을 거니까 쭉 계산 
		
		a = opr.Top();
		opr.Pop();
		b = opr.Top();
		opr.Pop();
		
		if(opt.Top() == '+'){
			opr.Push(b + a);
		}
		else if(opt.Top() == '-'){
			opr.Push(b - a);
		}
		else if(opt.Top() == '*'){
			opr.Push(b * a);
		}
		else if(opt.Top() == '/'){
			opr.Push(b / a);
		}
		
		opt.Pop();
	}
	
	out = opr.Top();

	return out;	
}

#endif
