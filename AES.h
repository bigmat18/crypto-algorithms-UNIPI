#include "Utils.h"

#define MATRIX(value, row, column) value[(row * 4) + column]

// assumiamo chiave a 16 bytes
unsigned char* NeyKey(unsigned char* key, int step) {
    if(step % 4 == 0) {
        // W[i] = W[i-1] xor W[i-1] 
    } else {
        // W[i] = W[i-1] xor T(W[i-1])
    }
}

void T(unsigned char* msg) {
    // msg = 4 byte

    // Shift ciclico di 1 dei 4 byte

    // Applicazione della S-box per ogni byte

    // calcolare dello XOR tra il byte più a sinistra con la costande
    // con la costande di round RC

    /**
     *      { 1             i = 1
     * RC = { 2RC_{i-1}     2 <= i <= 10
     *      {
    */
}

// input 1 solo byte
unsigned char* Sbox(unsigned char* msg) {
    int permutations[] = {
        // permutazione 16 x 16 byte permutazioni di tutti i 256 interi a 8 bit
    };

    /**
     * b[i][j] = b1,b2,b3,b4 b5,b6,b7,b8
     *             riga         colonna
     * 
    */
}

void SubstitutionByte(unsigned char* msg) {
    /**
     * Si applica la S-BOX per ogni byte
     * 
     * Ogni byte b[i][j] viene prima sostitito con il suo inverso moltiplicantivo
     * in GF(2^8)[non linearità] e poi moltiplicato per una matrice 8x8 bit e sommatto
     * con un vettore colonna
    */

   for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            MATRIX(msg, i, j) = Sbox(MATRIX(msg, i, j));
        }
   }
}

void ShiftRows(unsigned char* msg) {
    for(int i = 1; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            /**
             * I byte di ogni riga vengono shifati ciclicaemte verso sinistra di 0, 1, 2, 3
             * posizioi, rispetivamente alla riga in cui ci si trova
            */
           MATRIX(msg, i, j) = MATRIX(msg, i, (j + i) % 4);
        }
    }
}

// msg 16 byte 
void MixColumus(unsigned char* msg) {
    int M[] = {
        // Matrice scenta in modo che ciascun byte della colonna venga
        // mappato in un nuobo byte che è funzione di tutti i 4 byte presenti
        // nella colonna
    };
    
    /**
     * Ogni colonna del blocco viene trattata come vettore a 4 elementi
     * e moltiplicata con la corrispettiva colonna di una matrice M (4x4)
     * [moltiplicazione in mod 2^8 e somma mod 2]
    */
}

void AddRoundKey(unsigned char* msg, unsigned char* key) {

    // Viene fatto lo xor fra messaggio e key
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            MATRIX(msg, i, j) ^= MATRIX(key, i, j);
        }
    }
}

// msg è diviso in blocchi da 128, 192 o 256 bit in ogni caso multipli di 32bit
void AES_Enc(unsigned char* msg, unsigned char* key) {
    int steps = 10; // può essere 10, 12 o 14 in base alla lunghezza della chiave
    for(int i = 0; i < steps; i++){
        // ad ogni fase viene generata una nuova chiave a 
        // partire da quella precedente
        unsigned char new_key = NewKey(key); 

        SubstitutionByte(msg);
        ShiftRows(msg);
        MixColumus(msg);
        AddRoundKey(msg, key);
    }
    /** */
}

void AES_Dec(unsigned char* msg, unsigned char* key) {
    /** */
}