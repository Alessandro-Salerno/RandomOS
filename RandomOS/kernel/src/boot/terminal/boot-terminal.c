#include <boot/terminal/boot-terminal.h>
#include <stdint.h>
#include <stddef.h>
#include <limine.h>


// Limine terminal request
static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

// The terminal itself
static struct limine_terminal *terminal;


/**
 * Prepares the terminal driver
 * @return 0 if successful
*/
int8_t boot_terminal_init() {
    if (terminal_request.response == NULL
        || terminal_request.response->terminal_count < 1) {
        return -1;
    }

    terminal = terminal_request.response->terminals[0];
    return 0;
}

/**
 * Outputs a message on the main terminal
 * @param msg the message to display
 * @param len the length of the message
*/
void boot_terminal_putmsg(const char *msg, uint64_t len) {
    terminal_request.response->write(terminal, msg, len);
}
