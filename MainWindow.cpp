#include "MainWindow.h"
#include <iostream>
#include "gtkmm.h"
#include "stdlib.h"
#include <sstream>

using namespace std;

const char * image_names[] = {   
	// Set up CLUBS
	"img/0_0.png", "img/0_1.png", "img/0_2.png", "img/0_3.png",
	"img/0_4.png", "img/0_5.png", "img/0_6.png", "img/0_7.png",
	"img/0_8.png", "img/0_9.png", "img/0_j.png", "img/0_q.png",
	"img/0_k.png",

	// Set up DIAMONDS
	"img/1_0.png", "img/1_1.png", "img/1_2.png", "img/1_3.png",
	"img/1_4.png", "img/1_5.png", "img/1_6.png", "img/1_7.png",
	"img/1_8.png", "img/1_9.png", "img/1_j.png", "img/1_q.png",
	"img/1_k.png",

	// Set up HEARTS
	"img/2_0.png", "img/2_1.png", "img/2_2.png", "img/2_3.png",
	"img/2_4.png", "img/2_5.png", "img/2_6.png", "img/2_7.png",
	"img/2_8.png", "img/2_9.png", "img/2_j.png", "img/2_q.png",
	"img/2_k.png",

	// Set up SPADES
	"img/3_0.png", "img/3_1.png", "img/3_2.png", "img/3_3.png",
	"img/3_4.png", "img/3_5.png", "img/3_6.png", "img/3_7.png",
	"img/3_8.png", "img/3_9.png", "img/3_j.png", "img/3_q.png",
	"img/3_k.png",

	// Blank Card
	"img/nothing.png"
};

MainWindow::MainWindow() :start_button("Start Game"), end_button("End Game")
{
	set_title("straights game");
	set_border_width(5);
	add(v);

	//Winstate = 0 -> Game is not in progress
	//Winstate = 1 -> Game is in progress
	winState=0;

	//adding 3 hboxes and 1 vbox, h2 is a vbox
	v.add(h1);
	v.add(h2);
	v.add(h3);
	v.add(h4);

	//setting the start button,seed entry,end button
	h1.add(start_button);
	seed_entry.set_text("0");
	h1.add(seed_entry);
	h1.add(end_button);

	//Creating 4 Hboxes for each row in the deck
	for(int i=0;i<4;i++)
	{
		Gtk::HBox* h = new Gtk::HBox;
		cardRows.push_back(h);
	}
	h2.add(*cardRows[0]);
	cardRows[0]->set_border_width(10);
	h2.add(*cardRows[1]);
	cardRows[1]->set_border_width(10);
	h2.add(*cardRows[2]);
	cardRows[2]->set_border_width(10);
	h2.add(*cardRows[3]);
	cardRows[3]->set_border_width(10);

	//adding 4 frames, 1 for each player
	h3.add(player1Frame);
	h3.add(player2Frame);
	h3.add(player3Frame);
	h3.add(player4Frame);

	player1Frame.set_label("Player1");
	player2Frame.set_label("Player2");
	player3Frame.set_label("Player3");
	player4Frame.set_label("Player4");

	//each player's frame has a vbox
	player1Frame.add(player1VBox);
	player2Frame.add(player2VBox);
	player3Frame.add(player3VBox);
	player4Frame.add(player4VBox);

	//setting the human/computer buttons, points label and discards label
	for(int i=0;i<4;i++)
	{
		Gtk::Button* b = new Gtk::Button;
		b->set_label("Human");
		playerButtons.push_back(b);
		playerType.push_back(true);
	}
	player1VBox.add(*playerButtons[0]);
	player2VBox.add(*playerButtons[1]);
	player3VBox.add(*playerButtons[2]);
	player4VBox.add(*playerButtons[3]);

	for(int i=0;i<4;i++)
	{
		Gtk::Label* l = new Gtk::Label;
		l->set_label("0 points");
		playerPoints.push_back(l);
	}

	player1VBox.add(*playerPoints[0]);
	player2VBox.add(*playerPoints[1]);
	player3VBox.add(*playerPoints[2]);
	player4VBox.add(*playerPoints[3]);

	for(int i=0;i<4;i++)
	{
		Gtk::Label* l = new Gtk::Label;
		l->set_label("0 discards");
		playerDiscards.push_back(l);
	}

	player1VBox.add(*playerDiscards[0]);
	player2VBox.add(*playerDiscards[1]);
	player3VBox.add(*playerDiscards[2]);
	player4VBox.add(*playerDiscards[3]);

	//Setting all cards to nothing.png
	for(int i=0;i<53;i++)
	{
		deck[i]=new Gtk::Image(image_names[52]);
	}

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<13;j++)
		{
			cardRows[i]->add(*deck[(i*13)+j]);
		}
	}	

	//Setting all images in the hand to nothing.png
	for(int i=0;i<13;i++)
	{
		playerHands[i]=new Gtk::Image(image_names[52]);
	}

	for(int i=0;i<13;i++)
	{
		hand_button[i] = new Gtk::Button;
		hand_button[i]->set_image(*playerHands[i]);
	}

	for(int i=0;i<13;i++)
	{
		h4.add(*hand_button[i]);
	}

	for(int i=0;i<13;i++)
	{
		hand_button[i]->set_sensitive(false);
	}

	//intializing the number of discards to zero
	for(int i=0;i<4;i++)
	{
		playerDiscardsNumber[i]=0;
	}

	//if any of the human/computer/ragequit buttons are clicked
	playerButtons[0]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onButtonClicked ),1));
	playerButtons[1]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onButtonClicked ),2));
	playerButtons[2]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onButtonClicked ),3));
	playerButtons[3]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onButtonClicked ),4));

	//if start or end button is clicked
	start_button.signal_clicked().connect(sigc::mem_fun( *this, &MainWindow::startButtonClicked));
	end_button.signal_clicked().connect(sigc::mem_fun( *this, &MainWindow::endGameClicked));

	//if a card in the hand is selected
	hand_button[0]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),0));
	hand_button[1]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),1));
	hand_button[2]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),2));
	hand_button[3]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),3));
	hand_button[4]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),4));
	hand_button[5]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),5));
	hand_button[6]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),6));
	hand_button[7]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),7));
	hand_button[8]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),8));
	hand_button[9]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),9));
	hand_button[10]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),10));
	hand_button[11]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),11));
	hand_button[12]->signal_clicked().connect(sigc::bind(sigc::mem_fun( *this, &MainWindow::onHandClicked ),12));

	show_all_children();
}

