#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int arr[] = {42, 17, 93, 58, 76, 24, 89, 31, 65, 7};
	int arr_size = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe creation error\n");
		return (1);
	}
	pid_t id = fork();
	if (id == -1)
	{
		perror ("Fork error\n");
		return (2);
	}
	if (id == 0)
	{
		start = 0;
		end = arr_size / 2;
	}
	else
	{
		start = arr_size / 2;
		end = arr_size;
	}

	int sum = 0;
	int i = start;
	int childSum = 0;

	while (i != end)
	{
		sum += arr[i];
		i++;
	}

	if(id == 0)
		printf ("partil sum of child process: %d\n", sum);
	else
		printf ("partil sum of main process: %d\n", sum);
	if (id == 0)
	{
		close(fd[0]);
		if(write (fd[1], &sum, sizeof(sum)) == -1)
		{
			perror("write error\n");
			return (3);
		}
		close(fd[1]);
		return (0);
	}
	else
	{
		close(fd[1]);
		if(read(fd[0], &childSum, sizeof(childSum)) == -1)
		{
			perror("read error");
			return (4);
		}
		close(fd[0]);
		int status;
		pid_t pid = wait(&status);
		if (pid == -1)
		{
			perror("fork error\n");
			return (5);
		}
	}
	int totalSum = sum + childSum;
	printf("Total sum: %d\n", totalSum);
	return (0);
}