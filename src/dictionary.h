// the amount of games the user has to win in a row to move to the next difficulty
#define THRESHOLD 3
#define MAX 1024

typedef struct dictionary_node {
    char *word;
    struct dictionary_node *next;
} dictionary_node;

void initialize_dictionary(FILE *dictionary, dictionary_node *easy_root, dictionary_node *medium_root, dictionary_node *hard_root);
int is_common(char letter);