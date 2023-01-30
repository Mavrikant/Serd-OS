#ifndef _LIB_H
#define _LIB_H
#include "datatypes.h"

void set_register(uint64_t addr, uint32_t value);
uint32_t get_register(uint64_t addr);

void memset(void *dst, int value, unsigned int size);
void memcpy(void *dst, void *src, unsigned int size);
void memmove(void *dst, void *src, unsigned int size);
int memcmp(void *src1, void *src2, unsigned int size);

#endif