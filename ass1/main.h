struct gameDetails {
        bool gameOver; // game ends iff gameOver = true
        int* playerType; // whether player is a human or ai.
        int playerTurn; // 0 = player one's turn, player two's turn otherwise
    };

    struct boardDetails {
        char*** board; // 2d array of strings containing all the cards placed.
        int width; // the width of the board
        int height; // the height of the board
    };

    struct cardDetails {
        char*** playerCards; // holds both player's deck
        char** deck; // array containg all cards in the game 
        char* deckFile; // the path of the deck file being used
        int numberOfCards; // number of cards in the deck
        int cardsDealt; // the number of cards dealt so far
    };