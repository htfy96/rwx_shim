#include "test_lib.h"

// lea %rax, %rsi(%rdi)
// ret
unsigned char add[] = {0x8d, 0x04, 0x37, 0xc3};