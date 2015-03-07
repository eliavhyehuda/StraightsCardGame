#ifndef __GTKMM_Controller__
#define __GTKMM_Controller__

#include "Game.h"
#include "MainWindow.h"
#include <vector>


class MainWindow;
class Game;

class Controller
{
	private:
		Game* g;
	public:
		~Controller();
		Game* setupGame(vector<bool>,int,MainWindow*);
		void playTurn(Card*);
};

#endif