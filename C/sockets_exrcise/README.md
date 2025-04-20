## 📄 Description

This project implements a **distributed processing pipeline** using sockets, with one **client** and two **servers** that communicate via **TCP and UDP**. Each process transforms a string input by the user and returns the final result to the client.

The system is designed to support **multiple clients simultaneously**, using **`fork()`** to create child processes for concurrent execution.

---

## 🧩 System Components

You must implement three separate C programs:

- `client.c`
- `server1.c`
- `server2.c`

---

## 🔁 Processing Flow

1. **Client**:
   - Prompts the user for a string.
   - Sends the string to **Server 1** via TCP.
   - Waits to receive the final processed string from **Server 2** via TCP.
   - Prints the result along with Server 2's IP address and port number.

2. **Server 1**:
   - Accepts TCP connections from clients.
   - Uses `fork()` to create a new process per client.
   - Reverses the received string.
   - Prints the reversed string along with the client's IP and port.
   - Sends it to **Server 2** via UDP.

3. **Server 2**:
   - Listens for messages from Server 1 over UDP.
   - Uses `fork()` to create a process per message.
   - Converts all lowercase letters to uppercase.
   - Prints the result with Server 1's IP and port.
   - Sends the final string back to the correct client via TCP.

---

## 📬 Termination Logic

- Programs terminate when the user enters `"exit"`. The client and both servers print `exiting` along with their PIDs and terminate gracefully.

---

## 🛠️ Compilation Instructions

Use `gcc` to compile each component:

```bash
gcc client.c -o client
gcc server1.c -o server1
gcc server2.c -o server2
```

---

## 🚀 Execution Instructions

In separate terminal windows:

```bash
# Terminal 1 – Server 1
./server1

# Terminal 2 – Server 2
./server2

# Terminal 3 – Client
./client
```

Make sure the Srevers are started first then the Client.

---

## 💻 Technologies Used

- **Programming Language**: C  
- **Platform**: Linux (tested on Ubuntu)  
- **Network Communication**: TCP and UDP sockets  
- **Concurrency**: Process creation using `fork()`  
- **Signal Handling**: `signal.h`, `kill()`, `SIGKILL`  
- **String Functions**: `strrev()` (manual), `toupper()` from `<ctype.h>`  
- **Socket Management**: `bind()`, `connect()`, `accept()`, `getsockname()`, `send()`, `recv()`


---

## ⚠️ Project Status

This project is currently **incomplete** and under development.  
It is part of a university assignment and will be further improved and tested in the future.
