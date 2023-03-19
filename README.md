# PHILOSOPHERS

In this project you will learn the basics of threading a process.
You will see how to create threads and you will discover mutexes.

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
