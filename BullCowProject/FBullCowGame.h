#pragma once
#include<string>

using FString=std::string;
using int32=int;

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

struct FBullCowCount {
	int32 Bulls=0;
	int32 Cows=0;
};


class FBullCowGame {
public:
	FBullCowGame();//construcotr

	
	int32 GetMaxTries() const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength()const;
	bool IsGameWon()const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();

	//counts bull &cows, and increases a turn #, assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialization

	int32 MyCurrentTry;
	int32 MyMaxTires;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString)const;
	bool IsLowerCase(FString)const;
};