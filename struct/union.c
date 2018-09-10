#include <stdio.h>

typedef unsigned char u8;

int main( void )
{
    union{
        u8 led;         // for byte operation
        struct{         // for bits operation
            u8 p1:1;
            u8 p2:1;
            u8 p3:1;
            u8 p4:1;
            u8 p5:1;
            u8 p6:1;
            u8 p7:1;
            u8 p8:1;
        }pp;
    }led;    

    led.led = 0x55;

    printf( "led.pp.p1 = %d\n", led.pp.p1 );
    printf( "led.pp.p2 = %d\n", led.pp.p2 );
    printf( "led.pp.p3 = %d\n", led.pp.p3 );
    printf( "led.pp.p4 = %d\n", led.pp.p4 );
    printf( "led.pp.p5 = %d\n", led.pp.p5 );
    printf( "led.pp.p6 = %d\n", led.pp.p6 );
    printf( "led.pp.p7 = %d\n", led.pp.p7 );
    printf( "led.pp.p8 = %d\n", led.pp.p8 );



    return 0;
}
