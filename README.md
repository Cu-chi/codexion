*This project has been created as part of the 42 curriculum by equentin*
# Description
Inspired by the Philosophers' Dinner, the goal is to build a concurrent simulation using threads.  
N coders in circle with N dongles between them, to compile, a coder needs two adjacent dongles (left and right) and must wait after dongles are released on the table (cooldown).

Life cycle:  
Wait 2 dongles → Compile → Release → Debug → Refactor → Repeat
# Instructions
to build the project, run
```bash
make
```

to run the program, run
```bash
./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug]
[time_to_refactor] [number_of_compiles_required] [dongle_cooldown] [scheduler]
```
- `number_of_coders`: > 0
- `time_to_burnout`: > 0
- `time_to_compile`: >= 0
- `time_to_debug`: >= 0
- `time_to_refactor`: >= 0
- `number_of_compiles_required`: >= 0
- `dongle_cooldown`: >= 0
- `scheduler`: 'fifo' or 'edf'

### schedulers
#### fifo
First In First Out, the dongles are given to the first who requested

#### edf
Earliest Deadline First, the dongles are given to the one who has the earliest deadline (last_compile_start + time_to_burnout)

to clean objects files and other build files, run
```bash
make clean
```

to clean objects files, other build files **and** the executable, run
```bash
make fclean
```

to re-build the project, run
```bash
make re
```

# Resources
https://www.geeksforgeeks.org/c/thread-functions-in-c-c/  
https://tala-informatique.fr/index.php?title=C_pthread  
https://www.ibm.com/docs/fr/aix/7.3.0?topic=p-pthread-mutex-init-pthread-mutex-destroy-subroutine

AI usage: helgrind error explanation, pthread cond explanation and usage example.
Good practice and code review. Decision assistant. Correction of English spelling mistakes in this text.

# Blocking cases handled
### Dongles
for dongles, I have a function that manage who get the dongles using the queue. When a coder needs dongles, he is inserted in a queue using `fifo` or `edf`. When entering the function a variable is locked so no coder can take at the same time. It waits until coder is the first in the queue. If the dongles are not available, the coder wait using a `pthread_cond_wait` and if the dongle are in cooldown, it simply wait the timer to take dongles.  

### Monitor
the monitor loop on each coder every 100ns to check if they burned out or if everyone finished their compilations.
So it always detects a burn out within 10ms

### Logs
every print is surrounded by a mutex so each print is in order and when a burn out occurs, every prints are locked.

# Thread synchronization mechanisms
**pthread_mutex_t**: a mutex can be locked and unlocked, when locked by a thread, any other thread can't lock it, using `pthread_mutex_lock`, `pthread_mutex_unlock`  
A mutex must be initialized using `pthread_mutex_init` and destroyed using `pthread_mutex_destroy`.

**pthread_cond_t**: a cond can be broadcasted using `pthread_cond_broadcast`, all thread that were waiting on this cond (using `pthread_cond_wait`) will be waked up  
A cond must be initialized using `pthread_cond_init` and destroyed using `pthread_cond_destroy`.

**pthread_create**: is the function that creates the thread and executes it.

**pthread_join**: this function will join the associated thread with the thread calling it, so if you join in main, the main will wait for the thread to return.
### how race conditions are prevented
race conditions are prevented by using `pthread_mutex_lock` and `pthread_mutex_unlock` around shared data.

### how thread-safe communication is achieved
thread-safe communication is achieved between coders and the
monitor by using flag for exit and mutex around, so when a coder finish all needed compilation it he increases a counter that the monitor will check to detect when all coders ended their work. Same for the exit flag, coders check this flag to avoid doing action after the exit.
