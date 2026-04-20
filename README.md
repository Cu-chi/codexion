*This project has been created as part of the 42 curriculum by equentin*

# Description
Inspired by the **Dining Philosophers problem**, the goal is to build a concurrent simulation using threads.  
**N coders** are sitting in a circle with **N dongles** between them. To compile, a coder needs two adjacent dongles (left and right). Once the dongles are released, they remain on the table for a short period (cooldown) before they can be used again.

**Life cycle:** Wait for 2 dongles → Compile → Release → Debug → Refactor → Repeat

# Instructions
To build the project, run:
```bash
make
```

To run the program, use the following syntax:
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

### Schedulers
#### FIFO (First In First Out)
Dongles are assigned to the first coder who requested them.

#### EDF (Earliest Deadline First)
Dongles are assigned to the coder with the earliest deadline, calculated as: (last_compile_start + time_to_burnout)

To remove object files and other build artifacts:
```bash
make clean
```

To remove object files, build artifacts, and the executable:
```bash
make fclean
```

To re-build the project:
```bash
make re
```

# Resources
https://www.geeksforgeeks.org/c/thread-functions-in-c-c/  
https://tala-informatique.fr/index.php?title=C_pthread  
https://www.ibm.com/docs/fr/aix/7.3.0?topic=p-pthread-mutex-init-pthread-mutex-destroy-subroutine

AI usage: Helgrind error explanations, pthread_cond usage examples, general best practices, and English proofreading.

# Blocking cases handled
### Dongles
Dongle management is handled by a function that uses a queue. When a coder needs dongles, they are inserted into a queue based on the selected scheduler (`fifo` or `edf`). Access to the queue is protected by a mutex to prevent race conditions. The thread waits until the coder reaches the front of the queue. If the dongles are unavailable or in cooldown, the coder waits using `pthread_cond_wait` or a timer.

### Monitor
The monitor loops through every coder every 100ns to check if anyone has burned out or if everyone has finished their required compilations. This ensures a burnout is detected within 10ms.

### Logs
Every print statement is protected by a mutex to ensure logs appear in the correct order. When a burnout occurs, all subsequent prints are locked to prevent further output.

# Thread synchronization mechanisms
**pthread_mutex_t**: A mutex used to prevent simultaneous access to shared resources. Initialized with `pthread_mutex_init` and destroyed with `pthread_mutex_destroy`.

**pthread_cond_t**: A condition variable used to wake up waiting threads. Use `pthread_cond_broadcast` to wake all threads waiting via `pthread_cond_wait`.

**pthread_create**: The function that spawns and executes a new thread.

**pthread_join**: Blocks the calling thread until the target thread terminates.
### how race conditions are prevented
Race conditions are prevented by wrapping all access to shared data with `pthread_mutex_lock` and `pthread_mutex_unlock`.

### how thread-safe communication is achieved
Communication between coders and the monitor is achieved using an exit flag and shared counters, both protected by mutexes. When a coder finishes their required compilations, they increment a counter that the monitor tracks. Similarly, coders frequently check the exit flag to avoid performing actions after the simulation has ended.
