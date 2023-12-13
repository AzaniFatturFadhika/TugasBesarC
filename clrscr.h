#include <stdio.h>

void clearScreen(){
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux
    #endif
}