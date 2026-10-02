#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void FUN_00400476(char *param_1);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    FUN_00400476(argv[1]);

    return 0;
}

void FUN_00400476(char *param_1) {
    char local_48[64];
    
    strcpy(local_48, param_1);
    printf("Buffer content: %s\n", local_48);
    return;
}

int FUN_0040049e(void) {
    FUN_00400476("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
