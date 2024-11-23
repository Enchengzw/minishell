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
