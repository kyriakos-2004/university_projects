## 📋 Lab Description

This project is a **student grades management system implemented in MIPS32 Assembly**.

It demonstrates the use of:
- Arrays
- Loops
- Memory access
- Control structures
- Basic I/O
- Subroutine structure in Assembly

The program implements the following features:

1. **Add student**
2. **Display all students**
3. **Search by index number**
4. **Display average marks**
5. **Exit**

Each student entry consists of:
- An index number (integer)
- A mark (0–100)

These are stored in two parallel arrays (one for indexes, one for marks), with a maximum capacity of 10 students.

---

## 🔧 Functional Specifications

### 1. Add Student
- Prompts the user to enter an index and a mark.
- Stores the data in the arrays.
- No overflow or input validation is required.

### 2. Display All Students
- Displays all saved index/mark pairs.

### 3. Search by Index
- Prompts for an index number.
- Searches the index array and prints the corresponding mark if found.
- If not found, it prints a message that the student was not found.

### 4. Display Average Marks
- Calculates the average of all saved marks using integer division.

### 5. Exit
- Terminates the program.

---

## ⚠️ Notes

- **Important**: The current Assembly code does not strictly follow clean coding practices or programming standards.
- It was written as part of a lab exercise and prioritizes functionality over style or optimization.
- I might revisit and improve the code in the future for better readability, maintainability, and performance.
