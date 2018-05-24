#ifndef V4F_H
#define V4F_H

#include "v3f.h"
#include "../algo/bool.h"

struct v3f;

struct v4f
{
	float x, y, z, w;
};

typedef struct v4f v4f;

void v4freset(v4f *v);

void v4fset(v4f *v, float x, float y, float z, float w);

void v4fset2(v4f *v, const float *values);

dbool v4feq(v4f v1, v4f v2);

dbool v4fneq(v4f v1, v4f v2);

void v4fadd(v4f *v, v4f v1, v4f v2);

void v4fsub(v4f *v, v4f v1, v4f v2);

void v4fmul(v4f *v, v4f v1, const float num);

void v4fdiv(v4f *v, const v4f v1, const float num);

#endif
