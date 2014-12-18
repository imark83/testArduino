
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
 
/* My Arduino is on /dev/ttyACM0 */
char *portname = "/dev/ttyACM0";
char data[3];
 
int main(int argc, char **argv) {
	int arduino;
	int k=0;
 
	/* Open the file descriptor in 
	   READ ONLY
	   non-blocking mode */
	if (argc > 1) 
		arduino = open(argv[1], O_RDONLY | O_NOCTTY);
	else
 		arduino = open("/dev/ttyACM0", O_RDONLY | O_NOCTTY);
	/* Set up the control structure */
	struct termios toptions;
 
	/* Get currently set options for the tty */
	tcgetattr(arduino, &toptions);

	/* Set custom options */
	/* 9600 baud */
	cfsetispeed(&toptions, B9600);	
 
	/* wait for 3 bytes to come in before read returns */
	toptions.c_cc[VMIN] = 3;
	/* no minimum time to wait before read returns */
	toptions.c_cc[VTIME] = 0;
 
	/* commit the options */
	tcsetattr(arduino, TCSANOW, &toptions);
 
	/* Wait for the Arduino to reset */
	/* Flush anything already in the serial datafer */
	tcflush(arduino, TCIFLUSH);
	
	while (1) {
		printf ("%10u: input -> ", k++);
		int serialAvailable;
		ioctl (arduino, FIONREAD, &serialAvailable);
		if (serialAvailable) {
			read(arduino, data, 3);
 			if (data[0] != 'c') exit (0);
			//printf ("'%c', '%hi'\n", *((char*) data), *((short int*) (data+1)));
			printf ("'%c', '%+3hhi', '%hhu'\n", *((char*) data), *((unsigned char*) (data+1))-128, *((char*) (data+2)));
		} else printf ("\n");
		usleep (50*1000);
	}
	return 0;
}
