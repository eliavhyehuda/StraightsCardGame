#ifndef GTKMM__MainWindow__
#define GTKMM__MainWindow__

#include <gtkmm.h>
#include "Observer.h"
#include "Controller.h"
#include "Card.h"

class Observer;
class Controller;


class MainWindow : public Gtk::Window, public Observer {

public:
	MainWindow();
	virtual ~MainWindow() {}
private:
	Gtk::VBox v;

	Gtk::HBox h1;
	Gtk::VBox h2;
	Gtk::HBox h3;
	Gtk::HBox h4;

	Gtk::Button start_button;
	Gtk::Button end_button;
	Gtk::Entry seed_entry;


	std::vector<Gtk::HBox*> cardRows;		//4 Rows in the deck
	
	Gtk::Frame player1Frame;
	Gtk::Frame player2Frame;
	Gtk::Frame player3Frame;
	Gtk::Frame player4Frame;

	Gtk::VBox player1VBox;
	Gtk::VBox player2VBox;
	Gtk::VBox player3VBox;
	Gtk::VBox player4VBox;

	std::vector<Gtk::Button*> playerButtons;
	std::vector<Gtk::Label*> playerPoints;
	std::vector<Gtk::Label*> playerDiscards;

	std::vector<bool> playerType;			//false is computer, true is human

	Gtk::Image* deck[53];  
	Gtk::Image* playerHands[13];

	Gtk::Button* hand_button[13];
	void onButtonClicked(int p);
	void startButtonClicked();

	void update();

	Controller* control;
	Game* subject;

	int curr_player;
	vector<Card*> hand;
	vector<Card*> myLegalPlays;
	vector<Card*> discards;

	vector<Card*> Clubs;
	vector<Card*> Diamonds;
	vector<Card*> Hearts;
	vector<Card*> Spades;
	
	int playerDiscardsNumber[4];
	Table* table;
	int winState;
	void onHandClicked(int);

	Card* dummyCard;

	void endGameClicked();

};


#endif