/*
End game button clicked, delete control, set the Window to default state(winState=0), 
set all cards to point to nothing
*/
void MainWindow::endGameClicked() {	
	if(winState==0)
		return;		
	for(int i=0;i<13;i++)
	{
		hand_button[i]->set_sensitive(false);
	}			
	delete control;
	winState=0;
	for(int i=0;i<53;i++)
	{
		deck[i]->set(image_names[52]);
	}
	for(int i=0;i<13;i++)
	{
		playerHands[i]->set(image_names[52]);
	}
	for(int i=0;i<13;i++)
	{
		hand_button[i]->set_image(*playerHands[i]);
	}
	for(int i=0;i<4;i++)
	{
		playerType[i]=true;
		playerButtons[i]->set_label("Human");
		playerButtons[i]->set_sensitive(true);
		playerPoints[i]->set_label("0 points");
		playerDiscards[i]->set_label("0 discards");
	}
}


/*
Converts a number to string
*/
string NumberToString(int pNumber);

/*
If a card in the hand is clicked. Does the following:
1) If there are no legal plays, we playTurn. The card to playTurn does not matter.
	(playTurn will only return when it encounters the next human player)
2) Else, we make sure the card we selected is a legal play. if not we show a dialog box
3) Update the number of discards after calling play.
*/
void MainWindow::onHandClicked(int p) {
	if(winState==1 && p<hand.size())
	{
		myLegalPlays=subject->getCurrentLegalPlays();
		if(myLegalPlays.size()==0)
		{
			cerr<<"legal plays zero"<<endl;
			control->playTurn(hand[p]);
		}
		else
		{
			bool goodPlay=false;
			for(int i=0;i<myLegalPlays.size();i++)
			{
				if(*hand[p]==*myLegalPlays[i])
				{
					control->playTurn(hand[p]);
					goodPlay=true;
					break;
				}
			}
			if(!goodPlay)
			{
				Gtk::MessageDialog dialog(*this,"You have a valid play, you cannot discard");
				dialog.run();
			}
		}

	}
	for(int i=0;i<4;i++)
	{
		discards=subject->Contestants[i]->getDiscards();
		playerDiscardsNumber[i]=discards.size();
		std::string s=NumberToString(playerDiscardsNumber[i]);
		s+=" discards";
		playerDiscards[i]->set_label(s);
	}
}

