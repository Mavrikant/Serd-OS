#include "print.h"
#include "stdint.h"
#include "uart.h"

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
        uart_writeArray("Unknown");
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
    // no return from exception for now
    /*
    while (1)
    {
        asm volatile("nop");
    };
    */
}