#include <stdio.h>
#include <stdint.h>

// Questi simboli sono variabili globali usate dal binario originale.
// Vanno dichiarate come array, visto che gli offset sono consecutivi.
uint8_t DAT_00403010; // param1
uint8_t DAT_00403011; // param2
uint8_t DAT_00403012; // param3
uint8_t DAT_00403013; // param4
uint8_t DAT_00403014; // param5
uint8_t DAT_00403015; // param6
uint8_t DAT_00403016; // param7
uint8_t DAT_00403017; // param8

void print_final_result(uint8_t result) {
    printf("Risultato finale: 0x%02X\n", result);
}

// Funzione principale di manipolazione dei parametri (ex FUN_00400380)
int compute_and_print_result(void) {
    uint8_t value;

    // Primo step
    if (DAT_00403010 == 0x02) {
        value = DAT_00403011 + 0x42;
    } else if (DAT_00403010 == 0x03) {
        value = ('B' << (DAT_00403011 & 7)) | (0x42U >> (8 - (DAT_00403011 & 7)));
    } else if (DAT_00403010 == 0x01) {
        value = DAT_00403011 ^ 0x42;
    } else {
        value = 0x42;
        print_final_result(value);
        return 0;
    }

    // Secondo step
    if (DAT_00403012 == 0x02) {
        value = value + DAT_00403013;
    } else if (DAT_00403012 == 0x03) {
        value = (value << (DAT_00403013 & 7)) | (value >> (8 - (DAT_00403013 & 7)));
    } else if (DAT_00403012 == 0x01) {
        value = value ^ DAT_00403013;
    } else {
        print_final_result(value);
        return 0;
    }

    // Terzo step
    if (DAT_00403014 == 0x02) {
        value = value + DAT_00403015;
    } else if (DAT_00403014 == 0x03) {
        value = (value << (DAT_00403015 & 7)) | (value >> (8 - (DAT_00403015 & 7)));
    } else if (DAT_00403014 == 0x01) {
        value = value ^ DAT_00403015;
    } else {
        print_final_result(value);
        return 0;
    }

    // Quarto step
    if (DAT_00403016 == 0x02) {
        value = value + DAT_00403017;
    } else if (DAT_00403016 == 0x03) {
        value = (value << (DAT_00403017 & 7)) | (value >> (8 - (DAT_00403017 & 7)));
    } else if (DAT_00403016 == 0x01) {
        value = value ^ DAT_00403017;
    }
    print_final_result(value);
    return 0;
}

// Funzioni vuote decompilate (dummy, per completezza)
void dummy_function1(void) {}   // ex FUN_00400360
void dummy_function2(void) {}   // ex FUN_00400480
void dummy_function3(void) {}   // ex FUN_00400490
void dummy_function4(void) {}   // ex FUN_004004c0

// Main fittizio: nel binario stripped era richiamato tramite __libc_start_main
int main(void) {
    // Le variabili globali dovrebbero essere caricate da qualche parte, oppure configurate qui se necessario
    compute_and_print_result();
    return 0;
}
