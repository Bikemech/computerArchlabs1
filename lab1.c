#include <stdio.h>
#include <stdlib.h>
#include <cmath>

int main()
{
	char* mem = (char*) malloc(sizeof(int));
	int* ptr = (int*) mem;

	// *ptr = 0x04030201;
	*ptr = (int)  pow(2, 31);

	printf("\n");

	for (int i = 0; i < sizeof(double); i++)
	{
		printf("%x\t", (int) (255 + mem[i]) % 255);
	}
	printf("\n%d\n", *ptr);
}