#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i = 0;
    /* Should be &i, Segmentation fault now! */
    scanf("%d", i);
    printf("%d", i);
    return 0;
}
