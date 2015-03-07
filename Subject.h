#ifndef GTKMM__Subject__
#define GTKMM__Subject__

#include <vector>
#include "Observer.h"

class Observer;

class Subject {
	public:
		void subscribe(Observer*);
		void unsubscribe(Observer*);
	protected:
		void notify();
	private:
		std::vector<Observer*> observers;	
};

#endif