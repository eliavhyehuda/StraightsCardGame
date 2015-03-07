CXX= g++
CXXFLAGS = -MMD -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
OBJS = UserInterface.o MainWindow.o Subject.o Observer.o Card.o Command.o Controller.o Game.o Player.o HumanPlayer.o ComputerPlayer.o Table.o
DEPENDS= $(OBJS:.o=.d)
EXEC = straights

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC)

clean:
	rm $(DEPENDS) $(EXEC) $(OBJS)

-include $(DEPENDS)


# CXX = g++
# CXXFLAGS = -MMD -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
# LOGFOLDER = logic
# LOGOBJECTS = Command.o Card.o SuitList.o Deck.o Player.o HumanPlayer.o ComputerPlayer.o
# CUROBJECTS = Straights.o MainWindow.o DeckGUI.o TableController.o
# OBJECTS = $(CUROBJECTS) $(patsubst %, $(LOGFOLDER)/%, $(LOGOBJECTS))
# DEPENDS = $(OBJECTS:.o=.d)
# EXEC = straights

# $(EXEC) : $(OBJECTS)
# 	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(EXEC)

# clean:
# 	rm -rf $(DEPENDS) $(OBJECTS) $(EXEC)
