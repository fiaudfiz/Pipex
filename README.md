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

In this project, the part mandatory and the bonus part is separated : the mandatory part is to use only 2 command, and the bonus is the handle n-command.
The equivalence in shell is this command:
```bash
< file1 cmd1 | cmd2 > file2
```
## Set-up

To set-up this project, no need to clone my repo libft in this repo, I have made a submodule so, you just have to do this command :
```bash
git clone --recursive git@github.com:fiaudfiz/pipex
```
Then, you can enter in the folder pipex and compiling the project :
```bash
make
```
or 
```bash
make bonus
```

You can now execute this project : \
  -for mandatory:
  ```bash
      ./pipex file1 cmd1 cmd2 file2
```
  -for bonus :
    ```bash
    ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
    ```
