#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define ERROR_OPEN_FILE 1

#define FILE_PATH "./file.txt"

int main(void)
{
	//FILE *file = fopen(FILE_PATH);
	if (access(FILE_PATH, F_OK) == 0) //verify if the file exist
	{
		printf("The file %s exist\n", FILE_PATH);
		if (access(FILE_PATH, R_OK | W_OK) == 0) // verify if is possible read and write
			printf ("The file %s can be READ and WRITE\n", FILE_PATH);
		else
			printf ("The file %s can NOT be READ and WRITE\n", FILE_PATH);
	}
	else
		printf("The file %s do NOT exist\n", FILE_PATH);
	return (0);
}