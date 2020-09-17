#include <stdio.h>
#include <stdlib.h>

typedef struct _fl
{
	// 3 bit exp, 4 bit mantissa, 1 bit sign;
	// 3 bit exp means bias is 2 ^ (3 - 1) - 1 = 3
	// Remeber the leading 1 in the mantissa for any value less than one.
	char val;
} fl;

void print(char* bytes)
{
	for (int i = sizeof(double) - 1; i >= 0; i--)
	{
		printf("%x\t", (bytes[i] + 256) % 256);
	}
	printf("\n");
}


int main()
{
	double* a = malloc(sizeof(double));
	float* b = (float*) a;
	*a = 0.00;
	char* p = (char*) a;

	p[7] = 0x3f;
	p[6] = 0x00;
	p[5] = 0x00;
	p[3] = 0x00;

	printf("%lf\n", *a);
	print(p);

	return 0;
}