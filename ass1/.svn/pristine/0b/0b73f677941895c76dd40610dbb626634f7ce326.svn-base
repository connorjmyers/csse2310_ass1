/**
 * main.c
 * Author: Connor Myers, s4532397
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fileio.h"
#include "data.h"

// initialiser functions
char*** initialise_board(int width, int height);
void load_initial_values(BoardDetails* board,
        CardDetails* cards, char** argv, int argc);
char*** deal_cards(GameDetails* game, CardDetails* board, int argc);

// input functions 
void input(GameDetails* game, BoardDetails* board, CardDetails* card);
int* move_input();
void move_prompt(GameDetails* game, BoardDetails* board, CardDetails* card);
void ai_move_prompt(GameDetails* game, BoardDetails* board, CardDetails* card);
void ai_move_logic(GameDetails* game, BoardDetails* board, CardDetails* card);
int check_move(GameDetails* game, BoardDetails* board, CardDetails* card);

// logic functions
void logic(GameDetails* game, BoardDetails* board, CardDetails* card);
void place_card(GameDetails* game, BoardDetails* board, CardDetails* card);
void deal_card(GameDetails* game, CardDetails* card);
int check_adjacent(GameDetails* game,
        BoardDetails* board, CardDetails* card, int i, int j);

// display functions
void display(BoardDetails* board);
void draw_board(BoardDetails* board);

// utility functions
int get_num_cards(char** deck);
void count_dealt(CardDetails* cards);
void move_cards(GameDetails* game, CardDetails* card);
void allocate_possible_cards(CardDetails* cards);
void get_deck_file(CardDetails* card, char** argv, int argc);
void check_full_board(BoardDetails* board);
void check_full_game_board(BoardDetails* board, GameDetails* game);
int get_player_turn(int argc, char** argv);
char*** deal_saved_cards(CardDetails* cards, char*** playerCards);

int main(int argc, char** argv) {

    // checking users input
    check_args(argv, argc);
    
    // declaring structs
    struct GameDetails gameDetails;
    struct BoardDetails boardDetails;
    struct CardDetails cardDetails;

    // initialising variables/mallocing variables
    check_args(argv, argc);
    gameDetails.gameOver = false; 
    gameDetails.playerType = get_player_types(argv, argc);
    gameDetails.playerTurn = get_player_turn(argc, argv);
    gameDetails.move = malloc(sizeof(int) * 3); // don't free
    boardDetails.width = (get_dimensions(argv, argc))[0];
    boardDetails.height = (get_dimensions(argv, argc))[1];
    boardDetails.board = initialise_board(boardDetails.width,                
            boardDetails.height);
    get_deck_file(&cardDetails, argv, argc);
    cardDetails.numberOfCards = get_card_number(cardDetails.deckName);
    cardDetails.playerOneDealt = 0;
    cardDetails.playerTwoDealt = 0;
    cardDetails.deck = get_deck(cardDetails.deckName, 
            cardDetails.numberOfCards, argc);
    cardDetails.cardsDealt = 0;
    allocate_possible_cards(&cardDetails);
    cardDetails.playerCards = deal_cards(&gameDetails, &cardDetails, argc);
    load_initial_values(&boardDetails, &cardDetails, argv, argc);
    check_full_board(&boardDetails);

    // main game loop
    while (!gameDetails.gameOver) {
        display(&boardDetails);
        input(&gameDetails, &boardDetails, &cardDetails);
        logic(&gameDetails, &boardDetails, &cardDetails);
    }
}

/**
 * Input functions
 */

/**
 * Organises what next move will be. Human player inputs data, AI's move  *
 * decided here also.
 */
void input(GameDetails* game, BoardDetails* board, CardDetails* card) {

    // if the current player is human.
    if (game->playerType[game->playerTurn] == 0) {
        move_prompt(game, board, card);
    } else {
        ai_move_prompt(game, board, card);
        //exit(9); // for testing, segfaults if left to keep runnign
        // move = ai_move();
        // a lot of your segfaults are caused by this!
    }    
}

/**
 * Prompts human player to enter a move
 */
