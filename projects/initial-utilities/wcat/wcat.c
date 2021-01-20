#include <stdio.h>
#include <errno.h>
#include <stdlib.h>	// exit
#include <string.h>	// strerror

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[BUFFER_SIZE];
	
	// TODO: 1 == argc
	// take input from stdin
	// exit when hit EOF
	if ( 2 > argc ) {
		fprintf(stderr, "usage: %s <file1> ...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for ( size_t i = 1; i < argc; ++i ) {
		if ( NULL == (fp = fopen(argv[i], "r")) ) {
			fprintf(stderr, "wcat: cannot open file\n");
			exit(EXIT_FAILURE);
		}

		while ( fgets(buf, BUFFER_SIZE, fp) )
			printf("%s", buf);

		errno = 0;
		if ( 0 != fclose(fp) ) {
			strerror(errno);
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
