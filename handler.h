#ifndef _HANDLER_H
#define _HANDLER_H

void init_timer(void);
void enable_irq(void);
void exc_handler(unsigned long type, unsigned long esr, unsigned long elr, unsigned long spsr, unsigned long far);

#endif // _HANDLER_H