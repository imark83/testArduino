#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {

	FILE *arduino = fopen ("/dev/ttyACM0", "r");
	void *data = (void*) malloc (3);
	fflush (arduino);
	unsigned k=0;
	while (1) {
		if (fread(data, 1, 3, arduino) > 0) {
			usleep (10000);
			if (*((char*) data) != 'c') exit (0);
			printf ("%10u: input -> ", k++);
			//printf ("'%c', '%hi'\n", *((char*) data), *((short int*) (data+1)));
			printf ("'%c', '%+3hhi', '%hhu'\n", *((char*) data), *((unsigned char*) (data+1))-128, *((char*) (data+2)));
		} 
		usleep(40000);
		fflush (arduino);
	}
}
