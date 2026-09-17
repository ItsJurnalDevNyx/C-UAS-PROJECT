#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 

void loginuser() {
	borderutama();
		bordercs(75, 15, 32, 10, 15, 175, 212, 216, 228, 255);
		loginlogo(50, 2);

		if (formlogin()) {
		}
}




int formlogin() {
	char formnama[30];


	rgbbgt(215, 227, 254);
	rgbtext(49, 175, 212);
	posisi(55, 11);
	printf("Form Login Pengguna Pengguna");
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

	if (loginsql()) {
		posisi(55, 21);
		Sleep(1000);
		printf("LOGIN BERHASIL\n");
	}
	else {
		posisi(55, 21);
		printf("EMAIL ATAU PASSWORD SALAH COBA LAGI)");
		int ch = getch();
		loginuser();
	}
	resetcolor();
}

void halamanuser() {
	int pilihan;
	bordertop();
	borderutama();
	bordercs(142, 7, 0, 31, 250, 250, 250, 211, 211, 211);
	borderhorizontal(0, 30, 0);
	borderhorizontal(0, 31, 1);
	do
	{
		
		pilihan = menu_user();

		switch (pilihan) {
		case 1: panggil();  break;
		case 2: laporan(); break;
		case 0: logout(); tampilan(); break;
		}
	} while (1);
}

void tampilanlaporan() {
	if (!cek_laporan_aktif_user()) {
		posisi(6, 5);
		printf("Tidak ada laporan aktif.");
		getch();
		return;
	}

	tampilan_laporan_aktif();
}

void laporan()
{
	if (!cek_laporan_aktif_user()) {
		posisi(6, 5);
		printf("Tidak ada laporan aktif.");
		getch();
		return;
	}

	tampilan_laporan_aktif();

	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[200];

	sprintf(query,
		"SELECT status_laporan FROM laporan WHERE id_laporan=%d",
		SESSION_ID_LAPORAN
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row && strcmp(row[0], "MENUNGGU_SUPIR") == 0) {
		posisi(5, 17);
		printf("Tekan B untuk batalkan | T Melihat Data | ESC kembali");

		int ch = getch();
		if (ch == 'b' || ch == 'B') {
			batal_laporan();
		}
		if (ch == 't' || ch == 'T') {
			tampilan_total_laporan(30,6);
		}
	}
	else {
		posisi(5, 17);
		printf("Tekan ESC untuk kembali");
		getch();
	}

	mysql_free_result(res);
}

void panggil() {
	int rs_id;
	int id_amb;

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	ambiltanggal();
	posisi(5, 2);
	printf("Tanggal sekarang  : %s\n", date);

	posisi(5, 5);
	printf("Pilih Rumah Sakit : ");
	rs_id = listrs(27, 6);

	posisi(5, 11);
	printf("Pilih Ambulans    : ");
	id_amb = pilih_ambulans_dropdown(27, 11);

	proses_pesan_ambulans(rs_id, id_amb);

	posisi(80, 5);
	printf("Mohon gunakan ambulans secara bijak dan bertanggung jawab,");
	posisi(80, 6);
	printf("hanya dalam kondisi yang benar - benar membutuhkan.");

	posisi(80, 8);
	printf("Penyalahgunaan dapat menghambat pelayanan darurat");
	posisi(80, 9);
	printf("bagi pasien lain yang membutuhkan pertolongan.");
}

void tampilanpanggil() {

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	ambiltanggal();
	posisi(5, 2);
	printf("Tanggal sekarang  : %s\n", date);

	posisi(5, 5);
	printf("Pilih Rumah Sakit : ");

	posisi(80, 5);
	printf("Mohon gunakan ambulans secara bijak dan bertanggung jawab,");
	posisi(80, 6);
	printf("hanya dalam kondisi yang benar - benar membutuhkan.");

	posisi(80, 8);
	printf("Penyalahgunaan dapat menghambat pelayanan darurat");
	posisi(80, 9);
	printf("bagi pasien lain yang membutuhkan pertolongan.");
}

void tampilanhistori(int x, int y) {

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	ambiltanggal();
	posisi(5, 2);
	printf("Tanggal sekarang  : %s\n", date);
}

void aksipanggil() {
	int rs_id;

	// ===== TAMPILAN PILIH RS =====
	tampilanpanggil();

	rs_id = listrs(27, 6);
	if (rs_id == -1) return;

	// ===== KONFIRMASI RS =====
	kotak(32, 1, 26, 8, 211, 211, 211, 250, 250, 250);
	posisi(27, 6);
	printf("> %s", getNamaRSById(rs_id));

	posisi(27, 8);
	printf("Rumah Sakit dipilih : %s", getNamaRSById(rs_id));
	posisi(27, 9);
	printf("Tekan ENTER untuk lanjut...");
	getch();

	// ===== LANJUT PILIH AMBULANS =====
	pesan_ambulans(rs_id);
}


void profil() {
	tampilan_profil_user();
}