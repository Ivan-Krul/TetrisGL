#pragma once
#include "Variables.h"
#include "Defines.h"

class Block {
private:
	vec2i pos;
	typeBlock structure[4][4];
	typeBlock structure2[3][3];
	Pallette color;

	atlas type;

	void Sembling(atlas type) {
		unsigned short scheme = type;
		this->type = type;

		for (int i = 0;i < 16;i++) {

			if (type == I || type == O) {
				if (scheme % 2 == 1)
					structure[i % 4][i / 4] = CurrentBlock;
				else
					structure[i % 4][i / 4] = Air;
			}
			else {
				if (i / 4 != 3 && i % 4 != 3) {
					int b0 = 0;
					int b1 = 0;
					if (scheme % 2 == 1)
						structure2[((i % 4) + b0) % 3][((i / 4) + b1) % 3] = CurrentBlock;
					else
						structure2[((i % 4) + b0) % 3][((i / 4) + b1) % 3] = Air;
				}
			}

			scheme /= 2;
		}
	}
public:
	void ChangeColor() {
		switch (rand() % 17) {
		case 0:		color = White;		break;
		case 1:		color = Blue;		break;
		case 2:		color = Red;		break;
		case 3:		color = Lime;		break;
		case 4:		color = Green;		break;
		case 5:		color = Marble;		break;
		case 6:		color = LightBlue;	break;
		case 7:		color = LightGreen;	break;
		case 8:		color = Magmatic;	break;
		case 9:		color = Sea;		break;
		case 10:	color = Pink;		break;
		case 11:	color = DarkRed;	break;
		case 12:	color = Purple;		break;
		case 13:	color = LightClay;	break;
		case 14:	color = Raspberry;	break;
		case 15:	color = Orange;		break;
		case 16:	color = LavaRed;	break;
		}
	}

	void BlockAppeard() {
		int ran = rand() % 7;

		switch (ran) {
		case 0: Sembling(I); break;
		case 1: Sembling(L); break;
		case 2: Sembling(Z); break;
		case 3: Sembling(S); break;
		case 4: Sembling(O); break;
		case 5: Sembling(J); break;
		case 6: Sembling(T); break;
		}

		pos.x = 4;
		pos.y = 16;
		ChangeColor();
	}

	int sizeCol() {
		return (type == I || type == O) ? 4 : 3;
	}

	void Rotate(bool isTurnRight, typeBlock map[MAP_X][MAP_Y]) {
		typeBlock buffer[4][4];
		if (isTurnRight) {

			if (type == I || type == O) {

				for (int i = 0;i < 4;i++) {
					for (int j = 0;j < 4;j++) {
						buffer[i][j] = structure[j][3 - i];
					}
				}

			}
			else {

				for (int i = 0;i < 3;i++) {
					for (int j = 0;j < 3;j++) {
						buffer[i][j] = structure2[j][2 - i];
					}
				}

			}

		}
		else {
			if (type == I || type == O) {

				for (int i = 0;i < 4;i++) {
					for (int j = 0;j < 4;j++) {
						buffer[i][j] = structure[3 - j][i];
					}
				}

			}
			else {

				for (int i = 0;i < 3;i++) {
					for (int j = 0;j < 3;j++) {
						buffer[i][j] = structure2[2 - j][i];
					}
				}

			}
		}

		bool isFalsing = false;

		if (type == I || type == O) {

			for (int i = 0;i < 4;i++) {
				for (int j = 0;j < 4;j++) {

					if ((buffer[i][j] == CurrentBlock && !IsInMap(pos.x + i, pos.y + j)) || (buffer[i][j] == CurrentBlock && map[pos.x + i][pos.y + j]))
						isFalsing = true;

				}
			}

		}
		else {

			for (int i = 0;i < 3;i++) {
				for (int j = 0;j < 3;j++) {

					if ((buffer[i][j] == CurrentBlock && !IsInMap(pos.x + i, pos.y + j)) || (buffer[i][j] == CurrentBlock && map[pos.x + i][pos.y + j]))
						isFalsing = true;

				}
			}

		}

		if (!isFalsing) {
			if (type == I || type == O) {

				for (int i = 0;i < 4;i++) {
					for (int j = 0;j < 4;j++) {
						structure[i][j] = buffer[i][j];
					}
				}

			}
			else {

				for (int i = 0;i < 3;i++) {
					for (int j = 0;j < 3;j++) {
						structure2[i][j] = buffer[i][j];
					}
				}

			}

		}
	}

	bool Move(bool isDown, bool isRight, typeBlock map[MAP_X][MAP_Y]) {
		if (isDown) pos.y--;
		else if (isRight) pos.x++;
		else pos.x--;

		if (type == I || type == O) {

			for (int i = 0;i < 4;i++) {
				for (int j = 0;j < 4;j++) {

					if ((!IsInMap(i + pos.x, j + pos.y) && structure[i][j] == CurrentBlock) || (map[i + pos.x][pos.y + j] == PlacedBlock && structure[i][j] == CurrentBlock)) {

						if (isDown) pos.y++;
						else if (isRight) pos.x--;
						else pos.x++;

						return isCanMove(map);
					}

				}
			}
			return true;

		}
		else {

			for (int i = 0;i < 3;i++) {
				for (int j = 0;j < 3;j++) {

					if ((!IsInMap(i + pos.x, j + pos.y) && structure2[i][j] == CurrentBlock) || (map[i + pos.x][pos.y + j] == PlacedBlock && structure2[i][j] == CurrentBlock)) {

						if (isDown) pos.y++;
						else if (isRight) pos.x--;
						else pos.x++;

						return isCanMove(map);
					}

				}
			}
			return true;
		}
	}

	bool isCanMove(typeBlock map[MAP_X][MAP_Y]) {
		if (type == I || type == O) {
			for (int i = 0;i < 4;i++) {
				for (int j = 0;j < 4;j++) {

					if ((pos.y + j == 0 && structure[i][j] == CurrentBlock) || (map[i + pos.x][pos.y + j - 1] == PlacedBlock && structure[i][j] == CurrentBlock)) {
						return false;
					}

				}
			}
			return true;
		}
		else {
			for (int i = 0;i < 3;i++) {
				for (int j = 0;j < 3;j++) {

					if ((pos.y + j == 0 && structure2[i][j] == CurrentBlock) || (map[i + pos.x][pos.y + j - 1] == PlacedBlock && structure2[i][j] == CurrentBlock)) {
						return false;
					}

				}
			}
			return true;
		}
	}

	void setPosition(int x, int y) {
		pos.x = x;
		pos.y = y;
	}

	void Rewrite(Block block) {
		BlockAppeard();

		Sembling(block.getType());

		color = block.getColor();
	}

	vec2i getPosition() {
		return pos;
	}

	typeBlock getStructure(int x, int y) {
		if (type == I || type == O) return structure[x % 4][y % 4];
		else return structure2[x % 3][y % 3];
	}

	atlas getType() {
		return type;
	}

	Pallette getColor() {
		return color;
	}
};