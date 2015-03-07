//
//  Player.cpp
//  Straights Program
//
//  Created by Eliav Yehuda on 2013-07-01.
//  Copyright (c) 2013 Eliav Yehuda. All rights reserved.
//

#include "Player.h"
#include "Command.h"
#include<iostream>
#include<vector>
using namespace std;






/* ComputerPlayer */
void Player::clearHands()													//Called after each round - only clears discards vector as hand and legalPlays
{																			//will already by empty
    score=0;
    int r=(int)discards.size();
    for(int i=0;i<r;i++)
        discards.pop_back();
}


void Player::setScore()														//Called after each round - set's the player's current and total score
{
    int temp=0;
    for(int i=0;i<discards.size();i++)
    {
        temp=convertRank(discards[i]->getRank());
        score+=temp;
    }
    totalScore+=score;
}

void Player::printDiscards() const											//Getter - prints the player's discards
{
    for(int i=0;i<discards.size();i++)
        cout<<" "<<*discards[i];
    if(discards.size()==0)
        cout<<" ";
    cout<<endl;
}

void Player::updateMyLegalPlays(Table* t)									//Setter - compares player's hand with the LegalPlays vector in Table
{																			//and updates the player's legalPlays vector
    int r=this->legalPlays.size();
    for(int i=0;i<r;i++)
    {
        this->legalPlays.pop_back();
    }
    vector<Card*> PlaysOnTable = t->getLegalPlays();
    int n1= (int) PlaysOnTable.size();
    int n2= (int) this->hand.size();
    for(int i=0;i<n2;i++)
    {
        for(int j=0;j<n1;j++)
        {
            if(hand[i]==PlaysOnTable[j])
            {
                this->legalPlays.push_back(hand[i]);
                break;
            }
            
        }
    }
}







/* HumanPlayer */


