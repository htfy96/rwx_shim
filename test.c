#include "rwx_shim.h"
#include "test_lib.h"
#include <stdio.h>

RWX_SHIM_SECTION_ATTR char buf[] = {0x48, 0x83, 0xec, 0x08, 0x48,
                                    0x83, 0xc4, 0x08, 0xc3, 0x00};
int main(void) {
  _ensure_rwx_shm_linked();
  seal_rwx_shim();
  void (*buf_func)() = (void *)(&buf);
  int (*add_func)(int, int) = (void *)(&add);
  printf("Start: %p End: %p buf_func: %p add_func: %p\n", _get_rwx_shim_start(),
         _get_rwx_shim_end(), buf_func, add_func);
  buf_func();
  printf("Add 42 + 21 = %d\n", add_func(42, 21));
  printf("OK!\n");
  return 0;
}