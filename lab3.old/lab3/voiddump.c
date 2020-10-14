#include <stdlib.h>
#include <stdio.h>
// #include <string>

void view(const void* p)
{
	char* ptr = (char*) p;
	printf("    %p\t\t", p);

	for (int i = 0; i < 8; ++i)
	{
		if (i == 4) printf("  ");
		printf("%02x", *(ptr + i) & 0xff);
	}
	printf("\n");
}

void view_r(void* p)
{
	char* ptr = (char*) p;
	printf("    %p\t\t", p);

	for (int i = 3; i >= 0; --i)
	{
		printf("%02x", *(ptr + i) & 0xff);
	}
	printf("  ");
		for (int i = 7; i >= 4; --i)
	{
		printf("%02x", *(ptr + i) & 0xff);
	}
	printf("\n");
}

typedef struct link_
{
    int d;
    struct link_* p;
} link;

link* create_link(int data)
{
	link* p = (link*) malloc(sizeof(link));
	p->d = data;
	p->p = (link*) 0x558735af0e80;
}

int main()
{
    link* p = create_link(0xaaaabbcd);
    link* q = create_link(0xdeadbeef);

    p->p = q;

    // p->p->d = 0x99999999;

    char* ptr = (char*) p;

    for (int i = 0 ; i < 8; ++i) view(ptr + (i * sizeof(link)));
    printf("\n\n");
    for (int i = 0 ; i < 8; ++i) view_r(ptr + (i * sizeof(link)));

    // std::string text = "hejsan12345678900";

    // const char* ctext = text.c_str();

    printf("\n\n");
    // view(ctext);
    // view(ctext + 8);
    // view(ctext + 16);
    // view(ctext + 24);

	return 0;
}