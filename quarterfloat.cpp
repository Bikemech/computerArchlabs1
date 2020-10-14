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

	// smallest non negative representable value = 1/(2^3 * 2^4) = 1/(64)
	// smallest num:	0 000 0001

	// biggest representable value = 2^3 * (2 - 2^-4) = 15.5
	// biggest num:		0 110 1111


	char data;

public:
	qpfloat(float i)
	{
		if (i > 15.5)
		{
			this->data = 0x70;
			return;
		}
		if (i < -15.5)
		{
			this->data = 0xf0;
			return;
		}

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

		std::cout << std::endl;
	}
	~qpfloat();

	std::string bin()
	{
		char str[9];
		char i = this->data;

		for (int j = 0; j < 9; j++)
		{
			// printf("%x\t%x\n", i & 0xff, i & 0x80);
			if (j == 4)
				str[j] = ' ';
			else
			{
				if ((i & 0x80) >> 7 == 1)
					str[j] = '1';
				else
					str[j] = '0';
				i = i << 1;
			}
		}
	return str;
	}
};

int main()
{
	qpfloat& t = *(new qpfloat(INFINITY)); // less than minimum
	std::cout << t.bin() << std::endl;

	qpfloat& s = *(new qpfloat(-INFINITY)); // greater than maximum
	std::cout << s.bin() << std::endl;

	qpfloat& u = *(new qpfloat(-12));
	std::cout << u.bin() << std::endl;

	qpfloat& v = *(new qpfloat(12));
	std::cout << v.bin() << std::endl;

	qpfloat& w = *(new qpfloat(0.043));
	std::cout << w.bin() << std::endl;

	qpfloat& p = *(new qpfloat(-5523323.502));
	std::cout << p.bin() << std::endl;



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



sign 	1xxx xxxx
exp1	x11x xxxx
exp2	xxx1 xxxx
mant 	xxxx 1111


*/