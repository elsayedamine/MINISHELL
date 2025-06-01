# 🐚 Minishell

A simple Unix shell recreated in C as part of the 42 school curriculum. The project aims to deepen understanding of process creation, file descriptors, parsing, and terminal behaviors by implementing core shell features from scratch.

---

## 📌 Project Description

**Minishell** is a simple shell built in C, mimicking behavior of Bash for essential features. It allows execution of user commands, supports built-in functions, handles redirections and pipelines, and includes basic environment variable expansion.

This project strengthens skills in:
- Process management (fork, execve, wait)
- Input parsing & tokenization
- Signal handling (SIGINT, SIGQUIT)
- File descriptor manipulation
- Linked list data structures
- Memory and error management

---

## ✅ Features

- ✅ Prompt display and interactive input loop
- ✅ Command execution (both built-in and system binaries)
- ✅ Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- ✅ Environment variable support (`$VAR`)
- ✅ Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- ✅ Piping with `|`
- ✅ Quote handling (`'`, `"`) with proper parsing
- ✅ Signal management (e.g., `Ctrl-C`, `Ctrl-\`)
- ✅ Error handling (syntax and execution)
- ✅ Exit status propagation

---

## 📂 Bonus / Extra Features (Optional)

- These are not required but can boost your grade or show off your skills:
- Wildcard expansion (*)
- Subshells: (...)
- Logical operators: &&, ||
- Command grouping with {} or (...)
- History handling (using readline)
- Line editing (readline handles this)
- Custom builtins (e.g., help or clear)
- 

## 🔧 Installation & Usage

```bash
# Clone the repo
git clone https://github.com/aelsayed1337/minishell.git
cd minishell

# Compile
make

# Run
./minishell
```

---

## 🗂️ Example Commands

```sh
$ echo "Hello World"
$ export USERNAME=amin
$ echo $USERNAME
$ ls -l | grep ".c" > sources.txt
$ cat << EOF
> multiline
> input
> EOF
```

---

## ⚙️ Technical Details

- Language: C (C89/C99)
- Libraries: `readline`, standard C libs, libft
- Structures: Custom AST for command parsing, linked lists for token tracking
- Memory: Fully leak-free (checked with Valgrind)

---

## 📁 Project Structure

```
minishell/
│
├── libft/         # Custom standard C library
├── parsing/        # Tokenizer and syntax parser
├── execution/      # Command execution & redirection
├── builtins/      # Built-in commands
└── Makefile
```

---

## 👤 Authors

- **Amine ELSAYED** ([@aelsayed1337](https://github.com/aelsayed1337))
- **Aziz HAKKI** ([@a-hakki](https://github.com/aelsayed1337))
