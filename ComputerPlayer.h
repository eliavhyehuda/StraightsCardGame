//
//  ComputerPlayer.h
//  Straights Program
//
//  Created by Eliav Yehuda on 2013-07-01.
//  Copyright (c) 2013 Eliav Yehuda. All rights reserved.
//

#ifndef __Straights_Program__ComputerPlayer__
#define __Straights_Program__ComputerPlayer__

#include "Player.h"

class ComputerPlayer : public Player
{
    int play(Table*,Card*);															//Computer will either play or discard
public:
    ComputerPlayer(int j) : Player(j) {}										//Calls player's constructor with the player number
    void copyFromHuman(vector<Card*> h, vector<Card*> disc, int oldSc, int Sc)	//RAGEQUIT - converts human player to computer player
    {
        hand=h;
        discards=disc;
        totalScore=oldSc;
        score=Sc;
    }
};

#endif /* defined(__Straights_Program__ComputerPlayer__) */
