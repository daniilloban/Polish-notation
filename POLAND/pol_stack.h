#pragma once
#include <iostream>
#include <string.h>
#include <ctype.h>


using std::cout;
using std::endl;

enum TYPEVAL  { INT, FLOAT, OP };
enum TYPEOP   { ADD, SUB, DEV, MLT, DVC, OBR };// + - / * % (
union  param 	{ int d;		double f;		TYPEOP op; };
struct elem   { param value;		TYPEVAL type; };

const int BUFF_SZ = 255;

class Stack
{
private:
	const int capacity = 100;
	struct STACK  { elem * stack;    int size; };
	STACK * st;
public:
	Stack();
	~Stack();
	void stack_to_str(char **str);
	int pop(elem &el);
	int push(elem el);
	void print_stack();
	inline bool isempty() { return !st->size; };
	int compare(char op1);
	elem calc(char * str);
	void convert(char * str);

};