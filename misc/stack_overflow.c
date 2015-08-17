#include <stdio.h>

void stack_overflow(int depth) {
    /* Usually gcc us 32 bytes for one call */
    char blockdata[1024 -32];
    printf("Overflow: %d\n", depth);
    stack_overflow(depth + 1);
}


int main(int argc, char *argv[])
{
    stack_overflow(0);
    return 0;
}

/*********************************************************/
/* <===================OUTPUT On Mac===================> */
/* i309511@ misc (master) $ ulimit -a                    */
/* core file size          (blocks, -c) 0                */
/* data seg size           (kbytes, -d) unlimited        */
/* file size               (blocks, -f) unlimited        */
/* max locked memory       (kbytes, -l) unlimited        */
/* max memory size         (kbytes, -m) unlimited        */
/* open files                      (-n) 256              */
/* pipe size            (512 bytes, -p) 1                */
/* stack size              (kbytes, -s) 8515             */
/* cpu time               (seconds, -t) unlimited        */
/* max user processes              (-u) 709              */
/* virtual memory          (kbytes, -v) unlimited        */
/* i309511@ misc (master) $ ./a.out                      */
/* Overflow: 8378                                        */
/* Overflow: 8379                                        */
/* Segmentation fault: 11                                */
/*********************************************************/
