*This project has been created as part of the 42 curriculum by **ls-phabm***

# Description

> the project, including its goal and a brief overview

### Project

Learn the basics of threading a process by designing a simulation.

### Goal

- Create threads, explore the use of mutexes and handle time precision.

### Means

Simulate a philosophers' dinner with the following rules

- One or more philosophers sit at a round table.
- The philosophers take turns eating, thinking, and sleeping (each activity is mutually exclusive)
- There are as many forks as philosophers
- Philosopher routine
  - A philosopher must pick up both the fork to their right and the fork to their left before eating.
  - When a philosopher has finished eating, they put their forks back on the table and
    start sleeping.
  - Once awake, they start thinking again.
- The simulation stops when a philosopher dies of starvation

Important notes

- Every philosopher needs to eat and should never starve.
- Philosophers do not communicate with each other.
- Philosophers do not know if another philosopher is about to die.
- Needless to say, philosophers should avoid dying!

### Requirements

**Architecture**

- Global variables are forbidden!
- Program must take the following arguments:
  - number_of_philosophers
  - time_to_die time_to_eat (ms)
  - time_to_sleep (ms)
  - \[number_of_times_each_philosopher_must_eat\]
- Each philosopher has a number ranging from 1 to number_of_philosophers
- Philosopher number 1 sits next to philosopher number number_of_philosophers.
- Any other philosopher, numbered N, sits between philosopher N - 1 and philosopher
  N + 1.

**Logs**
Any state change of a philosopher must be formatted as follows:

- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died

**Race condition**
No overlapping in printed messages.

### Constraints

**Concurrency** : all threads including main run in concurrency : the OS scheduler decides who runs when. Without `pthread_join`, main won't wait for all threads to end before running. Risks :

- The main thread might finish before the other threads even start running
- Or while they are mid-execution
- Or after one finishes but not the other

**Race condition** : when multiple threads try to access a shared resource at the same time and the output depends on the order of the execution of those threads i.e. threads writing to stdout concurrently without synchronization → garbled output.
Fix with `mutex`.

**Deadlock** : when multiple threads are blocked forever as they are waiting for each other to release the occupied resource.

> !!! Missing unlock = "exiting thread still holds 1 lock" → deadlock (other threads wait forever for that mutex)
> → mutex never released
> → other threads block forever on pthread_mutex_lock
> → pthread_mutex_destroy in clean_up blocks or returns EBUSY
> → clean_up hangs or fails
> → program never exits

**Data race** : two threads access the same memory where at least one access is a write, concurrently without synchronization → UB (corrupted reads/writes).

> !!! Read & write must be protected !
> If only write is protected, then a thread might read a value not fully written yet.

**Time management** : detect death with 10ms precision

### Bonus

# Instructions

> any relevant information about compilation, installation, and/or execution

Commands to execute program:

```
make

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

./philo 10 800 200 400 [2]

valgrind --tool=helgrind ./a.out // spot data races

```

# Resources

> listing classic references related to the topic (documentation, articles, tutorials, etc.)
> a description of how AI was used — which tasks and which parts of the project.

- multithreading : <https://www.geeksforgeeks.org/c/multithreading-in-c/>
  - pthread : <https://www.geeksforgeeks.org/c/thread-functions-in-c-c/>
  - mutex :<https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/>
- philo :
  - <https://www.youtube.com/watch?v=raLCgPK-Igc>
  - <https://www.youtube.com/watch?v=zOpzGHwJ3MU>
- time management : <https://medium.com/@jalal92/the-dining-philosophers-7157cc05315>
- funcheck : <https://github.com/froz42/funcheck>
- Markdown : <https://www.markdownguide.org/cheat-sheet/>

AI was used to break down time management logic (gettimeofday(), get_time_in_ms, smart sleep), coding best practices (parsing & init via t_args, architecture design), debug edge cases.
