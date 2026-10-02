/* hash_table.c — Difficolta: ALTA
 * Hash table con chaining. Array di puntatori a struct + hashing:
 * stressa il recupero di tipi complessi e l'aritmetica di indicizzazione. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 16

struct Entry {
    char key[32];
    int value;
    struct Entry *next;
};

struct HashTable {
    struct Entry *buckets[TABLE_SIZE];
};

unsigned int hash(const char *key) {
    unsigned int h = 2166136261u;
    for (const char *p = key; *p; p++) {
        h ^= (unsigned char)*p;
        h *= 16777619u;
    }
    return h % TABLE_SIZE;
}

void ht_put(struct HashTable *ht, const char *key, int value) {
    unsigned int idx = hash(key);
    for (struct Entry *e = ht->buckets[idx]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) {
            e->value = value;
            return;
        }
    }
    struct Entry *e = malloc(sizeof(struct Entry));
    strncpy(e->key, key, sizeof(e->key) - 1);
    e->key[sizeof(e->key) - 1] = '\0';
    e->value = value;
    e->next = ht->buckets[idx];
    ht->buckets[idx] = e;
}

int ht_get(struct HashTable *ht, const char *key, int *found) {
    unsigned int idx = hash(key);
    for (struct Entry *e = ht->buckets[idx]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) {
            *found = 1;
            return e->value;
        }
    }
    *found = 0;
    return 0;
}

int main(void) {
    struct HashTable ht;
    memset(&ht, 0, sizeof(ht));

    ht_put(&ht, "alpha", 1);
    ht_put(&ht, "beta", 2);
    ht_put(&ht, "gamma", 3);
    ht_put(&ht, "beta", 20);  /* update */

    int found;
    printf("alpha = %d\n", ht_get(&ht, "alpha", &found));
    printf("beta  = %d\n", ht_get(&ht, "beta", &found));
    printf("delta found = %d\n", (ht_get(&ht, "delta", &found), found));

    return 0;
}
