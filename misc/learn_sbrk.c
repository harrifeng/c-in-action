#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    void *p;
    int size = 1;
    p = sbrk(0);
    printf("size : %d, p : %p \n", size, p);
    p = sbrk(size);
    p = sbrk(0);
    printf("size : %d, p : %p \n", size, p);
    return 0;
}

/**************************************************/
/* <===================OUTPUT===================> */
/* size : 1, p : 0x106295000                      */
/* size : 1, p : 0x106295001                      */
/**************************************************/
