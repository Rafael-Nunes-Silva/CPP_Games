#include "HangmanGame.hpp"
void HangmanGame::RunGame() {
	secretWord = GetRandomWord();

	Draw();

	while(misses<5) {
		char guess = GetPlayerGuess();

		if (!HasBeenGuessed(guess))
			guessedLetters.push_back(guess);

		if (!InSecretWord(guess))
			misses++;

		Draw();

		if (GuessedWord() == secretWord) {
			WonGame();
			return;
		}
	}
	LostGame();
}

std::string HangmanGame::GetRandomWord() {
	std::string word;
	std::vector<std::string> wordsList;
	std::ifstream file("Words.txt");
	while (std::getline(file, word))
		wordsList.push_back(word);
	file.close();

	word = wordsList[rand() % wordsList.size()];
	for (int i = 0; i < word.size(); i++)
		word[i] = toupper(word[i]);

	return word;
}
char HangmanGame::GetPlayerGuess() {
	std::cout << "Guess a Letter: ";
	char guess = ' ';
	std::cin >> guess;
	return toupper(guess);
}
void HangmanGame::Draw() {
	system("cls");

	std::cout << "****************" << std::endl;
	std::cout << "* Hangman Game *" << std::endl;
	std::cout << "****************" << std::endl;

	std::cout << "Guessed Letters:" << std::endl;
	for (int i = 0; i < guessedLetters.size(); i++)
		std::cout << guessedLetters[i] << ", ";
	std::cout << std::endl;

	switch (misses) {
	case 1:
		std::cout << " _________  " << std::endl;
		std::cout << " |/      |  " << std::endl;
		std::cout << " |      (_) " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		break;
	case 2:
		std::cout << " _________  " << std::endl;
		std::cout << " |/      |  " << std::endl;
		std::cout << " |      (_) " << std::endl;
		std::cout << " |      \\|  " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		break;
	case 3:
		std::cout << " _________  " << std::endl;
		std::cout << " |/      |  " << std::endl;
		std::cout << " |      (_) " << std::endl;
		std::cout << " |      \\|/ " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		break;
	case 4:
		std::cout << " _________  " << std::endl;
		std::cout << " |/      |  " << std::endl;
		std::cout << " |      (_) " << std::endl;
		std::cout << " |      \\|/ " << std::endl;
		std::cout << " |       |  " << std::endl;
		std::cout << " |      /   " << std::endl;
		std::cout << " |          " << std::endl;
		break;
	case 5:
		std::cout << " _________  " << std::endl;
		std::cout << " |/      |  " << std::endl;
		std::cout << " |      (_) " << std::endl;
		std::cout << " |      \\|/ " << std::endl;
		std::cout << " |       |  " << std::endl;
		std::cout << " |      / \\ " << std::endl;
		std::cout << " |          " << std::endl;
		break;
	default:
		std::cout << " _________  " << std::endl;
		std::cout << " |/      |  " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		std::cout << " |          " << std::endl;
		break;
	}

	std::cout << "_|___ ";
	for (int i = 0; i < secretWord.size(); i++) {
		if (HasBeenGuessed(secretWord[i]))
			std::cout << " " << secretWord[i] << " ";
		else std::cout << " _ ";
	}
	std::cout << std::endl;
}
void HangmanGame::AddNewWord() {
	std::cout << "\nType In a New Word To Be Added: ";
	std::string word, newWord;
	std::cin >> newWord;

	newWord[0] = toupper(newWord[0]);
	for (int i = 1; i < newWord.size(); i++)
		newWord[i] = tolower(newWord[i]);

	bool addNewWord = true;

	std::ifstream iFile("Words.txt");
	while (std::getline(iFile, word))
		if (word == newWord) {
			addNewWord = false;
			break;
		}
	iFile.close();

	if (addNewWord) {
		std::ofstream oFile("Words.txt", std::ios::app);

		oFile << "\n" << newWord.c_str();

		oFile.close();
	}
}

std::string HangmanGame::GuessedWord() {
	std::string guessedWord = "";
	for (int i = 0; i < secretWord.size(); i++) {
		for (int j = 0; j < guessedLetters.size(); j++) {
			if (secretWord[i] == guessedLetters[j])
				guessedWord.push_back(secretWord[i]);
		}
	}
	return guessedWord;
}
bool HangmanGame::HasBeenGuessed(char c) {
	for (int i = 0; i < guessedLetters.size(); i++)
		if (c == guessedLetters[i]) return true;
	return false;
}
bool HangmanGame::InSecretWord(char c) {
	for (int i = 0; i < secretWord.size(); i++)
		if (c == secretWord[i]) return true;
	return false;
}

void HangmanGame::LostGame() {
	std::cout << "*************" << std::endl;
	std::cout << "* You Lost! *" << std::endl;
	std::cout << "*************" << std::endl;
	std::cout << "The Right Word was: " << secretWord << ".\n" << std::endl;
	AddNewWord();
}
void HangmanGame::WonGame() {
	std::cout << "************" << std::endl;
	std::cout << "* You Won! *" << std::endl;
	std::cout << "************" << std::endl;
	AddNewWord();
}