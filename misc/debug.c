#include "debug.h"
#include <stdarg.h>

void dbg_hex_print(u8_t c)
{
   dbg_fmt_print("%02x ", c); 

   return;
}

void dbg_dec_print(u8_t c)
{
    dbg_fmt_print("%c", c);

    return;
}

void dbg_char_print(u8_t c)
{
    dbg_fmt_print("%d ", c);

    return;
}

void dbg_fmt_print(char *fmt, ...)
{
    va_list ap; 

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    return;
}

void dbg_data_print(u8_t *buff, u16_t len, dbg_print_t print)
{
    u16_t in = 0;

    if( NULL == buff || 0 == len )
        return;

    for( in = 0; in < len; in++ )
        print( buff[in] );

    dbg_fmt_print( "\r\n" );

    return;
}
