*This project has been created as part of the 42 curriculum by nalfonso, qcyril-a.*

# Minishell

## Description

Minishell is a minimal Unix shell implementation written in C as part of the 42 curriculum. The goal is to understand how a shell works at a low level — from reading user input, tokenizing and parsing it, expanding variables, managing processes, and handling I/O redirection and pipes.

The shell supports:
- Command execution (external programs via `execve`)
- Pipes (`cmd1 | cmd2 | ...`)
- I/O redirections (`<`, `>`, `>>`, `<<` heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Quote handling (`'single'`, `"double"`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Command history (via readline)

## Instructions

### Requirements

- GCC or Clang
- GNU Make
- `readline` library (`libreadline-dev` on Debian/Ubuntu, or `brew install readline` on macOS)

### Compilation

```bash
make
```

This builds the `minishell` binary in the root directory.

To clean object files:
```bash
make clean
```

To clean everything including the binary:
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

### Execution

```bash
./minishell
```

Once running, you will see the `minishell$` prompt. Type commands as you would in any Unix shell.

### Usage Examples

```bash
minishell$ echo "Hello, World!"
minishell$ ls -la | grep src
minishell$ cat < input.txt > output.txt
minishell$ export MY_VAR=hello
minishell$ echo $MY_VAR
minishell$ echo $?
minishell$ cd -
minishell$ exit 0
```

## Resources

### Shell and Unix Documentation

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — The canonical reference for shell behavior and POSIX compliance
- [The Open Group Base Specifications — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — POSIX standard for shell semantics
- [Linux `man` pages: `execve(2)`, `fork(2)`, `pipe(2)`, `dup2(2)`, `waitpid(2)`](https://man7.org/linux/man-pages/) — Core system calls used throughout the project
- [readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html) — Used for interactive input and history
- [Write Your Own Shell — Tutorial by Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — A clear walkthrough of building a shell in C

### AI Usage

AI assistance was used to create this project and find resources and testing the project.
