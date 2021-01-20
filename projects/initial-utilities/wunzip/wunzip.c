#include <stdio.h>
#include <stdlib.h>	// exit, free
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char str;
	int count;

	if ( 2 > argc ) {
		fprintf(stderr, "usage: %s [file1 ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for ( size_t i = 1; i < argc; ++i ) {
		if ( NULL == (fp = fopen(argv[i], "r")) ) {
			fprintf(stderr, "%s: cannot open file\n", argv[0]);
			exit(EXIT_FAILURE);
		}
		
		while ( fread(&count, sizeof(int), 1, fp) ) {
			fread(&str, sizeof(char), 1, fp);
			while ( count-- )
				fwrite(&str, sizeof(char), 1, stdout);
		}

		fclose(fp);
	}

	return EXIT_SUCCESS;
}
