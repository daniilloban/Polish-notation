// Polish notation version 0.1 (beta)

/**********************************
Algorithm:
a) If the stack is empty , then from the input strings are opepatsy is overwritten on the stack ;
b) opepatsy pushes the stack all opepatsii more or pavnym
ppiopitetom the string in the output ;

c) if ochepednoy character from the original strings are there otkpyvayuschaya bracket
ppotalkivaetsya it to the stack ;

d) round brackets zakpyvayuschaya pushes all opepatsii stack up
otkpyvayuschey nearest brackets , the brackets themselves are not in the string in output
is overwritten and destroyed d.puguyu d.puguyu .
*********************************/
#pragma once
#include <iostream>
#include "pol_stack.h" 

using std::cout;
using std::endl;

inline void print_info()
{
	cout << "Enter the expression using spaces as the delimiter settings\n"
		"The fractional part is recorded after the decimal point , if it is 0 then the literal with F\n"
		"(q -exit from the program, s - example expression):\n\n";
}

int main()
{
	Stack st1;
	elem result;

	char test1[] = "( 30 % 25 * 5F ) / ( - 10 + 3 * 2 - 8 )";
	char *stcalc = (char *)malloc(sizeof (char)*BUFF_SZ);

	do{
		print_info();
		fflush(stdin);
		fgets(stcalc, BUFF_SZ, stdin);
		if (strcmp(stcalc, "q\n") == 0) return 0;

		if (strcmp(stcalc, "s\n") == 0)
		{
			system("cls");
			print_info();
			strcpy_s(stcalc, strlen(stcalc), test1);
			cout <<  stcalc <<endl;
		}

		st1.convert(stcalc);
		cout <<"\nConversion:\n" << stcalc << endl;

		result = st1.calc(stcalc);
		cout << "\nResult:\n" 
			<< (result.type == INT ? result.value.d : result.value.f) << endl << endl;

		system("pause");
		system("cls");
	} while (true);

 return 0;
}












