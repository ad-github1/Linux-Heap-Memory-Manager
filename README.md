# Linux Heap Memory Manager

A **custom-designed Heap Memory Manager** built from scratch in **C** for Linux environments.  
This project re-implements and enhances core memory allocation functionalities such as `calloc()` and `free()` — with internal & external fragmentation prevention, block coalescing, and visualization of the heap state.---

## Features

-  **Custom heap allocator** built entirely from scratch (no system `malloc`).
-  Implements `XMALLOC()` (like `calloc`) and `XFREE()` (like `free`).
-  Prevents **internal and external fragmentation** using block splitting & merging.
-  Includes utilities to **inspect and visualize** memory blocks in use.
-  Modular structure with separate **Memory Manager** and **Glue Thread** modules.
-  Fully tested using `testapp.c`.

## Compilation

gcc -Iinclude -Iglthread -g -c src/testapp.c -o build/testapp.o
gcc -Iinclude -Iglthread -g -c src/mm.c -o build/mm.o
gcc -Iinclude -Iglthread -g -c glthread/glthread.c -o build/glthread.o
gcc -Iinclude -Iglthread -g build/testapp.o build/mm.o build/glthread.o -o build/test.exe

Then run: ./build/test.exe

# OUTPUT
<img width="1280" height="730" alt="Screenshot 2025-11-01 at 02 38 07" src="https://github.com/user-attachments/assets/08c46752-f13f-4c42-8384-f85670028614" />

<img width="1280" height="730" alt="Screenshot 2025-11-01 at 02 38 26" src="https://github.com/user-attachments/assets/353eb4f0-7cfd-43f8-8323-26a769d27810" />





