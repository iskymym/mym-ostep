#include <stdio.h>
#include <stdlib.h>	// exit free
#include <string.h>	// strstr

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char *line = NULL;
	size_t linecap = 0;

	if ( 2 > argc ) {
		fprintf(stderr, "wgrep: searchterm [file ...]\n");
		exit(EXIT_FAILURE);
	}

	if ( 3 <= argc && NULL == (fp = fopen(argv[2], "r")) ) {
		fprintf(stderr, "wgrep: cannot open file\n");
		exit(EXIT_FAILURE);
	}
	
	// $ ./wgrep searchterm
	// take input from stdin
	if ( 2 == argc )
		fp = stdin;

	while ( 0 < getline(&line, &linecap, fp) )
		if ( strstr(line, argv[1] ) )
			printf("%s", line);
	
	// getline malloc space for line if line is NULL
	free(line);
	fclose(fp);

	return 0;
}
