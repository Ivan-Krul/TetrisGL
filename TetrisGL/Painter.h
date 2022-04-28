#pragma once
#include <gl/GL.h>
#include "Variables.h"
#include <Windows.h>

#pragma comment(lib, "opengl32.lib")

class Painter {
private: 
	uint32_t frames = 0;
public: 
	static const uint16_t cFrequency = 30;
	vec3ub colorAir;
	vec3ub colorCurrentBlock;
	vec3ub colorPlacedBlock;
public:
	Painter() {
		int air = 0x0f0f0f;

		colorAir.x = air / 256 / 256;
		colorAir.y = air / 256 % 256;
		colorAir.z = air % 256;

		int cur_block = 0x919191;

		colorCurrentBlock.x = cur_block / 256 / 256;
		colorCurrentBlock.y = cur_block / 256 % 256;
		colorCurrentBlock.z = cur_block % 256;

		int placed_block = 0x303030;

		colorPlacedBlock.x = placed_block;
		colorPlacedBlock.y = placed_block / 256 % 256;
		colorPlacedBlock.z = placed_block % 256;
	}
private: 
	void Flip() { 
		Sleep(1000.0 / cFrequency);
		frames++;
	}

	void DrawBlock(typeBlock type_block) {
		glBegin(GL_TRIANGLE_STRIP);
		int block;

		switch (type_block) {
		case Air: block = (colorAir.x * 256 * 256) + (colorAir.y * 256) + colorAir.z; break;
		case CurrentBlock: block = (colorCurrentBlock.x * 256 * 256) + (colorCurrentBlock.y * 256) + colorCurrentBlock.z; break;
		case PlacedBlock: block = (colorPlacedBlock.x * 256 * 256) + (colorPlacedBlock.y * 256) + colorPlacedBlock.z; break;
		}

		glColor3f(float(block / 256 / 256) / 256.0f, float(block / 256 % 256) / 256.0f, float(block % 256) / 256.0f);
		glVertex2f(0.0f, 0.0f);

		glColor3f(float(block / 256 / 256 - 30) / 256.0f, float(block / 256 % 256 - 30) / 256.0f, float(block % 256 - 30) / 256.0f);
		glVertex2f(1.0f, 0.0f);

		glColor3f(float(block / 256 / 256 + 30) / 256.0f, float(block / 256 % 256 + 30) / 256.0f, float(block % 256 + 30) / 256.0f);
		glVertex2f(0.0f, 1.0f);

		glColor3f(float(block / 256 / 256) / 256.0f, float(block / 256 % 256) / 256.0f, float(block % 256) / 256.0f);
		glVertex2f(1.0f, 1.0f);
		glEnd();
	}
public: 
	uint32_t getFrames() { return frames; }
	void Paint() {
		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glScalef(2.0f / MAP_X,2.0f / MAP_Y,0.0f);
		DrawBlock(Air);
	}
};

