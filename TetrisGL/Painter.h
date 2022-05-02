#pragma once
#include "Variables.h"
#include "Block.h"
#include <gl/GL.h>
#include <Windows.h>

#pragma comment(lib, "opengl32.lib")

class Painter {
private: 
	uint32_t frames = 0;
public: 
	static const uint16_t cFrequency = 30;
	/////////////////////////////////////////
public:
	Painter() {
		srand(time(NULL));
	}
private: 
	void Flip() { 
		Sleep(1000.0 / (cFrequency));
		frames++;
	}

	void DrawBlock(typeBlock type_block,Pallette pallette) {
		glBegin(GL_TRIANGLE_STRIP);
		int block;

		switch (type_block) {
		case Air: block = Black; break;
		case CurrentBlock: block = pallette; break;
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

	void line(double x1, double y1, double x2, double y2) { glVertex2f(x1, y1);glVertex2f(x2, y2); }



	void ShowNumber(int num) {

		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		if (num == 0 || num == 4 || num == 5 || num == 6 || num == 8 || num == 9 || num == int('L') || num == int('V')) line(0.15, 0.85, 0.15, 0.5);
		if (num == 0 || num == 2 || num == 6 || num == 8 || num == int('L')) line(0.15, 0.5, 0.15, 0.15);
		if (num == 0 || num == 2 || num == 3 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9) line(0.15, 0.85, 0.85, 0.85);
		if (num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 8 || num == 9) line(0.15, 0.5, 0.85, 0.5);
		if (num == 0 || num == 2 || num == 3 || num == 5 || num == 6 || num == 8 || num == 9 || num == int('L') || num == int('V')) line(0.15, 0.15, 0.85, 0.15);
		if (num == 0 || num == 1 || num == 3 || num == 2 || num == 4 || num == 7 || num == 8 || num == 9 || num == int('V')) line(0.85, 0.5, 0.85, 0.85);
		if (num == 0 || num == 1 || num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9 || num == int('V')) line(0.85, 0.5, 0.85, 0.15);
		glEnd();
	}

	void DrawInterface(int score,int lv, Pallette pallette, Block nextBlock){
		int block;

		block = pallette;

		int delta = 20;

		int s = 0;
		while (score != 0) {
			glPushMatrix();
			glTranslatef(14-(s*0.5), 16, 0.0f);
			glScalef(0.5f, 1.0f, 0.0f);
			ShowNumber(score % 10);
			glEnd();
			glPopMatrix();
			s++;
			score /= 10;
		}

		glPushMatrix();
		glTranslatef(11, 10, 0.0f);
		glScalef(0.5f, 1.0f, 0.0f);
		ShowNumber('L');
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(11.5, 10, 0.0f);
		glScalef(0.5f, 1.0f, 0.0f);
		ShowNumber('V');
		glEnd();
		glPopMatrix();

		s = 0;
		while (lv != 0) {
			glPushMatrix();
			glTranslatef(13 - (s * 0.5), 10, 0.0f);
			glScalef(0.5f, 1.0f, 0.0f);
			ShowNumber(lv % 10);
			glEnd();
			glPopMatrix();
			s++;
			lv /= 10;
		}

		vec2i pos = nextBlock.getPosition();
		for (int i = 0;i < nextBlock.sizeCol();i++) {
			for (int j = 0;j < nextBlock.sizeCol();j++) {
				glPushMatrix();
				glTranslatef(i + pos.x, j + pos.y, 0.0f);

				if (nextBlock.getStructure(i, j) == CurrentBlock)
					DrawBlock(CurrentBlock, nextBlock.getColor());

				glPopMatrix();
			}
		}
	}
public: 
	uint32_t getFrames() { return frames; }
	void Paint(typeBlock map[MAP_X][MAP_Y],int score, int lv, Pallette pallette, Block nextBlock) {
		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glScalef(2.0f / (MAP_X*(3.0/2.0)),2.0f / MAP_Y,0.0f);
		for (int i=0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				glPushMatrix();
				glTranslatef(i, j, 0.0f);

				DrawBlock(map[i][j],pallette);

				glPopMatrix();
			}
		}

		DrawInterface(score, lv, pallette,nextBlock);

		Flip();
	}
};

