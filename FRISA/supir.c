#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 

void loginsupir()
{
		borderutama();
		bordercs(75, 15, 32, 10, 15, 175, 212, 216, 228, 255);
		loginlogo(50, 2);

		formloginsupir();

}

int formloginsupir()
{
	rgbbgt(215, 227, 254);
	rgbtext(49, 175, 212);

	posisi(55, 11);
	printf("Form Login Supir");
	posisi(55, 12);
	printf("==============================");

	posisi(40, 15);
	printf("Masukkan Email    : ");
	posisi(40, 16);
	printf("                    ");

	posisi(40, 18);
	printf("Masukkan Password : ");
	posisi(40, 19);
	printf("                    ");

	posisi(60, 15);
	mailput();         

	posisi(60, 18);
	starshow();     

	if (loginsupir_sql()) {
		posisi(55, 21);
		Sleep(1000);
		printf("LOGIN BERHASIL");
		resetcolor();
	}
	else {
		posisi(55, 21);
		printf("EMAIL ATAU PASSWORD SALAH COBA LAGI");
		getch();
		return 0;
	}
}



void halamansupir() {
	int pilihan;
	bordertop();
	borderutama();
	bordercs(142, 7, 0, 31, 250, 250, 250, 211, 211, 211);
	borderhorizontal(0, 30, 0);
	borderhorizontal(0, 31, 1);
	do
	{

		pilihan = menu_supir();

		switch (pilihan) {
		case 1:  aksi_tugas_supir();  break;
        case 2: tampilan_profil_supir(); break;
        case 0: tampilan(); break;
		}
	} while (1);
}

void aksi_tugas_supir()
{
    int id_laporan;
    char status[30];
    char query[200];
    MYSQL_RES* res;
    MYSQL_ROW row;

    tampil_tugas_supir(3, 3);

    posisi(3, 18);
    printf("Masukkan ID Laporan (0 = kembali): ");
    id_laporan = val_id();
    getchar();

    if (id_laporan == 0) return;

    sprintf(query,
        "SELECT status_laporan FROM laporan "
        "WHERE id_laporan=%d AND id_supir=%d",
        id_laporan, SESSION_ID_SUPIR
    );

    mysql_query(conn, query);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    if (!row)
    {
        mysql_free_result(res);
        posisi(3, 20);
        printf("Laporan tidak ditemukan!");
        getch();
        return;
    }

    strcpy(status, row[0]);
    mysql_free_result(res);

    posisi(3, 20);

    if (strcmp(status, "MENUNGGU_SUPIR") == 0)
    {
        printf("1. TERIMA TUGAS\n2. TOLAK TUGAS\nPilihan: ");
        char ch = getch();

        if (ch == '1')
        {
            sprintf(query,
                "UPDATE laporan SET status_laporan='DIPROSES' "
                "WHERE id_laporan=%d",
                id_laporan
            );
            mysql_query(conn, query);
        }
        else if (ch == '2')
        {
            sprintf(query,
                "UPDATE laporan SET status_laporan='DITOLAK_SUPIR' "
                "WHERE id_laporan=%d",
                id_laporan
            );
            mysql_query(conn, query);
        }
    }
    else
    {
        printf("Laporan tidak bisa diubah (status: %s)", status);
        getch();
    }
}

