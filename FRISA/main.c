#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 

int main(void) {
    resetcolor();
    conn = koneksiDB();   //koneksi

    SetConsoleOutputCP(65001);
    system("mode con cols=141 lines=38");
        char s;
        system("COLOR 72");
        printf("Tekan enter untuk lanjut");
        while ((s = getch()) != 13)
        {
            system("COLOR 74");
            Sleep(1);
            system("COLOR 72");
        }
        system("cls");
    resetcolor();
    tampilan();

    
    /*if (conn == NULL) {
        printf("Program berhenti\n");
        return 1;
    }

    printf("Koneksi berhasil!\n");*/


    putusKoneksi(conn);  //tutup koneksi
    end();
    return 0;
}



