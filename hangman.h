char *get_user();
FILE *open_user_profile(char filename[]);
void display_user_profile(char *user);

unsigned int easy_wins = 0;
unsigned int easy_losses = 0;
unsigned int medium_wins = 0;
unsigned int medium_losses = 0;
unsigned int hard_wins = 0;
unsigned int hard_losses = 0;
char difficulty[256];
unsigned int won_in_a_row = 0;