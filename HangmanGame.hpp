#ifndef HANGMANGAME_HPP
#define HANGMANGAME_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Constants.hpp"

class HangmanGame {
	int misses = 0;
	std::string secretWord;
	std::vector<char> guessedLetters;
public:
	void RunGame();

	std::string GetRandomWord();
	char GetPlayerGuess();
	void Draw();
	void AddNewWord();

	std::string GuessedWord();
	bool HasBeenGuessed(char c);
	bool InSecretWord(char c);

	void LostGame();
	void WonGame();
};
#endif