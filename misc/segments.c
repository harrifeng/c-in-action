#include <stdlib.h>
#include <stdio.h>

double t[0x02000000];

void segments() {
    static int s = 42;
    void *p = malloc(024);
    printf("%-20s%-20p\n", "stack", &p);
    printf("%-20s%-20p\n", "brk", sbrk(0));
    printf("%-20s%-20p\n", "heap", p);
    printf("%-20s%-20p\n", "static(bss)", t);
    printf("%-20s%-20p\n", "static(init)", &s);
    printf("%-20s%-20p\n", "text", segments);

}

int main(int argc, char *argv[])
{
    segments();
    return 0;
}


/**************************************************/
/* <===================OUTPUT===================> */
/* stack               0xbfdf3dec                 */
/* brk                 0x18200000                 */
/* heap                0x181df008                 */
/* static(bss)         0x804a040                  */
/* static(init)        0x804a01c                  */
/* text                0x8048444                  */
/**************************************************/
