#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
i = row position to access \
j = column position to access \
val = the value to store

void two_d_store(char * ptr, size_t m, size_t n, size_t s, int i, int j, int val)
{
	int index = n * s * i + s * j;
	if (index > m * n * s || i >= m || j >= n) return;

	*(ptr + index) = val;
}

void* two_d_fetch(void* ptr, size_t m, size_t n, size_t s, int i, int j)
{
	int index = n * s * i + s * j;
	if (index > m * n * s || i >= m || j >= n) return NULL;

	return (void*) (ptr + index); // parathesis are crucial becuase of the recasting
}

int main()
{

	int r, c, s;
	r = 8; c = 8; s =1;

	// char* p = two_d_alloc(r, c, s);
	double* p = malloc(64);

	*p = 0.123455;
	*(p + 3) = 123456.0000123;

	size_t n = r * c * s;

	// two_d_store(p, r, c, s, 1, 0, 255);
	// two_d_store(p, r, c, s, 1, 3, 0x11);
	// two_d_store(p, r, c, s, 7, 6, 0x77);

    print((char*) p, n);

	printf("\t%02x\n", *((int*) two_d_fetch(p, r, c, s, 0, 0)) & 0xff);
	printf("\t%02x\n", *((int*) two_d_fetch(p, r, c, s, 3, 1)) & 0xff);
	printf("\t%02x\n", *((int*) two_d_fetch(p, r, c, s, 3, 6)) & 0xff);


	return 0;
}


int* p;
char* t;