#include <stdio.h>
#include <stdlib.h>
#include <cmath>

void signtype()
{
	char a = 127;
	char b = -127;
	char r = a & b;	// Bitwise and operation
	/*
	*	a & b 	===		0111 1111 &
	*	127 & -127		1111 1111 =
	*					0111 1111 // for signed integers
	*
	*	a & b 	===		0111 1111 &
	* 	127 & -127		1000 0001 =
	*					0000 0001 // for two's complement
	*/
	
	if (r == 1) printf("Using two's complement\n");
	else printf("Using signed integer\n");
}


int main()
{
	char* mem = (char*) malloc(sizeof(int) * 2);
	int* ptr = (int*) mem;
	*(ptr + 1) = 0; // Initializing to erase scrap data;

	*(ptr + 1) = 0x04030201;
	// *ptr = 0x80;


	printf("\n");

	for (int i = 4; i < sizeof(int) + 4; i++)
	{
		printf("%x\t", (int) (256 + mem[i]) % 256);
	}
	printf("\n%d\n", *ptr);
	signtype();


}