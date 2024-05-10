#include "rwx_shim.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

extern void *_get_rwx_shim_end_filler_start(void);
extern void *_get_rwx_shim_end_filler_end(void);

void seal_rwx_shim(void) {
  if (_get_rwx_shim_end_filler_start() < _get_rwx_shim_end()) {
    fprintf(
        stderr,
        "_get_rwx_shim_end_filler_start() < _get_rwx_shim_end()\n: %p < %p\n",
        _get_rwx_shim_end_filler_start(), _get_rwx_shim_end());
    abort();
  }
  if (_get_rwx_shim_end_filler_start() > _get_rwx_shim_end() + 1) {
    fprintf(stderr,
            "_get_rwx_shim_end_filler_start() > _get_rwx_shim_end() + 1\n: %p "
            "> %p\n",
            _get_rwx_shim_end_filler_start(), _get_rwx_shim_end() + 1);
    abort();
  }
  const size_t len = _get_rwx_shim_end_filler_end() - _get_rwx_shim_start();
  if (len < 4096) {
    fprintf(stderr,
            "_get_rwx_shim_end_filler_end() - _get_rwx_shim_start() <= 4096\n: "
            "%p - %p <= 4096\n",
            _get_rwx_shim_end_filler_end(), _get_rwx_shim_start());
    abort();
  }
  const size_t seal_len = len / 4096 * 4096;
  mprotect(_get_rwx_shim_start(), seal_len, PROT_READ | PROT_EXEC);
}
