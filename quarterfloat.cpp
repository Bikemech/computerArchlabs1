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
		// if (i > 15.5) this->data = 0x70;
		// if (i < -15.5) this->data = 0xf0;

		float normBias = i * pow(2, -124);
		//	Float bias = 127, our bias = 3
		//	127 - 3 = 124

		char* memc = (char*) malloc(sizeof(float));
		float* memf = &normBias;
		memc = (char*) memf;

		char byte1 = memc[3];
		char byte2 = memc[2];

		// extract bits from our two bytes
		char sign = byte1 & 0x80; 			// sign is msb in byte 1;
		char exp1 = ((byte1 & 0x03) << 5);	// the exponent bits we need is at
											// the last two places in byte1
		char exp2 = ((byte2 & 0x80) >> 3);	// the other exponent bit is at msb in byte2
		char mant = ((byte2 & 0x78) >> 3);	// we need 4 bits from the mantissa which are
											// in byte2 in order one bit to the right from msb

		this->data = sign | exp1 | exp2 | mant;

		// printf("%x\t%x\t%x\t%x\t***\n", sign & 0xff, exp1 & 0xff, exp2 & 0xff, mant & 0xff);
		// printf("%x\t<< float", this->data  & 0xff);


		// printf("%x\n", sign & 0xff);

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
	// qpfloat& t = *(new qpfloat(INFINITY)); // less than minimum
	// qpfloat& s = *(new qpfloat(-INFINITY)); // greater than maximum
	qpfloat& u = *(new qpfloat(4.5));
	std::cout << u.bin() << std::endl;


	float q = pow(2, -124);
	char* cptr = (char*) malloc(sizeof(float));
	float* fptr = &q;
	cptr = (char*) fptr;


	return 0;
}

/*

	| s eee | eeee | e mmm | mmmm...
	IEEE float bias = 127
	0 000 0001 1 000 0000 ....
	= 2^(3 - 127) = 2 ^ -124


10.1 = 2.5 bin
1.01*2^1 = 2.5 bin
0101 0010


*/