/*
If the set human/computer button is clicked while the Window is in opening state (state 0),
we change label and player type
If the window is in state zero, we call ragequit function
*/
void MainWindow::onButtonClicked(int p)
{
	if(winState==0)
	{
		if(playerType[p-1])
		{
			this->playerButtons[p-1]->set_label("Computer");
			playerType[p-1]=false;
		}	

		else
		{
			this->playerButtons[p-1]->set_label("Human");
			playerType[p-1]=true;
		}
	}	
	else if(winState==1)
	{
		subject->playerQuits(p-1);
	}
}

/*
We setup the game. Call all the required constructors. -> Controller, Game, Table, Player
We find the first player and output a dialog box
We initially call playturn with a dummy card
*/
void MainWindow::startButtonClicked()
{	
	for(int i=0;i<13;i++)
	{
		hand_button[i]->set_sensitive(true);
	}
	winState=1;									//Since game has started, we change the state of the window
	for(int i=0;i<4;i++)
	{
		playerButtons[i]->set_label("Ragequit");
		playerPoints[i]->set_label("0 points");
	}

	control = new Controller();

	string s = seed_entry.get_text();
	int seed = atoi(s.c_str());

	subject=control->setupGame(playerType,seed,this);

	curr_player=subject->getCurrentPlayer();

	Gtk::MessageDialog dialog(*this," A new round begins. Player " + NumberToString(curr_player+1) + " 's turn to play");
	dialog.run();

	control->playTurn(dummyCard);
	return;
}

