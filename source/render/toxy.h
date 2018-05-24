

#ifndef TOXY_H
#define TOXY_H

#include "../math/v3f.h"
#include "../math/v4f.h"

extern v3f gfpv[8];
extern v3f gfpl[6];
extern float gfpld[6];
extern float gfsa[12];
extern float gfvvv[12];
extern v4f gfpv4[8];
extern v4f gfpl4[6];
extern v4f gfxax;
extern v4f gfyax;
extern v4f gfzax;
extern v4f gfview;
extern v4f gfpos;
extern float gfwh;

float sa3f(v3f a, v3f b, v3f c);
v3f toxy2(v3f vi, float wx, float wy, v3f p[8], v3f pl[6], float pld[6], float *d, float sa[12]);
v4f toxy24(v4f vi, float wx, float wy, v4f p[8], v4f pl[6], float pld[6], float *d, float sa[12]);
v3f toxy(v3f vi, float wx, float wy, v3f view, v3f pos, v3f up, v3f strafe, float maxd, float mind, float fov, float *d);
v3f toclip(v3f vi);
v4f toclip42(v4f vi);
v4f toclipvp0(v4f vi);
v4f toclipvp1(v4f vi);
v4f toclipvp2(v4f vi);
v4f toclipvp3(v4f vi);
extern v4f(*toclipvp[4])(v4f vi);
void pfrust(float wx, float wy, v3f view, v3f pos, v3f up, v3f strafe, float maxd, float mind, float fov, float *d, v3f *pv, v3f *pl, float *pld, float *sa);
void ofrust(float wx, float wy, v3f view, v3f pos, v3f up, v3f strafe, float maxd, float mind, float *d, v3f *pv, v3f *pl, float *pld, float *sa);
void pfrust4(float wx, float wy, v4f view, v4f pos, v4f up, v4f strafe, float maxd, float mind, float fov, float *d, v4f *pv, v4f *pl, float *pld, float *sa, v4f xax, v4f yax, v4f zax);
void ofrust4(float wx, float wy, v4f view, v4f pos, v4f up, v4f strafe, float maxd, float mind, float *d, v4f *pv, v4f *pl, float *pld, float *sa, v4f xax, v4f yax, v4f zax);
float vol3f(v3f a, v3f b, v3f c, v3f d);

#endif