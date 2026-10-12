#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc <= 2) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    uint8_t *buffer = (uint8_t *)malloc(32);
    if (buffer == NULL) {
        return 1;
    }
    memset(buffer, 0, 32);

    strncpy((char *)buffer, argv[1], 23);

    // buffer[28..31] = 1000
    *((uint32_t *)(buffer + 28)) = 1000;

    printf("Sessione %d aperta per %s\n", 1000, (char *)buffer);

    int is_logout = strcmp(argv[2], "logout");

    if (is_logout == 0) {
        free(buffer);
        printf("Accesso utente per %s\n", argv[1]);

        if (argc > 3) {
            strtol(argv[3], NULL, 10);
        }
        
        if (*(int *)(buffer + 24) == 0) {
            printf("Logout eseguito\n");
        } else {
            printf("Accesso amministratore per %s\n", argv[1]);
        }
    } else {
        if (argc > 3) {
            strtol(argv[3], NULL, 10);
        }

        if (*(int *)(buffer + 24) == 0) {
            printf("Logout eseguito\n");
            free(buffer);
        } else {
            printf("Accesso amministratore per %s\n", (char *)buffer);
            free(buffer);
        }
    }

    return 0;
}
