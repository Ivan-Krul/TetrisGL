#pragma once
#include <stdint.h>

struct vec4f {
	typedef float VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
	VAR w = 0;
};

struct vec3f{
	typedef float VAR;
	VAR x=0;
	VAR y=0;
	VAR z=0;
};

struct vec2f {
	typedef float VAR;
	VAR x=0;
	VAR y=0;
};

struct vec4d {
	typedef double VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
	VAR w = 0;
};

struct vec3d {
	typedef double VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
};

struct vec2d {
	typedef double VAR;
	VAR x = 0;
	VAR y = 0;
};

struct vec4i {
	typedef int VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
	VAR w = 0;
};

struct vec3i {
	typedef int VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
};

struct vec2i {
	typedef int VAR;
	VAR x = 0;
	VAR y = 0;
};

struct vec4ui {
	typedef unsigned int VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
	VAR w = 0;
};

struct vec3ui {
	typedef unsigned int VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
};

struct vec2ui {
	typedef unsigned int VAR;
	VAR x = 0;
	VAR y = 0;
};

struct vec4b {
	typedef char VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
	VAR w = 0;
};

struct vec3b {
	typedef char VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
};

struct vec2b {
	typedef char VAR;
	VAR x = 0;
	VAR y = 0;
};

struct vec4ub {
	typedef unsigned char VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
	VAR w = 0;
};

struct vec3ub {
	typedef unsigned char VAR;
	VAR x = 0;
	VAR y = 0;
	VAR z = 0;
};

struct vec2ub {
	typedef unsigned char VAR;
	VAR x = 0;
	VAR y = 0;
};

static enum typeBlock {
	Air,
	CurrentBlock,
	PlacedBlock
};

double pow(double x, double k) {
	double a = 1;
	for (int i = 0;i < k;i++) a *= x;
	return a;
}

bool IsInMap(int x, int y) {
	return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
}
