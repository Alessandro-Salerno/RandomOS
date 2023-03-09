#ifndef PANIC_H
#define PANIC_H

extern void kernel_freeze();
void kernel_panic(const char *msg);

#endif // PANIC_H
