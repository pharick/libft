# libft

**A static library of standard and custom functions implemented in C. A project completed at Ecole42.**

libft is the first École 42 project: a reimplementation of a subset of the C standard library (memory, string, character-class, conversion and output functions) plus a handful of allocating string helpers and a singly-linked-list toolkit, compiled with `-Wall -Wextra -Werror` into `libft.a`. It is the base library reused by later projects in this account (`minishell`, `malloc`, `ft_nm` each carry an extended copy).

## What it covers

| Group | Functions |
| --- | --- |
| Memory | `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memccpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc` |
| Strings (libc) | `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strnstr`, `ft_strncmp`, `ft_strdup`, `ft_atoi` |
| Character classes | `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower` |
| Allocating helpers (42-specific) | `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi` |
| Output to a file descriptor | `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd` |
| Linked list (`t_list {content, next}`, bonus) | `ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`, `ft_lstlast`, `ft_lstadd_back`, `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap` |

43 functions in 43 source files, one function per file, all declared in `libft.h`.

## Notable implementations

- `ft_memmove` chooses the copy direction from the relative position of `src` and `dst` so overlapping ranges are handled correctly; `ft_memccpy` returns the pointer just past the stop byte as the BSD/POSIX version does.
- `ft_strlcpy` / `ft_strlcat` follow the OpenBSD contract: they always NUL-terminate when `dstsize > 0` and return the length they tried to create, including the `dstsize == 0` edge case.
- `ft_split` counts tokens in a first pass, allocates the array once, extracts tokens in a second pass and frees everything already allocated if a later allocation fails.
- `ft_itoa` counts digits up front, widens to `long` to handle `INT_MIN`, and fills the buffer from the end.
- `ft_lstmap` builds the mapped list incrementally and clears the partial result with the caller's `del` if an allocation fails.
- `ft_calloc` sets `errno = ENOMEM` on failure; `ft_strtrim` and `ft_split` return `NULL` on `NULL` input rather than dereferencing it.

## Library Build

make

`make` builds `libft.a` with the 34 mandatory functions; `make bonus` adds the nine `ft_lst*` functions to the archive. `make clean`, `make fclean` and `make re` are available. Compilation uses `gcc -Wall -Wextra -Werror` through a `.c.o` suffix rule that depends on `libft.h`, and the archive is assembled with `ar rc`.

## Usage

Include the header and link the archive from another project:

```c
#include "libft.h"

char **words = ft_split("a b  c", ' ');   /* {"a", "b", "c", NULL} */
char *n = ft_itoa(-2147483648);           /* "-2147483648" */
t_list *lst = ft_lstnew(words[0]);
ft_lstadd_back(&lst, ft_lstnew(words[1]));
```

```bash
gcc -I<path/to/libft> main.c -L<path/to/libft> -lft
```

The `t_list` node is `{ void *content; struct s_list *next; }`; the `del` callbacks passed to `ft_lstdelone`, `ft_lstclear` and `ft_lstmap` receive `content` only, the node itself is freed by the library.

## Project layout

```
libft/
  Makefile        all, bonus, clean, fclean, re
  libft.h         t_list and the 43 prototypes
  ft_mem*.c       memory functions
  ft_str*.c       string functions
  ft_is*.c, ft_to*.c   character classes
  ft_put*_fd.c    output helpers
  ft_lst*.c       linked list (bonus)
  ft_atoi.c, ft_itoa.c, ft_calloc.c, ft_split.c
```

## Notes

- Written in 2020 to the 42 norm (25-line functions, no `for`, no ternaries in the norm version, one function per file). Some files still use the pre-norm-v3 style of the time.
- There are no unit tests in the repository; the library was validated with the school's testers at the time.
- Later projects keep their own extended copies of this library (`ft_strcmp`, `ft_realloc`, `get_next_line`, `ft_lst_remove_if`, hexadecimal output, ...) instead of depending on this repository.
