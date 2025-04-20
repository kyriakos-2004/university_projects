## 📄 Description

This lab focuses on creating a **multi-threaded program** in C where threads execute in a **cyclic order** and terminate **in the same order they were created**, upon receiving a signal (Ctrl+C).

The program demonstrates synchronization using **pthreads**, **mutexes**, **condition variables**, and **signal handling**.

---

## 🧩 Program Behavior

1. The `main()` function creates **N threads**, where `N` is provided by the user, and prints their thread IDs.
2. Each thread, upon creation, enters a waiting state using `pthread_cond_wait()`.
3. The main thread wakes up the threads **cyclically** in creation order (e.g., 1 → 2 → 3 → 1 → 2 → 3 ...).
4. When a thread is signaled:
   - It increments a **shared counter**.
   - Waits 1 second.
   - Prints: `Thread X is running Y` where `X` is the thread ID and `Y` is the counter value.
   - Then goes back to waiting.
5. If the user presses **Ctrl+C**, threads are terminated **in creation order**.
6. Each thread prints: `Thread X is terminating` before exiting.
7. Once all threads terminate, the main thread prints: `Main process is terminating`.

---

## 💻 Technologies Used

- **Programming Language**: C  
- **Platform**: Ubuntu Linux  
- **Threading Library**: `pthread`  
- **Functions Used**:
  - `pthread_create`, `pthread_join`, `pthread_mutex_lock`, `pthread_mutex_unlock`
  - `pthread_cond_wait`, `pthread_cond_signal`
  - `pthread_exit`, `pthread_self`
  - `signal()`, `sleep()`

---

## 💡 Technical Requirements

- Threads must wait on a condition variable immediately after creation.
- The main thread acts as the controller and is responsible for waking up threads cyclically.
- A single **shared counter** is incremented each time a thread runs.
- A **signal handler** must be implemented to detect `Ctrl+C` and begin termination.
- Threads must terminate **in the order they were created**, not all at once.

---

## 🛠️ Compilation Instructions

```bash
gcc threads.c -o threads
```

---

## 🚀 Execution Instructions

```bash
./threads
```
