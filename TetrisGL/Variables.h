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

enum Pallette : int {
	Black = 0x0f0f0f,
	White = 0xfcfcfc,
	Blue = 0x2038ec,
	Red = 0xd82800,
	Lime = 0x80d010,
	Green = 0x00a800,
	Marble = 0xdb00cc,
	Grey = 0x7f7f7f,
	LightBlue = 0x3ebeff,
	LightGreen = 0x58f898,
	Magmatic = 0xf83800,
	Sea = 0x6b88ff,
	Pink = 0xf878f8,
	DarkRed = 0xab0023,
	Purple = 0x6b47ff,
	LightClay = 0x6b47ff,
	Raspberry = 0xe7005b,
	Orange = 0xe7005b,
	LavaRed = 0xf83800,
};

enum atlas : unsigned short {
	L = 0b0000001000100011,
	I = 0b0100010001000100,
	Z = 0b0000001000110001,
	S = 0b0000001001100100,
	O = 0b0000011001100000,
	J = 0b0000001000100110,
	T = 0b0000001000110010,
};

double pow(double x, double k) {
	double a = 1;
	for (int i = 0;i < k;i++) a *= x;
	return a;
}

bool IsInMap(int x, int y) {
	return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
}
