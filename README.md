#Straights Game

The Straights game is a four-player game. The objective of the game is to get the fewest number of points among the players. The game ends when a player gets 80 points or more, and the player with the lowers score is declared the winner.

This project has a makefile which is used the compile the code which consists of header and cpp files.

The gtkmm GUI library is used. This will allow human users to interact and play the game with other human users or computer players.

#Gameplay

The Straights game uses the standard 52-card deck. Each player is dealt 13 cards at the beginning of each round. In this game, the Ace is considered to be the lowers card in each suit, while the King is the highest.

After the cards are dealt, the player with 7 of spades goes first. This player must play the 7 of spades. After the 7 of spades, the players take turns to play cards on the table. At this point, the players much play cards that constitute legal plays. The following cards are legal:

1. 7 of any suit
2. A card with the same suit and adjacent rank as another card that has already been played

For example, if 7 of spades is the only card on the table, then the legal plays are 8 of any other suit, 8 of spades or 6 of spades. The king and ace of a suit are not considered to be adjacent ranks.

When a player has no legal plays, they must choose a card in their hand, and discard it. Note that if a player has at least one legal play in their hand, then they MUST make a legal play. They cannot discard a card in this case. The round ends when all the cards are either been played or discarded.

For each player their score for the round is the sum of all the ranks of the player’s discards. Jacks, Queens and Kings count 11, 12 and 13 points respectively.

For example if a player discarded a two, a four and a queen the his number of points would be

2 + 4 + 12 = 18

Each player’s game score is the sum of his or her scores in each round. If no player has accumulated 80 points at the end of each round, then the deck is reshuffled and another round begins.
