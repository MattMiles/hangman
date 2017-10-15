#include "user.h"

char *get_user() {
    static char buffer[256];
    printf("User: ");
    fgets(buffer, sizeof(buffer), stdin);
    strtok(buffer, "\n");

    return buffer;
}

FILE *open_user_profile(char user[]) {
    char filename[256];
    sprintf(filename, "../users/%s.txt", user);
    FILE *user_profile = fopen(filename, "r");
    return user_profile;
}

void display_user_profile(user player) {
    printf("\n\n-----------------------------------\n");
    printf("User Profile: (W/L/W:LR) %s\n", player.username);

    // avoid division by zero
    if (player.easy_losses == 0)
        printf("\tEasy mode: (%u/%u/%u)\n", player.easy_wins, player.easy_losses, player.easy_wins);
    else
        printf("\tEasy mode: (%u/%u/%.2f)\n", player.easy_wins, player.easy_losses, (float) player.easy_wins / player.easy_losses);

    if (player.medium_losses == 0)
        printf("\tMedium mode: (%u/%u/%u)\n", player.medium_wins, player.medium_losses, player.medium_wins);
    else
        printf("\tMedium mode: (%u/%u/%.2f)\n", player.medium_wins, player.medium_losses, (float) player.medium_wins / player.medium_losses);

    if (player.hard_losses == 0)
        printf("\tHard mode: (%u/%u/%u)\n", player.hard_wins, player.hard_losses, player.hard_wins);
    else
        printf("\tHard mode: (%u/%u/%.2f)\n", player.hard_wins, player.hard_losses, (float) player.hard_wins / player.hard_losses);
    printf("\tCurrent difficulty: %s\n", player.difficulty);
    if (strcmp(player.difficulty, "easy") == 0 || strcmp(player.difficulty, "medium") == 0) {
        unsigned int remaining = THRESHOLD - player.progress;
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

user load_user_data(FILE *user_profile, user player) {
    char buffer[1000];
    // get user's easy wins
    fgets(buffer, sizeof(buffer), user_profile);
    player.easy_wins = atoi(buffer);

    // get user's easy losses
    fgets(buffer, sizeof(buffer), user_profile);
    player.easy_losses = atoi(buffer);

    // get user's medium wins
    fgets(buffer, sizeof(buffer), user_profile);
    player.medium_wins = atoi(buffer);

    // get user's medium losses
    fgets(buffer, sizeof(buffer), user_profile);
    player.medium_losses = atoi(buffer);

    // get user's hard wins
    fgets(buffer, sizeof(buffer), user_profile);
    player.hard_wins = atoi(buffer);

    // get user's hard losses
    fgets(buffer, sizeof(buffer), user_profile);
    player.hard_losses = atoi(buffer);

    // get user's current difficulty
    fgets(buffer, sizeof(buffer), user_profile);
    strtok(buffer, "\n");
    strcpy(player.difficulty, buffer);

    // get user's current progress for that difficulty
    fgets(buffer, sizeof(buffer), user_profile);
    player.progress = atoi(buffer);

    return player;
}

user update_user_profile(user player) {
    char filename[256];
    sprintf(filename, "../users/%s.txt", player.username);
    FILE *profile = fopen(filename, "w");

    char buffer[1024];
    sprintf(buffer, "%d\n", player.easy_wins);
    fputs(buffer, profile);

    sprintf(buffer, "%d\n", player.easy_losses);
    fputs(buffer, profile);

    sprintf(buffer, "%d\n", player.medium_wins);
    fputs(buffer, profile);

    sprintf(buffer, "%d\n", player.medium_losses);
    fputs(buffer, profile);

    sprintf(buffer, "%d\n", player.hard_wins);
    fputs(buffer, profile);

    sprintf(buffer, "%d\n", player.hard_losses);
    fputs(buffer, profile);

    if (player.progress >= 3) {
        // advance to next difficulty
        if (strcmp(player.difficulty, "easy") == 0)
            strcpy(player.difficulty, "medium");
        else if (strcmp(player.difficulty, "medium") == 0)
            strcpy(player.difficulty, "hard");
        else
            // cap users on hard difficulty to 3
            player.progress = 3;
        player.progress = 0;
    }
    else if (player.progress < 0) {
        // previous difficulty
        if (strcmp(player.difficulty, "medium") == 0)
            strcpy(player.difficulty, "easy");
        else if (strcmp(player.difficulty, "hard") == 0)
            strcpy(player.difficulty, "medium");
        player.progress = 2;

        if (strcmp(player.difficulty, "easy") == 0)
            player.progress = 0;
    }
    fputs(player.difficulty, profile);
    fputs("\n", profile);

    sprintf(buffer, "%d\n", player.progress);
    fputs(buffer, profile);

    fclose(profile);

    return player;
}