#include "util.h"
#include <limits.h>
#include <stdio.h>

int main( void )
{
    char buff[ 50 ] = { 0 };
    char *pstr;
    int i = 0;

    printf("arith_max( 5, 2 ) = %d\n", arith_max( 5, 2 ) );
    printf("arith_min( 5, 2 ) = %d\n", arith_min( 5, 2 ) );
    printf("arith_div( 5, 2 ) = %d\n", arith_div( 5, 2 ) );
    printf("arith_mod( 5, 2 ) = %d\n", arith_mod( 5, 2 ) );
    printf("arith_ceiling( 5, 2 ) = %d\n", arith_ceiling( 5, 2 ) );
    printf("arith_floor( 5, 2 ) = %d\n", arith_floor( 5, 2 ) );
    

    for( i = -3; i < 3; i++ )
    {
        pstr = int_to_string( i, buff, sizeof(buff) );
        printf( "pstr = %s\n", pstr );
    }
    


    return 0;
}
