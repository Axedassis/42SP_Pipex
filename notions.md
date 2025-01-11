## Notes


[Symlink] -> is a special type of file that carrie informations of where the real
file/folder is storege. it only point to the path

### Functions that i still dont know

### ERROR FUNTCIONS
the functions works with the global variable [errno] that the value is set by many
other functions whend somehting goes wrong

#### perror
perror -> print a message before print the error message[errno], is way to make the errors more descreptive

```c
void perror(const char *str);
```
print the [str] before the erorr message. This function is particularly useful for debugging when you want to provide context for an error


#### strerror
Unlike perror, strerror doesn't print the error but provides a *string description*, which you can use to *format your custom error messages*.
The error codes like [errno] can be passed directly to [strerror] to get their textual representations.

```c
char *strerror(int errcode);
```

### access

The access function is used to determine the accessibility of a file or directory
by checking specific permission

```c
#include <unistd.h>

int access(const char *pathname, int mode);
```
Constant	        Description
[F_OK]	    Check for the file's existence.
[R_OK]	    Check for read permission.
[W_OK]	    Check for write permission.tituir o programa que 
[X_OK]	    Check for execute/search permission.

we can combine the flags using the operator *OR*( | )

if the returned value is *0* the request access mode is permitted.
if the returned value is *-1* the requst failed and the variable [errno] is set
to be used.

whend a error occurs the [errno] variable is set, some comuns values are

[ENOENT] - File or directory does not exist
[EACCES] - Permision Denied
[EROFS] - Write request in a read-only filesystem

A race condition occurs when a file is *modified* during its [runtime] state while your 
program is simultaneously attempting to perform an operation on it. For example, this 
might happen if your program tries to *write* to a file that is set as *read-only* right after checking its permissions.

To avoid issues caused by race conditions, it is recommended **not** to use functions like access for verifying *permissions* before performing operations. Instead, directly use functions such as open or write, and *handle* any resulting errors appropriately. This approach ensures you can react dynamically to unexpected permission changes or other problems during the file operation

### dup & dup2
are used to duplicate [file_descriptor]

```c
int dup(int oldfd);
```

return the lowest available value to the duplicate descriptor, if has  an error
it return **-1**

already the [[dup2]] is a little more flexible, it allow to choose what gonna be 
the value of the new duplicate descriptor

```c
int dup2(int oldfd, int newfd);
```

return tne value of the new file descriptor(newfd) or in case of error it returns
the **-1** 

*!* is insteristing to notice if the value of newfd is already in use it close
and redirect that space to the new fd, instead of dup that is automatically put in
a open space and dont close any file descriptor.


### execve
the function execv make part of a whole family of function [exec], and it is used to replace a program that's been execute by another one, keeping the old process in stand by 

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

whend the function is called the current programn in process is replaced by a new one indicates by the specifer [path], the old program is discarded by the new one.

[path] the path to the new executable program
[argv] an arry of string that keep the new arguments that is been passed for to the new program
[envp] an array of string represent the arguments to the new programma

if the execv succeeds, nothing after this call will be executed in the old programn

if get a error the retunr is **-1** and the error is set in the [errno]

### fork
The fork function create a duplicate processes from it wa called

```c
#include <unistd.h>

pid_t fork(void);
```
fork do not recive any parms.

the return value made by fork in the parent processes and in the child processes is different

[parent_process] -> the return value is a PID of the [child_processes]
[child_process] -> return 0 with this the code know the processes is running
or **-1** if had an error, and the value is set in [errno]

__how it work__
1. whend the function *fork* is called it create a new process been exactly the
copy of the original processes include the variable values, register and another
resourcers from the processes.

2.after the creation of a main processes copy both one and other (parent and child processes)
still running independent from one to each other (*is possible has shared memory betwenn the processes*)

__uses of fork__
1. the most common use of fork in softwares is to create multiple sub processes to
execute task in parallel. it is way common in server where different processes can
handle with mant different connections

2.in complexy system it can be used to managed N things and execute another independemente
When you invoke multiple fork() calls within a loop or conditional structure, 
you can create a large number of child processes, which can be used for 
high-performance tasks or bulk processing

**COW** a acronym to Copy on Write, initial both the processes share the same 
space on memory, without duplicated, only whend one of the values change as a 
variable change their value is allocated and modify with the new value.

[Orphan_Processes]: An orphan process is a process that loses its parent process. It is adopted by the init process (PID 1).

[Zombie_Processes]: These are processes that have finished executing but the parent process has not called wait() to collect their exit status. The child process still appears in the process table until the parent "reaps" it.

__Orphan Processes__
Occurs when a process loses its parent because tha parent process finishes execution before the child. when this happens, the operating system automatically reassigns the orphaned process to the [init] processe (PDI 1)
__Zombie Processes__
Processes that have finished execution but still occupy an entry in the process table because heir *parent process* has not called **wait()** or **waitpid()**

whend a new process end to take their exit status code we had to use 


```c
int main(void)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("child processes context");
        return (0); //end child processes
    } else
    {
        wait (NULL) //parent waits for child to finishand reaps it;
        printf("Parent reaped the child process\n");
    }
    return (0);
}
```

The parent process calls wait(NULL) to collect the child process’s exit status, preventing it from becoming a zombie
/            \
  (1)child/ x      (2)secondChild/ z
         /
(2)grandChild/ y

(1): created by 1st fork
(2): created by 2nd fork

Explanation of the while() at the end:

The conditions set up in a way to make sure that a process can only break out of the loop if it has no more children alive. It is necessary because of the reasons explained in the video. The first process that will successfully break out of it will be either y or z, as they have no children to wait for: so wait() will return -1, and errno will be set to ECHILD .

