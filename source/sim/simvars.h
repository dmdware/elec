

#ifndef SIMVARS_H
#define SIMVARS_H

#include "../math/v3f.h"

struct part
{
};

typedef struct part part;

#define PARTS	4

extern part gpart[PARTS];


extern v3f partp[PARTS];
extern float partq[PARTS];
extern float partm[PARTS];
extern v3f partv[PARTS];

#endif