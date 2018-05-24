#include "../sys/inc.h"
#include "v4f.h"
#include "v3f.h"

void v4freset(v4f *v)
{
	v->x = v->y = v->z = v->w = 0;
}

void v4fset(v4f *v, float x, float y, float z, float w)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = w;
}

void v4fset2(v4f *v, const float *values)
{
	v->x = values[0];
	v->y = values[1];
	v->z = values[2];
	v->w = values[3];
}

dbool v4feq(v4f v1, v4f v2)
{
	if(v1.x == v2.x &&
	   v1.y == v2.y &&
	   v1.z == v2.z &&
	   v1.w == v2.w)
		return dtrue;
	
	return dfalse;
}

dbool v4fneq(v4f v1, v4f v2)
{
	if(v1.x == v2.x &&
	   v1.y == v2.y &&
	   v1.z == v2.z &&
	   v1.w == v2.w)
		return dfalse;
	
	return dtrue;
}

void v4fadd(v4f *v, v4f v1, v4f v2)
{
	v->x = v1.x + v2.x;
	v->y = v1.y + v2.y;
	v->z = v1.z + v2.z;
	v->w = v1.w + v2.w;
}

void v4fsub(v4f *v, v4f v1, v4f v2)
{
	v->x = v1.x - v2.x;
	v->y = v1.y - v2.y;
	v->z = v1.z - v2.z;
	v->w = v1.w - v2.w;
}

void v4fmul(v4f *v, v4f v1, const float num)
{
	v->x = v1.x * num;
	v->y = v1.y * num;
	v->z = v1.z * num;
	v->w = v1.w * num;
}

void v4fdiv(v4f *v, const v4f v1, const float num)
{
	v->x = v1.x / num;
	v->y = v1.y / num;
	v->z = v1.z / num;
	v->w = v1.w / num;
}