#include "Table.h"
#include<iostream>

using namespace std;

void shuffle(vector <Card*>& cards_){
    const int CARD_COUNT = 52;
	int n = CARD_COUNT;
    
	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
        Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}


void Table::clearTable()						//Clears table and initializes a new LegalPlays vector with 7S only
{
    int s=LegalPlays.size();
    for(int i=0;i<s;i++)
        LegalPlays.pop_back();
    s=Clubs.size();
    for(int i=0;i<s;i++)
        Clubs.pop_back();
    s=Diamonds.size();
    for(int i=0;i<s;i++)
        Diamonds.pop_back();
    s=Hearts.size();
    for(int i=0;i<s;i++)
        Hearts.pop_back();
    s=Spades.size();
    for(int i=0;i<s;i++)
        Spades.pop_back();
    LegalPlays.resize(8);
    LegalPlays[6]=OGDeck[45];
    LegalPlays[7]=OGDeck[45];
}


Table::Table()									//Initializes pointers to cards, shuffles deck

{
    LegalPlays.resize(8);
    Suit suitArray[4] = {CLUB,DIAMOND,HEART,SPADE};
    Rank rankArray[13] = {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
    for(int s=0; s<4 ; s++)
    {
        for(int r = 0; r<13; r++)
        {
            Card* c = new Card(suitArray[s],rankArray[r]);
            if(c->getRank()==SEVEN && c->getSuit()==SPADE)
            {
                LegalPlays[6]=c;
                LegalPlays[7]=c;
            }
            Deck.push_back (c);
            OGDeck.push_back(c);
        }
    }
    shuffle(Deck);
}





void Table::updateTable(Card* c)					//Setter - updates the four suit vectors and legalPlays vector
{
    Suit c_s=c->getSuit();
    Rank c_r=c->getRank();
    int compareRank=convertRank(c_r);
    if(c_s==CLUB)
    {
        if(Clubs.size()==0)
        {
            Clubs.push_back(c);
            LegalPlays[0]=OGDeck[5];
            LegalPlays[1]=OGDeck[7];
        }
        else
        {
            Card* suitCard=Clubs[0];
            if(suitCard->getRank()<c_r)
            {
                Clubs.push_back(c);
                if(compareRank!=13)
                {
                    LegalPlays[1]=OGDeck[compareRank];
                }
            }
            else
            {
                Clubs.push_back(c);
                for(int i=(int)Clubs.size()-1;i>0;i--)
                {
                    Card* temp=Clubs[i];
                    Clubs[i]=Clubs[i-1];
                    Clubs[i-1]=temp;
                }
                if(compareRank!=1)
                {
                    LegalPlays[0]=OGDeck[compareRank-2];
                }
            }
        }
    }
    if(c_s==DIAMOND)
    {
        if(Diamonds.size()==0)
        {
            Diamonds.push_back(c);
            LegalPlays[2]=OGDeck[18];
            LegalPlays[3]=OGDeck[20];
        }
        else
        {
            Card* suitCard=Diamonds[0];
            if(suitCard->getRank()<c_r)
            {
                Diamonds.push_back(c);
                if(compareRank!=13)
                {
                    LegalPlays[3]=OGDeck[12+compareRank+1];
                }
            }
            else
            {
                Diamonds.push_back(c);
                for(int i=(int)Diamonds.size()-1;i>0;i--)
                {
                    Card* temp=Diamonds[i];
                    Diamonds[i]=Diamonds[i-1];
                    Diamonds[i-1]=temp;
                }
                if(compareRank!=1)
                {
                    LegalPlays[2]=OGDeck[12+compareRank-1];
                }
            }
        }
    }
    if(c_s==HEART)
    {
        if(Hearts.size()==0)
        {
            Hearts.push_back(c);
            LegalPlays[4]=OGDeck[31];
            LegalPlays[5]=OGDeck[33];
        }
        else
        {
            Card* suitCard=Hearts[0];
            if(suitCard->getRank()<c_r)
            {
                Hearts.push_back(c);
                if(compareRank!=13)
                {
                    LegalPlays[5]=OGDeck[25+compareRank+1];
                }
            }
            else
            {
                Hearts.push_back(c);
                for(int i=(int)Hearts.size()-1;i>0;i--)
                {
                    Card* temp=Hearts[i];
                    Hearts[i]=Hearts[i-1];
                    Hearts[i-1]=temp;
                }
                if(compareRank!=1)
                {
                    LegalPlays[4]=OGDeck[25+compareRank-1];
                }
            }
        }
    }
    if(c_s==SPADE)
    {
        
        if(Spades.size()==0)
        {
            Spades.push_back(c);
            LegalPlays[0]=OGDeck[6];
            LegalPlays[1]=OGDeck[6];
            LegalPlays[2]=OGDeck[19];
            LegalPlays[3]=OGDeck[19];
            LegalPlays[4]=OGDeck[32];
            LegalPlays[5]=OGDeck[32];
            LegalPlays[6]=OGDeck[44];
            LegalPlays[7]=OGDeck[46];
        }
        else
        {
            Card* suitCard=Spades[0];
            if(suitCard->getRank()<c_r)
            {
                Spades.push_back(c);
                if(compareRank!=13)
                {
                    LegalPlays[7]=OGDeck[38+compareRank+1];
                }
            }
            else
            {
                Spades.push_back(c);
                for(int i=(int)Spades.size()-1;i>0;i--)
                {
                    Card* temp=Spades[i];
                    Spades[i]=Spades[i-1];
                    Spades[i-1]=temp;
                }
                if(compareRank!=1)
                {
                    LegalPlays[6]=OGDeck[38+compareRank-1];
                }
            }
        }
    }
    
    
    
}

void Table::printDeck() const							//Getter - prints contents of deck
{
    for(int i = 0; i <4; i++){
        cout<<*Deck[(13*i)];
        for(int j=1;j<13;j++)
            cout<<" "<<*Deck[(13*i)+j];
        cout<<endl;
    }
    cout<<endl;
    
}

void Table::printTable() const							//Getter - prints the four suits on the table
{
    cout<<"Cards on the table: "<<endl;
    int i;
    cout<<"Clubs:";
    int n=(int) this->Clubs.size();
    for(i=0;i<n;i++)
    {
        cout<<" ";
        int cardVal=convertRank(Clubs[i]->getRank());
        if(cardVal==1)
            cout<<"A";
        else if(cardVal==11)
            cout<<"J";
        else if(cardVal==12)
            cout<<"Q";
        else if(cardVal==13)
            cout<<"K";
        else
            cout<<cardVal;
    }
    if(i=Clubs.size()==0)
        cout<<" ";
    cout<<endl;
    
    cout<<"Diamonds:";
    n=(int) this->Diamonds.size();
    for(i=0;i<n;i++)
    {
        cout<<" ";
        int cardVal=convertRank(Diamonds[i]->getRank());
        if(cardVal==1)
            cout<<"A";
        else if(cardVal==11)
            cout<<"J";
        else if(cardVal==12)
            cout<<"Q";
        else if(cardVal==13)
            cout<<"K";
        else
            cout<<cardVal;
        
    }
    if(Diamonds.size()==0)
        cout<<" ";
    cout<<endl;
    
    cout<<"Hearts:";
    n=(int) this->Hearts.size();
    for(i=0;i<n;i++)
    {
        cout<<" ";
        int cardVal=convertRank(Hearts[i]->getRank());
        if(cardVal==1)
            cout<<"A";
        else if(cardVal==11)
            cout<<"J";
        else if(cardVal==12)
            cout<<"Q";
        else if(cardVal==13)
            cout<<"K";
        else
            cout<<cardVal;
    }
    if(Hearts.size()==0)
        cout<<" ";
    cout<<endl;
    
    cout<<"Spades:";
    n=(int) this->Spades.size();
    for(i=0;i<n;i++)
    {
        cout<<" ";
        int cardVal=convertRank(Spades[i]->getRank());
        if(cardVal==1)
            cout<<"A";
        else if(cardVal==11)
            cout<<"J";
        else if(cardVal==12)
            cout<<"Q";
        else if(cardVal==13)
            cout<<"K";
        else
            cout<<cardVal;
    }
    if(Spades.size()==0)
        cout<<" ";
    cout<<endl;
}

