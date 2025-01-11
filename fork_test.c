#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int	id1 = fork();
	int id2 = fork();

	if (id1 == 0)
	{
		if (id2 == 0)
			printf("the child x2 process\n");
		else
			printf("the child x1 process\n");
	}
	else
	{
		if (id2 == 0)
			printf ("the copy of us main\n");
		else
			printf ("the main process\n");
	}

	return (0);
}