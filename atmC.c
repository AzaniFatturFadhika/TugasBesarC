// TUGAS BERSAR LOGIKA & ALGORITMA
// NAMA  : AZANI FATTUR FADHIKA
// NIM   : 4.33.23.1.05

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clrscr.h"

// MACRO
#define kurangiRekening(nominal) (rekening.saldoRekening = rekening.saldoRekening - nominal) // Pengurangan Saldo

// FUNCTIONs
void selamatDatang();
void cekRekening();
void daftarMenu();
void prosesMenu(int input);
void cekSaldo();
void penarikanSaldo();
void transferSaldo();
void transaksiLain();
void keluar();


// GLOBAL Variabel
FILE *rek; // Pointer ke File rekening
FILE *rekTransfer; // Pointer ke File rekening transfer

char nomorRekening[16]; // input nomor rekening
char fileRekening[20]; // file_rekening.txt
char pin[8]; // input pin

// STRUCT
typedef struct {
    char nomorRekening[16];
    char namaRekening[50];
    char pin[8];
    unsigned long int saldoRekening;
} Rekening;

Rekening rekening;
Rekening rekeningTransfer;

// MAIN
int main()
{
    clearScreen();
    selamatDatang();

    return 0;
}

// FUNCTION CODE

void selamatDatang(){
    printf("                          SELAMAT DATANG\n");
    printf("                                DI\n");
    printf("                         BANK SEMESTA NUSA\n\n");
    cekRekening();
}

void cekRekening(){
    printf("                      MASUKKAN NOMOR REKENING\n\n\t\t\t  ");
    scanf("%16s",nomorRekening);
    strcpy(fileRekening, nomorRekening);
    strcat(fileRekening, ".txt");
    rek = fopen(fileRekening, "rt");
       
    if(rek == NULL){
        clearScreen(); 
        
        printf("\n                  Nomor Rekening Tidak Ditemukan\n\n");
        selamatDatang();
        
    } else {
        clearScreen();
        printf("                       Masukkan PIN\n\n\t\t\t");
        scanf("%8s",pin);
        fread(&rekening, sizeof(rekening), 1, rek);

        if(strcmp(rekening.nomorRekening, nomorRekening) == 0 && strcmp(rekening.pin, pin) == 0){
            daftarMenu(); 
        } else {
            clearScreen();
            fclose(rek);
            printf("\n                   Pin Yang Anda Masukkan Salah\n\n");
            selamatDatang();
        }
    }
}

void daftarMenu(){
    int input;
    clearScreen();
    printf("                    MENU UTAMA\n");
    printf("              PECAHAN UANG RP 50.000\n");
    printf("          ===============================\n");
    printf("               TEKAN <0> UNTUK BATAL\n\n");
    printf("  1.  100.000                           2.  500.000\n");
    printf("  3.  200.000                           4.  1.000.000\n");
    printf("  5.  PENARIKAN JUMLAH LAIN             6.  TRANSFER\n");
    printf("  7.  CEK SALDO\n\n\n");

    printf("  INPUT PILIHAN : ");
    scanf("%d", &input);
    prosesMenu(input);
}

void prosesMenu(int input){   
    const char pesanGagalTarik[50] = "    Saldo Anda Tidak Mencukupi, Transaksi Gagal";
    clearScreen();
    switch(input){
        case 1 : 
            if(rekening.saldoRekening >= 100000){
                kurangiRekening(100000);
                printf("    Penarikan Rp. 100.000  Berhasil");
            }else{
                printf(pesanGagalTarik);
            }
            transaksiLain();
            break; 
        case 2 : 
            if(rekening.saldoRekening >= 500000){
                kurangiRekening(500000);
                printf("    Penarikan Rp. 500.000  Berhasil");
            }else{
                printf(pesanGagalTarik);
            }
            transaksiLain();
            break; 
        case 3:
            if(rekening.saldoRekening >= 200000){
                kurangiRekening(200000);
                printf("    Penarikan Rp. 200.000  Berhasil"); 
            }else{
                printf(pesanGagalTarik);
            }
            transaksiLain();
            break; 
        case 4:
            if(rekening.saldoRekening >= 1000000){
                kurangiRekening(1000000);
                printf("    Penarikan Rp. 1.000.000  Berhasil"); 
            }else{
                printf(pesanGagalTarik);
            }
            transaksiLain();
            break; 
        case 5:
            penarikanSaldo();
            break;
        case 6:
            clearScreen();
            transferSaldo();
            break;
        case 7:
            cekSaldo();
            break;
        case 0:
            keluar();
            break;
        default :
            daftarMenu();
    }
}

