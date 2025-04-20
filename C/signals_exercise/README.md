## 📄 Description

This project involves the creation of a **multi-process program** that uses **UNIX signals** (`SIGSTOP`, `SIGCONT`, `SIGINT`) to control and synchronize the execution of child processes. It explores the coordination between processes and the use of signals to manage execution timing and graceful termination.

---

## 🧩 Program Behavior

- The **parent process** creates `N` child processes (`N` is user-defined).
- Each **child process** immediately calls `pause()` to suspend itself after being created.
- The parent then uses **SIGCONT** to resume the children in a **round-robin** order (e.g., 1, 2, 3, 1, 2, 3...).
- Each time a child wakes up:
  - It runs for **2 seconds**, printing its PID and a random number (0–1).
  - It prints the same number twice during its active time.
  - It then pauses again.
- The user can press **Ctrl+C** to send a `SIGINT`, which triggers:
  - Each child to print: `Child with process id PID is terminating.`
  - The parent waits for all children to finish and then prints: `Parent process is terminating.`

---

## 💻 Technologies Used

- **Programming Language**: C  
- **Platform**: Ubuntu Linux  
- **Process Creation**: `fork()`  
- **Process Control**: `pause()`, `sleep()`, `kill()`  
- **Signal Handling**: `signal()`, `SIGCONT`, `SIGSTOP`, `SIGINT`  
- **Random Number Generation**: `rand()`  
- **I/O Functions**: `printf()`, `scanf()`

---

## 💡 Technical Requirements

- All child processes must call `pause()` upon creation and wait to be resumed.
- The parent uses `SIGCONT` to activate each child in a cyclic order.
- Each child should:
  - Generate **one random number per cycle**, and reuse it for 2 seconds.
  - Print that number and its PID **twice**, with a 1-second interval.
  - Then pause again.
- On **Ctrl+C**, the signal handler must ensure:
  - All children terminate **gracefully**, printing a termination message.
  - The parent waits for all children to exit before printing its own termination message.
- Use of `signal(SIGINT, handler)` is required to catch and handle interrupts.

---

## 🛠️ Compilation Instructions

```bash
gcc signals.c -o signals
```

---

## 🚀 Execution Instructions

```bash
./signals
```
