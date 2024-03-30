# Shell Project 3

This project is an implementation of a Linux shell using the C programming language for Operating Systems course. 

## Group members
*Faris Ćatić* \
*Haris Planinčić*



## List of all files and directories
1. *main.c* - main project,
2. *system_calls.c* - code for implementation of fork(), wait() and exec() system calls,
3. *clone_execle.c* - code for implementation of clone() and execle(),
4. *forkbomb.c*: - code for implementation of forkbomb (not compiled)

- systemcall - compiled code for system_calls.c
- cloneexecle - compiled code for clone_execle.c
- shell - compiled code for main.c and the actuall shell.

## Outline
1. Custom prompt

2. The Shell can perform all built-in commands, but it also calls the custom implementations of the following commands:
- *wc* with flags:
	- 'l' or '--lines': _option to count number of lines_
	- 'b' or '--bytes': _option to count number of bytes_
	- 'w <word>': _custom implementation of counting occurences of a specific word in a file_
- *df*
- *grep* with flags:
    - '-i' or '--ignore-case': _option to perform case-sensitive search_ 
    - '-n' or '--line-number': _option to display line numbers along with matching lines_
    - '-r' or '--recursive': _option to search recursively in directories_
- *cmatrix*

3. System calls:
- *fork()*
- *wait()*
- *exec()*
- *clone()*
- *execle()*

4. Implementation of forkbomb



## Answers to task 1.5

### Q1: If we have a single-core, uniprocessor system that supports multiprogramming, how many processes can be in a running state in such a system, at any given time?

A1: In a single-core, uniprocessor system with multiprogramming support, the running state is exclusive to one process at any given moment. This means that only a single process can actively execute instructions on the CPU at a time. While other processes may be ready and waiting for their turn to execute, only the currently running process has access to the CPU resources. The operating system employs scheduling algorithms to manage this process allocation, ensuring fair and efficient utilization of the CPU among the various processes competing for execution.



### Q2: Explain why system calls are needed for a shared memory method of inter-process communication (IPC). If there are multiple threads in one process, are the system calls needed for sharing memory between those threads?


A2: Shared memory in inter-process communication (IPC) relies on system calls to establish memory segments accessible by multiple processes. These calls enable processes to create shared memory regions, which are mapped into their address spaces. Other processes wishing to access this memory also map it into their address spaces using the same system call.

However, within a single process, threads share the same address space, eliminating the need for system calls to share memory. This intra-process sharing is often more efficient as it avoids the overhead of invoking system calls and context switching between processes.

### Q3: Consider the following sample code from a simple shell program. Now,
### suppose the shell wishes to redirect the output of the command not to STDOUT but to a file
### “foo.txt”. Show how you would modify the above code to achieve this output redirection.


```
command = read_from_user();
int rc = fork();
if(rc == 0) { //child
	exec(command);
}
else { //parent
	wait();
}
```
A3: Firstly, to open the file I would use
```
int fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
```

and to redirect I would use
```
dup2(fd, STDOUT_FILENO); 
```

The complete modified code would look like this:
```
char *command = read_from_user();
    int rc = fork();
    
    if (rc < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (rc == 0) { // child
        int fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Redirect STDOUT to the file descriptor associated with "foo.txt"
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        close(fd);

        execlp(command, command, NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    } else { // parent
        wait(NULL);
    }
```

## How to compile and run

To use the Shell, simply open the terminal in the same directory as the program files and compile it with a compiler, like gcc, using the following command:

```bash
gcc -Wall -o shell main.c
```
To start the program run the following command:
```bash
./shell
```


To compile the system_calls.c file:
```bash
gcc -Wall -o systemcall system_calls.c
```
To start the program run the following command:
```bash
./systemcall
```

To compile the clone_execle.c file:
```bash
gcc -Wall -o cloneexecle clone_execle.c
```
To start the program run the following command:
```bash
./cloneexecle
```

Use forkbomb at your own will :)

## Challenges we encountered
- Debugging errors in piping.
- Handling input/output redirection, could not include piping and redirection in our project because we could not find solutions.
- testing cmatrix, had to give sudo permissions to user.




## Sources/tutorials
1. https://brennan.io/2015/01/16/write-a-shell-in-c/
2. https://github.com/Sa3eedoo/Simple-shell-implementation/blob/main/shell.c
3. https://www.youtube.com/watch?v=rj7DOPPTkQA&t=340s&ab_channel=ServetGulnaroglu
4. http://www.dmulholl.com/lets-build/a-command-line-shell.html
5. https://www.geeksforgeeks.org/making-linux-shell-c/
6. https://www.youtube.com/watch?v=K8dCh3ZMLN8&t=175s&ab_channel=JacobSorber
7. http://www.vishalchovatiya.com/clone-system-call-example/
