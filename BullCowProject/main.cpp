/*This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC patter, and is responsible for all user interaction. 

For game logic see the FBullCowGame class

*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText=std::string;
using int32=int;

//Prototypes
void introduction();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

//the entry point for application
int main() {
	bool bPlayAgain=false;
	do {
		introduction();
		PlayGame();
		bPlayAgain=AskToPlayAgain();
	}while(bPlayAgain);

	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries=BCGame.GetMaxTries();

	//loop for guess while the game is Not won
	//and there are still tries remaining
	while (!BCGame.IsGameWon()&&(BCGame.GetCurrentTry() <= MaxTries)) {
			FText Guess=GetValidGuess();

			//subit valid guess to game, and reveive counts
			FBullCowCount BullCowCount=BCGame.SubmitValidGuess(Guess);

			//print number of bulls and cows
			std::cout<<"Bulls= "<<BullCowCount.Bulls;
			std::cout<<"Cows= "<<BullCowCount.Cows;
			std::cout<<std::endl;
	}


	PrintGameSummary();

	return;
}

bool AskToPlayAgain(){
	std::cout<<"Do you want to play again? (y/n) ";
	FText Response="";
	std::getline(std::cin,Response);
	return (Response[0]=='y')||(Response[0]=='Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout<<"Game won!\n";
	}
	else {
		std::cout<<"Game lost!\n";
	}
}

void introduction() {
	//intruduce the game
	constexpr  int32 WORD_LENGTH=5;
	std::cout<<"\nWelcome to Bulls and Cows"<<std::endl;
	//printf("printf");

	std::cout<<"Can you guess the "<<BCGame.GetHiddenWordLength()
		<<" letter isogram I'm thinking of?"<<std::endl;

	return;
}

FText GetValidGuess() {
	EGuessStatus Status=EGuessStatus::Invalid_Status;
	FText Guess="";
	do{
		int32 CurrentTry=BCGame.GetCurrentTry();

		std::cout<<"Try "<<CurrentTry<<".";
		std::cout<<"Enter your guess:";
		//get a guess from the player
		
		std::getline(std::cin,Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
			case EGuessStatus::Wrong_Length:
				std::cout<<"Please enter a "<<BCGame.GetHiddenWordLength()<<" letter word.\n";
				break;

			case EGuessStatus::Not_Isogram:
				std::cout<<"Please enter a word without repeating letter.\n";
				break;

			case EGuessStatus::Not_Lowercase:
				std::cout<<"Please enter all lowercase letters.\n";
				break;
			default:
				//assume the guess is valid
				break;
		}
		std::cout<<std::endl;
	}while(Status!=EGuessStatus::OK);//keep looping until we get no errors

	return Guess;
	
}
