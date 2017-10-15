#include <stdio.h>
#include <string.h>

#include "hangman.h"

int play_hangman(char *word, int incorrects, char guesses[], int total_guesses) {
    printf("\n");
    printf("ROUND %d\n", total_guesses);

    draw_figure(incorrects);

    if (incorrects >= 6) {
        printf("You lost.\n");
        printf("The word was: %s\n", word);
        return -1;
    }

    // if draw_board doesn't draw any lines, player must have won
    if (!draw_board(word, guesses)) {
        printf("You won!\n");
        return 1;
    }

    scanf(" %c", &guesses[total_guesses]);
    if (!strchr(word, guesses[total_guesses]))
        incorrects++;
    total_guesses++;

    return play_hangman(word, incorrects, guesses, total_guesses);
}

int draw_board(char *word, char guesses[]) {
    // tracks if lines were drawn
    int lines_drawn = 0;

    for (int i = 0; i < strlen(word); i++) {
        if (!strchr(guesses, word[i])) {
            printf("__ ");
            lines_drawn = 1;
        }
        else
            printf("%c  ", word[i]);
    }
    printf("\n");

    return lines_drawn;
}

void draw_figure(int incorrects) {
    switch (incorrects) {
        case 0:
            printf("---------\n");
            printf("|\n");
            printf("|\n");
            printf("|\n");
            printf("|\n");


            break;
        case 1:
            printf("---------\n");
            printf("|       O\n");
            printf("|\n");
            printf("|\n");
            printf("|\n");


            break;
        case 2:
            printf("---------\n");
            printf("|       O\n");
            printf("|       |\n");
            printf("|\n");
            printf("|\n");


            break;
        case 3:
            printf("---------\n");
            printf("|       O\n");
            printf("|       |\\\n");
            printf("|\n");
            printf("|\n");


            break;
        case 4:
            printf("---------\n");
            printf("|       O\n");
            printf("|      /|\\\n");
            printf("|\n");
            printf("|\n");


            break;
        case 5:
            printf("---------\n");
            printf("|       O\n");
            printf("|      /|\\\n");
            printf("|      / \n");
            printf("|\n");


            break;
        case 6:
            printf("---------\n");
            printf("|       O\n");
            printf("|      /|\\\n");
            printf("|      / \\\n");
            printf("|\n");

            break;
    }
}
