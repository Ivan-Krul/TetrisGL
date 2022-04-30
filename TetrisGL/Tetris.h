#pragma once
#include "Variables.h"
#include "Defines.h"
#include "Painter.h"
#include <iostream>
#include <Windows.h>

class Block {
private:
	vec2i pos;
	typeBlock structure[4][4];

	enum atlas : unsigned short {
		L =		0b0000010001000110,
		I =		0b0100010001000100,
		Z =		0b0000010001100010,
		S =		0b0000001001100100,
		O =		0b0000011001100000,
		J =		0b0000001000100110,
		T =		0b0000010001100100,
	};
public:
	void BlockAppeard() {
		unsigned short scheme = 0;
		int ran = rand() % 7;

		switch (ran){
		case 0:
			scheme = I;
			break;
		case 1:
			scheme = L;
			break;
		case 2:
			scheme = Z;
			break;
		case 3:
			scheme = S;
			break;
		case 4:
			scheme = O;
			break;
		case 5:
			scheme = J;
			break;
		case 6:
			scheme = T;
			break;
		default:
			scheme = T;
			break;
		}

		for (int i = 0;i < 16;i++) {

			if (scheme % 2 == 1)
				structure[i % 4][i / 4] = CurrentBlock;
			else 
				structure[i % 4][i / 4] = PlacedBlock;
			scheme /= 2;

		}

		pos.x = 4;
		pos.y = 16;
	}

	Block() {
		BlockAppeard();
	}

	void Rotate(bool isTurnRight) {
		typeBlock buffer[4][4];
		if (isTurnRight) {
			for (int i = 0;i < 4;i++) {
				for (int j = 0;j < 4;j++) {
					buffer[i][j] = structure[j][3-i];
				}
			}
		}
		else {
			for (int i = 0;i < 4;i++) {
				for (int j = 0;j < 4;j++) {
					buffer[i][j] = structure[3-j][i];
				}
			}
		}
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				structure[i][j] = buffer[i][j];
			}
		}
	}

	bool Move(bool isDown, bool isRight, typeBlock map[MAP_X][MAP_Y]) {
		if (isDown) pos.y--;
		else if (isRight) pos.x++;
		else pos.x--;

		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {

				if ((!IsInMap(i + pos.x, j + pos.y)&& structure[i][j] == CurrentBlock) || (map[i + pos.x][pos.y + j] == PlacedBlock && structure[i][j] == CurrentBlock)) {

					if (isDown) pos.y++;
					else if (isRight) pos.x--;
					else pos.x++;

					return isCanMove(map);
				}

			}
		}
		return true;
	}

	bool isCanMove(typeBlock map[MAP_X][MAP_Y]) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {

				if ((pos.y + j == 0 && structure[i][j] == CurrentBlock )|| (map[i+pos.x][pos.y + j - 1] == PlacedBlock && structure[i][j] == CurrentBlock) ) {
					return false;
				}

			}
		}
		return true;
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
	Painter painter;
	typeBlock map[MAP_X][MAP_Y];
	uint8_t stepsToFall;

	void Place() {
		vec2i pos = block.getPosition();

		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {

				if (block.getStructure(i, j) == CurrentBlock && IsInMap(pos.x + i, pos.y + j)) {
					map[pos.x + i][pos.y + j] = PlacedBlock;
				}

			}
		}

		BlockAppeard();
	}
public:
	void Start() {
		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				map[i][j] = Air;
			}
		}

		block.BlockAppeard();
		stepsToFall = 0;
	}

	Tetris() {
		Start();
	}

	void BlockAppeard() {
		block.BlockAppeard();
		painter.ChangeColor();
	}

	void Move() {
		int Y = block.getPosition().y;
		bool isMove = true;

		if (GetAsyncKeyState(VK_NUMPAD2))
			if(!block.Move(true, false, map)) isMove = false;
		else if (GetAsyncKeyState(VK_NUMPAD6))
			if (!block.Move(false, true, map)) isMove = false;
		else if (GetAsyncKeyState(VK_NUMPAD4))
			if (!block.Move(false, false, map)) isMove = false;
		else if (GetAsyncKeyState(VK_NUMPAD9))
			block.Rotate(true);
		else if (GetAsyncKeyState(VK_NUMPAD7))
			block.Rotate(false);

		if (block.getPosition().y != block.getPosition().y)
			stepsToFall = 0;

		if (stepsToFall > painter.cFrequency) {
			if (!block.Move(true, false, map)) isMove = false;
			stepsToFall = 0;
		}

		if (!isMove) Place();
	}

	void CheckLines() {
		for (int i = MAP_Y - 1;i >= 0;i--) {
			int C = 0;

			for (int j = 0;j < MAP_X;j++) {
				if (map[j][i] == PlacedBlock)
					C++;
			}

			if (C == MAP_X) {
				for (int q = i+1;q < MAP_Y;q++) {
					for (int j = 0;j < MAP_X;j++) {
						map[j][q - 1] = map[j][q];
					}
				}
			}
		}
	}
	bool isWork() {
		for (int j = 0;j < MAP_X;j++) {
			if (map[j][19] == PlacedBlock)
				return false;
		}
		return true;
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

		painter.Paint(map);
		stepsToFall++;
	}
};

