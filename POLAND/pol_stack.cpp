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
#include "pol_stack.h" 

Stack::Stack()
{
	st = new STACK;
	st->stack = new  elem[capacity];
	st->size = 0;
}

Stack::~Stack()
{
	delete[] st->stack;
	delete st;
}

void Stack::stack_to_str(char **str)
{
	elem number;
	const int buffsz = 255;
	char buff[buffsz];
	int len = 0;
	*str[0] = 0;

	while (!isempty())
	{
		pop(number);
		switch (number.type)
		{
		case INT:
			sprintf_s(buff, "%d ", number.value.d);
			strcat_s(*str, buffsz, buff);
			break;
		case FLOAT:
			sprintf_s(buff, "%gF ", number.value.f);
			strcat_s(*str, buffsz, buff);
			break;
		case OP:
			switch (number.value.op)
			{
			case ADD: strcat_s(*str, buffsz, "+ "); break;
			case SUB: strcat_s(*str, buffsz, "- "); break;
			case MLT: strcat_s(*str, buffsz, "* "); break;
			case DEV: strcat_s(*str, buffsz, "/ "); break;
			case DVC: strcat_s(*str, buffsz, "% "); break;
			}
			break;
		}
	}
}

int Stack::push(elem el)
{
	if (capacity == st->size)
	{
		cout << "stack is full";
		return -1;
	}
	st->stack[st->size++] = el;
	return 0;
}

int Stack::pop(elem &el)
{
	if (isempty())
	{
		el.value.d = 0;
		el.type = INT;
		cout << "stack is empty\n";
		return -1;
	}
	el = st->stack[(st->size--) - 1];
	return 0;
}

void Stack::print_stack()
{
	elem number;
	cout << "Your stack is:\n";

	while (!isempty())
	{
		pop(number);
		switch (number.type)
		{
		case INT:
			cout << number.value.d << '\n';
			break;
		case FLOAT:
			cout << number.value.f << '\n';
			break;
		case OP:
			switch (number.value.op)
			{
			case ADD:	cout << "+\n"; break;
			case SUB: cout << "-\n"; break;
			case MLT: cout << "*\n"; break;
			case DEV: cout << "/\n"; break;
			case DVC: cout << "%\n"; break;
			}
			break;
		}
	}
}

//inline bool Stack::isempty() { return !st->size; }

int Stack::compare(char op1)
{
	if (isempty()) return 1;

	elem el;
	pop(el);
	push(el);

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

elem Stack::calc(char * str)
{
	char * ast;
	char *context = NULL;
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
			push(number);
		}
		else
		{
			pop(second);
			pop(first);
			number.value.d = 0;
			number.value.f = 0;
			switch (ast[0])
			{
			case '+':
				if ((first.type == INT) & (second.type == INT))
					number.value.d = first.value.d + second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f += (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = (first.type == INT) & (second.type == INT) ? INT : FLOAT;
				break;
			case '-':
				if ((first.type == INT) & (second.type == INT))
					number.value.d = first.value.d - second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f -= (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = (first.type == INT) & (second.type == INT) ? INT : FLOAT;
				break;
			case '*':
				if ((first.type == INT) & (second.type == INT))
					number.value.d = first.value.d * second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f *= (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = (first.type == INT) & (second.type == INT) ? INT : FLOAT;
				break;
			case '/':
				if ((first.type == INT) & (second.type == INT))
					number.value.d = first.value.d / second.value.d;
				else
				{
					number.value.f += (first.type == INT) ? first.value.d : first.value.f;
					number.value.f /= (second.type == INT) ? second.value.d : second.value.f;
				}
				number.type = (first.type == INT) & (second.type == INT) ? INT : FLOAT;
				break;
			case '%':
				if ((first.type == INT) & (second.type == INT))
				{
					number.value.d = first.value.d % second.value.d;
					number.type = INT;
				}
				break;
			}
			push(number);
		}
		ast = strtok(NULL, " ");
	}
	pop(number);
	return number;
}

void Stack::convert(char * str)
{
	elem number, oper, movop;
	char **context = NULL;
	char * ast;
	bool issign = false;//true;

	Stack  res0;
	Stack  tmp;

	ast = strtok(str, " ");

	while (ast != NULL)
	{
		if (isdigit(ast[0]))
		{
			if ((atoi(ast) < atof(ast)) | (((ast[strlen(strupr(ast)) - 1])) == 'F') | (((ast[strlen(strupr(ast)) - 2])) == 'F'))
			{
				number.value.f = atof(ast);
				number.type = FLOAT;
			}
			else
			{
				number.value.d = atoi(ast);
				number.type = INT;
			}
			res0.push(number);
			issign = false;
		}
		else
		{
			if (ast[0] != ')' && ast[0] != '(')

			while (tmp.compare(ast[0]) != 1)
			{
				tmp.pop(movop);
				res0.push(movop);
			}
			oper.type = OP;

			switch (ast[0])
			{
			case ')':
				do
				{
					tmp.pop(oper);
					res0.push(oper);

				} while (oper.value.op != '(' && !tmp.isempty());
				break;
			case '(': oper.value.op = OBR; 	break;
			case '+': oper.value.op = ADD; 	break;
			case '-':
				if (issign)
				{
					number.type = INT;
					number.value.d = 0;
					res0.push(number);
				}
				oper.value.op = SUB;
				break;
			case '*': oper.value.op = MLT; 	break;
			case '/':	oper.value.op = DEV; 	break;
			case '%': oper.value.op = DVC; 	break;
			}

			if (ast[0] != ')')
			{
				tmp.push(oper);
			}
			issign = true;
		}
		ast = strtok(NULL, " ");

	}

	while (!tmp.isempty())  { tmp.pop(oper); res0.push(oper); }
	while (!res0.isempty()) { res0.pop(oper); tmp.push(oper); }

	tmp.stack_to_str(&str);
}