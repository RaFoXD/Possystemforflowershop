#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
//these are the include guards
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
//Prototypes for the functions and structures

typedef struct Flower
{
	int id;
	char name[20];
	float size;
	char type[20];
	char color[20];
	float pricePerUnit;
}flower;

void open();
void read(int option);
void add();
void deleteItem();

#endif