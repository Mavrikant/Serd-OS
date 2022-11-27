#ifndef _RAND_H
#define _RAND_H

#include "stdint.h"

void rand_init();
uint32_t rand(uint32_t min, uint32_t max);

#endif // _RAND_H