//
//  HumanPlayer.h
//  Straights Program
//
//  Created by Eliav Yehuda on 2013-07-01.
//  Copyright (c) 2013 Eliav Yehuda. All rights reserved.
//

#ifndef __Straights_Program__HumanPlayer__
#define __Straights_Program__HumanPlayer__
#include "Player.h"

class HumanPlayer : public Player
{
    int play(Table*,Card*);												//Returns 0 if Player either plays,discards
    //Returns -1 if player quits, -2 if player ragequits
public:
    void printHand() const;											//Prints player's hand
    void printlegalPlays() const;									//Prints player's legal plays
    HumanPlayer(int j) : Player(j) {}								//Calls Base class constructor with player number
    vector<Card*> getHand() const { return hand; }					//Getter - returns player's hand (Used if player Ragequits)
};


#endif /* defined(__Straights_Program__HumanPlayer__) */
