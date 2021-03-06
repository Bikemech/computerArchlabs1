#include <stdio.h>
#include <stdlib.h>
#include <cmath>

void signtype()
{
	/*
	*	a & b 	===		0111 1111 &
	*	127 & -127		1111 1111 =
	*					0111 1111 // for signed integers
	*
	*	a & b 	===		0111 1111 &
	* 	127 & -127		1000 0001 =
	*					0000 0001 // for two's complement
	*/
	char a = 127;
	char b = -127;
	char r = a & b;	// Bitwise and operation

	if (r == 1) printf("Using two's complement\n\n");
	else if (r == 127) printf("Using signed integer\n\n");
	else printf("wut??\n\n");
}


int main()
{
	int s = 8;
	int offset = 4;
	char* mem = (char*) malloc(sizeof(int) * s);
	int* ptr = (int*) mem;

	*(ptr + offset) = 0x04030201;

	for (int i = 0; i < 4 * s; i++)
	{
		printf("%02x ", (int) mem[i] & 0xff);
		if (i % 4 == 3) printf("\n");
	}
	printf("\n");
	signtype();
	return 0;

}