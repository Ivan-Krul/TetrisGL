#pragma once
#include "Variables.h"
#include "Defines.h"
#include "Painter.h"
#include "Block.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

class Tetris {
private:
	Block block, nextBlock;
	Painter painter;
	typeBlock map[MAP_X][MAP_Y];
	uint8_t stepsToFall;
	int score;
	bool isSaved = false;
	double LV = 1;
	const int cPositionNextBlockX = 11;
	const int cPositionNextBlockY = 12;

	void Place() {
		Beep(400, 200);
		vec2i pos = block.getPosition();

		for (int i = 0;i < block.sizeCol();i++) {
			for (int j = 0;j < block.sizeCol();j++) {

				if (block.getStructure(i, j) == CurrentBlock && IsInMap(pos.x + i, pos.y + j)) {
					map[pos.x + i][pos.y + j] = PlacedBlock;
				}

			}
		}
		BlockAppeard();
	}
public:
	void Start() {
		Beep(800, 200);
		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				map[i][j] = Air;
			}
		}

		isSaved = false;
		block.BlockAppeard();
		nextBlock.BlockAppeard();
		nextBlock.setPosition(cPositionNextBlockX, cPositionNextBlockY);
		stepsToFall = 0;
		score = 0;
		LV = 1;
	}

	Tetris() {
		Start();
	}

	void BlockAppeard() {
		Beep(500, 200);
		block.Rewrite(nextBlock);
		nextBlock.BlockAppeard();
		nextBlock.setPosition(cPositionNextBlockX, cPositionNextBlockY);
	}

	void Move() {
		int Y = block.getPosition().y;
		bool isMove = true;
		bool isClicked = false;

		if (GetAsyncKeyState(VK_NUMPAD2)){
			bool a = block.Move(true, false, map);
			if(!a)
				isMove = false;
			isClicked = true;
		}
		else if (GetAsyncKeyState(VK_NUMPAD6)){
			bool a = block.Move(false, true, map);
			if (!a)
				isMove = false;
			isClicked = true;
		}
		else if (GetAsyncKeyState(VK_NUMPAD4)){
			bool a = block.Move(false, false, map);
			if (!a)
				isMove = false;
			isClicked = true;
		}
		else if (GetAsyncKeyState(VK_NUMPAD9)){
			block.Rotate(true,map);
			isClicked = true;
		}
		else if (GetAsyncKeyState(VK_NUMPAD7)) {
			block.Rotate(false, map);
			isClicked = true;
		}

		//if(isClicked) Beep(300, 50);

		if (block.getPosition().y != block.getPosition().y)
			stepsToFall = 0;

		if (stepsToFall > painter.cFrequency*2) {
			bool a = block.Move(true, false, map);
			if (!a){
				isMove = false;
			}
			stepsToFall = 0;
		}

		if (!isMove) Place();
	}

	void CheckLines() {
		int P = 0;
		for (int i = MAP_Y - 1;i >= 0;i--) {
			int C = 0;

			for (int j = 0;j < MAP_X;j++) {
				if (map[j][i] == PlacedBlock)
					C++;
			}

			if (C == MAP_X) {
				P++;
				LV += 0.125;
				Beep(500+(100 * P), 300);
				for (int q = i+1;q < MAP_Y;q++) {
					for (int j = 0;j < MAP_X;j++) {
						map[j][q - 1] = map[j][q];
					}
				}
			}
		}
		if (P == 4) score += 22800;
		else score += 760 * P;
	}
	bool isWork() {
		for (int j = 0;j < MAP_X;j++) {
			if (map[j][18] == PlacedBlock) {
				Beep(200, 300);
				if (!isSaved){
					Failure();
					isSaved = true;
				}
				return false;
			}
		}
		return true;
	}

	void Failure() {
		Beep(1000, 1000);
		std::ofstream file;
		std::ifstream indexer("Count.txt");
		file.open("Records.txt",std::ios::app);
		int ind = 0;
		indexer >> ind;
		indexer.close();
		std::ofstream indexe("Count.txt");
		indexe.clear();
		indexe << ind + 1;
		indexe.close();
		file << ind << " : " << score<<"\n";
		file.close();
	}

	int getScore() {
		return score;
	}

	void WriteBlock() {
		typeBlock buffer[MAP_X][MAP_Y];
		vec2i pos = block.getPosition();

		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				buffer[i][j] = map[i][j];
				if (map[i][j] == CurrentBlock) {
					map[i][j] = Air;
				}

			}
		}

		for (int i = 0;i < block.sizeCol();i++) {
			for (int j = 0;j < block.sizeCol();j++) {

				if (block.getStructure(i, j) == CurrentBlock && IsInMap(pos.x + i, pos.y + j)) {
					map[pos.x + i][pos.y + j] = CurrentBlock;
				}

			}
		}

		painter.Paint(map, score, LV,block.getColor(),nextBlock);

		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				map[i][j] = buffer[i][j];
			}
		}


		stepsToFall += LV ;
	}
};

