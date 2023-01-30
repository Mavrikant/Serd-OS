#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H
#include "datatypes.h"

void init_fb();
void fb_showlLoadingScreen();
void fb_showHacettepeLogo();
void fb_cleanScreen();
void draw_pixel(uint32_t x, uint32_t y, unsigned char attr);
void draw_char(unsigned char ch, uint32_t x, uint32_t y, unsigned char attr);
void draw_string(uint32_t x, uint32_t y, char *s, unsigned char attr);
void draw_rect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, unsigned char attr, uint32_t fill);
void draw_circle(uint32_t x0, uint32_t y0, uint32_t radius, unsigned char attr, uint32_t fill);
void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, unsigned char attr);

#endif // _FRAMEBUFFER_H