#include <time.h>

#include "dictionary.h"

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
        if (word_difficulty >= 3) {
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

char *get_word(dictionary_node *easy_root, dictionary_node *medium_root, dictionary_node *hard_root, user player) {
    dictionary_node *current = malloc(sizeof(dictionary_node));
    srand(time(NULL));
    if (strcmp(player.difficulty, "easy") == 0)
        current = easy_root;
    else if (strcmp(player.difficulty, "medium") == 0)
        current = medium_root;
    else
        current = hard_root;

    unsigned int loc = rand() % get_dictionary_length(current);

    for (int i = 0; i < loc; i++) {
        current = current->next;
    }

    return current->word;
}

int get_dictionary_length(dictionary_node *head) {
    dictionary_node *current = head;
    int count = 0;

    while (current->next != NULL) {
        current = current->next;
        count++;
    }

    return count;
}