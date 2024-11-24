# **Minishell**

**Minishell** is a project to build a simple shell, similar to Bash from scratch, with core functionalities like executing commands, handling pipes, and managing redirections. This project focuses on understanding processes, file descriptors, and signals.

---

## **Features**
- Displays a customizable **prompt**.
- Maintains a working **command history**.
- Executes commands using `PATH`, relative, or absolute paths.
- Implements **redirection operators**:
  - `<` Redirect input from a file.
  - `>` Redirect output to a file.
  - `>>` Append output to a file.
  - `<<` Read input until a specified delimiter is encountered (heredoc).
- Supports **pipes (`|`)** for command chaining.
- Expands **environment variables** using `$`, including `$?` for the exit status of the last executed command.
- Handles:
  - **Single quotes (`'`)**: Prevent interpretation of special characters.
  - **Double quotes (`"`)**: Interpret `$` for variable expansion but prevent other special character interpretation.
- Responds to key combinations:
  - `Ctrl-C`: Interrupts and displays a new prompt.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: Does nothing.
- Implements the following **built-in commands**:
  - `echo` with the `-n` option.
  - `cd` with relative or absolute paths.
  - `pwd` to display the current directory.
  - `export` to set environment variables.
  - `unset` to remove environment variables.
  - `env` to display environment variables.
  - `exit` to close the shell.

# **Allowed functions**

You are allowed to use any functions that you have written from scratch. 
You may also use all of these external functions: 

### Functions Overview

#### Command Line and History Management
- `rl_replace_line`
- `rl_redisplay`
- `add_history`

#### Memory Management
- `malloc`
- `free`

#### Input/Output (I/O)
- `printf`
- `write`
- `read`
- `close`
- `open`
- `access`

#### Process Management
- `fork`
- `wait`
- `waitpid`
- `wait3`
- `wait4`

#### Signal Handling
- `signal`
- `sigaction`
- `sigemptyset`
- `sigaddset`
- `kill`

#### Program Termination
- `exit`

#### File System and Directory Management
- `getcwd`
- `chdir`
- `stat`
- `lstat`
- `fstat`
- `unlink`

#### Execution
- `execve`

#### File Descriptor Management
- `dup`
- `dup2`
- `pipe`

#### Directory Management
- `opendir`
- `readdir`
- `closedir`

#### Error Handling
- `strerror`
- `perror`

#### Terminal Management
- `isatty`
- `ttyname`
- `ttyslot`
- `ioctl`
- `getenv`
- `tcsetattr`
- `tcgetattr`
- `tgetent`
- `tgetflag`
- `tgetnum`
- `tgetstr`
- `tgoto`
- `tputs`
