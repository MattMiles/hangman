#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

#include "user.c"
#include "hangman.c"
#include "dictionary.c"

int main(void) {
    // user data
    user player = { .username = malloc(256), .easy_wins = 0, .easy_losses = 0, .medium_wins = 0, .medium_losses = 0, .hard_wins = 0, .hard_losses = 0, .difficulty = malloc(256), .progress = 0 };

    // dictionary data
    dictionary_node *easy_root = malloc(sizeof(dictionary_node));
    dictionary_node *medium_root = malloc(sizeof(dictionary_node));
    dictionary_node *hard_root = malloc(sizeof(dictionary_node));

    FILE *dictionary = fopen("../dictionary.txt", "r");

    if (easy_root == NULL || medium_root == NULL || hard_root == NULL) {
        printf("Error: out of memory.\n");
        exit(1);
    }

    if (dictionary != NULL)
        // load dictionary into memory
        initialize_dictionary(dictionary, easy_root, medium_root, hard_root);
    else {
        printf("Error: dictionary file not found.\n");
        exit(2);
    }

    char user[256];
    // collect the user's name
    strcpy(user, get_user());
    strcpy(player.username, user);

    // open user's profile
    FILE *user_profile = open_user_profile(player.username);
    // load user data into memory
    if (user_profile != NULL)
        player = load_user_data(user_profile, player);
    else {
        strcpy(player.difficulty, "easy");
        player = update_user_profile(player);
    }

    display_user_profile(player);

    printf("Play? (y/n) ");
    char play_condition = ' ';
    scanf("\n%c", &play_condition);
    while (play_condition == 'y') {
        char *guesses = malloc(256);
        char *current_word = get_word(easy_root, medium_root, hard_root, player);
        int win = play_hangman(current_word, 0, guesses, 0);
        // if won
        if (win == 1) {
            // update user's difficulty if applicable
            if (strcmp(player.difficulty, "easy") == 0)
                player.easy_wins++;
            else if (strcmp(player.difficulty, "medium") == 0)
                player.medium_wins++;
            else
                player.hard_wins++;

        }
        // if loss
        else {
            // update user's difficulty if applicable
            if (strcmp(player.difficulty, "easy") == 0)
                player.easy_losses++;
            else if (strcmp(player.difficulty, "medium") == 0)
                player.medium_losses++;
            else
                player.hard_losses++;
        }

        // update user's file
        player = update_user_profile(player);
        display_user_profile(player);

        printf("Play again? (y/n) ");
        scanf("\n%c", &play_condition);
    }

    fclose(dictionary);
    fclose(user_profile);
}