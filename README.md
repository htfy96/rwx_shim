# rwx_shim

`rwx_shim` is a minimal shim written in Assembly and C that allows users to place variables into a runtime-writable and executable section by linking with this library. It also provides some additional utility to seal the section to at runtime.

This is mostly useful for programs that want to JIT-generate some fixed amount of code at startup, and then execute them without much modification. One example is Linux's [Static Keys](https://docs.kernel.org/staging/static-keys.html).

Compared to `mmap()` an `rwx` page at runtime, this shim allows users to create variables into an RWX section at link time and provided better debugging experience.

## Usage

### Prerequisite

- GNU AS
- GCC
- objtool
- ld

Tested platform: x86-64. Supposed to work any recent Linux distro. Sys-V AMD64 ABI.

### Build and use

```bash
$ make
# You will see librwx_shim.a and ./test generated under current directory

# See rwx_shim.h for API sample. See test.c for usage example

# To use it in your program, simply include rwx_shim.h and link your binary against librwx_shim.a
```

```c
#include "rwx_shim.h"

// lea %rax, %rsi(%rdi)
// ret
unsigned char add[] RWX_SHIM_SECTION_ATTR = {0x8d, 0x04, 0x37, 0xc3};

int main(void) {
    _ensure_rwx_shm_linked();
    seal_rwx_shim();
    int (*add_func)(int, int) = (void *)(&add);
    // prints out 63
    printf("Add 42 + 21 = %d\n", add_func(42, 21));
    // add[0] = '\0'; will cause segmentation fault
    return 0;
}
```

## Security

Creating a wriable and executable section in your binary greatly increases the attack surface and enables easier code execution. Please only use this in a trusted environment.

## License

Apache v2
