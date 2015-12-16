// Polish notation
//
#include "stdafx.h"
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


enum TYPEVAL { INT, FLOAT, OP };
enum TYPEOP { ADD, SUB, DEV, MLT, DVC, OBR };// + - / * % (

union param
{
	int d;
	double f;
	TYPEOP op;
};

struct elem
{
	param value;
	TYPEVAL type;
};

struct STACK
{
	elem * stack;
	int size;
};

int push(STACK * st, elem number);
int  pop(STACK * st, elem &el);
bool isempty(STACK * st);

void print_stack(STACK * st);
void setup_stack(STACK * st);
void stack_to_str(STACK * st, char **str);

void free_stack(STACK * st);
void create_stack(STACK *&st);

elem calc(char * str);
void convert(char * str);

#define capacity  100
#define BUFF_SZ   255

inline void print_info();


int _tmain(int argc, _TCHAR* argv[])
{

	setlocale(LC_ALL, "rus");

	STACK * st1;
	create_stack(st1);
	elem result;

	char test1[] = "( 30 % 25 * 5F ) / ( - 10 + 3 * 2 - 8 )";
	

	char *stcalc = (char *)malloc(sizeof (char)*BUFF_SZ);


	do{
		print_info();
		fflush(stdin);
		fgets(stcalc, BUFF_SZ, stdin);
		if (strcmp(stcalc, "q\n") == 0) break;

		if (strcmp(stcalc, "s\n") == 0)
		{
			system("cls");
			print_info();
			strcpy(stcalc, test1);
			printf("%s\n", stcalc);
		}


		convert(stcalc);
		printf("Conversion: %s\n", stcalc);

		result = calc(stcalc);
		if (result.type == INT)
			printf("Result %d\n", result.value.d);
		else
			printf("Result %g\n", result.value.f);

		system("pause");
		system("cls");
	} while (true);



	free_stack(st1);

	system("pause");
	return 0;
}

inline void print_info()
{
	printf("Enter the expression using spaces as the delimiter settings\n"
		"The fractional part is recorded after the decimal point , if it is 0 then the literal with F\n"
		"(q -exit from the program, s - example expression): \n");
}


int compare(STACK * st, char op1)
{
	if (isempty(st)) return 1;

	elem el;
	pop(st, el);
	push(st, el);

	switch (op1)
	{
	case '(':
		return 1;
		break;
	case '+':
	case '-':
		if (el.value.op == MLT || el.value.op == DEV || el.value.op == DVC)
			return -1;
		else
		if (el.value.op == ADD || el.value.op == SUB)
			return 0;
		else
			return 1;
		break;
	case '/':
	case '*':
	case '%':
		if (el.value.op == MLT || el.value.op == DEV || el.value.op == DVC)
			return 0;
		else
		if (el.value.op == ADD || el.value.op == SUB)
			return 1;
		else
			return -1; //?
		break;
	}

	return 0;
}

void create_stack(STACK *&st)
{
	st = (STACK *)malloc(sizeof(STACK));
	st->stack = (elem *)malloc(capacity * sizeof(elem));
	st->size = 0;
}


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
void convert(char * str)
{
	STACK * res0, *tmp;
	elem number, oper, movop;
	char * ast;
	bool issign = true;

	create_stack(res0);
	create_stack(tmp);

	ast = strtok(str, " ");
	while (ast != NULL)
	{
		if (isdigit(ast[0]))
		{
			if (atoi(ast) < atof(ast) || ast[strlen(strupr(ast))-1] == 'F')
			{
				number.value.f = atof(ast);
				number.type = FLOAT;
			}
			else
			{
				number.value.d = atoi(ast);
				number.type = INT;
			}
			push(res0, number);
			issign = false;
		}
		else
		{
			if (ast[0] != ')' && ast[0] != '(')
			while (compare(tmp, ast[0]) != 1)
			{
				pop(tmp, movop);
				push(res0, movop);
			}
			oper.type = OP;

			switch (ast[0])
			{
			case ')':
				do
				{
					pop(tmp, oper);
					push(res0, oper);
				} while (oper.value.op != '(' && !isempty(tmp));
				break;
			case '(':
				oper.value.op = OBR;
				break;
			case '+':
				oper.value.op = ADD;
				break;
			case '-':
				if (issign)
				{
					number.type = INT;
					number.value.d = 0;
					push(res0, number);
				}
				oper.value.op = SUB;
				break;
			case '*':
				oper.value.op = MLT;
				break;
			case '/':
				oper.value.op = DEV;
				break;
			case '%':
				oper.value.op = DVC;
				break;
			}

			if (ast[0] != ')')
			{
				push(tmp, oper);
			}
			issign = true;
		}
		ast = strtok(NULL, " ");
	}

	while (!isempty(tmp))
	{
		pop(tmp, oper);
		push(res0, oper);
	}

	while (!isempty(res0))
	{
		pop(res0, oper);
		push(tmp, oper);
	}

	stack_to_str(tmp, &str);

	free_stack(res0);
	free_stack(tmp);
}

