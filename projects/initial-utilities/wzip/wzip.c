#include <stdio.h>
#include <stdlib.h>	// exit
#include <string.h>

void write_to_file(int count, char old_buff)
{
	fwrite(&count, sizeof(int), 1, stdout);
	fwrite(&old_buff, sizeof(char), 1, stdout);
	// printf("%c", count);
	// printf("%c", old_buff);
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char cur_buff = 0;
	char old_buff = 0;
	int  count = 0;

	if ( 1 == argc ) {
		fprintf(stderr, "%s: file1 [file2 ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for ( size_t i = 1; i < argc; ++i ) {
		if ( NULL == (fp = fopen(argv[i], "r")) ) {
			fprintf(stderr, "%s: cannot open file\n", argv[0]);
			exit(EXIT_FAILURE);
		}

		while ( fread(&cur_buff, 1, 1, fp) ) {
			if ( cur_buff == old_buff) {
				++count;
				continue;
			}
			
			if ( 0 != old_buff )
				write_to_file(count, old_buff);

			count = 1;
			old_buff = cur_buff;
		}

		fclose(fp);
	}
	write_to_file(count, old_buff);

	return EXIT_SUCCESS;
}
