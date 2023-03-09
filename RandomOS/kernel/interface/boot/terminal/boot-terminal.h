#ifndef BOOT_TERMINAL_BOOTTERMINAL_H
#define BOOT_TERMINAL_BOOTTERMINAL_H

#include <stdint.h>


int8_t boot_terminal_init();
void boot_terminal_putmsg(const char *msg, uint64_t len);

#endif // BOOT_TERMINAL_BOOTTERMINAL_H
