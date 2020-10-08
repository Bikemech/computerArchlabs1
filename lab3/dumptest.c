#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* get_dump(size_t size)
{
	char* ptr = malloc(size + 8);
	int* iptr = (int*) ptr;
	*iptr = size + 8;
	*(iptr + 1) = 8;
	return ptr;
}

void dump_putch(char* dump, char* words)
{
	int* iptr = (int*) dump;
	size_t size = *iptr;
	int index = *(iptr + 1);

	int len = strlen(words);
	int end = index + len;
	if (end > size) end = size;

	for (int i = index; i < end; i++)
	{
		*(dump + i) = *(words + i);
	}
}

void view_dump(char* dump)
{
	int* iptr = (int*) dump;
	int size = *iptr;
	for (int i = 8; i < size ; ++i)
	{
		if (i % 8 == 0) printf("\n");
		if (i % 4 == 0) printf("\t");
		printf("%02x", *(dump + i + 8) & 0xff);
	}
	printf("\n");

}

int main(int argc, char** argv)
{
	char* dump = get_dump(32);
	char* word = "alex";
	dump_putch(dump, word);

	view_dump(dump);

	return 0;
}