void cekSaldo(){
    clearScreen();
    printf("\n\n              HALO %s\n\n",rekening.namaRekening);
    printf("               SISA SALDO ANDA\n\n");
    printf("                 "); printf("Rp %lu",rekening.saldoRekening);
    transaksiLain();
}

void transaksiLain(){
    int input;
    printf("\n\n\n    APAKAH ANDA INGIN MELAKUKAN TRANSAKSI LAIN?\n\n");
    printf("                   1. YA            2. TIDAK\n\n");
    printf("Pilihan : ");
    scanf("%d", &input);
    switch (input){
        case 1: 
            daftarMenu(); 
            break;
        default:
            keluar(); 
            break;
    }
}

void keluar(){
    rek = fopen(fileRekening, "wt");
    fwrite(&rekening, sizeof(rekening), 1, rek);
    fclose(rek);
    clearScreen();
    selamatDatang();
}

void penarikanSaldo(){
    unsigned long int nominal;
    int input;

    clearScreen();
    printf("\n\n           MASUKKAN NOMINAL MINIMAL Rp 50.000\n\n");
    printf("                  Rp ");
    scanf("%lu",&nominal);
    printf("\n\n    1. BENAR          2. ULANGI         3. KEMBALI KE MENU");
    printf("\n\n\tPILIHAN : ");

    scanf("%d", &input);
    clearScreen();

    switch (input){
        case 1:
            if((nominal%50000 == 0) && rekening.saldoRekening > nominal){
                rekening.saldoRekening = rekening.saldoRekening - nominal;
                printf("\t\t     PENARIKAN SEJUMLAH ");
                printf("%li",nominal);
                printf(" BERHASIL");
                transaksiLain();
                break;
            }else{
            printf("\t\t  MAAF TRANSAKSI GAGAL");
                transaksiLain();
            break;
            }
        case 2: 
            penarikanSaldo();
            break;
        default:
            daftarMenu();
    }
}

void transferSaldo(){
    unsigned long int nominal;
    int input;
    char nomorRekeningTujuan[18];

    printf("                      MASUKKAN NOMOR REKENING");
    printf("\n\n\t\t\t   ");
    scanf("%16s",nomorRekeningTujuan);

    if(strcmp(nomorRekening, nomorRekeningTujuan) == 0){
        clearScreen();
        fclose(rekTransfer); 
        printf("\n      Tidak Dapat Mentransfer ke Rekening Sendiri\n\n");
        transferSaldo();
    } else {
        strcat(nomorRekeningTujuan, ".txt");
        rekTransfer = fopen(nomorRekeningTujuan, "rt");
        if(rekTransfer == NULL){
            clearScreen();
            fclose(rekTransfer); 
            printf("\n        Nomor Rekening Tidak Ditemukan\n\n");
            transferSaldo();
        }else{
            clearScreen();
            fread(&rekeningTransfer, sizeof(rekeningTransfer), 1, rekTransfer);
            printf("\n         REKENING TUJUAN : %s\n\n",rekeningTransfer.namaRekening);

            printf("\n           MASUKKAN NOMINAL TRANSFER\n\n");
            printf("                  Rp ");
            scanf("%lu",&nominal);
            printf("\n\n    1. BENAR          2. ULANGI         3. KEMBALI KE MENU");
            printf("\n\n\tPILIHAN : ");

            scanf("%d", &input);
            clearScreen();

            switch (input){
                case 1:
                    if(rekening.saldoRekening >= nominal){
                        kurangiRekening(nominal);
                        rekeningTransfer.saldoRekening = rekeningTransfer.saldoRekening + nominal;

                        rekTransfer = fopen(nomorRekeningTujuan, "wt");

                        fwrite(&rekeningTransfer, sizeof(rekeningTransfer), 1, rekTransfer);
                        fclose(rekTransfer);

                        printf("\t\t     TRASNFER SEJUMLAH ");
                        printf("%li",nominal);
                        printf(" BERHASIL");
                        transaksiLain();
                        break;
                    }else{
                        printf("\t\t  MAAF TRANSAKSI GAGAL");
                        transaksiLain();
                    break;
                    }
                case 2: 
                    transferSaldo();
                    break;
                default:
                    daftarMenu();
            }
        }
    }
}