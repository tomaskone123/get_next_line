# get_next_line

## Overview
The `get_next_line` project is a custom implementation designed to read a line of text from a file descriptor, one line at a time. This function is a practical exercise in managing dynamic memory, working with file descriptors, and handling edge cases in I/O operations.

## Features
The `get_next_line` function provides:

- The ability to read lines of arbitrary length from a file or standard input.
- A flexible buffer size that can be defined at compile time.
- Efficient memory management for both the static and dynamic parts of the function.

## Function Prototype
```c
char *get_next_line(int fd);
```

### Parameters:
- `fd`: The file descriptor to read from.

### Returns:
- The next line from the file descriptor, including the newline character if one is encountered.
- `NULL` if there are no more lines to read or an error occurs.

## Usage
1. Include the `get_next_line.h` header in your project.
2. Compile the library (if provided as a standalone `.a` file) or include the source files in your project.
3. Call `get_next_line` in your code to retrieve lines one by one.

### Example
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    char *line;

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

## Implementation Details
- **Static Variable**: A static variable is used to store leftover data between function calls, enabling the function to handle lines spanning multiple reads.
- **Dynamic Buffer Allocation**: Buffers are dynamically allocated and resized as needed to accommodate lines of any length.
- **Read Chunking**: The function reads the file in chunks defined by the `BUFFER_SIZE` macro, ensuring efficient file I/O.
- **Memory Management**: The function carefully manages allocated memory to avoid leaks and ensures all buffers are freed appropriately.

## Limitations
- Requires a valid `BUFFER_SIZE` macro to be defined during compilation.
- May exhibit undefined behavior with invalid file descriptors or improperly handled errors.
- Does not handle binary files or non-text data well.

## Compilation
To compile the project, use the provided Makefile:

```bash
make
```

This will generate the `get_next_line.a` library file. You can link it to your project using:

```bash
gcc -Wall -Wextra -Werror main.c get_next_line.a -o program
```

