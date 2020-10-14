#include <stdio.h>
#include <stdlib.h>

typedef struct link_
{
	struct link_* head;
	int val;
} link;

char* two_d_alloc(size_t rows, size_t columns, size_t elem_size)
{
	return (char*) malloc(rows * columns * elem_size);
}

void print_dump(char* p)
{
	printf("\t|%p| ", p);

	for (int i = 0; i < 16; ++i)
	{
		if (i % 4 == 0) printf("\t");
		printf("%02x", *(p + i) & 0xff);
	}

	printf("\t");
		for (int i = 0; i < 16; ++i)
	{
		if (i % 4 == 0) printf("\t");
		if (*(p + i) < 0xfe && *(p + i) >= 0x20) printf("%c", *(p + i));
		else printf(".");
	}

	printf("\n");

}

link* push(link* head, int val)
{
	link* new = malloc(sizeof(link));
	new->val = val;
	new->head = head;
	return new;
}

int main()
{
	char* ptr = two_d_alloc(8, 8, sizeof(link));

	link* lptr = (link*) ptr;
	lptr->val = 0x31323334;
	(lptr + 1)->head = lptr;
	(lptr + 1)->val = 0x35363738;

	print_dump(ptr);
	print_dump(ptr + 0x10);
	print_dump(ptr + 0x20);
	print_dump(ptr + 0x30);

	printf("%x\n", (lptr + 1)->head->val);


	return 0;
}