Now the tricky part starts here, because lets say it was process z that just terminated: its parent process was also waiting for one of its children(z or x) to finish. So lets look at what is going on in the parent after z terminated.

So after z finished running, the wait() call will return in the parent, and the loop will evaluate the return value, which wont be -1 in this case, because parent had a child (z) which just terminated. And this is why wait() is called inside a loop: in the case wait() returned in the parent, but it is not desired to continue execution in the parent, the parent process will get stuck at the wait() again instead of continuing. It will get inside the loop and print "Waited for child to finish", it will then loop back to the wait call, and since it has one more child (x) alive, it will wait for that child to change state. 
This cycle will keep repeating until there are no children to wait for in the parent process.

The fact that the printf() inside the while loop printed 3 times means that there were 3 cases in total when wait() didn't produce an error, meaning 3 times when a process had a child process that terminated. One printf() comes from the parent when z terminated, one comes from x when y terminated, and the 3rd one comes from parent again when x terminated. So each time the wait() function didn't produce an error, the while loop kept calling it again and forced it to produce one, which I personally find interesting.

After z terminated the parent produced the first printf() from inside the loop. Then the only process that can do anything is y, which has no other children, so the wait() inside y will return with -1 and y will terminate as well. This then will be detected by the wait() inside x which was waiting for y to exit, but in this case wait() returns the pid of y, meaning that x will go inside the while loop and print the second "Waited for child to finish" msg, which serves no real purpose at this time, as there are no other children that x is waiting for. So after the printf(), x will have to loop back and make a call to wait() again until all of its children terminated. If x, or any of the processes had more than one child, the loop would make sure that all of them are properly terminated.

Suggestion: instead of calling wait() at the end of the function and printing the same stuff from all of the children, call it at the start, right after you forked.
You already have an if else tree to identify all the processes, so if you printf() AFTER you waited can use it to visualize who waited for who and see if the code really worked as expected or not.
The parent should print last, and y should print before x.

int	main()
{
	int		id1 = fork();
	int		id2 = fork();

	while (wait(NULL) != -1 || errno != ECHILD)
	{
		;
	}
	if (id1 == 0)
	{
		if (id2 == 0)
		{
			printf("grandchild\n");
		}
		else
		{
			printf("1st child of parent\n");
		}
	}
	else
	{
		if (id2 == 0)
		{
			printf("2nd child of parent\n");
		}
		else
		{
			printf("parent\n");
		}
	}
	return (0);
}


So in this case the possible outputs would be:

2nd child
grandchild
1st child
parent

or:

grandchild
1st child
2nd child
parent
### wait and waitpid

__wait__ 
the wait funtion suspends execution of the calling process until one of its *child* processes terminates.

```c
pid_t wait(int *status);
```
status values can be NULL if we don't need the information of the response.
in the case of recieve the status value is gonna be the PID of end process
or **-1** in case of an error (the errno function is also set in this scneraio)

__waitpid__
thw waitpid function provides more control compared to [wait]. It allows waiting for a specific child process or gor processes mathing certain criteria.

```c
pid_t waitpid(pid_t pid, int *status, int options);
```
[pid] can hold some values that change their behavior
- *-1* wait for ant child process (same as [wait])
- *>0* wait for the child process with this specific PID
- *< -1* wait for any child process in the process group whose ID is [pid]

[status] pointer to store the child process's status
    to inspect the status we can use macros as  *WIFEXITED*, *WEXITSTATUS*,*WIFSIGNALED*, *WIFSIGNALED*,
*WTERMSIG*


FUNCTIONS SYNTAX (for their names)
[Prefix]		[Meaning]
W			Wait (esperar)
IF			If (se, condição)
EXITED		Saiu normalmente
EXITSTATUS	Código de saída
SIGNALED	Encerrado por um sinal
TERMSIG		Sinal de término
STOPPED		Processo parado
STOPSIG		Sinal que parou
CONTINUED	Processo continuado


__WIFEXITED__ -> Retorna [TRUE] se o processo filho terminou normalmente como um exit(sucess ex) ou
o retorno da main.

__WEXITSTATUS__ -> Retorna o código de retorno do exit ou de um return na main. somente valido
a verifição se __WIFEXITED__ retornar true!!


__WIFSIGNALED__ -> Verifica se o processo foi terminado por um sinal do sistema

__WTERMSIG__ -> retorna o sinal terminado pelo processo filho. existem alguns sinais que são comun
mas todos eles podem ser encontrados dentro da biblioteca <signal.h>
SIGSEGV, SIGKILL,SIGABRT ......

-----------------------------------------------------------------------
A way to wait all child process finish is with

```c
while (wait(NULL) != -1 || errno != ECHILD)
	printf ("Waited for a child to finish\n");
```

a wait that return `-1` means that's nothing more to wait or something
goes wrong to prevent to continue without wait everthnig 

-----------------------------------------------------------------------

[options] modifes the behavior of *waitpid* common option incluse
- *WNOHANG* return immediatly if no child process has exited
- *WUNTRACED* waits for child processes that have stopped

Returns the PID of the terminated or stopped child process.
If no child process has exited, and WNOHANG is specified, it returns 0.
On error, it returns -1.

### pipe
the pipe function handle with the task of create a connection between two different processes that are relationated, as example a parent processes and a child processes 

```c
int pipe(int pipefd[2]);
```

the arguments of pipefd are an array of two integers
- pipefd[0] -> the fd of read file
- pipefd[1] -> the fd of write file

the return value  is is *zero* if everything goes well or *minus one if had an error*