/*
State 0 - A new round has just begun
State 1 - Get the current player's hand
State 2 - Update the deck
State 3 - End of round - Show points and discards in a dialog
State -3 - End of Game - Print Winner. Reset everything in the Window
State -1 - Everything has been clearer, and we are ready to start a new round
State -2 - Print Winner
*/
void MainWindow::update() {
	int state=subject->getState();
	if(state==0)				
	{
		int cP= subject->getCurrentPlayer();
		Gtk::MessageDialog dialog(*this," A new round begins. Player " + NumberToString(cP+1) + " 's turn to play");
		dialog.run();
	}
	else if(state==1)
	{
		hand=subject->getCurrentPlayerHand();
		vector<Card*> lP=subject->Contestants[subject->getCurrentPlayer()]->getLegalPlays();
		curr_player=subject->getCurrentPlayer();
		Suit suitArray[4] = {CLUB,DIAMOND,HEART,SPADE};
		Suit s;
		Rank r;
		int i;
		int i_s,i_r;
		for(i=0;i<(int)hand.size();i++)
		{
			s=hand[i]->getSuit();
			r=hand[i]->getRank();
			i_s,i_r;
			for(int j=0;j<4;j++)
			{
				if(suitArray[j]==s)
				{
					i_s=j;
					break;
				}
			}
			i_r=convertRank(r);
			playerHands[i]->set(image_names[((i_s*13)+i_r)-1]);
			hand_button[i]->set_image(*playerHands[i]);
		}
		for(;i<13;i++)
    	{
    		playerHands[i]->set(image_names[52]);
    		hand_button[i]->set_image(*playerHands[i]);
    		hand_button[i]->set_sensitive(false);
    	}
    	for(int i=0;i<4;i++)
    	{
    		if(i==subject->getCurrentPlayer())
    			playerButtons[i]->set_sensitive(true);	
    		else
    			playerButtons[i]->set_sensitive(false);
    	}
    	if(lP.size()!=0)
    	{
    		for(int i=0;i<hand.size();i++)
    		{
    			hand_button[i]->set_sensitive(false);
    			for(int j=0;j<lP.size();j++)
    			{
    				if(*hand[i]==*lP[j])
    				{
    					hand_button[i]->set_sensitive(true);
    					break;
    				}
    			}
    		}
    	}
    	if(lP.size()==0)
    	{
    		for(int i=0;i<hand.size();i++)
    			hand_button[i]->set_sensitive(true);
    	}


    	show_all_children();
	}
	else if(state==2)
	{
		table    = subject->getTable();
		Clubs    = table->getClubs();
		Diamonds = table->getDiamonds();
		Hearts   = table->getHearts();
		Spades   = table->getSpades();
		for(int j=0;j<Clubs.size();j++)
		{
			int i_r=convertRank(Clubs[j]->getRank());
			deck[i_r-1]->set(image_names[i_r-1]);
		}
		for(int j=0;j<Diamonds.size();j++)
		{
			int i_r=convertRank(Diamonds[j]->getRank());
			deck[13+i_r-1]->set(image_names[13+i_r-1]);
		}
		for(int j=0;j<Hearts.size();j++)
		{
			int i_r=convertRank(Hearts[j]->getRank());
			deck[26+i_r-1]->set(image_names[26+i_r-1]);
		}
		for(int j=0;j<Spades.size();j++)
		{
			int i_r=convertRank(Spades[j]->getRank());
			deck[39+i_r-1]->set(image_names[39+i_r-1]);
		}

	}
	else if(state==3)
	{
		int* playerTotalScores=subject->getScore();
		int* playerRoundScores=subject->getRoundScore();
		vector<string> s1;
		s1.resize(4);
		for(int i=0;i<4;i++)
		{
			s1[i]="Player ";
			string num=NumberToString(i+1);
			s1[i]+=num;
			s1[i]+="\'s score = ";
			num=NumberToString(playerTotalScores[i]);
			s1[i]+=num;
			s1[i]+=" + ";
			num=NumberToString(playerRoundScores[i]);
			s1[i]+=num;
			s1[i]+=" = ";
			string num1=NumberToString(playerTotalScores[i]+playerRoundScores[i]);
			s1[i]+=num1;
			playerPoints[i]->set_label(num1+" points");

		}

		for(int i=0;i<4;i++)
		{
			playerDiscards[i]->set_label("0 discards");
		}
		for(int i=0;i<53;i++)
		{
			deck[i]->set(image_names[52]);
		}
		for(int i=0;i<13;i++)
		{
			playerHands[i]->set(image_names[52]);
			hand_button[i]->set_image(*playerHands[i]);
		}

	}
	else if (state==-3)
	{
		ostringstream s;
		int* totalScore;
		totalScore=subject->getScore();
		int* roundScore;
		roundScore=subject->getRoundScore();
		for(int i=0;i<4;i++)
		{
			vector<Card*> h=subject->Contestants[i]->getDiscards();
			s<<"Player " + NumberToString(i+1) + "'s discards :";
			for(int j=0;j<h.size();j++)
				s<<" "<<*h[j];
			s<<endl;
			s<<"Player " + NumberToString(i+1) + "'s score :";
			s<<NumberToString(totalScore[i])<<" + "<<NumberToString(roundScore[i])<<" = ";
			s<<NumberToString(totalScore[i]+roundScore[i])<<endl;
		}
		Gtk::MessageDialog dialog(*this,s.str());
		dialog.run();
	}
	else if (state==-1)
		control->playTurn(dummyCard);
	else if(state==-2)
	{
		for(int i=0;i<13;i++)
		{
			hand_button[i]->set_sensitive(false);
		}
		vector<int> w=subject->getWinners();
		ostringstream s;
		for(int i=0;i<w.size();i++)
		{
			s<<"Player "<<NumberToString(w[i])<<" wins"<<endl;
		}
		Gtk::MessageDialog dialog(*this,s.str());
		dialog.run();
	}
}

/*
Self explanatory
*/
string NumberToString(int pNumber)
{
 ostringstream oOStrStream;
 oOStrStream << pNumber;
 return oOStrStream.str();
}