
#include "rand.h"
#include "delay.h"
#include "print.h"
#include "registers.h"

/**
 * Initialize the RNG
 */
void init_rand()
{
    *RNG_STATUS = 0x40000;
    // mask interrupt
    *RNG_INT_MASK |= 1;
    // enable
    *RNG_CTRL |= 1;

    printk("%u ms: RNG is initialized!\r\n", (uint64_t)get_system_timer() / 1000);
}

/**
 * Return a random number between [min..max]
 */
uint32_t rand(uint32_t min, uint32_t max)
{
    if (min == max)
    {
        return min;
    }
    if (min > max)
    {
        uint32_t tmp = min;
        min = max;
        max = tmp;
    }
    // may need to wait for entropy: bits 24-31 store how many words are
    // available for reading; require at least one
    while (!((*RNG_STATUS) >> 24))
    {
        asm volatile("nop");
    }
    uint32_t range = (max - min) + 1U; // inclusive upper bound
    return (uint32_t)(*RNG_DATA % range) + min;
}