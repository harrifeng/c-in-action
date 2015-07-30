#include <stdio.h>

int main(int argc, char *argv[])
{
    int j;

    for (j = 0; j < argc; j++)
        printf("agrv[%d] = %s\n", j, argv[j]);
    return 0;
}

/**************************************************/
/* <===================OUTPUT===================> */
/* $ ./necho hello world                          */
/* agrv[0] = ./necho                              */
/* agrv[1] = hello                                */
/* agrv[2] = world                                */
/**************************************************/
