
#include "registers.h"
#include "rand.h"

/**
 * Initialize the RNG
 */
void rand_init()
{
    *RNG_STATUS=0x40000;
    // mask interrupt
    *RNG_INT_MASK|=1;
    // enable
    *RNG_CTRL|=1;

    uart_writeArray("RNG is initialized!\r\n");
}

/**
 * Return a random number between [min..max]
 */
uint32_t rand(uint32_t min, uint32_t max)
{
    // may need to wait for entropy: bits 24-31 store how many words are
    // available for reading; require at least one
    while(!((*RNG_STATUS)>>24)) asm volatile("nop");
    return *RNG_DATA % (max-min) + min;
}