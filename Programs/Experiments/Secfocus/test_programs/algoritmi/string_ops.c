/* string_ops.c — Difficolta: MEDIA-ALTA
 * Manipolazione stringhe con aritmetica dei puntatori. I decompilatori
 * tendono a trasformare l'accesso ai char in complessa aritmetica di puntatori. */
#include <stdio.h>
#include <string.h>

int my_strlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return (int)(p - s);
}

void reverse_string(char *s) {
    int len = my_strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

int count_vowels(const char *s) {
    int count = 0;
    for (const char *p = s; *p; p++) {
        char c = *p;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            count++;
    }
    return count;
}

int is_palindrome(const char *s) {
    int len = my_strlen(s);
    for (int i = 0; i < len / 2; i++)
        if (s[i] != s[len - 1 - i]) return 0;
    return 1;
}

int main(void) {
    char buf[] = "reverse me";
    printf("Lunghezza: %d\n", my_strlen(buf));
    printf("Vocali: %d\n", count_vowels(buf));
    reverse_string(buf);
    printf("Invertita: %s\n", buf);

    char pal[] = "radar";
    printf("'%s' palindromo: %d\n", pal, is_palindrome(pal));
    return 0;
}
