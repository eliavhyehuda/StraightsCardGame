#include "Game.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include <iostream>
using namespace std;

/*
1) Creates players
2) Initializes scores
3) Creates table
4) State=0
5) Finds first player
6) Sets TurnNo to zero
*/
Game::Game(vector<bool> pType, int seed) {
    srand48(seed);
    playerType=pType;

    /*Checks if players are human or computer*/
    for(int i=0;i<4;i++)
    {
        Player* p;
        if(playerType[i])
            p = new HumanPlayer(i+1);
        else
            p = new ComputerPlayer(i+1);
        Contestants.push_back(p);
    }

    maxScore=0;
    for(int i=0;i<4;i++)
    {
        totalScore[i] = 0;
        roundScore[i] = 0;
    }
    table = new Table();
    state=0;
    currentPlayer=0;

    int j=0;
    Card *check = new Card(SPADE,SEVEN);
    /*Assigns each player his hand and finds the first player*/
    for(int i=1;i<4+1;i++)
    {
        Player* p=Contestants[i-1];
        
        for(;j<(i*13);j++)
        {
            Card* c=table->getCardInDeck(j);
            p->pushBackHand(c);
            if(*c==*check)
                currentPlayer=i-1;
        }
    }
    delete check;
    if(playerType[currentPlayer])
        currPlayerHand=Contestants[currentPlayer]->getHand();
    turnNo=0;
}

/*
Deletes players
Deletes table
*/
Game::~Game()
{
 
    for(int i=0;i<4;i++)
        delete Contestants[i];
    delete table;
}

/*
RageQuit Function
*/
void Game::playerQuits(int p) {
    Player* newP= new ComputerPlayer(p+1);
    Player* currP = Contestants[p];
    newP->copyFromHuman(currP->getHand(), currP->getDiscards(), currP->getTotalScore(),currP->getScore());
    delete currP;
    Contestants[p]=newP;
    playerType[p]=false;
    playTurn(cardToPlay);
}

/*
Finds first player each round, except for round 1
If human player is encountered, notifies
Plays card passed in. If current player is a computer, card passed in does not matter
If we are at turn 51 ie end of round then
    1) Notify to update scores
    2) If max score is above 80, call notify again to print winner
*/

void Game::playTurn(Card* c)
{
    if(state==-1)
    {
        state=0;
        Card *check = new Card(SPADE,SEVEN);
        /*Assigns each player his hand and finds the first player*/
        int j=0;
        for(int i=1;i<4+1;i++)
        {
            Player* p=Contestants[i-1];
            
            for(;j<(i*13);j++)
            {
                Card* c=table->getCardInDeck(j);
                p->pushBackHand(c);
                if(*c==*check)
                    currentPlayer=i-1;
            }
        }
        delete check;
        if(playerType[currentPlayer])
            currPlayerHand=Contestants[currentPlayer]->getHand();
        notify();
    }


    int noQuit;
	//52 Turns every round
    for(;turnNo<52;turnNo++)
    {
        currentPlayer%=4;
        if(state==0)
        {
            if(playerType[currentPlayer])
            {
                
                state=2;                    //deck needs to be updated
                notify();
                currPlayerHand=Contestants[currentPlayer]->getHand();
                Contestants[currentPlayer]->updateMyLegalPlays(table);
                currLegalPlays=Contestants[currentPlayer]->getLegalPlays();
                state=1;                    //user needs to select a card
                notify();
                return;
            }
        }

        //noQuit has no meaning. Carried over from part 1
        noQuit=Contestants[currentPlayer]->play(table,c);

        currentPlayer++;
        
        if(turnNo==51)
        {
            state=3;
            for(int i=0;i<4;i++)
            {
                Contestants[i]->printDiscards();
                totalScore[i]=Contestants[i]->getTotalScore();
                Contestants[i]->setScore();
                roundScore[i]=Contestants[i]->getScore();
            }
            notify();
            for(int i=0;i<4;i++)
            {
                if(maxScore<Contestants[i]->getTotalScore())
                    maxScore=Contestants[i]->getTotalScore();
            }
            if(maxScore>=80)
            {

                state=-3;
                notify();
                printWinner();
                state=-2;
                notify();
                for(int i=0;i<4;i++)
                {
                    Contestants[i]->clearHands();
                }
                table->clearTable();
                delete table;
                return;
            }
            else
            {
                state=-3;
                notify();
                state=-1;
                //state=-1;
                for(int i=0;i<4;i++)
                {
                    Contestants[i]->clearHands();
                }
                
                /*Clears table and calls shuffle*/
                table->clearTable();
                table->callShuffle();
                turnNo=0;
                notify();
                return;
            }
        }
        state=0;
    }

}

/*
Instead of printing winner, sets the winners in a vector called winningPlayers
*/
void Game::printWinner()
{
	int minScore=Contestants[0]->getTotalScore();
	/*finds the min score*/
    for(int i=1;i<4;i++)
    {
        int tempo=Contestants[i]->getTotalScore();
        if(tempo<minScore)
        {
            minScore=tempo;
        }
    }
	/*Prints all players with min score*/
	for(int i=0;i<4;i++)
	{
		int tempo=Contestants[i]->getTotalScore();
		if(tempo==minScore)
			winningPlayers.push_back(i+1);
	}
}