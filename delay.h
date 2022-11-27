#ifndef _DELAY_H
#define _DELAY_H

#include "stdint.h"

uint64_t get_system_timer();
void wait_cycles(uint32_t n);
void wait_msec_st(uint32_t n);
void wait_msec(uint32_t n);
void wait_sec_st(uint32_t n);
void wait_sec(uint32_t n);
void wait_usec_st(uint32_t n);
void wait_usec(uint32_t n);

#endif // _DELAY_H