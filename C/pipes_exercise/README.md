## 📄 Description

This lab implements a **multi-stage processing pipeline** using three child processes that communicate via **UNIX pipes**. Each process performs a transformation on user-provided strings and passes the result along the pipeline.

---

## 🧩 Functionality

- The **parent process** creates **three child processes** and prints its PID along with the PIDs of the children.
- The **1st child**:
  - Prompts the user to enter a string.
  - Prints the input string and its PID.
  - Sends the string to the 2nd child through a pipe.
- The **2nd child**:
  - Receives the string.
  - Reverses the string.
  - Prints the reversed string and its PID.
  - Sends it to the 3rd child through another pipe.
- The **3rd child**:
  - Receives the reversed string.
  - Converts all lowercase letters to uppercase.
  - Prints the final string and its PID.
- The **1st child** then prompts for a new string and the cycle repeats.
- If the user enters the string `"exit"`:
  - All four processes print an exit message in the following order:
    1. 1st child
    2. 2nd child
    3. 3rd child
    4. Parent

---

## 💻 Technologies Used

- **Programming Language**: C
- **Platform**: Linux (Ubuntu)
- **System Calls**: `fork()`, `pipe()`, `getpid()`
- **I/O Functions**: `printf()`, `scanf()`
- **Additional Functions**: `toupper()` from `<ctype.h>`

---

## ⚠️ Project Status

This project is currently **incomplete**. It is part of a university programming exercise, shared here for learning purposes and future reference. I might complete and refine it in the future.

---

## 🛠️ How to Compile & Run

```bash
gcc pipes.c -o pipes
./pipes
