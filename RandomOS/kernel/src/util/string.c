#include <boot/terminal/boot-terminal.h>
#include <util/string.h>


/**
 * Displays a message on screen
 * @param msg the message to display
 * @return the length of the message
*/
size_t kernel_print(const char *msg) {
    size_t lprint = 0;
    while (*(msg++)) {
        boot_terminal_putmsg(msg, 1);
        lprint++;
    }

    return lprint;
}
