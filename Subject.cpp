#include "Subject.h"
#include <iostream>

void Subject::subscribe(Observer* obs)
{
	observers.push_back(obs);
}

void Subject::unsubscribe(Observer* obs)
{	
	for(int i=0;i<observers.size();i++)
	{
		if(observers[i]==obs)
		{
			Observer* temp = observers[observers.size()-1];
			observers[observers.size()-1]=observers[i];
			observers[i]=temp;
			observers.pop_back();
			break;
		}
			
	}
}

void Subject::notify() {
	int n= observers.size();
	for(int i=0;i<n;i++)
	{
		observers[i]->update();
	}
}
