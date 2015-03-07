//
//  ComputerPlayer.cpp
//  Straights Program
//
//  Created by Eliav Yehuda on 2013-07-01.
//  Copyright (c) 2013 Eliav Yehuda. All rights reserved.
//

#include "ComputerPlayer.h"

int ComputerPlayer::play(Table* t,Card* cardToPlay)
{
    updateMyLegalPlays(t);
    int index;
    
    /* First Case: if legal play can be made
     1) Searches hand for first legal play
     2) Swaps the card to be played to the last element of the hand vector (kind of like bubble up)
     3) Removes the last element from hand vector
     4) Adds the removed card to table
     5) Prints what card the player just played
     */
    
    if(legalPlays.size()!=0)
    {
        Card* myCard=legalPlays[0];
        for(int i=0;i<hand.size();i++)
        {
            if(*myCard==*hand[i])
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
        hand.pop_back();
        t->updateTable(myCard);
        cout<<"Player "<<playerNo<<" plays "<<*myCard<<"."<<endl;
    }
    /*Case Two: If there are no legal plays
     1) Takes the first card in hand and moves it to the end of the hand vector (kind of like bubble up)
     2) Removes last element
     3) Adds the removed element to the player's discards array
     4) Prints what card the player discarded
     */
    else
    {
        Card* myCard=hand[0];
        for(int i=0;i<hand.size()-1;i++)
        {
            Card* temp = hand[i];
            hand[i]=hand[i+1];
            hand[i+1]=temp;
        }
        hand.pop_back();
        discards.push_back(myCard);
        cout<<"Player "<<playerNo<<" discards "<<*myCard<<"."<<endl;
        
    }
    return 0;
}

