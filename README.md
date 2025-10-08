# User Documentation for Text Search Application [AI GENERATED]

**Note**: This application and its documentation are in progress and subject to change.

---

# mini-grep-cpp

A simple command-line text search utility (grep clone) in C++.
Searches for lines matching a pattern (regular expression) in files or stdin. Supports recursion, counting, and options.

---

## Table of Contents

* Features
* Build
* Usage

  * Syntax
  * Options
* Design / Architecture

  * Modules / Components
* Examples
* Limitations & Notes

---

## Features

* Accepts a regex pattern as required argument
* Reads from files, directories (non-recursively or recursively), or stdin
* Option to ignore case
* Option to include line numbers
* Option to count matches instead of printing lines
* Skips binary-like files

---

## Build

Requires a C++17-capable compiler.

From repo root:

```bash
make
```

This builds the binary (e.g. `mini-grep` or as defined in Makefile).

Alternatively compile manually:

```bash
g++ -std=c++17 src/*.cpp -I include -o mini-grep
```

---

## Usage

### Syntax

```
mini-grep [OPTIONS] <pattern> [FILES_OR_DIRS...]
```

* `pattern` (required): a regular expression (ECMAScript / std::regex)
* `FILES_OR_DIRS...`: zero or more paths. If none, reads from stdin

### Options

| Flag | Long            | Effect                                                              |
| ---- | --------------- | ------------------------------------------------------------------- |
| `-i` | `--ignore-case` | Case-insensitive matching                                           |
| `-n` | `--line-number` | Prefix output with line number                                      |
| `-c` | `--count`       | Instead of printing matching lines, print count per file (or total) |
| `-r` | `--recursive`   | If encountering a directory, search inside it recursively           |

---

## Design / Architecture

The code is organized into modules (likely under `src/` and headers in `include/`):

* **main / driver**: parses command-line arguments, dispatches search
* **Config / Options module**: holds user options (pattern, flags, input paths)
* **Finder / Search module**: traverses paths, handles directories, applies recursion
* **Input / File reading**: reads lines from files or stdin
* **Output module**: formats matched lines or counts, includes filename/linenumber
* **Utility / Helpers**: e.g. skip binary files, apply case folding, regex wrapper

Flow:

1. Parse options & pattern
2. For each path (or stdin):
   a. If directory and `-r` is set, recursively enumerate contained files
   b. For each file: open, read line by line
   c. For each line: test regex match (with case-insensitive option adjusted)
   d. If match: either increment count or emit formatted line
3. After processing each file (or all input), if `-c`, output counts

Binary skipping: file contents are heuristically inspected; if not predominantly text, skip to avoid meaningless output.

When multiple files are searched, the output of each matching line is prefixed by its filename (unless reading from single file or stdin).

---

## Examples

* Search `error` in `log.txt` (case-sensitive):

  ```sh
  mini-grep "error" log.txt
  ```

* Case-insensitive:

  ```sh
  mini-grep -i "error" log.txt
  ```

* With line numbers:

  ```sh
  mini-grep -n "TODO" src/
  ```

* Recursive search in directory:

  ```sh
  mini-grep -r "ConfigManager" src/
  ```

* Count matches in each file:

  ```sh
  mini-grep -c "pattern" *.cpp
  ```

* Read from piped stdin:

  ```sh
  cat file.txt | mini-grep "someRegex"
  ```

---

## Limitations & Notes

* The regex flavor is that of `std::regex` (ECMAScript by default).
* Performance is limited for very large inputs (single-threaded).
* Binary-detection heuristic may skip files incorrectly (false negatives).
* Directory traversal does not follow symbolic links (unless code explicitly handles it).
* No support for context lines (before/after), inverse matching, color highlighting, etc.

---

If you want, I can also generate a Doxygen-style reference or embed this as `docs/USAGE.md`. Would you like that?
