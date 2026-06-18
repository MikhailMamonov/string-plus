# s21_string+

A custom implementation of the `string.h` library in C with extended functionality (including formatted I/O functions `sprintf` and `sscanf`, as well as special string processing functions).

The project is developed in accordance with the **C11** standard, POSIX.1-2017, and Google Style for C++.

---

## 🛠 Implemented Features

### Part 1. Core `string.h` Functions
Implemented `s21_size_t` type, `S21_NULL` macro, and the following functions with the `s21_` prefix:
* `void *s21_memchr(const void *str, int c, size_t n)` — Searches for the first occurrence of a character.
* `int s21_memcmp(const void *str1, const void *str2, size_t n)` — Compares memory blocks.
* `void *s21_memcpy(void *dest, const void *src, size_t n)` — Copies a memory area.
* `void *s21_memset(void *str, int c, size_t n)` — Fills memory with a character.
* `char *s21_strncat(char *dest, const char *src, size_t n)` — Appends part of a string.
* `char *s21_strchr(const char *str, int c)` — Finds the first occurrence of a character in a string.
* `int s21_strncmp(const char *str1, const char *str2, size_t n)` — Compares parts of strings.
* `char *s21_strncpy(char *dest, const char *src, size_t n)` — Copies part of a string.
* `size_t s21_strcspn(const char *str1, const char *str2)` — Calculates the length of the initial segment without matches.
* `char *s21_strerror(int errnum)` — Returns an error message string (implemented with error arrays for macOS and Linux platforms).
* `size_t s21_strlen(const char *str)` — Calculates the length of a string.
* `char *s21_strpbrk(const char *str1, const char *str2)` — Finds the first match from a set of characters.
* `char *s21_strrchr(const char *str, int c)` — Finds the last occurrence of a character.
* `char *s21_strstr(const char *haystack, const char *needle)` — Finds a substring.
* `char *s21_strtok(char *str, const char *delim)` — Splits a string into tokens.

### Part 2 & 3. `s21_sprintf` Function
Full formatted output to a string is implemented:
* **Specifiers:** `c`, `d`, `f`, `s`, `u`, `%`, plus bonus `g`, `G`, `e`, `E`, `x`, `X`, `o`, `p`.
* **Flags:** `-`, `+`, space, `#`, `0`.
* **Width:** Numeric value and dynamic width via `*`.
* **Precision:** Numeric value and dynamic precision via `.*`.
* **Length:** Modifiers `h`, `l`, `L`.

### Part 4. `s21_sscanf` Function (Bonus)
Full formatted input reading from a string is implemented, including support for all standard flags, specifiers, width, length modifiers, and assignment suppression `*`.

### Part 5. Special Functions (Bonus)
String processing functions based on the `String` class logic from C#:
* `void *s21_to_upper(const char *str)` — Converts to uppercase.
* `void *s21_to_lower(const char *str)` — Converts to lowercase.
* `void *s21_insert(const char *src, const char *str, size_t start_index)` — Inserts a substring at the specified position.
* `void *s21_trim(const char *src, const char *trim_chars)` — Removes leading and trailing characters from a set.

---

## 🏗 Build & Testing

The project is compiled using `Makefile`. Testing is implemented with the **Check** library. Code coverage is verified using **gcov**.

### Available Makefile Targets:
* `make all` — Full build of the library and tests.
* `make s21_string.a` — Builds the static library in the `src/` folder.
* `make test` — Builds and runs unit tests, comparing results with the standard `string.h` library.
* `make gcov_report` — Generates a detailed HTML coverage report (function coverage exceeds 80%).
* `make clean` — Cleans build files, reports, and executables.

---

## 📂 Project Structure
```text
.
├── src/
│   ├── s21_string.h         # Main library header file
│   ├── s21_string.c         # Implementation of core library functions
│   ├── s21_sprintf.c        # Implementation of the sprintf function
│   ├── s21_sscanf.c         # Implementation of the sscanf function
│   ├── s21_special.c        # Implementation of special C#-style functions
│   ├── s21_string_test.c    # Unit tests (Check)
│   └── Makefile             # Project build script
├── .gitignore
└── README.md