void move_prompt(GameDetails* game, BoardDetails* board, CardDetails* card) {

    int validMove = 1;
    int numCards = get_num_cards(card->playerCards[game->playerTurn]);

    printf("Hand(%d):", game->playerTurn + 1);

    for (int i = 0; i <= numCards; i++) { 
        printf(" %s", (card->playerCards[game->playerTurn][i]));
    }

    do {
        printf("\nMove? "); // formatting
        game->move = move_input();
        validMove = check_move(game, board, card);
    } while(!validMove);
}

/**
 * Displays the message to terminal when an ai is making a move. 
*/
void ai_move_prompt(GameDetails* game,
        BoardDetails* board, CardDetails* card) {

    int numCards = get_num_cards(card->playerCards[game->playerTurn]);
    
    printf("Hand(%d): ", game->playerTurn + 1);

    for (int i = 0; i <= numCards; i++) { 
        printf(" %s ", (card->playerCards[game->playerTurn][i]));
    }
    printf("\n");

    ai_move_logic(game, board, card);
    move_cards(game, card);
}

// not working properly
void ai_move_logic(GameDetails* game, BoardDetails* board, CardDetails* card) {

    bool cardFound = false;
    int i, j;
    for (i = 0; i < board->height; i++) {
        for (j = 0; j < board->width; j++) {
            if (strcmp(board->board[i][j], "..") != 0) {
                cardFound = true;
                break;
            }
        }
        if (cardFound) {
            break;
        }
    }

    if (!cardFound) {
        int y = (i / 2) - 1;
        int x = (j / 2) - 1;
        board->board[y][x] = card->playerCards[game->playerTurn][0];
        printf("Player %d plays %s in column %d row %d\n",
                game->playerTurn + 1,
                card->playerCards[game->playerTurn][0], x + 1, y + 1);
        game->move[0] = 1;
    } else {
        if (i == 0) {
            i = board->height - 1;
        } else if (j == 0) {
            j = board->width - 1;
        } else {
            check_adjacent(game, board, card, i, j);
        }
    }
}

/**
 * Checking if any adjacent cards are nearby. Return 1 if there are, 0
 * otherwise. 
*/
int check_adjacent(GameDetails* game,
        BoardDetails* board, CardDetails* card, int i, int j) {
    // to do
    return 0;    
}

/**
 * Handles a human player entering their move into the terminal.
 * Returns array with the cardnumber in the first index.
 * Column in the second. And, row in the third.
 * Please remember to free the memory <3
 */
int* move_input() {

    int* move = malloc(sizeof(int) * 3); // freed
    char input[80]; // enough 

    // use fgets instead?
    if (fgets(input, 80, stdin) == NULL) {
        exit_seven();
    }

    // doesn't work all the time, but it will do for now.
    move[0] = (int)(input[0] - '0');
    move[1] = (int)(input[2] - '0');
    move[2] = (int)(input[4] - '0');

    return move;
}

/**
 * Checks if a move is legal.
 */
int check_move(GameDetails* game, BoardDetails* board, CardDetails* card) {

    int cardNumber = game->move[0];
    int column = game->move[1];
    int row = game->move[2];

    if (column > board->width || row > board->height) {
        return 0;          
    } 

    if (strcmp(board->board[row - 1][column - 1], "..") != 0) {
        return 0;
    }

    if (cardNumber > get_num_cards(card->playerCards[game->playerTurn]) + 1) {
        return 0;
    }

    return 1;
}

/**
 * Logic functions
 */

/**
 * Tracks the score, checks for invalid placement and reshifts cards in deck.
 */
void logic(GameDetails* game, BoardDetails* board, CardDetails* card) {

    // if the current player is human.
    if (game->playerType[game->playerTurn] == 0) {
        place_card(game, board, card);
        free(game->move);
    } else {

    } 
    game->playerTurn = game->playerTurn ^ 1;
    // put valid move onto board
    
    bool full = true;
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            if (strcmp(board->board[i][j], "..") == 0) {
                full = false;
            }
        }
    }

    if (full) {
        game->gameOver = true;
    }
}

/**
 * Places a card onto the board
 */
void place_card(GameDetails* game, BoardDetails* board, CardDetails* card) {

    int cardNumber = game->move[0];
    int column = game->move[1];
    int row = game->move[2];

    char* cardName = card->playerCards[game->playerTurn][cardNumber - 1];
    board->board[row - 1][column - 1] = cardName;
    check_full_game_board(board, game);
    move_cards(game, card);
}

/**
 * Display functions
 */

/**
 * Refreshes the board display and
 */
