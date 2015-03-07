#include "Controller.h"

Game* Controller::setupGame(vector<bool> playerType,int seed,MainWindow* mW) {
	g=new Game(playerType,seed);
	g->subscribe(mW);
	return g;
}


void Controller::playTurn(Card* c)
{
	g->playTurn(c);
}


/*
If Game has not already been deleted at the end of a round, delete Game
*/
Controller::~Controller() {
	if(g->getState()!=(-2))
		delete g;
}

