#include "util.h"
#include <limits.h>

// arith module
int arith_max(int x, int y) {
	return x > y ? x : y;
}

int arith_min(int x, int y) {
	return x > y ? y : x;
}

/*  
 *  (x < 0) != (y < 0 )     for no same symbol
 *
 * */
int arith_div(int x, int y) {
	if (-13/5 == -2
	&&	(x < 0) != (y < 0) && x%y != 0)
		return x/y - 1;
	else
		return x/y;
}

int arith_mod(int x, int y) {
	if (-13/5 == -2
	&&	(x < 0) != (y < 0) && x%y != 0)
		return x%y + y;
	else
		return x%y;
}

int arith_floor(int x, int y) {
	return arith_div(x, y);
}

int arith_ceiling(int x, int y) {
	return arith_div(x, y) + (x%y != 0);
}


// int to string.
char *int_to_string(long n, char *buff, unsigned char len) 
{
	char *s = buff + len;
    char *sm = buff;
	unsigned long m;

	if (n == LONG_MIN)
		m = LONG_MAX + 1UL;
	else if (n < 0)
		m = -n;
	else
		m = n;

	do
		*--s = m%10 + '0';
	while ((m /= 10) > 0);

	if (n < 0)
		*--s = '-';
    
    while( s < buff + len )
        *sm++ = *s++;

    *sm = '\0';

    return buff;         //return buff start address
}

