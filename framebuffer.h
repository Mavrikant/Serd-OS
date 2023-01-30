void init_fb();
void fb_showlLoadingScreen();
void fb_cleanScreen();
void draw_pixel(int x, int y, unsigned char attr);
void draw_char(unsigned char ch, int x, int y, unsigned char attr);
void draw_string(int x, int y, char *s, unsigned char attr);
void draw_rect(int x1, int y1, int x2, int y2, unsigned char attr, int fill);
void draw_circle(int x0, int y0, int radius, unsigned char attr, int fill);
void draw_line(int x1, int y1, int x2, int y2, unsigned char attr);