#ifndef __Straights_Program__Table__
#define __Straights_Program__Table__

#include "Card.h"
#include <vector>
#include <stdlib.h>
using namespace std;
void shuffle(vector <Card*>&);

class Table {
    vector<Card*> Clubs;										//Cards of each suit on the table
    vector<Card*> Hearts;
    vector<Card*> Spades;
    vector<Card*> Diamonds;
    vector<Card*> Deck;											//Shuffled Deck
    vector<Card*> OGDeck;										//We maintain a copy of the orginal unshuffled deck for easy access
	vector<Card*> LegalPlays;									//The set of ALL legal plays that can be played
public:
    vector<Card*> getClubs() const { return Clubs; }			//Getter
    vector<Card*> getHearts() const { return Hearts; }			//Getter
    vector<Card*> getSpades() const { return Spades; }			//Getter
    vector<Card*> getDiamonds() const { return Diamonds; }		//Getter
    vector<Card*> getLegalPlays() const { return LegalPlays; }	//Getter
    Card* getCardInDeck(int j) const { return Deck.at(j); }		//Getter
    void printTable() const;									//Prints table
    void printDeck() const;										//Prints deck
    void updateTable(Card*);									//Setter - updates table
    void callShuffle() { shuffle(Deck); }						//Setter - shuffles deck
    void clearTable();											//Clears table and initializes a new LegalPlays vector with 7S only
    Table();													//Initializes pointers to cards, shuffles deck
    ~Table() 													//Destroys all Cards
    {
        for(int i=0;i<52;i++)
        {
            delete OGDeck[i];
        }
    }
};







#endif /* defined(__Straights_Program__Table__) */
