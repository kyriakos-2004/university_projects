## 📝 Description

This project is an implementation of a simple C program in **MIPS32 Assembly**. The original program computes the sum of the first `n` natural numbers using a `for` loop.

The original C code:
```c
#include <stdio.h>

int sum_of_natural_numbers(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    int n = 10;
    int result = sum_of_natural_numbers(n);
    printf("The sum of the numbers is: %d\n", result);
    return 0;
}
```
---

## ⚠️ Notes

- **Important**: The current Assembly code does not strictly follow clean coding practices or programming standards.
- It was written as part of a lab exercise and prioritizes functionality over style or optimization.
- I might revisit and improve the code in the future for better readability, maintainability, and performance.