void display(BoardDetails* board) {
    draw_board(board);
}

/*
 * Displays the board in the terminal
 */
void draw_board(BoardDetails* board) {

    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            printf("%s", board->board[i][j]);
        }
        printf("\n");
    }
}

/**
 * Initialiser functions
 */

/**
 * Deals the initial five cards to each player at the start of the game
 */
char*** deal_cards(GameDetails* game, CardDetails* cards, int argc) {

    // holds both player's decks. [0] for player1, [1] for player2
    char*** playerCards = malloc(sizeof(char**) * 2); // don't free.
    
    // 6 cards per deck + "ED" terminator.
    playerCards[0] = (char**) malloc(sizeof(char*) * 7); // don't free.
    playerCards[1] = (char**) malloc(sizeof(char*) * 7); // don't free.


    for (int i = 0; i < 7; i++) {
        
        playerCards[0][i] = (char*) malloc(sizeof(char) * 3);
        playerCards[1][i] = (char*) malloc(sizeof(char) * 3);
    }

    if (argc == 4) {
        return deal_saved_cards(cards, playerCards);
    }

    for (int i = 0; i < 5; i++) {
    
        playerCards[0][i] = cards->deck[cards->cardsDealt + 1];
        count_dealt(cards);
    }

    for (int i = 0; i < 5; i++) {
    
        playerCards[1][i] = cards->deck[cards->cardsDealt + 1];
        count_dealt(cards);
    }

    char* terminator = malloc(sizeof(char) * 3);
    strcpy(terminator, "ED");
    playerCards[0][5] = cards->deck[cards->cardsDealt + 1]; //sixth card
    count_dealt(cards);
    playerCards[1][5] = cards->deck[cards->cardsDealt + 1];
    count_dealt(cards); // not working?
    playerCards[0][6] = terminator;
    playerCards[1][6] = terminator;

    return playerCards;
}

/**
 * Mallocs the memory required for the 3d board
 */
char*** initialise_board(int width, int height) {

    char*** board = (char***) malloc(sizeof(char**) * height); 

    for (int i = 0; i < height; i++) {
        board[i] = (char**) malloc(sizeof(char*) * width);
        for (int j = 0; j < width; j++) {
            // 2 chars per card in the deck, and 1 more for terminator (/0)
            board[i][j] = (char*) malloc(sizeof(char) * 3);
        }
    }
    return board;
}

/*
 * Loads initial card values onto the board
 */
void load_initial_values(BoardDetails* board,
        CardDetails* cards, char** argv, int argc) {

    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            board->board[i][j] = "..";
        }
    } 
    
    if (argc == 4) {

        // get board values from savefile

    }
}
/**
 * Utility Functions
 */

/**
 * Returns the number of cards in a players deck
 */
int get_num_cards(char** deck) {

    int counter = 0;

    while (strcmp(deck[counter], "ED") != 0) {
        counter++;
    }

    return counter - 1;
}

/**
 * Adds to the count of cards dealt
 */
void count_dealt(CardDetails* cards) {

    cards->cardsDealt = cards->cardsDealt + 1;
}

/**
 * Deals the next appropriate card from the deck to the player.
 */
void deal_card(GameDetails* game, CardDetails* card) {

    char* nextCard = malloc(sizeof(char) * 3);
    int numCards = get_num_cards(card->playerCards[game->playerTurn]);
    char* terminator = malloc(sizeof(char) * 3);
    strcpy(terminator, "ED");

    // find new card.
    strcpy(nextCard, card->deck[card->cardsDealt]);
    //strcpy(nextCard, "ye"); // fix this!!
    // right now, terminator is at numCards, right?
    card->playerCards[game->playerTurn][numCards] = nextCard;
    card->playerCards[game->playerTurn][numCards + 1] = terminator;
    count_dealt(card);
}

/**
 * Shifts card in deck when a card is placed.
*/
void move_cards(GameDetails* game, CardDetails* card) {

    char* terminator = malloc(sizeof(char) * 3);
    strcpy(terminator, "ED");
    int numCards = get_num_cards(card->playerCards[game->playerTurn]);

    for (int i = (game->move[0] - 1); i < numCards; i++) {
        card->playerCards[game->playerTurn][i] =
                card->playerCards[game->playerTurn][i + 1];     
    }

    card->playerCards[game->playerTurn][numCards] = terminator;
}

