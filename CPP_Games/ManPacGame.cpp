#include "ManPacGame.hpp"
#pragma region Map
Map::Map() {
	index = -1;
}
Map::Map(int index) {
	this->index = index;
	Load();
	Draw();
}

bool Map::IsInside(Position pos) {
	if (pos.x < 0 || pos.y < 0) return false;

	if (pos.y >= map.size() || pos.x >= map[pos.y].size())
		return false;

	return true;
}
bool Map::IsWalkable(Position pos, char character) {
	if (map[pos.y][pos.x] == Walkable_Symbol)
		return true;
	if (map[pos.y][pos.x] == Player_Symbol)
		return true;
	if (character == Player_Symbol) {
		if (map[pos.y][pos.x] == Bomb_Symbol)
			return true;
	}
	return false;
}

bool Map::FindPlayer(Position* player) {
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] != Player_Symbol) continue;
			player->x = x;
			player->y = y;
			return true;
		}
	}
	return false;
}
void Map::Kill(Position pos, char character) {
	if (!IsInside(pos)) return;

	if (map[pos.y][pos.x] == character)
		map[pos.y][pos.x] = Walkable_Symbol;
}
void Map::Move(Position* character, Position nextPos, char symbol) {
	if (!IsInside(nextPos) || !IsWalkable(nextPos, symbol)) return;

	char c = map[character->y][character->x];
	map[character->y][character->x] = Walkable_Symbol;
	map[nextPos.y][nextPos.x] = c;

	*character = nextPos;
}
void Map::GetEnemies(std::vector<Position>* enemies) {
	enemies->clear();
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == Enemy_Symbol) enemies->push_back(Position(x, y));
		}
	}
}

std::vector<Position> Map::Bombs() {
	std::vector<Position> bombs;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == Bomb_Symbol)
				bombs.push_back(Position(x, y));
		}
	}
	return bombs;
}

void Map::Load() {
	std::string name = "Map_", exten = ".txt";
	std::string mapPath = (index < 0) ? PATH_testMap : (PATH_Maps + name + std::to_string(index) + exten);

	std::string line;
	std::ifstream mapFile(mapPath);
	while (std::getline(mapFile, line)) {
		map.push_back(line);
	}
	mapFile.close();
}
void Map::Draw() {
	system("cls");
	for (std::string s : map) {
		for (char c : s) {
			if (c == Walkable_Symbol)
				std::cout << ' ';
			else
				std::cout << c;
		}
		std::cout << std::endl;
	}
}
#pragma endregion
#pragma region ManPacGame
void ManPacGame::RunGame() {
	std::cout << "Choose The Index of The Map: (-1 testMap)" << std::endl;
	int mapIndex = -1;
	std::cin >> mapIndex;
	map = Map(mapIndex);

	map.FindPlayer(&player);
	SetupEnemies();

	do {
		GetInput();

		EnemiesLogic();

		map.Draw();
		std::cout << "Bombs: " << playerBombs << std::endl;
		std::cout << "Controls:\n W \nASD\nB - bomb\n" << std::endl;
	} while (!FinishGame());
}

void ManPacGame::GetInput() {
	char input = ' ';
	std::cin >> input;
	input = toupper(input);

	Position nextPos;
	switch (input) {
	case 'W':
		nextPos.y--;
		break;
	case 'S':
		nextPos.y++;
		break;
	case 'D':
		nextPos.x++;
		break;
	case 'A':
		nextPos.x--;
		break;
	case 'B':
		if (playerBombs > 0) UseBomb();
		break;
	default:
		return;
		break;
	}

	for (Position p : map.Bombs()) {
		if (player + nextPos == p) {
			playerBombs++;
		}
	}

	map.Move(&player, player + nextPos);
}
void ManPacGame::UseBomb() {
	Position bombArea[8] = {
						 {0, -2},
						 {0, -1},
		{-2, 0}, {-1, 0},		{1,  0}, {2,  0},
						 {0,  1},
						 {0,  2}
	};
	for (Position ba : bombArea)
		map.Kill(player + ba, Enemy_Symbol);
	playerBombs--;
	SetupEnemies();
}

void ManPacGame::SetupEnemies() {
	map.GetEnemies(&enemies);

	usedPos.clear();
	for (int e = 0; e < enemies.size(); e++) {
		usedPos.push_back(Position(enemies[e].x, enemies[e].y));
	}
}
void ManPacGame::EnemiesLogic() {
	Position betterPos;

	for (int e = 0; e < enemies.size(); e++) {
		for (int i = 0; i < std::size(posAround); i++) {
			Position pos = (enemies[e] + posAround[i]);

			if (!map.IsInside(pos) || !map.IsWalkable(pos) || pos == usedPos[e]) {
				std::cout << "pos inacesible : (" << pos.x << "x, " << pos.y << "y)" << std::endl;

				F[i] = -1;
				continue;
			}

			usablePos[i] = posAround[i];
			F[i] = ((pos.x - player.x) < 0) ? -(pos.x - player.x) : (pos.x - player.x);
			F[i] += ((pos.y - player.y) < 0) ? -(pos.y - player.y) : (pos.y - player.y);
		}

		int lowerF = 1000;
		for (int i = 0; i < std::size(F); i++) {
			std::cout << "F[i]: " << F[i] << std::endl;

			if (F[i] < 0) continue;

			if (F[i] < lowerF) {
				lowerF = F[i];
				betterPos = usablePos[i];

				std::cout << "f: " << lowerF << std::endl;
				std::cout << "usablePos: (" << usablePos[i].x << "x, " << usablePos[i].y << "y)" << std::endl;
			}
		}

		usedPos[e] = enemies[e];

		map.Move(&enemies[e], enemies[e] + betterPos);
	}
}
bool ManPacGame::IsUsed(Position* used, Position pos) {
	for (int i = 0; i < enemies.size(); i++) {
		if (pos == used[i]) return true;
	}
	return false;
}

bool ManPacGame::FinishGame() {
	if (!map.FindPlayer(&player)) {
		std::cout << "*************" << std::endl;
		std::cout << "* You Died! *" << std::endl;
		std::cout << "*************" << std::endl;
		return 1;
	}

	if (enemies.size() <= 0) {
		std::cout << "************" << std::endl;
		std::cout << "* You Won! *" << std::endl;
		std::cout << "************" << std::endl;
		return 1;
	}

	return 0;
}
#pragma endregion