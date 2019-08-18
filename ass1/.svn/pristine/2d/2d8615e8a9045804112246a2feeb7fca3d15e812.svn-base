/**
 * fileio.c
 * Author: Connor Myers, s4532397
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"


// check formatting functions
void check_args(char** argv, int argc);
void check_move(int* move, BoardDetails* board);

// getter functions
int* get_player_types(char** argv, int argc);
int* get_dimensions(char** argv, int argc);
int get_card_number(char* deckName);
char** get_deck(char* deckName, int numberOfCards, int argc);
int* get_saved_dimensions(char** argv, int argc);

// exit functions
void exit_one();
void exit_two();
void exit_three();
void exit_four();
void exit_five();
void exit_six();
void exit_seven();

/**
 * Checks that arguments are correctly formatted.
 * Exits program if not correct with exit status 1
 */
void check_args(char** argv, int argc) {

    // can't possibly be valid if they don't have either 4 or 6 inputs
    if (argc != 4 && argc != 6) {
        exit_one();
    } 
}

/**
 * Returns number of cards in a deck
 */
int get_card_number(char* deckName) {

    int position = 0;
    char* cardNumber = malloc(sizeof(char) * 10);

    FILE* deckFile = fopen(deckName, "r"); // fixed

    if (deckFile == NULL) {
        exit_three();
    }

    int result = 0;
    while (1) {
        result = fgetc(deckFile);

        if (((char)result == '\n') || ((char)result == EOF)) {
            break;
        } else {
            cardNumber[position] = (char) result;
            position++;
        }
    }
    cardNumber[position] = '\0';
    fclose(deckFile);
    return atoi(cardNumber);
}

/**
 * Returns char** containing all the cards in the deckName.deck file
 */
char** get_deck(char* deckName, int numberOfCards, int argc) {

    char** deck = malloc(sizeof(char*) * (numberOfCards));

    FILE* deckFile = fopen(deckName, "r");
    int result;

    if (deckFile == NULL) {
        exit_three();
    }

    for (int i = 0; i <= numberOfCards; i++) {

        int position = 0;
        char* card = malloc(sizeof(char) * 3);

        while (1) {
            if (((result = fgetc(deckFile)) == '\n') || (result == EOF)) {
                card[2] = '\0';
                break;
            }
            card[position] = (char)result;
            position++;
        }

        deck[i] = card;
    }

    //fclose(deckFile); 
    return deck;    
}

/**
 * Extracts the player types from args
 */
int* get_player_types(char** argv, int argc) {

    int* playerTypes = malloc(sizeof(int) * 2);

    if (argc == 6) {
        for (int i = 0; i < 2; i++) {
            if (strcmp(argv[4 + i], "h") == 0) { 
                playerTypes[i] = 0;
            } else if (strcmp(argv[4 + i], "a") == 0) {
                playerTypes[i] = 1;
            } else {
                exit_two();
            }
        }
    } else {
        for (int i = 0; i < 2; i++) {
            if (strcmp(argv[2 + i], "h") == 0) { 
                playerTypes[i] = 0;
            } else if (strcmp(argv[2 + i], "a") == 0) {
                playerTypes[i] = 1;
            } else {
                exit_two();
            }
        }
    }
    return playerTypes;
}

/**
 * Extracts dimensions of board from args
 */
int* get_dimensions(char** argv, int argc) {

    int* dimensions = malloc(sizeof(int) * 2);
  
    if (argc == 6) {

        if (((atoi(argv[2]) < 3) || (atoi(argv[2]) > 100)) 
                || ((atoi(argv[3]) < 3) || (atoi(argv[3]) > 100))) {
            exit_two();
        } else {
            dimensions[0] = atoi(argv[2]);
            dimensions[1] = atoi(argv[3]);
        }
        
    } else {
        dimensions = get_saved_dimensions(argv, argc);       
    }
    return dimensions;
}

/**
 * Gets dimensions of board from savefile.
*/
int* get_saved_dimensions(char** argv, int argc) {

    int* dimensions = malloc(sizeof(int) * 2);

    char* saveName = argv[1];
    FILE* saveFile = fopen(saveName, "r");

    if (saveFile == NULL) {
        exit_four();
    }

    char* ignore = malloc(sizeof(char) * 80);
    fgets(ignore, 80, saveFile);
    fgets(ignore, 80, saveFile);
    fgets(ignore, 80, saveFile);
    fgets(ignore, 80, saveFile);
    
    //
    char* width = malloc(sizeof(char) * 80);
    fgets(width, 80, saveFile);
    width[strcspn(width, "\n")] = '\0'; 

    int height = 0;
    while (1) {
        if (fgets(ignore, 80, saveFile) == NULL) {
            height++;
            break;
        }
        height++;
    }

    dimensions[0] = strlen(width) / 2;
    dimensions[1] = height;

    free(ignore);
    free(width);
    fclose(saveFile);

    return dimensions;
}

/**
 * Exit functions
 */

/**
 * Exits program with exit status 1 and sends error message to stderr
 */
void exit_one() {
    fprintf(stderr, "Usage: bark savefile p1type p2type\nbark deck width height p1type p2type\n");
    exit(1);
}

/**
 * Exits program with exit status 2 and sends error message to stderr
 */
void exit_two() {
    fprintf(stderr, "Incorrect arg types\n");
    exit(2);
}

/**
 * Exits program with exit status 3 and sends error message to stderr
 */
void exit_three() {
    fprintf(stderr, "Unable to parse deckfile\n");
    exit(3);
}

/**
 * Exits program with exit status 4 and sends error message to stderr
 */
void exit_four() {
    fprintf(stderr, "Unable to parse savefile\n");
    exit(4);
}

/**
 * Exits program with exit status 5 and sends error message to stderr
 */
void exit_five() {
    fprintf(stderr, "Short deck\n");
    exit(5);
}

/**
 * Exits program with exit status 6 and sends error message to stderr
 */
void exit_six() {
    fprintf(stderr, "Board full\n");
    exit(6);
}

/**
 * Exits program with exit status 6 and sends error message to stderr
 */
void exit_seven() {
    fprintf(stderr, "End of input\n");
    exit(7);
}
