typedef struct dictionary_node {
    char *word;
    struct dictionary_node *next;
} dictionary_node;

void initialize_dictionary(FILE *dictionary, dictionary_node *easy_root, dictionary_node *medium_root, dictionary_node *hard_root);
int is_common(char letter);
char *get_hangman_word(dictionary_node *easy_root, dictionary_node *medium_root, dictionary_node *hard_root);
char *get_word(dictionary_node *easy_root, dictionary_node *medium_root, dictionary_node *hard_root, user player);
int get_dictionary_length(dictionary_node *head);