# Pipex - @42

A C implementation of the Unix pipe mechanism.

---

## Description

This project was developed as part of the 42 school curriculum. The objective is to replicate the behavior of the Unix pipe (|) to execute multiple commands, redirecting the output of one to the input of the next.

This project introduces several core Unix concepts and system calls:

    Parent/Child Processes: Using fork() to create independent child processes that execute commands simultaneously.

    execve: Searching and executing binary commands using the system's PATH.

    dup2: Handling file descriptor redirections to manage STDIN and STDOUT.

    pipe: Creating a unidirectional data channel (a "tunnel") between processes to pass data from one command to another.

## Project Structure
This repository includes a submodule for my personal C library, [Libft](https://github.com/fiaudfiz/libft).

The project is divided into two parts:
    -Mandatory: Handling two commands and two files.
    -Bonus: Handling multiple pipes (n-commands) and here_doc support (no handled for now).
    
Shell Equivalence

The behavior of the program is identical to the following shell command:
```bash
< file1 cmd1 | cmd2 > file2
```
## Installation & Setup

Since this project uses a submodule, you must clone the repository recursively to include the libft source code:
```bash
git clone --recursive git@github.com:fiaudfiz/pipex.git
```
### Compilation

To compile the mandatory part:
```bash
make
```
To compile the bonus part (multiple pipes) : 
```bash
make bonus
```
 ## Usage
Mandatory Part
Execute with two commands:\
  -for mandatory:
  ```bash
      ./pipex infile "ls -l" "wc -l" outfile
```
  -for bonus :
 ```bash
    ./pipex infile "cmd1" "cmd2" "cmd3' ... "cmdN" outfile
```
