.PHONY: clean

OBJCOPY ?= objcopy
# OBJCOPY_FLAGS

AS ?= as
# AS_FLAGS

CC ?= cc

AR ?= ar

all: test

rwx_shim_raw.o: rwx_shim.S
	$(AS) $(AS_FLAGS) $^ -o $@

rwx_shim.o: rwx_shim_raw.o
	$(OBJCOPY) --set-section-alignment rwx_shim=4096 $(OBJCOPY_FLAGS) $^ $@

librwx_shim.a: rwx_shim.o rwx_shim_seal.o
	$(AR) -rvcs $@ $^

%.o: %.c
	$(CC) $^ $(CFLAGS) -c -o $@

libtestlib.a: test_lib.o
	$(AR) -rvcs $@ $^

test: test.o librwx_shim.a libtestlib.a
	$(CC) test.o -L . -l testlib -l rwx_shim -o test

clean:
	rm -f *.o *.a test