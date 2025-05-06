# C Garbage Collector v2

This project implements a simple garbage collection system in C to manage dynamically allocated memory. It provides a mechanism to allocate and free memory while keeping track of all allocations to prevent memory leaks.

## Features

- **Dynamic Memory Allocation**: Allocate memory dynamically and automatically track it.
- **Garbage Collection**: Free all tracked memory in one call to prevent memory leaks.
- **Ease of Use**: Simple API with minimal overhead.

## Files

- **`garbage.h`**: Header file containing type definitions and function declarations.
- **`garbage.c`**: Implementation of the garbage collection system.
- **`.vscode/settings.json`**: VS Code settings for file associations.

## API Overview

### `void *alloc(size_t size, e_action action)`

Allocates or frees memory based on the specified action.

- **Parameters**:
  - `size`: Size of memory to allocate (used only when `action` is `ALLOC`).
  - `action`: Either `ALLOC` to allocate memory or `FREE` to free all tracked memory.
- **Returns**:
  - Pointer to the allocated memory if `action` is `ALLOC`.
  - `NULL` if `action` is `FREE`.

### `void free_garbage(t_garbage **garbage)`

Frees all memory tracked by the garbage list.

- **Parameters**:
  - `garbage`: Pointer to the garbage list.

### `t_garbage *new_garbage(void *allocated)`

Creates a new garbage node for a given memory allocation.

- **Parameters**:
  - `allocated`: Pointer to the allocated memory.
- **Returns**:
  - Pointer to the new garbage node.

### `void garbage_add_back(void *allocated, t_garbage **garbage)`

Adds a new memory allocation to the garbage list.

- **Parameters**:
  - `allocated`: Pointer to the allocated memory.
  - `garbage`: Pointer to the garbage list.

## Usage

1. Include `garbage.h` in your project.
2. Use `alloc(size, ALLOC)` to allocate memory and automatically track it.
3. Use `alloc(0, FREE)` to free all tracked memory when it is no longer needed.

### Example

```c
#include "garbage.h"

int main() {
    int *arr = alloc(10 * sizeof(int), ALLOC);
    if (!arr)
        return 1;

    // Use the allocated memory...
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    // Free all tracked memory
    alloc(0, FREE);
    return 0;
}
```