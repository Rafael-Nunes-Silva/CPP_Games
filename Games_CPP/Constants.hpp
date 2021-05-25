#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>

#define PATH_testMap	"Resources/Maps/testMap.txt"
#define PATH_WordsList	"Resources/Words.txt"
#define PATH_Maps		"Resources/Maps/"

#define Map_		"Map_"
#define MapExten	".txt"

#define Walkable_Symbol ','
#define Player_Symbol	'P'
#define Enemy_Symbol	'&'
#define Bomb_Symbol		'@'

#define AStar_UP	Position(0, -1)
#define AStar_DOWN	Position(0, 1)
#define AStar_RIGHT	Position(1, 0)
#define AStar_LEFT	Position(-1, 0)

struct Position {
	int x, y;

	Position(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	Position operator + (Position p) {
		return Position(x + p.x, y + p.y);
	}
	bool operator == (Position p) {
		return (x == p.x && y == p.y) ? true : false;
	}
	bool operator != (Position p) {
		return  (x == p.x && y == p.y) ? false : true;
	}
};

#define HARD	3
#define MEDIUM	2
#define EASY	1

#define Guessing_Game	0
#define Hangman_Game	1
#define ManPac_Game		2
#endif