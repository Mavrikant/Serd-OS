#include "lib.h"
#include "print.h"
#include "registers.h"
#include "stdint.h"
#include "uart.h"

void enable_timer(void);
uint32_t read_timer_status(void);
void set_timer_interval(uint32_t value);
uint32_t read_timer_freq(void);

static uint32_t timer_interval = 0;
static uint64_t ticks = 0;

void init_timer(void)
{
    timer_interval = read_timer_freq() / 100;
    enable_timer();
    out_word(CNTP_EL0, (1 << 1));
    printk("%u ms: Timer is initialized!\r\n", (uint64_t)get_system_timer() / 1000);
    // printk("timer_interval: %u \r\n", timer_interval);
}

static void timer_interrupt_handler(void)
{
    uint32_t status = read_timer_status();
    if (status & (1 << 2))
    {
        ticks++;
        if (ticks % 100 == 0)
        {
            printk("timer %d \r\n", ticks);
        }

        set_timer_interval(timer_interval);
    }
}

void exc_handler(unsigned long type, unsigned long esr, unsigned long elr, unsigned long spsr, unsigned long far)
{
    // print out interruption type
    switch (type)
    {
    case 0:
        uart_writeArray("Synchronous");
        break;
    case 1:
        uart_writeArray("IRQ");
        break;
    case 2:
        uart_writeArray("FIQ");
        break;
    case 3:
        uart_writeArray("SError");
        break;
    }
    uart_writeArray(": ");

    // decode exception type (some, not all. See ARM DDI0487B_b chapter D10.2.28)
    switch (esr >> 26)
    {
    case 0b000000:
        uart_writeArray("Unknown");
        break;
    case 0b000001:
        uart_writeArray("Trapped WFI/WFE");
        break;
    case 0b001110:
        uart_writeArray("Illegal execution");
        break;
    case 0b010101:
        uart_writeArray("System call");
        break;
    case 0b100000:
        uart_writeArray("Instruction abort, lower EL");
        break;
    case 0b100001:
        uart_writeArray("Instruction abort, same EL");
        break;
    case 0b100010:
        uart_writeArray("Instruction alignment fault");
        break;
    case 0b100100:
        uart_writeArray("Data abort, lower EL");
        break;
    case 0b100101:
        uart_writeArray("Data abort, same EL");
        break;
    case 0b100110:
        uart_writeArray("Stack alignment fault");
        break;
    case 0b101100:
        uart_writeArray("Floating point");
        break;
    default:
        uart_writeArray("Unknown (default)");
        break;
    }

    // decode data abort cause
    if (esr >> 26 == 0b100100 || esr >> 26 == 0b100101)
    {
        uart_writeArray(", ");
        switch ((esr >> 2) & 0x3)
        {
        case 0:
            uart_writeArray("Address size fault");
            break;
        case 1:
            uart_writeArray("Translation fault");
            break;
        case 2:
            uart_writeArray("Access flag fault");
            break;
        case 3:
            uart_writeArray("Permission fault");
            break;
        }
        switch (esr & 0x3)
        {
        case 0:
            uart_writeArray(" at level 0");
            break;
        case 1:
            uart_writeArray(" at level 1");
            break;
        case 2:
            uart_writeArray(" at level 2");
            break;
        case 3:
            uart_writeArray(" at level 3");
            break;
        }
    }

    // dump registers
    uart_writeArray(":\n  ESR_EL1 ");
    uart_writeHex(esr);
    uart_writeArray(" ELR_EL1 ");
    uart_writeHex(elr);
    uart_writeArray("\n SPSR_EL1 ");
    uart_writeHex(spsr);
    uart_writeArray(" FAR_EL1 ");
    uart_writeHex(far);
    uart_writeArray("\n");

    uint32_t irq = in_word(CNTP_STATUS_EL0);
    if (irq & (1 << 1))
    {
        timer_interrupt_handler();
    }
}