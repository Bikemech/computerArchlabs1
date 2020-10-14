#include <stdio.h>
#include <stdlib.h>

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

int main()
{
	char* hej = "hejdittsvettskrellemankanskriva mer trams haerblahabladhgrguear9832498324uf!@##@%";
	print_dump(hej);
	print_dump(hej + 0x10);
	print_dump(hej + 0x20);
	print_dump(hej + 0x30);
	print_dump(hej + 0x40);
	print_dump(hej + 0x50);
	print_dump(hej + 0x60);
	printf("\n");
	return 0;
}