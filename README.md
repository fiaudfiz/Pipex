# Pipex - @42

Reimplementation du mecanisme des pipes Unix en C.

---

## Description

this project has been made in the 42's curriculum by me, the principe is to make the same system as the Unix pipe to execute multiples commandes on a file or on the terminal.
In this project, there are some differents new notions/functions in C : 
-the notion son/father : the program father use the function fork to creeate a independant son which execute one of the command asked.
-the function execve : this function is executed in a son to found in the PATH the command shell to execute.
-the function dup2 : this fonction is used for create somne redirections to STDIN or STDOUT.
-the function pipe : this function allow us to create a new pipe which is a tunnel beetween commands to send the result of cmd1 to entry of cmd2 for exemple.

## Project Structure

In this project, you will find all the sources for a good execution, and a submodule called libft, which is the repo : https://github.com/fiaudfiz/libft . This is my own librairie to help for execution.In this project, the part mandatory and the bonus part is separated : the mandatory part is to use only 2 command, and the bonus is the handle n-command.

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
  -
