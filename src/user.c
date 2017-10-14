#include "user.h"

char *get_user(char *user) {
    char buffer[256];
    printf("User: ");
    fgets(buffer, sizeof(buffer), stdin);

    strncpy(user, buffer, strlen(buffer) - 1);

    return user;
}

FILE *open_user_profile(char user[]) {
    char filename[256];
    sprintf(filename, "../users/%s.txt", user);
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