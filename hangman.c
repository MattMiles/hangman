#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hangman.h"

int main(void) {
    // collect the user's name
    char user[256];
    get_user(user);

    // open user's profile
    FILE *user_profile = open_user_profile(user);

    // load user data into memory
    if (user_profile != NULL) {
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

        printf("%s", difficulty);
        printf("%u", won_in_a_row);
    }

    display_user_profile(user);
}

char *get_user(char *user) {
    char buffer[256];
    printf("User: ");
    fgets(buffer, sizeof(buffer), stdin);

    // get rid of the trailing null character
    for (int i = 0; i < strlen(buffer) - 1; i++) {
        user[i] = buffer[i];
    }

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
    printf("Easy mode: (%u/%u/%.2f)\n", easy_wins, easy_losses, (float) easy_wins / easy_losses);
    printf("Medium mode: (%u/%u/%.2f)\n", medium_wins, medium_losses, (float) medium_wins / medium_losses);
    printf("Hard mode: (%u/%u/%.2f)\n", hard_wins, hard_losses, (float) hard_wins / hard_losses);
    printf("Current difficulty: %s\n", difficulty);
    if (strcmp(difficulty, "easy") == 0 || strcmp(difficulty, "medium") == 0) {
        printf("You have to win %u more games to advance to the next difficulty.\n", 3 - won_in_a_row);
    }
    else {
        printf("You are currently at the highest difficulty.\n");
    }
}