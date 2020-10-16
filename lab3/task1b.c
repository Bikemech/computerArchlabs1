#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Column major form */

int intpow(int a, int b)
{
	if (b == 0) return 1;
	int base = a;
	for (int i = 0; i < b - 1; ++i)
	{
		a = base * a;
	}
	return a;
}

// Helper function fetchb

char fetchb(char * ptr, size_t m, size_t n, size_t s, int j, int i)
{
	int index = n * s * i + s * j;
	int inc = n * s;
	if (index > m * n * s || i >= m || j >= n) return 0;
	return *(ptr + index);
}


void print(char * ptr, int size)
{
	for (int i = 0; i < size ; i++)
	{
		if (i % 8 == 0 && i > 0) printf("\n");
		if (i % 4 == 0) printf("\t0x");
		printf("%02x", *(ptr + i) & 0xff);
	}
	printf("\n");
}


char* two_d_alloc(size_t rows, size_t columns, size_t elem_size)
{
	return (char*) malloc(rows * columns * elem_size);
}

void two_d_dealloc(char* ptr)
{
	free(ptr);
}


// \
m = number of rows \
n = number of columns \
s = size of element \
i = column position to access \
j = row position to access \
val = the value to store

void two_d_store(char * ptr, size_t m, size_t n, size_t s, int j, int i, int val)
{
	// interpret int as a char*
	char* vptr = (char*) &val;


	int index = n * s * i + s * j;
	int inc = n * s;
	if (index > m * n * s || i + 3 >= m || j >= n) return;

	for (int k = 0; k < 4; ++k)
	{
		*(ptr + index + k * inc) = *(vptr + k);
	}
    

	*(ptr + index) = val;
}

int two_d_fetch(char * ptr, size_t m, size_t n, size_t s, int j, int i)
{
	int index = n * s * i + s * j;
	int inc = n * s;
	if (index > m * n * s || i >= m || j >= n) return 0;


	int value = 0;
	char bytek;
	for (int k = 0; k < 4; ++k)
	{
		bytek = fetchb(ptr, m, n, s, j, i + k);
		printf("bytek:\t%02x\n", bytek);
		value = value + bytek * intpow(256, (3 - k));
	}
	return value;
}



int main()
{

	int r, c, s;
	r = 8; c = 8; s =1;

	char* p = two_d_alloc(r, c, s);

	size_t n = r * c * s;

	two_d_store(p, r, c, s, 1, 0, 255);
	two_d_store(p, r, c, s, 0, 4, 0x71223344);
	two_d_store(p, r, c, s, 7, 6, 0x77);

    print(p, n);

	// printf("\t%x\n", two_d_fetch(p, r, c, s, 1, 0) & 0xff);
	// printf("\t%x\n", two_d_fetch(p, r, c, s, 1, 3) & 0xff);
	printf("\t%x\n", two_d_fetch(p, r, c, s, 0, 4) & 0xff);


	return 0;
}