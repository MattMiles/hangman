#include <stdlib.h>

// the amount of games the user has to win in a row to move to the next difficulty
#define THRESHOLD 3

typedef struct dictionary_node {
    char *word;
    struct dictionary_node *next;
} dictionary_node;

char *get_user();
FILE *open_user_profile(char filename[]);
void display_user_profile(char *user);
void load_user_data(FILE *user_profile);
void initialize_dictionary(FILE *dictionary, dictionary_node *easy_root, dictionary_node *medium_root, dictionary_node *hard_root);
int is_common(char letter);
int play_hangman(char *word);

unsigned int easy_wins = 0;
unsigned int easy_losses = 0;
unsigned int medium_wins = 0;
unsigned int medium_losses = 0;
unsigned int hard_wins = 0;
unsigned int hard_losses = 0;
char difficulty[256];
unsigned int won_in_a_row = 0;