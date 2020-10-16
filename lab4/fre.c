#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int buf_in(int fd, char** c){
    int sz; /*Read size*/
    if(*c[0] == 0)
    {
        printf("\nFill buf!\n");
        sz = read(fd, *c, 16);
        return sz;
    }
    else
    {
        printf("%c", *c[0]);
    }
    /*
    {
        sz = read(fd, *c, 1);
    } */
    *c = *c+1;
        if(*c[0] == 0)
        {
            *c = *c - 16;
            *c[0] = 0;

        }
    return sz;
}

int main(){

    int fd, sz;
    char* c = (char*) malloc(16*sizeof(char));
    fd = open("foo.txt", O_RDONLY);
    if(fd < 0)
    {
        perror("Could not read file"); 
        return 1;
    }

/*
    sz = buf_in(fd, &c);
    printf("\ncall to buf_in with empty buffer" 
            "returned %d bytes were read.\n", sz); 

    c[sz] = '\0'; 
    printf("Those bytes are as follows: %s\n\n", c);

    sz = buf_in(fd, &c);
    printf("\ncall to buf_in with non-empty buffer" 
            "returned %d bytes were read.\n", sz);
    c[sz] = '\0'; 
    printf("Those bytes are as follows: %s\n\n", c);

    printf("\n%#x\n", c[2] & 0xff);
*/
    int i;
    for (i = 0; i < 200; i++)
    sz = buf_in(fd, &c);

    printf("\n");

    return 0;
}