//
//  HumanPlayer.cpp
//  Straights Program
//
//  Created by Eliav Yehuda on 2013-07-01.
//  Copyright (c) 2013 Eliav Yehuda. All rights reserved.
//

#include "HumanPlayer.h"
#include "Command.h"
void HumanPlayer::printHand() const
{
    cout << "Your hand:";
    int n=(int) this->hand.size();
    for(int i=0;i<n;i++)
        cout<<" "<<*hand[i];
    cout<<endl;
}

void HumanPlayer::printlegalPlays() const{
    cout << "Legal plays:";
    int n=(int) this->legalPlays.size();
    for(int i=0;i<n;i++)
        cout<<" "<<*legalPlays[i];
    if(legalPlays.size()==0)
        cout<<" ";
    cout<<endl;
}

int HumanPlayer::play(Table* t,Card* cardToPlay)
{
    updateMyLegalPlays(t);
    t->printTable();
    printHand();
    printlegalPlays();
    Command c;

    c.type=DISCARD;
    for(int k=0;k<(int)legalPlays.size();k++)
    {
        if(*cardToPlay==*legalPlays[k])
        {
            c.type=PLAY;
        }
    }

    /*CASE 1: Player plays
     1) If player has no legal plays, take in another command
     2) If a player has legal plays
     i)   go through hand and find the card
     ii)  push the card to the back of the hand
     iii) pop card from hand
     iv)  updates table with the card that the player plays
     v)   Prints what card the player played
     */
    if(c.type==PLAY)
    {
        
        /*you have a legal play*/
        int index;
        for(int i=0;i<hand.size();i++)
        {
            if(*cardToPlay==*hand[i])
            {
                index=i;
                break;
            }
        }
        
        for(int i=index;i<hand.size()-1;i++)
        {
            Card* temp = hand[i];
            hand[i]=hand[i+1];
            hand[i+1]=temp;
        }
        Card* myCard=hand.back();
        hand.pop_back();
        
        /*updating table*/
        t->updateTable(myCard);
        cout<<"Player "<<playerNo<<" plays "<<*myCard<<"."<<endl;
    
        
    }
    /*CASE 5: Player Discards
     1)Checks if player has any legal plays
     i)If yes, waits for another command to be taken in
     2)If player has no legal plays
     i)   Push selected card to the back of the hand
     ii)  Pop card from hand
     iii) Update player's discards hand
     iv)  Print what card the player discarded
     */
    else if(c.type==DISCARD)
    {
        int index=0;
        for(int i=0;i<hand.size();i++)
        {
            if(*cardToPlay==*hand[i])
            {
                index=i;
                break;
            }
        }        
        {
            for(int i=index;i<hand.size()-1;i++)
            {
                Card* temp = hand[i];
                hand[i]=hand[i+1];
                hand[i+1]=temp;
            }
            Card* myCard=hand.back();
            hand.pop_back();
            discards.push_back(myCard);
            cout<<"Player "<<playerNo<<" discards "<<*myCard<<"."<<endl;
        }
        return -3;
        
    }
    
    return 0;
}


