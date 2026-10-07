/*
 * Traduzione fedele del binario stripped "test_O3" (ELF 64-bit, x86-64).
 *
 * Ricavata dalla decompilazione di FUN_00400400 (main) e dalla disassemblazione
 * corrispondente. I valori costanti sono letti dal segmento .rodata
 * (indirettamente, come carichi vettorizzati in .text) e riproducono:
 *
 *    0x401360..0x40136c : 0 1 2 3   (start delle 4 lane)
 *    0x401370..0x40137c : 1 1 1 1   (offset)
 *    0x401380..0x40138c : 4 4 4 4   (step)
 *
 * Stringhe di formato (.rodata):
 *    0x401310 : "Troppi elementi"
 *    0x401320 : "Somma: %u\n"
 *    0x401330 : "Elementi: %u, byte allocati: %u\n"
 *
 * La maschera "& 0xff" sulla dimensione di malloc e il tipo/la stampa di "sum"
 * sono riportati ESATTAMENTE come nel binario (sono parte del programma originale).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    long n;                 /* risultato di strtol */
    unsigned int nu;        /* n come unsigned (uVar9) */
    int *arr;               /* __ptr */
    int sum;                /* somma parziale / finale (stampa con %u) */

    if (argc < 2) {
        return 1;
    }
    setvbuf(stdout, (char *)0, 2, 0);
    n = strtol(argv[1], 0, 10);
    nu = (unsigned int)n;
    if (100 < nu) {
        puts("Troppi elementi");
        return 1;
    }

    /* bug originale: la dimensione di malloc viene troncata a 8 bit */
    arr = (int *)malloc((unsigned long)((nu * 4) & 0xff));

    printf("Elementi: %u, byte allocati: %u\n",
           (unsigned int)n,
           (unsigned long)(unsigned char)(nu * 4));

    /* Costanti caricate dal .rodata (movdqa su 0x401360/0x401370/0x401380) */
    int start0, start1, start2, start3;
    int off0, off1, off2, off3;
    int step0, step1, step2, step3;

    start0 = 0; start1 = 1; start2 = 2; start3 = 3;   /* 0x401360,64,68,6c */
    off0   = 1; off1   = 1; off2   = 1; off3   = 1;   /* 0x401370,74,78,7c */
    step0  = 4; step1  = 4; step2  = 4; step3  = 4;   /* 0x401380,84,88,8c */

    sum = (int)nu;
    if (nu != 0) {
        unsigned int nbase;          /* uVar10 */
        if (nu - 1 < 4) {
            nbase = 0;
            sum = 0;
        }
        else {
            int s0, s1, s2, s3;      /* xmm2 iniziale = {0,1,2,3} */
            int acc0, acc1, acc2, acc3; /* xmm1 = {0,0,0,0} (accumulator) */
            int *p;
            int *pnext;
            int v0, v1, v2, v3;

            s0 = start0; s1 = start1; s2 = start2; s3 = start3;
            acc0 = 0; acc1 = 0; acc2 = 0; acc3 = 0;
            p = arr;
            do {
                pnext = p + 4;
                v0 = s0 * 3;
                v1 = s1 * 3;
                v2 = s2 * 3;
                v3 = s3 * 3;
                s0 = s0 + step0;
                s1 = s1 + step1;
                s2 = s2 + step2;
                s3 = s3 + step3;
                v0 = v0 + off0;
                v1 = v1 + off1;
                v2 = v2 + off2;
                v3 = v3 + off3;
                *p     = v0;
                p[1]   = v1;
                p[2]   = v2;
                p[3]   = v3;
                acc0 = acc0 + v0;
                acc1 = acc1 + v1;
                acc2 = acc2 + v2;
                acc3 = acc3 + v3;
                p = pnext;
            } while (arr + ((nu >> 2) & 0x3fffffff) * 4 != p);

            /* somma orizzontale delle 4 lane (psrldq/paddd) */
            sum = acc0 + acc2 + acc1 + acc3;
            if ((n & 3) == 0) {
                goto stampa;
            }
            nbase = nu & 0xfffffffc;
        }

        /* epilogo: elementi residui del gruppo di 4 */
        {
            int t = (int)nbase * 3;
            sum = t + 1 + sum;
            if (((nbase + 1 < nu) && (sum = t + 4 + sum, nbase + 2 < nu)) &&
                (sum = t + 7 + sum, nbase + 3 < nu)) {
                sum = t + 10 + sum;
            }
        }
    }
stampa:
    printf("Somma: %u\n", (unsigned int)sum);
    free(arr);
    return 0;
}
