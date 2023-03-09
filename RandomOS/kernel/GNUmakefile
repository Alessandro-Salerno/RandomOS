# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

# Recursive wildcard
rwildcard = $(foreach d, $(wildcard $(1:=/*)), $(call rwildcard ,$d, $2) $(filter $(subst *, %, $2), $d))

# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := kernel.elf

# Convenience macro to reliably declare overridable command variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
$(eval $(call DEFAULT_VAR,CC,x86_64-linux-gnu-gcc))

# Same thing for "ld" (the linker).
$(eval $(call DEFAULT_VAR,LD,x86_64-linux-gnu-ld))

# User controllable CFLAGS.
CFLAGS ?= -g -O2 -pipe -Wall -Wextra

# User controllable preprocessor flags. We set none by default.
CPPFLAGS ?=

# User controllable nasm flags.
NASMFLAGS ?= -F dwarf -g

# User controllable linker flags. We set none by default.
LDFLAGS ?=

# Internal C flags that should not be changed by the user.
override CFLAGS +=       \
    -std=gnu11           \
    -ffreestanding       \
    -fno-stack-protector \
    -fno-stack-check     \
    -fno-lto             \
    -fno-pie             \
    -fno-pic             \
    -m64                 \
    -march=x86-64        \
    -mabi=sysv           \
    -mno-80387           \
    -mno-mmx             \
    -mno-sse             \
    -mno-sse2            \
    -mno-red-zone        \
    -mcmodel=kernel      \
    -I ./interface

override CPPFLAGS := \
    -I.              \
    $(CPPFLAGS)      \
    -MMD

# Internal linker flags that should not be changed by the user.
override LDFLAGS +=         \
    -nostdlib               \
    -static                 \
    -m elf_x86_64           \
    -z max-page-size=0x1000 \
    -T linker.ld

# Check if the linker supports -no-pie and enable it if it does.
ifeq ($(shell $(LD) --help 2>&1 | grep 'no-pie' >/dev/null 2>&1; echo $$?),0)
    override LDFLAGS += -no-pie
endif

# Internal nasm flags that should not be changed by the user.
override NASMFLAGS += \
    -f elf64

# Use find to glob all *.c, *.S, and *.asm files in the directory and extract the object names.
override CFILES := $(call rwildcard, src, *.c)
override ASFILES := $(call rwildcard, src, *.S)
override NASMFILES := $(call rwildcard, src, *.asm)
override OBJ := $(patsubst src/%.c, obj/C/%.o, $(CFILES)) $(patsubst src/%.S, obj/Assembly/%.o, $(ASFILES)) $(patsubst src/%.asm, obj/Assembly/%.o, $(NASMFILES))

# Default target.
.PHONY: all
all: $(KERNEL)

limine.h:
	cd interface && curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $@

# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

# Compilation rules for *.c files.
obj/C/%.o: src/%.c limine.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
obj/Assembly/%.o: src/%.S limine.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
obj/Assembly/%.o: src/%.asm
	nasm $(NASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f limine.h
