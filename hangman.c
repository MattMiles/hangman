#include <stdio.h>
#include <string.h>

int main(void) {
    // collect the user's name
    char buffer[256];
    printf("User: ");
    fgets(buffer, sizeof(buffer), stdin);

    // get rid of the trailing null character
    char user[strlen(buffer) - 1];
    for (int i = 0; i < strlen(buffer) - 1; i++) {
        user[i] = buffer[i];
    }

    // attempt to open user's profile
    char filename[256];
    sprintf(filename, "users/%s.txt", user);
    FILE *user_profile = fopen(filename, "r");

    if (user_profile != NULL) {
        // get user stats
    }
}