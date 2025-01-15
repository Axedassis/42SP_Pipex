#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FORK_FAILED 1
#define WAIT_FAILED 2

int main(void)
{
	pid_t pid = fork();

	if (pid == -1) // cannot 
	{
		perror("fork failed\n"); //print message before the error (to describe)
		return (FORK_FAILED);
	}

	if (pid == 0) //enter in the subprocess
	{
		printf ("Child process in execution\n");
		return (42);
	}

	int status = 0;
	pid_t pid_child = wait(&status);
	
	if (pid_child == -1)
	{
		perror ("wait failed\bn");
		return (WAIT_FAILED);
	}
	printf ("Child process %d ended\n", pid_child);
	if (WIFEXITED(status))
		printf ("The child process %d was end with codes status %d\n", pid_child, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf ("The child process %d was end by the system signal %d\n", pid_child, WIFSIGNALED(status));
	return (0);
}