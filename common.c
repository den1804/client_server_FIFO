#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SOCK_PATH "/home/denis/socket"

char* getContent(char* filename);
int isFile(char *location);

char* getContent(char* filename)
{
	FILE *f = fopen(filename, "r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;

	return string;
}

int isFile(char *location)
{
	struct stat path_stat;
	stat(location, &path_stat);
	return S_ISREG(path_stat.st_mode);
}
