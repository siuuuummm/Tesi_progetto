#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * Funzione helper: allocatore di un puntatore a int che memorizza un valore
 * (corrisponde a FUN_00400496).
 */
int *alloc_int(uint32_t val) {
  int *p = (int *)malloc(sizeof(int));
  *p = (int)val;
  return p;
}

/*
 * Funzione per gestire il caso in cui il puntatore è nullo:
 * allocatore delegato (corrisponde a FUN_004004b7).
 */
int *handle_null_ptr(int *ptr, int val) {
  if (ptr == NULL) {
    ptr = alloc_int((uint32_t)val);
  } else if ((uint32_t)val < (uint32_t)(*ptr)) {
    int left = handle_null_ptr(ptr + 2, (int)(*(uint8_t *)(ptr + 2)));
    ptr[2] = (int)left;
  } else if ((uint32_t)(*ptr) < (uint32_t)val) {
    int right = handle_null_ptr(ptr + 4, (int)(*(uint8_t *)(ptr + 4)));
    ptr[4] = (int)right;
  }
  return ptr;
}

/*
 * Funzione ricorsiva per calcolare l'altezza di un albero (corrisponde a FUN_004004f7).
 */
int tree_height(uint32_t node) {
  if (node != 0) {
    int left = tree_height((node + 8) & 0xFFFFFFFFUL);
    int right = tree_height((node + 0x10) & 0xFFFFFFFFUL);
    int h = (right <= left) ? left : right;
    return h + 1;
  }
  return 0;
}

/*
 * Funzione ricorsiva per contare i nodi totali (corrisponde a FUN_0040052e).
 */
int tree_nodes(uint32_t node) {
  if (node != 0) {
    int left = tree_nodes((node + 8) & 0xFFFFFFFFUL);
    int right = tree_nodes((node + 0x10) & 0xFFFFFFFFUL);
    return left + 1 + right;
  }
  return 0;
}

/*
 * Funzione di stampa in ordine di visita (inorder) per un albero
 * rappresentato come array di 8 elementi (corrisponde a FUN_00400565).
 */
void inorder_print(uint32_t *data) {
  if (data != NULL) {
    inorder_print(&data[2]);
    printf("%d ", (int)(unsigned long)data[0]);
    inorder_print(&data[4]);
  }
}

/*
 * Funzione principale del programma (corrisponde a FUN_004005ba).
 * Costruisce l'albero a partire da un array di 8 valori e stampa
 * inorder, altezza e numero di nodi.
 */
uint8_t main(void) {
  uint8_t uVar1;
  uint8_t uVar2;
  uint8_t *puVar3;
  uint8_t local_38[8];

  puVar3 = local_38;
  local_38[0] = 0x32;
  local_38[1] = 0x1e;
  local_38[2] = 0x46;
  local_38[3] = 0x14;
  local_38[4] = 0x28;
  local_38[5] = 0x3c;
  local_38[6] = 0x50;
  uVar2 = 0;

  do {
    uVar2 = handle_null_ptr((int *)&uVar2, (int)((unsigned char)*puVar3));
    puVar3 = puVar3 + 1;
  } while (puVar3 != local_38 + 7);

  printf("Visita inorder: ");
  inorder_print((uint32_t *)&uVar2);
  putchar('\n');

  uVar1 = tree_height((uint32_t)uVar2);
  printf("Altezza: %d\n", (int)(unsigned long)uVar1);

  uVar1 = tree_nodes((uint32_t)uVar2);
  printf("Numero nodi: %d\n", (int)(unsigned long)uVar1);

  free((void *)uVar2);

  return 0;
}
