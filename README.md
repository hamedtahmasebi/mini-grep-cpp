# User Documentation for Text Search Application [AI GENERATED]

**Note**: This application and its documentation are in progress and subject to change.

## Overview
This C++ application searches for a specified text pattern in input files or standard input (stdin). It supports case-insensitive searches and optional line number display.

## Usage
Run the application from the command line with the following syntax:

```
./program <pattern> [options] [file1 file2 ...]
```

- `<pattern>`: The text string to search for (required).
- `[options]`: Optional flags to modify behavior.
- `[file1 file2 ...]`: Optional list of input files. If none provided, reads from stdin.

### Options
- `-i`: Enables case-insensitive search.
- `-n`: Displays line numbers for matching lines.

### Examples
1. Search for "hello" in `file.txt`:
   ```
   ./program hello file.txt
   ```
2. Case-insensitive search for "world" in multiple files:
   ```
   ./program world -i file1.txt file2.txt
   ```
3. Search with line numbers from stdin:
   ```
   echo -e "Hello\nWorld" | ./program hello -n
   ```

## Features
- **Input Sources**: Reads from files or piped stdin.
- **Case Sensitivity**: Use `-i` for case-insensitive matching.
- **Line Numbers**: Use `-n` to show line numbers for matches.
- **Multiple Files**: Supports searching multiple files in one command.

## Limitations
- Only the first input stream is processed in the current implementation.
- Error handling for invalid files or patterns is not fully implemented.
- Application is in development; expect updates and improvements.

## Requirements
- C++ compiler with C++11 or later.
- Standard libraries: `<algorithm>`, `<cctype>`, `<cstdio>`, `<iostream>`, `<istream>`, `<memory>`, `<string>`, `<vector>`.
- Custom headers: `config.cpp`, `debug_logger.hpp`, `input.cpp`.
