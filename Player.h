#ifndef __Straights_Program__Player__
#define __Straights_Program__Player__

#include "Table.h"
#include "Card.h"
#include<vector>
#include<iostream>
using namespace std;

class Player {
protected:
    vector<Card*> hand;									//stores player's hand
    vector<Card*> legalPlays;							//stores player's legal plays
    vector<Card*> discards;								//stores player's cards as they discard
    int score;											//stores player's current round score
    int totalScore;										//stores player's total score
    int playerNo;										//playerNo = 1 or 2 or 3 or 4

public:
    void updateMyLegalPlays(Table*);                    //updates the player's legalPlays vector
	virtual int play(Table*,Card*) = 0;											//Discards or plays
    //Returns -1 if player quits -2 if player ragequits 0 otherwise
    virtual void copyFromHuman(vector<Card*>, vector<Card*>, int, int) {}	//RAGEQUIT - converts human player to computer player
    virtual vector<Card*> getHand() const {}										//Getter - returns player's hand
    virtual vector<Card*> getDiscards() const { return discards; }									//Getter - returns player's Discards
    virtual vector<Card*> getLegalPlays() {return legalPlays;}
    void printDiscards() const;
    void setScore();														//Sets the player's score
    int getScore() const { return score; }									//Getter - returns player's current round score
    int getTotalScore() const { return totalScore; }						//Getter - returns player's total score
    void clearHands();														//Setter - clears the discards vector after each round
	void pushBackHand(Card* c) { hand.push_back(c); }						//Setter - Updates player's hand
	int getPlayerNo() const { return playerNo; }							//Getter - returns player's no (1 or 2 or 3 or 4)
    Player(int playNo)
    {
        playerNo=playNo;
        score=0;
        totalScore=0;
    }
    virtual ~Player() {}
};











#endif /* defined(__Straights_Program__Player__) */
