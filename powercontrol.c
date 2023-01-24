#include "powercontrol.h"
#include "registers.h"
#include "datatypes.h"

// Function to reboot the Raspberry Pi 3 using assembly code
void reboot(void)
{
    // trigger a restart by instructing the GPU to boot from partition 0
    uint32_t r = *PM_RSTS; 
    r &= ~0xfffffaaa;
    *PM_RSTS = PM_WDOG_MAGIC | r;   // boot from partition 0
    *PM_WDOG = PM_WDOG_MAGIC | 10;
    *PM_RSTC = PM_WDOG_MAGIC | PM_RSTC_FULLRST;
}
