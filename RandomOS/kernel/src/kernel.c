#include <boot/terminal/boot-terminal.h>
#include <stddef.h>
#include <stdint.h>
#include <util/panic.h>
#include <util/string.h>


/**
 * Kernel entry point
*/
void _start() {
    if (boot_terminal_init() != 0) {
        // Freeze the kernel, could not initialize terminal
        kernel_freeze();
    }

    kernel_print("Kernel terimnal initialized!\n");

    // We're done, just hang...
    kernel_freeze();
}
