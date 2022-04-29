#pragma once
#include "Variables.h"
#include "Defines.h"
#include <iostream>
#include <Windows.h>

class Block {
private:
	vec2i pos;
	typeBlock structure[4][4];

	enum atlas : unsigned short {
		L = 0b0000010001000110,
		I = 0b0100010001000100,
		Z = 0b0000010001100010,
		RZ = 0b0000001001100100,
		O = 0b0000011001100000,
		RL = 0b0000001000100110,
		T = 0b0000010001100100,
	};
public:
	void BlockAppeard() {
		unsigned short scheme;
		switch (rand() % 7) {
		case 0:
			scheme = L;
			break;
		case 1:
			scheme = I;
			break;
		case 2:
			scheme = Z;
			break;
		case 3:
			scheme = RZ;
			break;
		case 4:
			scheme = O;
			break;
		case 5:
			scheme = RL;
			break;
		case 6:
			scheme = T;
			break;
		}
		unsigned short buf;
		for (int i = 0;i < 16;i++) {
			buf = scheme / int(pow(2, i));
			buf = buf % int(pow(2, 15 - i));
			if (buf) structure[i / 4][i % 4] = CurrentBlock;
			else structure[i / 4][i % 4] = Air;
		}

		pos.x = 3;
		pos.y = 21;
	}

	Block() {
		BlockAppeard();
	}

	void Move(bool isDown, bool isRight) {
		if (isDown) pos.y--;
		else if (isRight) pos.x++;
		else pos.x--;
	}

	vec2i getPosition() {
		return pos;
	}

	typeBlock getStructure(int x, int y) {
		return structure[x % 4][y % 4];
	}
};


class Tetris {
private:
	Block block;
public:
	typeBlock map[MAP_X][MAP_Y];
	Tetris() {
		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				map[i][j] = Air;
			}
		}
	}

	void BlockAppeard() {
		block.BlockAppeard();
	}

	void Move() {
		if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
			block.Move(true, false);
		else if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
			block.Move(false, true);
		else if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
			block.Move(false, false);
	}

	void WriteBlock() {
		vec2i pos = block.getPosition();

		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				if (map[i][j] == CurrentBlock) {
					map[i][j] = Air;
				}
			}
		}

		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				if (block.getStructure(i, j) == CurrentBlock && IsInMap(pos.x+i,pos.y+j)) {
					map[pos.x + i][pos.y + j] = CurrentBlock;
				}
			}
		}
	}
};

