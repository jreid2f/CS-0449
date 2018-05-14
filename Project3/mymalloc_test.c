/*
   Joseph Reidell
   My Custom Malloc
   Project 3

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

#define MALLOC my_worstfit_malloc

#define FREE my_free

void test1(){
	void* a = MALLOC(100);
	void* b = MALLOC(50);

	printf("brk during test1: %p\n", sbrk(0));

	FREE(a);
	FREE(b);
	
	void* c = MALLOC(75);

	FREE(c);
}

void test2(){
	void* a = MALLOC(150);
	void* b = MALLOC(200);
	void* c = MALLOC(75);

	printf("brk during test2: %p\n", sbrk(0));

	FREE(a);
	FREE(b);
	FREE(c);

	void* d = MALLOC(25);
	void* e = MALLOC(100);

	FREE(d);
	FREE(e);
}

int main(){
	
	test1();
	printf("brk after test1: %p\n", sbrk(0));
	printf("-----------\n");
	test2();
	printf("brk after test2: %p\n", sbrk(0));
	return 0;

}
