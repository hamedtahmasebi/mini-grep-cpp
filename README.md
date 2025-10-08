# User Documentation for Text Search Application [AI GENERATED]

**Note**: This application and its documentation are in progress and subject to change.

Here is a **Usage Documentation** (in Markdown) for **mini-grep-cpp**:

---

# mini-grep Usage Guide

```
mini-grep [OPTIONS] <pattern> [FILES_OR_DIRS…]
```

## Arguments

* `pattern`
  A required regular expression to search for in the input.

* `FILES_OR_DIRS…`
  Zero or more file or directory paths.
  If no paths are provided, `mini-grep` reads from standard input.

## Options

| Option | Long form       | Description                                                    |
| ------ | --------------- | -------------------------------------------------------------- |
| `-i`   | `--ignore-case` | Match case-insensitively                                       |
| `-n`   | `--line-number` | Prefix each matching line with its line number                 |
| `-c`   | `--count`       | Instead of printing matching lines, print the count of matches |
| `-r`   | `--recursive`   | If an argument is a directory, search inside it recursively    |

## Behavior & Output Format

* When reading from multiple files or directories, output lines are prefixed with the filename.
* When `-n` is used, matching lines also show their line numbers.
* When `-c` is used:

  * The program prints the number of matching lines per file (or total, if reading from stdin).
  * No matching lines are printed.
* If recursion (`-r`) is enabled, directories are traversed to locate files to search.
* If input is from stdin (no files/dirs passed), the output does not include a filename prefix.
* Binary-like files are skipped (by heuristic) to avoid non-text output.

## Examples

* Search for the literal “error” in `log.txt`:

  ```bash
  mini-grep "error" log.txt
  ```

* Case-insensitive search in many files:

  ```bash
  mini-grep -i "warning" *.txt
  ```

* Show matching lines with line numbers:

  ```bash
  mini-grep -n "TODO" src/
  ```

* Search recursively through a directory:

  ```bash
  mini-grep -r "Config" src/
  ```

* Count matches instead of printing:

  ```bash
  mini-grep -c "pattern" *.cpp
  ```

* Using stdin (piped input):

  ```bash
  cat file.txt | mini-grep "regex"
  ```

---

If you send me the actual command-line parsing logic or help output (e.g. `--help` print), I can tailor this documentation to match exactly.
