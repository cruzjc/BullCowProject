#include "FBullCowGame.h"
#include<map>
#define TMap std::map

using int32=int;

//default consttuctor
FBullCowGame::FBullCowGame(){Reset();}

void FBullCowGame::Reset()
{
	bGameIsWon=false;
	const int32 MAX_TRIES=8;
	MyCurrentTry=1;
	MyMaxTires=MAX_TRIES;


	const FString HIDDEN_WORD="planet";
	MyHiddenWord=HIDDEN_WORD;
	return;
}

int32 FBullCowGame::GetMaxTries()const {
	TMap<int32,int32>WordLengthToMaxTries{{3,4},{4,7},{5,10},{6,16},{7,20}};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry()const {return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}

bool FBullCowGame::IsGameWon()const {return bGameIsWon;}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{
	//if the guess isn't an isogram, return an error
	if (!IsIsogram(Guess)){
		return EGuessStatus::Not_Isogram;
	}
	//if the guess isn't all lowercase , return an error
	else if (!IsLowerCase(Guess)) { 
		return EGuessStatus::Not_Lowercase;
	}
	//if guess length is wrong
	else if (Guess.length()!=GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
			
	

	//otherwise return okay

	return EGuessStatus::OK;
}

//revieves a valid guess, incriments turn, and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength=MyHiddenWord.length();//assuming same length as guess


	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
	//compare letters against the guess
		for(int32 GChar=0;GChar<WordLength;GChar++){
    //if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
	//incriment bull if they're in the same place
	//incrememtn cows if not
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon=true;
	}
	else {
		bGameIsWon=false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if(Word.length()<=1){return true;}

	TMap<char, bool> LetterSeen;//setup of map
	for (auto Letter : Word) {
		Letter=tolower(Letter);//handle mixed case
		
		if(LetterSeen[Letter]){//if the letter is in the map
			return false;
		}
		else {
			LetterSeen[Letter]=true;
		}
		//add the letter to the map as seen

	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter))//if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}
