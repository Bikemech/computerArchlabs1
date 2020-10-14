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

link* push_p(link* head, int val)
{
	(head + 1)->val = val;
	(head + 1)->head = head;
	return head + 1;
}

int main()
{
	char* ptr = two_d_alloc(16, 1, sizeof(link));

	link* list = push_p((link*) ptr, 0x30);
	link* home = list;
	list->head = NULL;

	for (int i = 0; i < 10; i++)
	{
		list = push_p(list, i + 0x31);
	}

	for (int i = 0; i < 16; i++)
	{
		print_dump((char*) home + sizeof(link) * i);
	}

	return 0;
}