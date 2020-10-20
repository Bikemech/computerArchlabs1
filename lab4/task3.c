#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char buf_in(int fd, char* buf, int* ptr)
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

		if (sz == 0) sz = -1;
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

void buf_out(int fd, char* buf)
{
	write(fd, buf, 16);
}

void buf_flush(int fd, char* buf, int sz)
{
	write(fd, buf, sz);	
}

int main(int argc, char** argv)
{
	if (argc < 3) return 1;

	char* source = argv[1];
	char* destination = argv[2];
	int fd_out = open(destination, O_WRONLY | O_CREAT);
	int fd_in = open(source, O_RDONLY);

	char* buffer = malloc(16);

	int sz = 16;

	while (1)
	{
		sz = buf_in(fd_in, buffer, NULL);
		printf("%d\n", sz);
		if (sz != 16) break;
		buf_out(fd_out, buffer);
		buffer[0] = 0;
	}

	buf_flush(fd_out, buffer, sz);

	close(fd_out);

	return 0;
}