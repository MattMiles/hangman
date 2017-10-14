#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hangman.h"

int main(void) {
    char user[256];
    // collect the user's name
    get_user(user);

    // open user's profile
    FILE *user_profile = open_user_profile(user);

    // load user data into memory
    if (user_profile != NULL) {
        load_user_data(user_profile);
    }

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
}

char *get_user(char *user) {
    char buffer[256];
    printf("User: ");
    fgets(buffer, sizeof(buffer), stdin);

    strncpy(user, buffer, strlen(buffer) - 1);

    return user;
}

FILE *open_user_profile(char user[]) {
    char filename[256];
    sprintf(filename, "users/%s.txt", user);
    FILE *user_profile = fopen(filename, "r");
    return user_profile;
}

void display_user_profile(char *user) {
    printf("\n\n-----------------------------------\n");
    printf("User Profile: (W/L/W:LR) %s\n", user);
    printf("\tEasy mode: (%u/%u/%.2f)\n", easy_wins, easy_losses, (float) easy_wins / easy_losses);
    printf("\tMedium mode: (%u/%u/%.2f)\n", medium_wins, medium_losses, (float) medium_wins / medium_losses);
    printf("\tHard mode: (%u/%u/%.2f)\n", hard_wins, hard_losses, (float) hard_wins / hard_losses);
    printf("\tCurrent difficulty: %s\n", difficulty);
    if (strcmp(difficulty, "easy") == 0 || strcmp(difficulty, "medium") == 0) {
        unsigned int remaining = THRESHOLD - won_in_a_row;
        printf("\tYou have to win %u more", remaining);
        if (remaining == 1)
            printf(" game ");
        else
            printf(" games ");

        printf("to advance to the next difficulty.\n");
    }
    else
        printf("You are currently at the highest difficulty.\n\n");
}

void load_user_data(FILE *user_profile) {
    char buffer[1000];
    // get user's easy wins
    fgets(buffer, sizeof(buffer), user_profile);
    easy_wins = atoi(buffer);

    // get user's easy losses
    fgets(buffer, sizeof(buffer), user_profile);
    easy_losses = atoi(buffer);

    // get user's medium wins
    fgets(buffer, sizeof(buffer), user_profile);
    medium_wins = atoi(buffer);

    // get user's medium losses
    fgets(buffer, sizeof(buffer), user_profile);
    medium_losses = atoi(buffer);

    // get user's hard wins
    fgets(buffer, sizeof(buffer), user_profile);
    hard_wins = atoi(buffer);

    // get user's hard losses
    fgets(buffer, sizeof(buffer), user_profile);
    hard_losses = atoi(buffer);

    // get user's current difficulty
    fgets(buffer, sizeof(buffer), user_profile);
    strncpy(difficulty, buffer, strlen(buffer) - 1);

    // get user's current wins in a row for that difficulty
    fgets(buffer, sizeof(buffer), user_profile);
    won_in_a_row = atoi(buffer);
}

void initialize_dictionary(FILE *dictionary, dictionary_node *easy_root, dictionary_node *medium_root, dictionary_node *hard_root) {
    char buffer[256];
    dictionary_node *current_easy = easy_root;
    dictionary_node *current_medium = medium_root;
    dictionary_node *current_hard = hard_root;

    while (fgets(buffer, sizeof(buffer), dictionary) != NULL) {
        unsigned int common_letters = 1;
        unsigned int uncommon_letters = 1;

        for (int i = 0; i < strlen(buffer); i++) {
            if (is_common(buffer[i]))
                common_letters++;
            else
                uncommon_letters++;
        }

        float word_difficulty = (float) common_letters / uncommon_letters;
        if (word_difficulty >= 1) {
            current_easy->word = malloc(sizeof(buffer));
            strcpy(current_easy->word, buffer);

            current_easy->next = malloc(sizeof(dictionary_node));

            if (current_easy->word == NULL || current_easy->next == NULL) {
                printf("Error: out of memory.\n");
                exit(1);
            }
            current_easy = current_easy->next;
        }
        else if (word_difficulty >= 0.7) {
            current_medium->word = malloc(sizeof(buffer));
            strcpy(current_medium->word, buffer);

            current_medium->next = malloc(sizeof(dictionary_node));

            if (current_medium->word == NULL || current_medium->next == NULL) {
                printf("Error: out of memory.\n");
                exit(1);
            }

            current_medium = current_medium->next;
        }
        else {
            current_hard->word = malloc(sizeof(buffer));
            strcpy(current_hard->word, buffer);

            current_hard->next = malloc(sizeof(dictionary_node));

            if (current_hard->word == NULL || current_hard->next == NULL) {
                printf("Error: out of memory.\n");
                exit(1);
            }

            current_hard = current_hard->next;
        }
    }
}

int is_common(char letter) {
    // e, t, a, o, i, n, s, r, h = common letters used in the English language
    if (letter == 'e' || letter == 't' || letter == 'a' || letter == 'o' || letter == 'i' || letter == 'n' || letter == 's' || letter == 'r' || letter == 'h')
        return 1;
    else
        return 0;
}