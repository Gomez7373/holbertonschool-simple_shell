# holbertonschool-simple_shell in C programming language

## Overview

Simple Shell is a Holberton School Project, our goal is to write a simple UNIX command interpreter.

## Content

- Installation
- General Requirements
- List of allowed functions
- Task's
- Authors

## Installation

git clone git@github.com:Gomez7373/holbertonschool-simple_shell.git

## General Requirements

- **Allowed editors:** vi, vim, emacs
- **OS:** Ubuntu 14.04 LTS
- **Compiler:** gcc 4.8.4
- **Compilation flags:** -Wall -Werror -Wextra -pedantic
- **File ending:** All files should end with a new line
- **README.md:** A README.md file is mandatory and should be placed at the root of the project folder
- **Coding style:** Your code should follow the Betty style, checked using betty-style.pl and betty-doc.pl
- **Functions per file:** No more than 5 functions per file
- **Header files:** All header files should be include guarded
- **System calls:** Use system calls only when necessary

## List of allowed functions and system calls+

all functions from string.h

- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- printf (man 3 printf)
- fprintf (man 3 fprintf)
- vfprintf (man 3 vfprintf)
- sprintf (man 3 sprintf)
- putchar (man 3 putchar)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

## Tasks 

0. README, man, AUTHORS (Mandatory)

- Write a README
- Write a man for your shell.
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

1. Betty would be proud (Mandatory)

- Write a beautiful code that passes the Betty checks

2. Simple shell 0.1 (Mandatory)

- Write a UNIX command line interpreter.
- Usage: simple_shell
- Your Shell should: Display a prompt and wait for the user to type a command. A command line always ends with a new line. The prompt is displayed again each time a command has been executed. The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features. The command lines are made only of one word. No arguments will be passed to programs. If an executable cannot be found, print an error message and display the prompt again.
Handle errors. You have to handle the “end of file” condition (Ctrl+D)
- You don’t have to: use the PATH, implement built-ins, handle special characters : ", ', `, \, *, &, # or be able to move the cursor. Handle commands with arguments

3. Simple shell 0.2 (Mandatory)

- Handle command lines with arguments

4. Simple shell 0.3 (Mandatory)

- Handle the PATH
- fork must not be called if the command doesn’t exist

5. Simple shell 0.4 (Mandatory)

- Implement the exit built-in, that exits the shell
- Usage: exit
- You don’t have to handle any argument to the built-in exit

6. Simple shell 1.0 (Mandatory)

- Implement the env built-in, that prints the current environment

## Authors:

- [Sheila Gomez](https://github.com/Gomez7373)
- [Abdiel Feliciano](https://github.com/Abdiel-88)
- [Mitzael Pitre](https://github.com/MitzaelPitre)
