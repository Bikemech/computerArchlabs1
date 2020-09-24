#include <iostream>
#include <string>
#include <cmath>

class qpfloat
{
	// 4 bit mantissa
	// 3 bit exp
	// 1 bit sign

	// bias is 2^(3 - 1) - 1 = 3;

	// exp max is 6 - bias = 3
	// exp min is -bias = -3;

	// e-mach = 0.0625
	// e-mach is represented as: 0 011 0001

	// smallest non negative representable value = 1/(2^3 * 2^4) = 1/(128)
	// smallest num:	0 000 0001

	// biggest representable value = 2^3 * (2 - 2^-4) = 15.5
	// biggest num:		0 110 1111


	char data;
public:
	qpfloat(float i)
	{
		this->data = 0;
		if (i > 15.5) this->data = 0x70;
		if (i < -15.5) this->data = 0xf0;

		char mem[sizeof(float)];
		float* ptr = (float*) mem;
		int* iptr = (int*) mem;
		// *iptr = *iptr >> 3;
		// *ptr = i;

		printf("%d\n", *iptr);
		for (int j = sizeof(float) - 1; j >= 0 ; j--)
			printf("%x\t", (256 + mem[j]) % 256);

		std::cout << std::endl;
	}
	~qpfloat();

	std::string bin()
	{

		unsigned char it = this->data;	// This is the char that i need for conversion to binary
										// However using a signed char yields errors.
		char str[8];
		int index = 7;

		while (index + 1)
		{
			if (it % 2)
			{
				str[index] = '1';
			}
			else
			{
				str[index] = '0';
			}
			it = it / 2;
			index--;
		}
		std::cout << std::endl;
		return std::string(str);
	}
};

int main()
{
	qpfloat& t = *(new qpfloat(INFINITY)); // less than minimum
	qpfloat& s = *(new qpfloat(-INFINITY)); // greater than maximum

	
	std::cout << t.bin() << std::endl;
	std::cout << s.bin() << std::endl;



	return 0;
}