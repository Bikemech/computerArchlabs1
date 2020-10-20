#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void buf_out(int fd, char* buf)
{
	write(fd, buf, 16);
}

void buf_flush(int fd, char* buf, int sz)
{
	write(fd, buf, sz);	
}

int main()
{
	int fd = open("fisk.txt", O_WRONLY);
	char* line = "ALPHABETalphabet";

	unsigned int index = 0;

	char c = 1;
	int i;
	while (c != 0)
	{
		for (i = 0; i < 16; i++)
		{
			c = line[i + index];
			if (c == 0) break;
		}
		if (i == 16)
		{
			buf_out(fd, line + index);
			index = index + 16;
			printf("rebuff\n");
		}
	}

	buf_flush(fd, line + index, i);

	close(fd);

	return 0;
}