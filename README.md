# Libasm

**Libasm** is a small educational library written entirely in x86 assembly.  
It was created as part of my learning journey into low-level programming and understanding how things work "under the hood."

> ⚠️ This is not optimized or production-quality code — it's the result of learning and experimenting with assembly language.

---

## 📚 What It Is

This project implements a few basic C library functions in **x86 Assembly (NASM syntax)**.  
The main goal was to better understand:

- How functions are implemented at the machine level
- How the stack and registers are used
- Calling conventions (e.g., cdecl)
- Manual memory manipulation and syscall usage

---

## ⚙️ Implemented Functions

Common C functions (or equivalents) re-implemented in assembly:

- `ft_strlen`
- `ft_strcpy`
- `ft_strcmp`
- `ft_write`
- `ft_read`
- `ft_strdup`

> These follow the basic behavior of their libc counterparts, but are not optimized.

---

## 🛠️ Build & Usage

### Requirements

- `nasm`
- `gcc` or `ld` (to link)
- Linux with an x86 architecture or emulator


```bash
make
