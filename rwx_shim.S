.section rwx_shim,"awxG",@progbits,rwx_shim_group

.globl _ensure_rwx_shm_linked
.type _ensure_rwx_shim_linked,@function
_ensure_rwx_shm_linked:
 .cfi_startproc 
ret
ud2
.cfi_endproc

# fillers at the end of rwx sessions to make rwx_shim + filler at least having a size of
# 1 page, so that we can safely mprotect() previous pages
.section rwx_shim_end_filler,"awxG",@progbits,rwx_shim_group
# ud2
.fill 2048,2,0x0b0f

.section rwx_shim_meta,"ax",@progbits

.globl _get_rwx_shim_start
.type _get_rwx_shim_start,@function
_get_rwx_shim_start:
 .cfi_startproc 
lea __start_rwx_shim(%rip),%rax
ret
.cfi_endproc

.globl _get_rwx_shim_end
.type _get_rwx_shim_end,@function
_get_rwx_shim_end:
.cfi_startproc 
lea __stop_rwx_shim(%rip),%rax
ret
.cfi_endproc


.globl _get_rwx_shim_end_filler_start
.type _get_rwx_shim_end_filler_start,@function
_get_rwx_shim_end_filler_start:
 .cfi_startproc 
lea __start_rwx_shim_end_filler(%rip),%rax
ret
.cfi_endproc

.globl _get_rwx_shim_end_filler_end
.type _get_rwx_shim_end_filler_end,@function
_get_rwx_shim_end_filler_end:
.cfi_startproc 
lea __stop_rwx_shim_end_filler(%rip),%rax
ret
.cfi_endproc
