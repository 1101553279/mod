#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

/* p::  -p  ip address      option argument */
/* l:   -l  listen port     must has a argument */
/* d::  -d  display mode    option argument */
/* s:   -s  signal install  must has a argument */
/* the first colon ':'  means that will return ':' when a option missing argument */
/* notice: must is this format -p192.168.68.3 if option arguement */
/*         this format -p 192.168.68.3 is not ok! */
#define SRV_VERBOSE "verbose"
#define SRV_SIMPLE  "simple"

const char *optstring = "+:p::l:d::s:";
char *opt_ip = NULL;
char *opt_mode = SRV_SIMPLE;          /* log verbose or simple */
int main(int argc, char *argv[])
{
    int ret = 0;
    unsigned int opt_port = 3000;   /* listen port */
    unsigned char opt_sig = 0;      /* whether signal handler register */
    int opt_err = 0;                /* command parser result */
    
    opterr = 0;     /* prevent the error message when function(getopt) parsing */

    while(-1 != (ret=getopt(argc, argv, optstring)))
    {
        switch(ret)
        {
            case 'p':
                if(NULL != optarg)
                {
                    opt_ip = strdup(optarg);
                    printf("optarg = %s, opt_ip = %s\r\n", optarg, opt_ip);
                }
                break;
            case 'l':
                opt_port = atoi(optarg);
                break;
            case 'd':
                if(NULL != optarg && 0 == strcasecmp("verbose", optarg))
                    opt_mode = SRV_VERBOSE;
                else if(NULL != optarg && 0 != strcasecmp("simple", optarg))
                {
                    printf("-d \'argument\' must be \"verbose\" or \"simple\"\r\n");
                    opt_err = 1;
                }
                break; 
            case 's':
                opt_sig = (0==strcasecmp("yes", optarg))? 1: 0;
                break;
            case ':':   /* missing option argument */
                printf("\'%c\' must has a argument\r\n", optopt);
                opt_err = 1;
                break;
            case '?':   /* unrecognized option element */
                printf("\'%c\' no this option\r\n", optopt);
                opt_err = 1;
                break;
            default:
                break;
        }
    }
    if(1 == opt_err)
        return -1;

    return 0;
}

