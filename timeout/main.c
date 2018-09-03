#include <stdio.h>
#include "out.h"
#include "debug.h"

void timeout( u8_t no, u8_t flag )
{
    dout("timeout: no: %d, flag: %d\n", no, flag );
    return;
}

int main( void )
{
    int i = 0;  
    s8_t ret= 0;
    s32_t index;
    u16_t len;
    out_t outs[ 5 ];

#if 1
#if 1
    dout( ">> dout check!\n" ); 
    out_init( outs, 0, MODE_SINGLE, 5, timeout );
    out_init( outs+1, 1, MODE_PERIOD, 5, timeout );
   
    out_start( outs );
    out_print( outs, 2 );

    while( 1 )
    {
        out_check( outs );
        out_check( outs+1 );
        sleep( 1 );

        out_print( outs, 2 );
    }

#else
    dout( ">> dout init 4 single mode, one period!\n" );
    for( i = 0; i < 4; i++ )
        out_init( outs+i, i+1, MODE_SINGLE, 30+i, timeout );
    
    out_init( outs+i, i+1, MODE_PERIOD, 30+i, timeout );
    
    out_print(  outs, 5);
    
#if 0
    dout( ">> dout config!\n" );
    ret = out_config( outs+2, CON_ACTIVE, OUT_ACTIVE );
    if( 0 != ret )
        dout( "config fail! ret = %d\n", ret );
    ret = out_config( outs+2, CON_MODE, MODE_PERIOD );
    ret = out_config( outs+2, CON_FLAG, FLAG_ON );
    ret = out_config( outs+2, CON_STIME, 20 );
    ret = out_config( outs+2, CON_TIMEOUT, 10 );
    ret = out_config( outs+2, CON_HANDLE, led_con );
#endif
    out_print( outs, 5 );
   
    dout( ">> dout start!\n" );
    out_start( outs+2 );

    out_print( outs, 5 );

    dout( ">> dout stop!\n" );
    out_stop( outs+4 );

    out_print( outs, 5 );
#endif
#endif
    
    return 0;
}
