# PHILOSOPHERS

In this project you will learn the basics of threading a process.
You will see how to create threads and you will discover mutexes.

# - Forks -

Fork system call is used to create a new process, which is called <i>child process</i>,
which runs concurrently with the process that makes the fork() call <i>parent process</i>.
After been created the child one, both processes will execute the next instruction
following fork() call. Both processes use same program counter, CPU registers, same open files.

fork() takes no parameter and returns integer:
- negative value -> unsuccessfull creation of child process;
- zero -> successfull cration of child process;
- positive value -> returned to parent or caller.
<pre>
<code>
#include <stdio.h>
#include <sys/types.h>

int main()
{
	fork();
	fork();
	fork();
	printf("hello world\n");
	return 0;
}

OUTPUT:

hello world		The number of times "hello world\n" is printed
hello world		is equal to number of processes crated.
hello world		NUM of processes = 2^n, where n is the number of 
hello world		fork system calls. In this case n = 3,
hello world		2^3 = 8.
hello world
hello world
hello world
</code>
</pre>

# - Threads -

A program under execution is known as process an a thread is a basic unit of
execution.
So each program has a number of processes associated with it and each process has a number of threads executing in it.
A thread is a basic unit of CPU utilization.

Thread comprises ->
		                THREAD ID;
			                  PROGRAM COUNTER;
				                    REGISTER SET;
					                      A STACK

It shares with other thread belonging to the same process its code section,
data section and other operating-system resources such as open files and signals.

A traditional/heavyweight process has a SINGLE THREAD of control.
If process has MULTIPLE THREADS of control, it can perform more than a task at a time.
<pre>
<code>

----------------------------		------------------------------------------
|      SINGLE THREAD	   |		|         MULTI-THREADED PROCESS         |
----------------------------		------------------------------------------
|  code	|  data	 |  files  |		|     code     |    data     |	 files   |
----------------------------		------------------------------------------
|  registers  |   stack	   |	        |   registers  |  registers  | registers |
----------------------------		------------------------------------------
|	   thread	   |		|     stack    |    stack    |	 stack   |
----------------------------		------------------------------------------
					|     thread   |   thread    |   thread  |
					------------------------------------------
					
</code>
</pre>
Benefits of multithreaded programming has 4 major categories:

Responsiveness. Multithreading an interactive application may allow a program to continue running
even if part of it is blocked or is performing a lenghty operation, thereby increasing responsiveness to the user.

Resource sharing. By default, threads share memory and resources of the process where they belong.
The benefit of sharing code and data is that it allows an application to have several different threads of activity whitin the same address space.

Economy. Allocating memory and resources for process creation is costly.
Cause threads share resources of the process where they belong, it's more economical to create and switch threads.

Utilization of multiprocessor architecture. Benefits of multithreading can be greatly increased in a multiprocessor architecture,
where threads may be running in parallel on different processors.
A single-threaded process can only run on one CPU, no matter how many are available. Multithreading on a multi-CPU machine increases concurrency.

# - Mutex -

A mutex is a MUTually EXclusive flag. Acts as a gate keeper to a section of code
allowing one thread in and blocking access to all others.
This ensures that the code being controlled will only be hit by a single thread at a time.
Always remember to destroy the mutex when everything is done.

# - Semaphores -

Semaphores are very useful in process synchronization and multithreading.
Must include <semaphore.h> and compile the code with -lpthread -lrt.

To lock a semaphore or wait we can use the sem_wait function -> <i>int sem_wait(sem_t *sem);</i>

To release or signal a semaphore we can use the sem_post function -> <i>int sem_post(sem_t *sem);</i>

A semaphore is initialized
by using sem_open() for IPC
-> <i>sem_open(sem_t *sem);</i>

by using the sem_init function for process and threads
-> <i>int sem_init(sem_t *sem, int pshared, unsigned int value);</i>
- sem = semaphore to be initialized
- pshared = this argument specifies if initialized sem is shared between processes or threads
-> non-zero value = sem shared btw processes
-> zero value = sem shared btw threads
- value = value to assign to new initialized semaphore

To destroy a semaphore we can use sem_destroy function -> <i>int sem_destroy(sem_t *sem);</i>

