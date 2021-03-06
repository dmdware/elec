



#ifndef SYSWIN_H
#define SYSWIN_H

#include "inc.h"
#include "../math/v2i.h"
#include "../algo/vec.h"
#include "../algo/list.h"

#define INI_WIDTH			640
#define INI_HEIGHT			480
#define INI_BPP				32
#define DRAW_FRAME_RATE		20
#define SIM_FRAME_RATE		30
#define MIND		0.001
#define MAXD		20
#define FOV		90
#define PROJ_RIGHT			2.2
#define MIN_ZOOM		0.05f
#define MAX_ZOOM		0.7f
#define INI_ZOOM			1.0f

extern dbool g_quit;
extern dbool g_bg;
extern dbool g_active;
extern dbool g_fs;
extern double g_indrawfps;
extern double g_inupfps;
extern double g_upiv;
extern double g_drawiv;

extern v2i g_selres;
extern list g_ress;
extern list g_bpps;

#ifndef MATCHMAKER
extern float g_vp4wh;
extern int g_currw;
extern int g_currh;
extern int g_width;
extern int g_height;
extern int g_bpp;
extern v2i g_mouse;
extern v2i g_mousestart;
extern dbool g_keyin;
extern dbool g_keys[SDL_NUM_SCANCODES];
extern dbool g_mousekeys[5];
extern float g_zoom;
extern int g_curst;	/* cursor state */
extern int g_kbfocus;	/* keyboad focus counter */
extern dbool g_mouseout;
#endif

void calcdrawrate();
dbool drawnext();
void calcuprate();
dbool upnext();
void enumdisp();
void resize(int width, int height);
void breakwin(const char* title);
dbool makewin(const char* title);

#endif
