#include "GuessingGame.hpp"
void GuessingGame::RunGame() {
	std::cout << "*****************" << std::endl;
	std::cout << "* Guessing Game *" << std::endl;
	std::cout << "*****************" << std::endl;

	std::cout << "Choose the Difficulty: " << EASY << " - Easy | " << MEDIUM << " - Medium | " << HARD << " - Hard" << std::endl;
	std::cin >> difficulty;

	switch (difficulty)
	{
	case EASY:
		tries = 5;
		std::cout << "You Have Choosen Easy." << std::endl;
		break;
	case MEDIUM:
		tries = 3;
		std::cout << "You Have Choosen Medium." << std::endl;
		break;
	case HARD:
		tries = 1;
		std::cout << "You Have Choosen Hard." << std::endl;
		break;
	default:
		RunGame();
		break;
	}
	std::cout << "You Have a Total of " << tries << " Tries.\n" << std::endl;

	int guess = 0;
	for (int i = tries; i > 0; i--) {
		std::cout << "You Have " << i << " Tries Left." << std::endl;
		std::cout << "Guess a Number: ";
		std::cin >> guess;

		points -= (((guess - secretNum) < 0) ? -(guess - secretNum) : (guess - secretNum)) * (difficulty * 10);

		if (guess > secretNum) {
			std::cout << "Your Guess was Too High." << std::endl;
			continue;
		}
		if (guess < secretNum) {
			std::cout << "Your Guess was Too Low." << std::endl;
			continue;
		}

		WonGame();
		return;
	}
	LostGame();
}

void GuessingGame::LostGame() {
	std::cout << "*************" << std::endl;
	std::cout << "* You Lost! *" << std::endl;
	std::cout << "*************" << std::endl;
	std::cout << "You Finished the Game With a Total of " << points << "Points.\n" << std::endl;
}
void GuessingGame::WonGame() {
	std::cout << "************" << std::endl;
	std::cout << "* You Won! *" << std::endl;
	std::cout << "************" << std::endl;
	std::cout << "You Finished the Game With a Total of " << points << "Points.\n" << std::endl;
}