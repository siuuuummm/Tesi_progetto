/*
 * Reconstructed from stripped binary (main = FUN_004004e6).
 *
 * Data layout of the two 32-byte (0x20) buffers allocated in main:
 *   offset 0x00 : char name[0x18]  (24 bytes; filled via strncpy(..., 0x17))
 *   offset 0x18 : int              (4 bytes; "role" field, 0 => utente)
 *   offset 0x1c : int              (4 bytes; "sessione"/value field)
 *   sizeof      : 0x20 (32 bytes)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int     iVar1;
    int     iVar2;
    int     ret;
    char  *__dest;
    char  *__dest_00;

    if (argc < 3) {
        ret = 1;
    }
    else {
        setvbuf(stdout, (char *)0x0, 2, 0);

        /* Record #1: user session (name comes from argv[1]). */
        __dest = (char *)malloc(0x20);
        memset(__dest, 0, 0x20);
        strncpy(__dest, argv[1], 0x17);
        __dest[0x1c] = -0x18;
        __dest[0x1d] = '\x03';
        __dest[0x1e] = '\0';
        __dest[0x1f] = '\0';
        printf("Sessione %d aperta per %s\n",
               (unsigned long)*(unsigned int *)(__dest + 0x1c), __dest);

        iVar1 = strcmp(argv[2], "logout");
        if (iVar1 == 0) {
            free(__dest);
            puts("Logout eseguito");
        }

        /* Record #2: fixed "promemoria" note (numeric field from argv[3]). */
        __dest_00 = (char *)malloc(0x20);
        memset(__dest_00, 0, 0x20);
        strncpy(__dest_00, "promemoria", 0x17);
        if (argc < 4) {
            iVar2 = 0;
        }
        else {
            iVar2 = atoi(argv[3]);
        }
        *(int *)(__dest_00 + 0x18) = iVar2;
        __dest_00[0x1c] = '\a';
        __dest_00[0x1d] = '\0';
        __dest_00[0x1e] = '\0';
        __dest_00[0x1f] = '\0';

        if (*(int *)(__dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", __dest);
        }
        else {
            printf("Accesso amministratore per %s\n", __dest);
        }

        free(__dest_00);
        if (iVar1 != 0) {
            free(__dest);
        }
        ret = 0;
    }
    return ret;
}
