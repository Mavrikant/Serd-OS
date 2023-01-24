#include "datatypes.h"
#include "registers.h"
#include "uart.h"

// return 64-bit system timer that works at 1 MHz
uint64_t get_system_timer()
{
    uint32_t h = -1, l;
    // we must read MMIO area as two separate 32 bit reads
    h = *SYSTMR_HI;
    l = *SYSTMR_LO;
    // we have to repeat it if high word changed during read
    if (h != *SYSTMR_HI)
    {
        h = *SYSTMR_HI;
        l = *SYSTMR_LO;
    }
    return ((uint64_t)h << 32) | l; // merge value
}

uint64_t get_system_timer_ms() { return get_system_timer() / (uint64_t)1000; }

// wait cpu cycles
void wait_cycles(uint32_t n)
{
    if (n)
        while (n--)
        {
            asm volatile("nop");
        }
}

// wait microsecond
void wait_usec(uint32_t n)
{
    register uint64_t f, t, r;
    // get the current counter frequency
    asm volatile("mrs %0, cntfrq_el0" : "=r"(f));
    // read the current counter
    asm volatile("mrs %0, cntpct_el0" : "=r"(t));
    // calculate expire value for counter
    t += ((f / 1000) * n) / 1000;
    do
    {
        asm volatile("mrs %0, cntpct_el0" : "=r"(r));
    } while (r < t);
}

// wait milliseconds
void wait_msec(uint32_t n) { wait_usec(n * 1000); }

// wait seconds
void wait_sec(uint32_t n) { wait_msec(n * 1000); }

// wait microseconds
void wait_usec_st(uint32_t n)
{
    uint64_t t = get_system_timer();
    // we must check if it's non-zero, because qemu does not emulate
    // system timer, and returning constant zero would mean infinite loop
    if (t > 0)
        while (get_system_timer() < t + n)
        {
            asm volatile("nop");
        }
}

// wait milliseconds
void wait_msec_st(uint32_t n) { wait_usec_st(n * 1000); }

// wait seconds
void wait_sec_st(uint32_t n) { wait_msec_st(n * 1000); }