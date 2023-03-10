#include "stack.h"
#include "calculator.h"
#include <iostream>

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

// stack & calculator test

int main()
{
	// Stack test
	Stack<int> s;
	
	s.Push(23);
	s.Push(102);
	s.Print();
	printf("--\n");
	
	s.Push(345);
	s.Push(77);
	s.Print();
	printf("--\n");
	
	s.Pop();
	s.Push(678);
	s.Push(91011);
	s.Print();
	printf("--\n");
	
	for(int i=0; i<6; i++)
	{
		try {
			s.Pop();
			std::cout << "Pop() is called" << std::endl;
		}
		catch(const char* message)
		{
			std::cout << message << std::endl;
		}		
	}

	// Calculator test
	char str1[] ="-10-((-2+(2+4*3))-12) + 122 * (123 + (120+888) - 300)";
	// The correct result is 101372
	double res1 = Eval(str1);
	std::cout << "Result : " << res1 << std::endl;
	
	
	char str2[] = "1.2 + 2.4 + 3.0*2";
	// The correct result is 9.6
	double res2 = Eval(str2);
	std::cout << "Result : " << res2 << std::endl;
	
	char str3[] = "(2/-567 )           * 4235 - (5456 /     5.743) +      48 * -156 + (12 /    -23.1) / 213235*       2346 - -2341        + 3425 /       123.145 -362 * 3426 / -1435.1462 + (34611 * 3462 -436 + (542/ 34612.6341) *1463 / (146 + (1436 / 436) - 463.14) * 12.21)";
	double res3 = Eval(str3);
	std::cout << "Result : " << res3 << std::endl;

	return 0;
}
