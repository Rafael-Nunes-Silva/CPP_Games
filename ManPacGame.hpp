#ifndef MANPACGAME_HPP
#define MANPACGAME_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Constants.hpp"

class Map {
public:
	std::vector<std::string> map;

	int index;
public:
	Map();
	Map(int index);

	bool IsInside(Position pos);
	bool IsWalkable(Position pos, char character = Enemy_Symbol);

	bool FindPlayer(Position* player);
	void Kill(Position pos, char character);
	void Move(Position* character, Position nextPos, char symbol = Enemy_Symbol);
	void GetEnemies(std::vector<Position>* enemies);

	std::vector<Position> Bombs();

	void Load();
	void Draw();
};

class ManPacGame {
	Map map;

	Position player;
	int playerBombs=0;

	std::vector<Position> enemies;
	Position posAround[4] = {
						{0, -1},
				{-1, 0},		{1, 0},
						{0,  1},
	};
	Position usablePos[4];
	std::vector<Position> usedPos;
	int F[4];
public:

	void RunGame();

	void GetInput();
	void UseBomb();

	void SetupEnemies();
	void EnemiesLogic();
	bool IsUsed(Position* used, Position pos);

	bool FinishGame();
};
#endif