elem calc(char * str)
{
	STACK * st;
	create_stack(st);
	char * ast;

	elem number, first, second;
	ast = strtok(str, " ");
	while (ast != NULL)
	{
		if (isdigit(ast[0]))
		{
			if (atoi(ast) < atof(ast) || ast[strlen(strupr(ast)) - 1] == 'F')
			{
				number.value.f = atof(ast);
				number.type = FLOAT;
			}
			else
			{
				number.value.d = atoi(ast);
				number.type = INT;
			}
			push(st, number);
		}
		else
		{
			pop(st, second);
			pop(st, first);
			number.value.d = 0;
			number.value.f = 0;
			switch (ast[0])
			{
			case '+':
				if (first.type == INT && second.type == INT)
					number.value.d = first.value.d + second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f += (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = first.type == INT && second.type == INT ? INT : FLOAT;
				break;
			case '-':
				if (first.type == INT && second.type == INT)
					number.value.d = first.value.d - second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f -= (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = first.type == INT && second.type == INT ? INT : FLOAT;
				break;
			case '*':
				if (first.type == INT && second.type == INT)
					number.value.d = first.value.d * second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f *= (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = first.type == INT && second.type == INT ? INT : FLOAT;
				break;
			case '/':
				if (first.type == INT && second.type == INT)
					number.value.d = first.value.d / second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f /= (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = first.type == INT && second.type == INT ? INT : FLOAT;
				break;
			case '%':
				if (first.type == INT && second.type == INT)
				{
					number.value.d = first.value.d % second.value.d;
					number.type = INT;
				}
				break;
			}
			push(st, number);
		}
		ast = strtok(NULL, " ");
	}
	pop(st, number);
	free_stack(st);
	return number;
}

void free_stack(STACK * st)
{
	free(st->stack);
	st->size = 0;
	free(st);
}

bool isempty(STACK * st)
{
	return !st->size;
}

void setup_stack(STACK * st)
{
#define MAXNUMSIZE 15
	char buff[MAXNUMSIZE];

	elem number;
	do
	{
		fflush(stdin);
		fgets(buff, MAXNUMSIZE, stdin);

		if (atoi(buff) < atof(buff))
		{
			number.value.f = atof(buff);
			number.type = FLOAT;
		}
		else
		{
			number.value.d = atoi(buff);
			number.type = INT;
		}

		if (buff[0] == '-') break;

		push(st, number);

	} while (true);
}

void print_stack(STACK * st)
{
	elem number;
	printf("Your stack is:\n");

	while (!isempty(st))
	{
		pop(st, number);

		switch (number.type)
		{
		case INT:
			printf("%d\n", number.value.d);
			break;
		case FLOAT:
			printf("%g\n", number.value.f);
			break;
		case OP:
			switch (number.value.op)
			{
			case ADD:
				printf("+\n");
				break;
			case SUB:
				printf("-\n");
				break;
			case MLT:
				printf("*\n");
				break;
			case DEV:
				printf("/\n");
				break;
			case DVC:
				printf("%\n");
				break;
			}
			break;
		}
	}
}


void stack_to_str(STACK * st, char **str)
{
	elem number;
	char buff[15];

	int len = 0;

	*str[0] = 0;

	while (!isempty(st))
	{
		pop(st, number);

		switch (number.type)
		{
		case INT:

			sprintf(buff, "%d ", number.value.d);
			strcat(*str, buff);
			break;
		case FLOAT:
			sprintf(buff, "%gF ", number.value.f);
			strcat(*str, buff);
			break;
		case OP:
			switch (number.value.op)
			{
			case ADD:
				strcat(*str, "+ ");
				break;
			case SUB:
				strcat(*str, "- ");
				break;
			case MLT:
				strcat(*str, "* ");
				break;
			case DEV:
				strcat(*str, "/ ");
				break;
			case DVC:
				strcat(*str, "% ");
				break;
			}
			break;
		}
	}
}



int push(STACK * st, elem el)
{
	if (capacity == st->size)
	{
		printf("stack is full");
		return -1;
	}
	st->stack[st->size++] = el;
	return 0;
}

int  pop(STACK * st, elem &el)
{
	if (isempty(st))
	{
		el.value.d = 0;
		el.type = INT;
		printf("stack is empty\n");
		return -1;
	}
	el = st->stack[(st->size--) - 1];
	return 0;
}
