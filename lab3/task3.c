#include <stdlib.h>
#include <stdio.h>

typedef struct _link
{
	int data;
	struct _link* head;
} link;

link* push(link* prev, int data)
{
	link* new = malloc(sizeof(link));
	new->data = data;
	new->head = prev;
	return new;
}

int pop(link* head)
{
	link* temp = head;

	head = head->head;
    int val = head->data;
    free(temp);
    return val;
}

void iter_link(link* ptr)
{
	while (ptr)
	{
		printf("Data at %p\t%d\n", ptr, ptr->data);
		ptr = ptr->head;
	}
}

int main()
{
	link* list = NULL;

    for (int i = 0; i < 10; ++i)
    {
    	list = push(list, i);
    }

    iter_link(list);


    pop(list);

    printf("\n");

    iter_link(list);

	return 0;
}