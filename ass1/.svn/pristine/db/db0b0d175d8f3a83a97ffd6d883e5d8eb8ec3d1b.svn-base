#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// declaring structs

typedef struct GameDetails {
    bool gameOver; // game ends iff gameOver = true
    int* playerType; // whether player is a human or ai.
    int playerTurn; // 0 = player one's turn, player two's turn otherwise
    int* move; // [0] is the card, [1] is the column [2] is row
} GameDetails;

typedef struct BoardDetails {
    int width; // the width of the board
    int height; // the height of the board
    char*** board; // 2d array of strings containing all the cards placed.
} BoardDetails;

typedef struct CardDetails {
    char* saveName;
    char* deckName; // the path of the deck file being used
    int numberOfCards; // number of cards in the deck
    char** deck; // array containg all cards in the game
    int cardsDealt; // the number of cards dealt so far
    char*** playerCards; // holds both player's deck
    char*** possiblePlayerCards; // holds the two decks of each player
    int playerOneDealt; // number of cards player 1 has been dealt
    int playerTwoDealt; // number of cards player 2 has been dealt.
} CardDetails;