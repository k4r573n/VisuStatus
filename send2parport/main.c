/*
 * File:   main.c
 * Author: karsten
 *
 * Created on 27. September 2010, 15:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


//zum  lpt ansteuern
#include <linux/ppdev.h>
#include <fcntl.h>
#include <sys/ioctl.h>

short verbose=0;

int init_parport(char *device)
{
	//öffnen
	int port;
	port = open( device, O_RDWR );
	ioctl( port, PPCLAIM, NULL );
	fprintf(stderr, "open.\n");

	return(port);
}


void close_parport(int port)
{	//schließen*/
	ioctl( port, PPRELEASE, NULL );
	close( port );
	fprintf(stderr, "Close.\n");
}


/* ein programm zum ausgeben von animationen auf einer
 * LED leiste
 *
 * * loged in User
 * * Recording
 * * converting job o.ä. running
 * * backup running
 * * Internet available
 * * Volkers PC an
 * * still alive - toggle
 *
 *
 */
int main(int argc, char** argv) {

    unsigned char wert = 0;
    extern char *optarg;
    extern int optind, opterr, optopt;
    int opt;
    char *device = "/dev/parport0";
    char effect = 0;

       //interpret parameters
    while ((opt = getopt(argc, argv, "w:s:d:h12345678v")) != -1) {
            switch (opt) {
                    case 'w': // decimal value
                        wert = atoi(optarg);
                        wert %= 256;
                        break;
                    case '1': // Xte LED
                        wert |= (1 << 0);
                        break;
                    case '2': // Xte LED
                        wert |= (1 << 1);
                        break;
                    case '3': // Xte LED
                        wert |= (1 << 2);
                        break;
                    case '4': // Xte LED
                        wert |= (1 << 3);
                        break;
                    case '5': // Xte LED
                        wert |= (1 << 4);
                        break;
                    case '6': // Xte LED
                        wert |= (1 << 5);
                        break;
                    case '7': // Xte LED
                        wert |= (1 << 6);
                        break;
                    case '8': // Xte LED
                        wert |= (1 << 7);
                        break;

                    case 's': //SPECIAL
                        effect = optarg[0];
                        break;

                    case 'd': // device
                        device = optarg;
                        break;
                    case 'v': // verbose
                        verbose = 1;
                        break;
                    case 'h': // help
                        //show_help();
                        exit(0);
                        break;
                    default:
                        //error
                        fprintf(stderr, "Short Usage: %s [-w <value>] [-d <device>] \n\t\t try -h for more information\n", argv[0]);
                        exit(1);
            }
    }

    int port = init_parport(device);//parport öffnen

    if (effect != 0 ) {
        switch (effect) {
            case '1':
                //a single LED load animation
                while (1) {
                    wert = 1;
                    int i;
                    for (i=1; i<9; i++) {
                        usleep(200000);
                        ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register
                        wert <<= 1;
                    }
                }
                break;

            case '2'://a filling load bar
                while (1) {
                    wert = 0;
                    int i;
                    for (i=1; i<10; i++) {
                        usleep(200000);
                        ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register
                        wert <<= 1;
                        wert += 1;
                    }
                }
                break;

            case '3': //a single LED reverse load animation
                while (1) {
                    wert = 128;
                    int i=1;
                    for (i=1; i<9; i++) {
                        usleep(200000);
                        ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register
                        wert >>= 1;
                    }
                }
                break;

            case '4': {// a single LED load left right animation
                wert= 1;
                int i;
                while (1) {
                    for (i=1; i<8; i++) {
                        usleep(200000);
                        ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register
                        wert <<= 1;
                    }
                    for (i=1; i<8; i++) {
                        usleep(200000);
                        ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register
                        wert >>= 1;
                    }

                }
                break;
            }
            case 'p': {
                int v;
                int counter =0;

                while (1) {
                    counter++;
                    counter%= 99999999; // um überlauf zuvermeiden
                    printf("counter %i value: %i \n",counter,v);
                    v = (counter/20);
                    v %= 255;

                    wert = 255;
                    ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register
                    usleep(v*10);

                    wert = 0;
                    ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register
                    usleep((255-v)*10   );
                }

                break;
            }
        }

    }


    ioctl( port, PPWDATA   , &wert ); // schreibt das "data"    Register

    //schließen
    close_parport(port);

    return (EXIT_SUCCESS);
}