/**
 * Allocates memory for possible cards variable
 */
void allocate_possible_cards(CardDetails* cards) {

    cards->possiblePlayerCards = malloc(sizeof(char**) * 2); // 2 players
    
    for (int i = 0; i < 2; i++) {
        cards->possiblePlayerCards[i] = 
                malloc(sizeof(char*) * cards->numberOfCards);
        for (int j = 0; j < cards->numberOfCards; j++) {
            cards->possiblePlayerCards[i][j] = malloc(sizeof(char) * 3);
        }
    }
}

/**
 * Extracts the deckFile name from args
 */
void get_deck_file(CardDetails* card, char** argv, int argc) {

    if (argc == 6) {
        card->deckName = argv[1];
    } else {
        card->saveName = argv[1];
        FILE* saveFile = fopen(argv[1], "r");
        char* ignore = malloc(sizeof(char) * 80); // enough
        char* deckName = malloc(sizeof(char) * 80); // enough
        if (saveFile == NULL) {
            exit_four();
        }

        // skipping the first line
        fgets(ignore, 80, saveFile);
        free(ignore); // we don't care about this.
        fgets(deckName, 80, saveFile);
        
        // for some reason if it ends in '/' it doesn't get the \n at the end?
        if (deckName[strlen(deckName) - 2] == '/') {
            exit_three();
        }

        deckName[strcspn(deckName, "\n")] = '\0'; 
        card->deckName = deckName;
        fclose(saveFile);
    }
}

/**
 * Checks if the board is full
 */
void check_full_board(BoardDetails* board) {

    bool full = true;
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            if (strcmp(board->board[i][j], "..") == 0) {
                full = false;
            }
        }
    }

    if (full) {
        exit_six();
    }
}

/**
 * Checks if the board is full for a game in progress
 */
void check_full_game_board(BoardDetails* board, GameDetails* game) {

    bool full = true;
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            if (strcmp(board->board[i][j], "..") == 0) {
                full = false;
            }
        }
    }

    if (full) {
        game->gameOver = true;
        exit(0);
    }
}

/**
 * Gets player turn from savefile.
*/
int get_player_turn(int argc, char** argv) {

    if (argc == 6) {
        return 0;
    }

    if (argc == 4) {
        FILE* saveFile = fopen(argv[1], "r");
        if (saveFile == NULL) {
            exit_four();
        }

        char* buffer = malloc(sizeof(char) * 80);
        fgets(buffer, 80, saveFile);
        buffer[strcspn(buffer, "\n")] = '\0';

        fclose(saveFile);
        return ((int)(buffer[strlen(buffer) - 1] - '0') - 1);
    }

    return 0;
}

/**
 * Deals cards saved in savefile. 
*/
char*** deal_saved_cards(CardDetails* cards, char*** playerCards) {

    FILE* saveFile = fopen(cards->saveName, "r");

    if (saveFile == NULL) {
        exit_four();
    }

    char* buffer = malloc(sizeof(char) * 80);
    fgets(buffer, 80, saveFile);
    fgets(buffer, 80, saveFile);

    // we don't care about first two lines.
    fgets(buffer, 80, saveFile);
    buffer[strcspn(buffer, "\n")] = '\0'; 

    int playerOneCards = (strlen(buffer) / 2);
    for (int i = 0; i < strlen(buffer); i = i + 2) {
        char* card = malloc(sizeof(char) * 3);
        card[0] = buffer[i];
        card[1] = buffer[i + 1];
        card[2] = '\0';
        playerCards[0][i / 2] = card;
    }

    fgets(buffer, 80, saveFile);
    buffer[strcspn(buffer, "\n")] = '\0'; 
    int playerTwoCards = (strlen(buffer) / 2);
    for (int i = 0; i < strlen(buffer); i = i + 2) {
        char* card = malloc(sizeof(char) * 3);
        card[0] = buffer[i];
        card[1] = buffer[i + 1];
        card[2] = '\0';
        playerCards[1][i / 2] = card;
    }

    char* terminator = malloc(sizeof(char) * 3);
    strcpy(terminator, "ED");
    playerCards[0][playerOneCards] = terminator;
    playerCards[1][playerTwoCards] = terminator;

    cards->cardsDealt = (playerOneCards + playerTwoCards);
    return playerCards;
}