# OSN Assignment 2

## Specification

This program is created to mimic the behaviour of all shell commands using c language.
I have tried to use at most of system call possible to make this program.
This program contains one makefile.c file for all the codes and there's history.txt file will be created as well upon execution.

This program contains all the specification such as cd, echo, pwd, ls, exit with all it's 
flag has been implemented completely. 
Foreground and background process are also handled completly. There has been also the 
implementation of using defined command "pinfo" to give various information about the 
process.

## Functions


# run_command():
This function work by tokenizing the give input from the command line and 
breaking it in parts with the delimiter ";" and "&". Then it calls run() function to break 
each command tokens then execute it checking for first word to categorize it into various 
shell commands.

# run():
This function tokenize the command with delimiter " " and "\t" the check for each tokens
[0] and match it with suitable command of shell then execute it via suitable functions.

# currentdir():
This function will be called each time to display the current working directory

# username():
username() has been used to fetch the username of the system for priting on the shell

# get_home_dir():
It's been used to get the home directory of the given linux system but it's not been used 
as our home directory hass to be the directory where we're executing our command

# tokenize():
This function has been used to implement the tokenization process in one go rather than 
writing the line of code everytime needed

# ls():
It's been used to implement all the flags of ls as this would require a lot of line of 
code. So I prefered to write it as a fuction.

# switchtosytem():
It decides wheather the function is foreground or background then call run_background() 
for background process and run_foreground() for foreground process.

# run_background():
This runs the program in background by fork() such that it doesn't wait the the child 
process to be completed

# run_forground():
This execute the program in foreground by waiting for the child process to get executed.