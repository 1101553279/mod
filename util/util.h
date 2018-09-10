#ifndef __UTIL_H__
#define __UTIL_H__


// arith module
extern int arith_max(int x, int y);
extern int arith_min(int x, int y);
extern int arith_div(int x, int y);
extern int arith_mod(int x, int y);
extern int arith_ceiling(int x, int y);
extern int arith_floor  (int x, int y);

// array size calculation
#define NELEMS(x) ((sizeof (x))/(sizeof ((x)[0])))

// int to string
char *int_to_string(long n, char *buff, unsigned char len);

#endif
