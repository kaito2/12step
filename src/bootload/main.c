#include "defines.h"
#include "serial.h"
#include "lib.h"

volatile int value = 10;

int main(void)
{
    serial_init(SERIAL_DEFAULT_DEVICE);

    puts("first line\n");

    putxval(value, 0);
    puts("\n");

    // 静的変数の値の書き換えが反映されないことを確認
    value = 20;

    putxval(value, 0);
    puts("\n");

    while (1)
        ;

    return 0;
}
