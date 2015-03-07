#ifndef __Straights_Program__File__
#define __Straights_Program__File__

#include<vector>
#include "Player.h"
#include "Card.h"
#include "Subject.h"

class Game : public Subject {
	void printWinner();
	int maxScore;
    int totalScore[4];
    int roundScore[4];
    vector<Card*> currPlayerHand;
    vector<Card*> currLegalPlays;
    vector<bool> playerType;
    vector<int> winningPlayers;
    Table *table;
    int currentPlayer;
    int turnNo;
    int state;
    Card* cardToPlay;

public:
	vector<Player*> Contestants;
	
	//Getters
	int 			getState() { return state;}
	int 			getCurrentPlayer() { return currentPlayer;}
	vector<Card*> 	getCurrentPlayerHand() { return currPlayerHand;}
	vector<Card*> 	getCurrentLegalPlays() { return currLegalPlays;}
	int* 			getScore() {return totalScore;}
	int* 			getRoundScore() {return roundScore;}
	vector<int> 	getWinners() { return winningPlayers; }
	Table* 			getTable() { return table;}

	//Modifiers
	void 			playerQuits(int);
	void 			playTurn(Card *);
    Game(vector<bool>,int);
    ~Game();										//frees memory allocated to each player
													//implements the play function
};

#endif
