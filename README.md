# get_next_line

A C function that reads a text file (or any file descriptor: stdin, socket, pipe...) line by line, without relying on any full-file read.

## Why it's interesting

The naive way to read a line is to read the whole file into memory. `get_next_line` can't do that: it must return exactly one line per call while keeping just enough state between calls to resume reading later, no matter the buffer size or the file size.

## How it works

- A static buffer persists between calls and accumulates leftover data from the last `read()`.
- Each call reads `BUFFER_SIZE` bytes at a time until a `\n` is found or EOF is reached.
- The line up to (and including) the `\n` is returned; the remainder is kept for the next call.
- `BUFFER_SIZE` is configurable at compile time (`-D BUFFER_SIZE=n`), including edge cases like `1`.

## Bonus

The bonus version (`get_next_line_bonus.c`) handles **multiple file descriptors simultaneously**, each with its own independent read state, using a single static structure indexed by `fd`.

## Usage

```c
#include "get_next_line.h"

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

Compile the relevant `.c` files together with your project, defining `BUFFER_SIZE` if you want a specific value:

```bash
cc -D BUFFER_SIZE=42 -Wall -Wextra -Werror your_files.c get_next_line*.c
```

## Skills demonstrated

Manual memory management, static/persistent state across function calls, low-level `read()` syscall handling, edge-case robustness (empty files, no trailing newline, tiny/huge buffers).

*42 School — Common Core project.*
