#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <stdio.h>
#include "btype.h"

#define DBG1(fmt, args...)              do{ dbg_fmt_print(fmt, ##args); }while(0)
#define DBG2(fmt, ...)                  do{ dbg_fmt_print(fmt, ##__VA_ARGS__); }while(0)
#define DBG_DATA(buff, len, fmt, args...)   \
                                        do{ \
                                            dbg_fmt_print(fmt, ##args); \
                                            dbg_data_print(buff, len, dbg_hex_print); \
                                        }while(0)

typedef void (* dbg_print_t)(u8_t c);

void dbg_fmt_print(char *fmt, ...);
void dbg_hex_print(u8_t c);
void dbg_dec_print(u8_t c);
void dbg_char_print(u8_t c);
void dbg_data_print(u8_t *buff, u16_t len, dbg_print_t print);
#endif
