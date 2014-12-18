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
			printf ("%10u: input -> ", k++);
			//printf ("'%c', '%hi'\n", *((char*) data), *((short int*) (data+1)));
			printf ("'%c', '%hhu', '%hhu'\n", *((char*) data), *((char*) (data+1)), *((char*) (data+2)));
		} 
		usleep(104000);
		fflush (arduino);
	}
}
