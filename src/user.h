typedef struct user {
    char *username;
    unsigned int easy_wins;
    unsigned int easy_losses;
    unsigned int medium_wins;
    unsigned int medium_losses;
    unsigned int hard_wins;
    unsigned int hard_losses;
    char *difficulty;
    int progress;
} user;

char *get_user();
FILE *open_user_profile(char filename[]);
void display_user_profile(user player);
user load_user_data(FILE *user_profile, user player);
user update_user_profile(user player);