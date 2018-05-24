

#include "simvars.h"

part gpart[PARTS];


v3f partp[PARTS] = {
	{0.1f, 0.2f, 0.8f},
	{0.4f, 0.19f, 0.5f},
	{0.32f, 0.49f, 0.89f},
	{0.73f, 0.74f, 0.47f} };
float partq[PARTS] =
	{ 1, -1, 1, -1 };
float partm[PARTS] =
	{ -100, 101, 10, 50 };
v3f partv[PARTS] = {
	{0.001f,0.02f,-0.011f},
	{0,-0.02,0.01f},
	{0,-0.001f,-0.012f},
	{-0.003f,0,0.011f} };

