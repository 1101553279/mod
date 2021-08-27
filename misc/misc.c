#include "debug.h"




int main(int argc, char *argv[])
{
    u8_t buff[10] = { 0x11, 0x22, 0x33, 0x44};

    DBG1("test DBG1 macro! %d\r\n", 1);
    DBG2("test DBG2 macro! %d\r\n", 2);
    DBG_DATA(buff, 5, "frame(%d) : ", 5);

    return 0;
}
