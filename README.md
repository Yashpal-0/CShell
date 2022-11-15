# OSN Assignment 3

## Specification

In this assignment we have to extend the previous made shell. 
And add input-output redirection, user defined codes, autocomplete,
piping and signal handling.

## Modules

# makefile.c
This is the module which has the main() function to execute.

# ioredirect.c
This module dup the STDOUT_FILENO & STDIN_FILENO to the given file descriptor.
It uses dup and dup2 funtions to perform the task.

# jobs.c
This modules give the information of all background process. It do so by
opening the /proc/[pid]/stat and it the process status.

# kill.c
This module has been used for signal handling.