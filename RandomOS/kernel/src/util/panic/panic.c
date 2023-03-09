#include <boot/terminal/boot-terminal.h>
#include <util/panic.h>


/**
 * Halts the kernel and prints a message
 * @param msg the message
*/
void kernel_panic(const char *msg) {
    // Something to print
    kernel_freeze();
}
