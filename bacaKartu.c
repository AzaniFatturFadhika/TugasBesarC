// Nama    : Azani Fattur Fadhika
// Program untuk menghitung volume balok dengan ketentuan

#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *pf; // Pointer ke File
    struct Rekening{
        char nomorRekening[16];
        char namaRekening[50];
        char pin[8];
        unsigned long int saldoRekening;
    } rekening;

    gets(rekening.nomorRekening);
    strcat(rekening.nomorRekening, ".txt");

    pf = fopen(rekening.nomorRekening, "rb");
    if(pf == NULL){
        puts("File tidak dapat dibuka");
        exit(1);
    }

    int i = 0;

    while(fread(&rekening, sizeof(rekening), 1, pf) == 1){
        i++;
        printf("Balok %d\n",i);
        printf("Nomor   : %s\nNama     : %s\npin    : %s\nSaldo    : %li\n\n",
        rekening.nomorRekening,
        rekening.namaRekening,
        rekening.pin,
        rekening.saldoRekening
    );
    }

    fclose(pf);             // Menutup file
    return 0;
}