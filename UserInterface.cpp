
#include <gtkmm.h>
#include "MainWindow.h"

using namespace std;

int main( int argc, char * argv[] ) {
	Gtk::Main  kit( argc, argv );      // Initialize gtkmm with the command line arguments, as appropriate.
	MainWindow window;                 // Create the window with the image.
	Gtk::Main::run( window );          // Show the window and return when it is closed.
	
	return 0;
} // main