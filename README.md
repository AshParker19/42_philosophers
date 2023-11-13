## **_I never thought philosophy would be so deadly._**

## This project is about the famous dining philosophers problem. In order to solve this problem, I used the threads and mutexes concepts.

---

## _The dining philosophers problem_ is a classic synchronization problem. It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present formulation.

#### The word `philosopher` was kind of too long for the variable name, and the word 'philo' was annoying me a lot for some reason, so in my program I have a word `thinker` instead, why not?:)

The idea is to design a program in which a number of thinkers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.

• Every thinker needs to eat and should never starve.
• thinkers don’t speak with each other.
• thinkers don’t know if another thinker is about to die.
• There are also forks on the table. There are as many forks as thinkers.
• To eat, a thinker needs two forks.

---

## ```The new concepts of this project are```:

### `threads` 
To understand what is a thread, we need to understand what the processes are.
_Process is an instance of a program. When we start our computers we start the process, when we open the terminal we start the process, when we open the browser we start the process. Each process has a unique identifier called PID (process identifier)._

The thread is a sequence of instructions within a process. Each process has at least one thread. The difference between a process and a thread is that a process has its own memory space and a thread shares the memory space with the other threads of the same process. The threads of the same process can communicate with each other through shared memory. In other words, one thread can affect the variables of another thread.
And now the concept of `mutex` takes it's place. 

### `mutex`
`mutex` stands for mutual exclusion. It is a lock that we can use to protect a shared resource. A mutex has two states: locked and unlocked. When a thread locks a mutex, it becomes locked and no other thread can lock it. When a thread unlocks a mutex, it becomes unlocked and another thread can lock it. If a thread tries to lock a mutex that is already locked, it will be blocked until the mutex is unlocked.

### `threads synchronization`
Threads synchronization is a way to control the order of execution of threads. We can use mutexes to synchronize threads. For example, if we want to make sure that a thread A executes before a thread B, we can lock a mutex before the thread A and unlock the mutex after the thread A. Then, we can lock the mutex before the thread B and unlock the mutex after the thread B. In this case, the thread B will wait for the thread A to finish before it starts.

### `Data races`
Data races are the situations when two or more threads are trying to access the same shared variable at the same moment of time.
Thus, we need to protect the shared variables with mutexes. When the mutex is locked, no other thread can access the shared variable. So they will wait until the mutex is unlocked.

---

## ```The functions that I used are:```
| Function | Functionality |
| :---: | --- |
| ```pthread_create``` | create a thread |
| ```pthread_destroy``` | destroy a thread |
| ```pthread_join``` | wait for a thread to finish |
| ```pthread_mutex_init``` | initialize a mutex |
| ```pthread_mutex_destroy``` | destroy a mutex |
| ```pthread_mutex_lock``` | lock a mutex |
| ```pthread_mutex_unlock``` | unlock a mutex |

---

## ```Parameters of the program:```
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

---

## ```The algorithm of the syncronization:```

The biggest problem was to establish the order of the `thinker' actions. 
The rouctine for each should be the same as for the others, but they not suppose to affect each other.
So the idea was: the thinker with an even number will start eating first, and the thinker with an odd number will start eating after.
The problem was that the first thinker will start eating, and the second one will start eating at the same time, and the first one will die, because he will not be able to take the fork.

So, in a case of 4 thinkers, the order of the actions will be:
the thinkers with 2 and 4 indexes will start eating first, then they continue the routine, start sleeping etc. And only after that the thinkers with 1 and 3 indexes will start eating.

This approach makes sure that thinkers avoid stealing forks from each other.

So if `time to die` is greater than `time to eat` + `time to sleep`, the program will work correctly, and we will have an infitite routine of the thinkers. In the other case, one of the thinkers supppose to die of starwation.

---

## `Tools:`
in order to check memory leaks I used `valgrind`, as usually, but there are 2 flags which we need to use to check the program with threads had any data races:
* `--tool=helgrind`
* `--tool=drd`

---

## `How to use it`
1. Clone the repository with the command ```git clone```
2. Compile the program with the command ```make```
3. Run the program with the command ```./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]```

---

## `Recources:`
1. [Unix Threads in C](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=fUCFgG97IADL-acb)
2. [Mutexes in C](https://youtu.be/raLCgPK-Igc?si=wjyrMUThFqAyJKto)
