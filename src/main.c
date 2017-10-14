#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hangman.c"
#include "dictionary.c"
#include "user.c"

int main(void) {
    char user[256];
    // collect the user's name
    get_user(user);

    // open user's profile
    FILE *user_profile = open_user_profile(user);

    // load user data into memory
    if (user_profile != NULL)
        load_user_data(user_profile);

    display_user_profile(user);

    FILE *dictionary = fopen("dictionary.txt", "r");

    dictionary_node *easy_root = malloc(sizeof(dictionary_node));
    dictionary_node *medium_root = malloc(sizeof(dictionary_node));
    dictionary_node *hard_root = malloc(sizeof(dictionary_node));

    if (easy_root == NULL || medium_root == NULL || hard_root == NULL) {
        printf("Error: out of memory.\n");
        exit(1);
    }

    if (dictionary != NULL)
        initialize_dictionary(dictionary, easy_root, medium_root, hard_root);
    else {
        printf("Error: dictionary file not found.\n");
        exit(2);
    }

    char guesses[256];
    int win = play_hangman("supercali", 0, guesses, 0);

    if (win) {
        if (strcmp(difficulty, "easy") == 0)
            easy_wins++;
        else if (strcmp(difficulty, "medium") == 0)
            medium_wins++;
        else
            hard_wins++;
    }
    else {
        if (strcmp(difficulty, "easy") == 0)
            easy_losses++;
        else if (strcmp(difficulty, "medium") == 0)
            medium_losses++;
        else
            hard_losses++;
    }
}