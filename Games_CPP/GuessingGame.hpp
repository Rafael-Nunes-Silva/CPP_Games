#ifndef GUESSINGGAME_HPP
#define GUESSINGGAME_HPP

#include <iostream>

#include "Constants.hpp"

class GuessingGame {
	int difficulty = MEDIUM;
	int tries = 3;
	int secretNum = 8;
	int points = 1000;
public:
	void RunGame();

	void LostGame();
	void WonGame();
};
#endif