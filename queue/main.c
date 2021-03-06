#include <stdio.h>
#include "com.h"
#include "frame.h"
#include "debug.h"




u8_t frame_match( un_t master, un_t slave )
{
    return master == slave;
}

int main( void )
{
    int i = 0;  
    un_t da;
    s8_t ret= 0;
    s32_t index;
    com_t com;
    frame_t frame; 
    frame_t query; 
    un_t buff[ 100 ]; 
    u16_t len;
    un_t store[ ] = { 
                    0x02,0x42,0x35,0x03,0x38,0x3a,
                    0x02,0x42,0x37,0x03,0x38,0x38,
                    0x02,0x2,0x42,0x37,0x38,0x3,
                    0x02,0x2,0x42,0x37,0x3,0x39,
#if 0
                    0x02,0x41,0x36,0x03,0x38,0x39,
                    0x02,0x42,0x36,0x03,0x38,0x39,
                    0x02,0x41,0x31,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x33,0x32,0x03,0x30,0x30, 
                    0x02,0x41,0x32,0x03,0x38,0x3d,
                    0x02,0x41,0x38,0x30,0x30,0x30,0x30,0x03,0x30,0x30,
#endif
                    };
#if 1 
    dout( ">> frame init & put two frames \n" );
    ret = frame_init( &frame, 0x02, 0x03, 0x41, 0 );
    if( 0 != ret )
        dout( "frame_init fault!\n" );

    frame_match_set( &frame, frame_match );

    for( i= 0; i < sizeof(store); i++ )
    {
        ret = frame_put_one( &frame, store[i] );
        if( 0 != ret )
            dout( "frame put one fail!: i = %d, data = %#x\n", i, store[i] );
    }
    
    frame_print( &frame ); 
    
//    ret = frame_frame( &frame ); 
//    dout( "frame frame = %d\n", ret );
    dout( ">> get 4 frame!\n" );
    for( i = 0; i < 4; i++ )
    {
        len = frame_get( &frame, buff, sizeof(buff) ); 
//        len = frame_match_get( &frame, buff, sizeof(buff) ); 
        if( 0 != len )
        {
            dout( "frame get success!: i = %d, len = %d : ", i, len );
                debug_dump( buff, len, print_hex ); 
        }
        else
            dout( "frame get fail!: i = %d, len = %d \n", i, len );

        frame_print( &frame );
    }

//    ret = frame_frame( &frame ); 
//    dout( "frame frame = %d\n", ret );

//    dout( "\n" );
//    frame_print( &frame );

    dout( ">> frame query !\n" );
    frame_query( &frame, &query );
    frame_print( &query );
    dout( "\n" );

#endif

#if 0
    com_init( &com );
#if 0
    com_push( &com, 0 );

    if( com_in( &com, 0 ) )
        dout( "0 in com \n" );
    else
        dout( "0 not in com \n" );
#endif 
    dout( ">>. com start\n" );
    com_print( &com );

    dout( ">>. com push 11 units\n" );
    for( i = 0; i < 11; i++ )
    {
        ret = com_push( &com, i );
        if( 0 != ret )
           dout( "push error: ret = %d, i = %d\n", ret, i ); 
    }

    com_print( &com );
    
    dout( ">>. com pop 4 units\n" );
    for( i = 0; i < 4; i++ )
    {
        ret = com_pop( &com, &da );
        if( 0 != ret )
            dout( "pop error: ret = %d, i = %d\n", ret, i );
        else
            dout( "%d pop %d\n", i, da );
    }

    com_print( &com );

    dout( ">>. com push 3 units\n" );
    for( i = 0; i < 3; i++ )
    {
        ret = com_push( &com, i );
        if( 0 != ret )
           dout( "push error: ret = %d, i = %d\n", ret, i ); 
    }

    com_print( &com);
    
    dout( ">>. com push 1 unit\n" );
    ret = com_push( &com, i );
    if( 0 != ret )
        dout( "push error: ret = %d, i = %d\n", ret , i );
    
    com_print( &com );
 
    dout( ">>. com push 1 unit\n" );
    i++; 
    ret = com_push( &com, i );
    if( 0 != ret )
        dout( "push error: ret = %d, i = %d\n", ret , i );
    com_print( &com );

    dout( ">>. com pop 5 units!\n" );
    for( i = 0; i < 5; i++ )
    {
        ret = com_pop( &com, &da );
        if( 0 != ret )
            dout( "pop error: ret = %d, i = %d\n", ret, i );
        else
            dout( "%d pop %d\n", i, da );
    }
   
    com_print( &com ); 
    dout( ">>. com push rear 6 unit\n" );
    for( i = 0; i < 6; i++ )
    {
        ret = com_push_rear( &com, i );
        if( 0 != ret )
            dout( "push error: ret = %d, i = %d\n", ret , i );
    }
    com_print( &com );
   
    dout( ">> com reset !\n" ); 
    com_reset( &com );
    com_print( &com);

    dout( ">> com push rear 6 unit !\n" );
    for( i = 0; i < 6; i++ )
    {
        ret = com_push_rear( &com, i );
        if( 0 != ret )
            dout( "push error: ret = %d, i = %d\n", ret , i );
    }
    com_print( &com );
    
    dout( ">> com find !\n" );
    for( i = 0; i < 7; i++ )
    {
        index = com_find( &com, i ); 
        if( index >= 0 )
            dout( "find %d, find %d\n", i, index);
        else 
            dout( "find %d, no find!\n", i );
    }
    
    dout( ">> com push & pop 7 units!\n" ); 
    for( i = 0; i < 7; i++ )
    {
        ret = com_push( &com, i );
        if( 0 != ret )
            dout ( "push err: ret = %d, i = %d\n" , ret, i );

        ret = com_pop( &com, &da );
        if( 0 != ret )
            dout( "pop err: ret = %d, i = %d\n", ret, i );
        else
            dout( "pop unit: i = %d, am = %x\n", i, da );
    }
    com_print( &com ); 

    dout( ">> com len!\n" );
    for( i = 0; i < 8; i++ )
    {
        len = com_len( &com, i );
        if( len != 0 )
            dout( "index %d, len = %d\n", i, len );
        else
            dout( "index %d, no in range!\n", i );
    }

#endif

#if 0
//   printf( " LED_RUN = %d\n", LED_RUN );        // output 0

//init
    led_init( );


//for test
    for( i = 0; i < 2; i++ )
    {
        led_con( i, LED_ON );
        led_con( i, LED_OFF );
        dbg_out( "-------------\r\n" );
        
    }

    led_con_all( LED_ON );
    led_con_all( LED_OFF );
#endif 
    return 0;
}
