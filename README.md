# 🐚 Mini Shell

## 📌 Project Overview
**Mini Shell** is a lightweight, command-line shell implemented in **C** for Linux systems. It mimics the behavior of the **BASH** shell by using **Linux kernel system calls**, **IPC mechanisms**, and **signal handling**.

The shell processes user-typed commands, executes them using `fork()` and `exec()` system calls, and manages user inputs like `Ctrl+C` using signal handling. It can be easily extended to include features like **command history**, **piping**, and **I/O redirection**.

---

## 🚀 Features
- Execute basic Linux commands (`ls`, `cd`, `pwd`, `echo`, etc.)
- Built-in commands like `cd`, `exit`
- Handle keyboard interrupts (e.g., `Ctrl+C` with `SIGINT`)
- Use of `fork()`, `execvp()`, `waitpid()`, etc.
- Supports background processes (with `&`)
- Simple command parsing using string manipulation

---

## 🧠 Pre-requisites
To understand or modify this project, you should be familiar with:
- Linux system calls (`fork()`, `exec()`, `wait()`)
- IPC: Signal handling (`SIGINT`, `SIGCHLD`)
- Pointers and string parsing in C

---

## 🛠️ Tech Stack
- **Language**: C
- **Platform**: Linux
- **Tools**: GCC, GDB (for debugging)

---
