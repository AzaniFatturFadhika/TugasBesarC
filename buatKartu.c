#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *pf; // Pointer ke File
    char nomorRekening[20];

    struct Rekening{
        char nomorRekening[16];
        char namaRekening[50];
        char pin[8];
        unsigned long int saldoRekening;
    } rekening;

    printf("Nomor  : ");
    gets(rekening.nomorRekening);
    strcpy(nomorRekening, rekening.nomorRekening);
    strcat(nomorRekening, ".txt");
    pf = fopen(nomorRekening, "wt");
    printf("Nama   : ");
    scanf("%s", rekening.namaRekening);
    printf("Pin    : ");
    scanf("%s", rekening.pin);
    printf("Saldo  : ");
    scanf("%li", &rekening.saldoRekening);
    fflush(stdin);      // Hapus penampung keyboard
    fwrite(&rekening, sizeof(rekening), 1, pf);   // Rekam data bertipe strktur

    fclose(pf);             // Menutup file

    return 0;
}