#pragma once
#include<string>

class BullCowGame {
public:
	BullCowGame();

	void reset();
	bool checkGuessValidity(std::string);

	int getMaxTries()const;
	int getCurrentTry()const;
	bool isGameWon() const;

private:
	int myCurrentTry;
	int myMaxTries;
};