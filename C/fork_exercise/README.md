## 📄 Description

This project is based on an assigned lab exercise where the goal is to create and manage a hierarchy of `N` UNIX processes using `fork()`. The processes are organized such that:

- The initial process (Process 1) is the **root**.
- Each process `i` creates a child process `i+1`, forming a chain of `N` processes.
- **Odd-numbered** processes print their PID, child's PID (if any), their position in the hierarchy, and a random number between 0 and 1 every 3 seconds.
- **Even-numbered** processes print their PID, **parent's** PID, position in the hierarchy, and a random number between 0 and 1 every 3 seconds.
- Each process repeats this action **5 times**, then terminates.
- A parent process must **wait** for its child to terminate before it exits, and then prints its PID and position.

## 💻 Technologies Used

- Language: C
- System: Linux (tested on Ubuntu)
- Functions allowed: `fork()`, `wait()`, `waitpid()`, `getpid()`, `getppid()`, `sleep()`, `printf()`, `scanf()`, `rand()`

## ⚠️ Project Status

This project is currently **incomplete**. It is part of a university programming exercise, shared here for learning purposes and future reference. I might complete and refine it in the future.

## 🛠️ How to Compile & Run

```bash
gcc fork.c -o fork
./fork
