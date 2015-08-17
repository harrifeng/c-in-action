#include <stdio.h>

void stack_overflow(int depth) {
    char blockdata[1024 * 1024];
    printf("Overflow: %d\n", depth);
    stack_overflow(depth + 1);
}


int main(int argc, char *argv[])
{
    stack_overflow(0);
    return 0;
}
