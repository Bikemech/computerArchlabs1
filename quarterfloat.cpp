#include <iostream>
#include <string>

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

	// smallest non negative representable value = 1/(2^3 * 2^4) = 1/(127)
	// smallest num:	0 000 0001

	// biggest representable value = 2^3 * (2 - 2^-4) = 15.5
	// biggest num:		0 110 1111


	char data;
public:
	qpfloat(double i)
	{
		this->data = 0;
		if (i > 15.5) this->data = 0x70;
		if (i < -15.5) this->data = 0xf0;
	}
	~qpfloat();

	std::string bin()
	{

		std::cout << (int) this->data << std::endl << std::endl;

		unsigned char it = this->data;
		char str[8];
		int index = 7;

		while (index + 1)
		{
			std::cout << it << "\t";
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
	qpfloat& t = *(new qpfloat(-20));

	t.bin();
	std::cout << t.bin() << std::endl;

	return 0;
}