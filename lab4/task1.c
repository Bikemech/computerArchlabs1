#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int buf_in(int fd, char* buf, int* ptr)
{
	if (buf[0] == 0)
	{
		int sz = read(fd, buf, 16);
		printf("\nBUFFUP! \t%d\n", sz);
		if (sz == 16) return sz;
		
		int i;
		for (i = sz; i < 16; i++)
		{
			buf[i] = 0;
		}
		return sz;
	}

	int byte = (int) buf[*ptr];
	*ptr = *ptr + 1;
	if (*ptr == 16)
	{
		*ptr = 0;
		buf[0] = 0;
	}
	return byte;
}

int main()
{
	int fd = open("foo.txt", O_RDONLY);
    char* buffer = malloc(16);
    int ptr = 0;
    int sz = buf_in(fd, buffer, &ptr);

    int i;
    char c = 1;
    while (c)
    {
    	c = buf_in(fd, buffer, &ptr);
    	printf("%c ", c);
    }


	return 0;
}