#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	FILE *fpin;
	FILE *fpout;
	char *buff[BUFFER_SIZE];
	
	fpin = stdin;
	fpout = stdout;

	if ( 2 == argc ) {
		if ( NULL == (fpin = fopen(argv[1], "r")) ) {
			fprintf(stderr, "%s: cannot open file \'%s\'\n", argv[0], argv[1]);
			exit(EXIT_FAILURE);
		}

		fpout = stdout;
	}

	if ( 3 == argc ) {
		// FIXME: check whether the two files are same
		if ( 0 == strcmp(argv[1], argv[2]) ) {
			fprintf(stderr, "Input and output file must differ\n");
			exit(EXIT_FAILURE);
		}
		
		if (
			NULL == (fpin = fopen(argv[1], "r")) ||
			NULL == (fpout = fopen(argv[2], "w"))
		) {
			fprintf(stderr, "%s: cannot open file\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
       
	if ( 3 < argc )	{
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(EXIT_FAILURE);
	}

	// read input from stream fpin
	char *line;
	size_t linecap = 0;
	// FIXME: reverse at most BUFFER_SIZE lines?
	int  nline = 0;
	while ( 0 < getline(&line, &linecap, fpin) ) {
		buff[nline] = malloc(sizeof(char) * linecap);
		strcpy(buff[nline], line);
		++nline;
	}
	free(line);

	// write output to stream fpout
	for ( int i = nline; i > 0; --i ) {
		fwrite(buff[i - 1], 1, strlen(buff[i - 1]), fpout);
		free(buff[i - 1]);
	}

	fclose(fpin);
	fclose(fpout);

	return EXIT_SUCCESS;
}
