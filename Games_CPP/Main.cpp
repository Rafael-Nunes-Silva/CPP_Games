#include <iostream>
#include <string>
#include <map>

#include "Constants.hpp"
#include "GuessingGame.hpp"
#include "HangmanGame.hpp"

void Replay();

std::map<int, std::string> gamesList{
	{ 0, "Guessing Game"},
	{ 1, "Hangman Game"},
};

int main() {
	system("cls");
	std::cout << "************" << std::endl;
	std::cout << "* Welcome! *" << std::endl;
	std::cout << "************" << std::endl;

	int gameIndex = 0;
	GuessingGame guessingGame;
	HangmanGame hangmanGame;

	std::cout << "Choose a Game to Play:" << std::endl;

	for (int i = 0; i < gamesList.size(); i++)
		std::cout << i << " - " << gamesList[i] << std::endl;

	std::cin >> gameIndex;

	system("cls");
	switch (gameIndex)
	{
	case 0:
		guessingGame.RunGame();
		break;
	case 1:
		hangmanGame.RunGame();
		break;
	}

	Replay();

	return 0;
}

void Replay() {
	std::cout << "Nice! Wanna Play Again? (Y) (N)" << std::endl;
	char replay = ' ';
	std::cin >> replay;
	if (std::toupper(replay) == 'Y')
		main();
}