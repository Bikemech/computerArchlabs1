#include <stdio.h>
#include <stdlib.h>

char* two_d_alloc(int n, int m, int size)
{
	int total_size = n * m * size;
	// extra 12 bytes for a header
	char* ptr = malloc(total_size + 12);
	int* iptr = (int*) ptr;

	*iptr = n;
	*(iptr + 1) = m;
	*(iptr + 2) = size;

	return ptr;
}

void two_d_dealloc(char* ptr)
{
	free(ptr);
}

void two_d_store(char* ptr, int m, int n, int data)
{
	int* head_ptr = (int*) ptr;
	int row = *head_ptr;
	int col = *(head_ptr + 1);
	int dsize = *(head_ptr + 2);

	int index = 12 + dsize * (m * col + row);

	char databytes[dsize];
	*((int*) databytes) = data;
    for (int i = 0; i < dsize; i++)
    {
    	*(ptr + index + i) = databytes[i];
    }
}

char* two_d_fetch(char* ptr, int m, int n)
{
	int* head_ptr = (int*) ptr;
	int row = *head_ptr;
	int col = *(head_ptr + 1);
	int dsize = *(head_ptr + 2);

	int index = 12 + dsize * (m * col + row);

	return ptr + index;
}

int main()
{
	char* mem = two_d_alloc(10, 20, 4);
	two_d_store(mem, 3, 3, 0x30313233);

	char* a = two_d_fetch(mem, 3, 3);
	printf("\t%s\n", a);

	return 0;
}