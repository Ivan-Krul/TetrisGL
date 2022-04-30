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
	}currentPallette;
	/////////////////////////////////////////
public:
	void ChangeColor() {
		switch (rand() % 17) {
		case 0:currentPallette = White;break;
		case 1:currentPallette = Blue;break;
		case 2:currentPallette = Red;break;
		case 3:currentPallette = Lime;break;
		case 4:currentPallette = Green;break;
		case 5:currentPallette = Marble;break;
		case 6:currentPallette = LightBlue;break;
		case 7:currentPallette = LightGreen;break;
		case 8:currentPallette = Magmatic;break;
		case 9:currentPallette = Sea;break;
		case 10:currentPallette = Pink;break;
		case 11:currentPallette = DarkRed;break;
		case 12:currentPallette = Purple;break;
		case 13:currentPallette = LightClay;break;
		case 14:currentPallette = Raspberry;break;
		case 15:currentPallette = Orange;break;
		case 16:currentPallette = LavaRed;break;
		}
	}

	Painter() {
		srand(time(NULL));
		ChangeColor();
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
		case Air: block = Black; break;
		case CurrentBlock: block = currentPallette; break;
		case PlacedBlock: block = Grey; break;
		}

		int delta = 20;

		glColor3f(float(block / 256 / 256) / 256.0f, float(block / 256 % 256) / 256.0f, float(block % 256) / 256.0f);
		glVertex2f(0.0f, 0.0f);

		glColor3f(float(block / 256 / 256 - delta) / 256.0f, float(block / 256 % 256 - delta) / 256.0f, float(block % 256 - delta) / 256.0f);
		glVertex2f(1.0f, 0.0f);

		glColor3f(float(block / 256 / 256 + delta) / 256.0f, float(block / 256 % 256 + delta) / 256.0f, float(block % 256 + delta) / 256.0f);
		glVertex2f(0.0f, 1.0f);

		glColor3f(float(block / 256 / 256) / 256.0f, float(block / 256 % 256) / 256.0f, float(block % 256) / 256.0f);
		glVertex2f(1.0f, 1.0f);
		glEnd();
	}
public: 
	uint32_t getFrames() { return frames; }
	void Paint(typeBlock map[MAP_X][MAP_Y]) {
		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glScalef(2.0f / MAP_X,2.0f / MAP_Y,0.0f);
		for (int i=0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				glPushMatrix();
				glTranslatef(i, j, 0.0f);

				DrawBlock(map[i][j]);

				glPopMatrix();
			}
		}

		Flip();
	}
};

