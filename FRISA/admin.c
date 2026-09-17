#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 

void loginadmin()
{
		borderutama();
		bordercs(75, 15, 32, 10, 15, 175, 212, 216, 228, 255);
		loginlogo(50, 2);

		if (formlogin_admin()) {
			halamanadmin();  
			return;
	}
}


int formlogin_admin()
{
	char username[50];

	rgbbgt(215, 227, 254);
	rgbtext(49, 175, 212);

	posisi(55, 11);
	printf("Form Login Admin");

	posisi(55, 12);
	printf("==============================");

	posisi(40, 15);
	printf("Masukkan Username : ");
	posisi(40, 16);
	printf("                    ");

	posisi(40, 18);
	printf("Masukkan Password : ");
	posisi(40, 19);
	printf("                    ");

	posisi(60, 15);
	val_uname();

	posisi(60, 18);
	starshow();

	if (loginsql_admin(get_username, input_password)) {
		posisi(55, 21);
		printf("LOGIN ADMIN BERHASIL\n");
		Sleep(1000);
		return 1;
	}
	else {
		posisi(55, 21);
		printf("USERNAME ATAU PASSWORD SALAH");
		getch();
		return 0;
	}

	resetcolor();
}


void halamanadmin() {
	bordertop();
	borderutama();
	bordercs(142, 7, 0, 31, 250, 250, 250, 211, 211, 211);
	borderhorizontal(0, 30, 0);
	borderhorizontal(0, 31, 1);
	do
	{
		int pilihan;
		pilihan = menu_admin();
		switch (pilihan) {
		case 1: tampil_semua_laporan(33, 5); break;
		case 2: menu_akun(); break;
		case 3: menu_ambulans(); break;
		case 0: logout_admin(); tampilan(); break;
		case 4: menu_rumah_sakit(); break;
		}
	} while (1);

}


void menuakunabal() {
	int pilihanMenu = 0;

	if (pilihanMenu == 1) {
		kotak(18, 3, 31, 3, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
		rgbbgt(250, 250, 250);
		posisi(36 + 2, 4); printf("User");
		tampil_user(7, 7);
	}
	else {
		kotak(18, 3, 31, 3, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
		rgbbgt(250, 250, 250);
		posisi(36 + 2, 4); printf("User");
	}

	// SUPIR
	if (pilihanMenu == 2) {
		kotak(19, 3, 59, 3, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		tampil_supir(29, 7);
		posisi(64 + 2, 4); printf("supir");
	}
	else {
		kotak(19, 3, 59, 3, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
		rgbbgt(250, 250, 250);
		posisi(64 + 2, 4); printf("supir");
	}

	// ADMIN
	if (pilihanMenu == 3) {
		kotak(19, 3, 88, 3, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
		rgbbgt(250, 250, 250);
		posisi(93 + 2, 4); printf("Admin");
	}
	else {
		kotak(19, 3, 88, 3, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
		rgbbgt(250, 250, 250);
		posisi(93 + 2, 4); printf("Admin");
	}
}

int menu_akun() {
	int pilihanMenu = 1;
	char ch;

	while (1) {

		// ===== USER =====
		if (pilihanMenu == 1) {
			kotak(18, 3, 31, 3, 0, 79, 255, 250, 250, 250);
			rgbtext(0, 79, 255); rgbbgt(250, 250, 250);
			posisi(36 + 2, 4); printf("User");
			tampil_user(7, 7);
		}
		else {
			kotak(18, 3, 31, 3, 36, 191, 165, 250, 250, 250);
			rgbtext(36, 191, 165); rgbbgt(250, 250, 250);
			posisi(36 + 2, 4); printf("User");
		}

		// ===== SUPIR =====
		if (pilihanMenu == 2) {
			kotak(19, 3, 59, 3, 0, 79, 255, 250, 250, 250);
			rgbtext(0, 79, 255); rgbbgt(250, 250, 250);
			posisi(64 + 2, 4); printf("supir");
			rgbtext(0, 79, 255);
			rgbbgt(211, 211, 211);
			tampil_supir(29, 7);
		}
		else {
			kotak(19, 3, 59, 3, 36, 191, 165, 250, 250, 250);
			rgbtext(36, 191, 165); rgbbgt(250, 250, 250);
			posisi(64 + 2, 4); printf("supir");
		}

		// ===== ADMIN =====
		if (pilihanMenu == 3) {
			kotak(19, 3, 88, 3, 0, 79, 255, 250, 250, 250);
			rgbtext(0, 79, 255); rgbbgt(250, 250, 250);
			posisi(93 + 2, 4); printf("Admin");
			kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
			tampil_admin(45, 7);
		}
		else {
			kotak(19, 3, 88, 3, 36, 191, 165, 250, 250, 250);
			rgbtext(36, 191, 165); rgbbgt(250, 250, 250);
			posisi(93 + 2, 4); printf("Admin");
		}

		// ===== INPUT =====
		ch = getch();

		if (ch == 75 && pilihanMenu > 1) {
			kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
			pilihanMenu--;
		}
		if (ch == 77 && pilihanMenu < 3) {
			kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
			pilihanMenu++;
		}

		if (ch == 13) {
			submenu_akun(pilihanMenu);
		}

		if (ch == 27) break;
	}
}

void menu_ambulansabal() {
	int pilihanMenu = 0;

	if (pilihanMenu == 1) {
		kotak(30, 3, 4, 6, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255); rgbbgt(250, 250, 250);
	}
	else {
		kotak(30, 3, 4, 6, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165); rgbbgt(250, 250, 250);
	}

	posisi(7, 7); printf("Tambah Ambulans");


	if (pilihanMenu == 2) {
		kotak(30, 3, 4, 10, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255); rgbbgt(250, 250, 250);
	}
	else {
		kotak(30, 3, 4, 10, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165); rgbbgt(250, 250, 250);
	}
	posisi(8, 11); printf("Edit Ambulans");

	if (pilihanMenu == 3) {
		kotak(30, 3, 4, 14, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255); rgbbgt(250, 250, 250);
	}
	else {
		kotak(30, 3, 4, 14, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165); rgbbgt(250, 250, 250);
	}
	posisi(8, 15); printf("Hapus Ambulans");

	if (pilihanMenu == 4) {
		kotak(30, 3, 4, 18, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255); rgbbgt(250, 250, 250);
	}
	else {
		kotak(30, 3, 4, 18, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165); rgbbgt(250, 250, 250);
	}
	posisi(9, 19); printf("Lihat Tabel");

}

void tampil_menu_rs(int pilihanMenu)
	
{
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);;
	posisi(7, 5);
	printf("MENU RUMAH SAKIT");

	if (pilihanMenu == 1) {
		kotak(30, 3, 4, 6, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 6, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(7, 7);
	printf("Tambah RS");

	if (pilihanMenu == 2) {
		kotak(30, 3, 4, 10, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 10, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(8, 11);
	printf("Edit RS");

	if (pilihanMenu == 3) {
		kotak(30, 3, 4, 14, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 14, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(8, 15);
	printf("Hapus RS");


	if (pilihanMenu == 4) {
		kotak(30, 3, 4, 18, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 18, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(9, 19);
	printf("Tabel RS");
}

void menurshover() {
	int pilihanMenu = 0;
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);;
	posisi(7, 5);
	printf("MENU RUMAH SAKIT");

	if (pilihanMenu == 1) {
		kotak(30, 3, 4, 6, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 6, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(7, 7);
	printf("Tambah RS");

	if (pilihanMenu == 2) {
		kotak(30, 3, 4, 10, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 10, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(8, 11);
	printf("Edit RS");

	if (pilihanMenu == 3) {
		kotak(30, 3, 4, 14, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 14, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(8, 15);
	printf("Hapus RS");


	if (pilihanMenu == 4) {
		kotak(30, 3, 4, 18, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 18, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(9, 19);
	printf("Tabel RS");
}


void submenu_akun(int pilihanMenu)
{
	int pilihanSub = 1;
	char ch;

	while (1)
	{

		if (pilihanMenu == 1)
		{

			kotak(19, 5, 59, 23, 0, 79, 255, 250, 250, 250);
			rgbtext(36, 191, 165);
			rgbbgt(250, 250, 250);
			posisi(61, 26);
			printf("  Lihat Tabel");

			pilihanSub = 1;
		}


		if (pilihanMenu == 2)
		{
			kotak(19, 3, 59, 25, 0, 79, 255, 250, 250, 250);
			rgbtext(0, 79, 255);
			rgbbgt(250, 250, 250);
			posisi(61, 26);
			printf("  Lihat Tabel");

			pilihanSub = 1;
		}

		if (pilihanMenu == 3)
		{
			// Tambah Admin
			if (pilihanSub == 1) {
				kotak(18, 3, 29, 25, 0, 79, 255, 250, 250, 250);
				rgbtext(0, 79, 255);
			}
			else {
				kotak(18, 3, 29, 25, 36, 191, 165, 250, 250, 250);
				rgbtext(36, 191, 165);
			}
			rgbbgt(250, 250, 250);
			posisi(31, 26); printf("Tambah Admin");

			// Edit Admin
			if (pilihanSub == 2) {
				kotak(19, 3, 51, 25, 0, 79, 255, 250, 250, 250);
				rgbtext(0, 79, 255);
			}
			else {
				kotak(19, 3, 51, 25, 36, 191, 165, 250, 250, 250);
				rgbtext(36, 191, 165);
			}
			rgbbgt(250, 250, 250);
			posisi(53, 26); printf("Edit Admin");

			// Hapus Admin
			if (pilihanSub == 3) {
				kotak(18, 3, 74, 25, 0, 79, 255, 250, 250, 250);
				rgbtext(0, 79, 255);
			}
			else {
				kotak(18, 3, 74, 25, 36, 191, 165, 250, 250, 250);
				rgbtext(36, 191, 165);
			}
			rgbbgt(250, 250, 250);
			posisi(76, 26); printf("Hapus Admin");

			// Lihat Tabel
			if (pilihanSub == 4) {
				kotak(18, 3, 96, 25, 0, 79, 255, 250, 250, 250);
				rgbtext(0, 79, 255);
			}
			else {
				kotak(18, 3, 96, 25, 36, 191, 165, 250, 250, 250);
				rgbtext(36, 191, 165);
			}
			rgbbgt(250, 250, 250);
			posisi(98, 26); printf("Lihat Tabel");

		}

		// ================= INPUT =================
		ch = getch();

		// navigasi HANYA ADMIN
		if (pilihanMenu == 3)
		{
			if (ch == 75 && pilihanSub > 1)
				pilihanSub--;

			if (ch == 77 && pilihanSub < 4)
				pilihanSub++;
		}

		if (ch == 27)
			break;

		if (ch == 13)
		{
			if (pilihanMenu == 1)
			{
				kotak(131, 3, 3, 25, 211, 211, 211, 211, 211, 211);
				tampil_semua_user(7, 7);
			}

			if (pilihanMenu == 2) {
				kotak(131, 3, 3, 25, 211, 211, 211, 211, 211, 211);
				tampil_semua_supir(29, 7);
			}

			if (pilihanMenu == 3 && pilihanSub == 1) tambah_admin();
			if (pilihanMenu == 3 && pilihanSub == 2) edit_admin();
			if (pilihanMenu == 3 && pilihanSub == 3) hapus_admin();
			if (pilihanMenu == 3 && pilihanSub == 4) tampil_semua_admin(45, 7);

			kotak(131, 3, 3, 25, 211, 211, 211, 211, 211, 211);
			break;
		}
	}

	kotak(131, 3, 3, 25, 211, 211, 211, 211, 211, 211);
}







void tampilandashboard() {

	int totaluser, totalrs, totalambulans, totallaporan, ambulansfree;
	totaluser = hitung_total_user();
	totalrs = hitung_total_rs();
	totalambulans = hitung_total_ambulans();
	totallaporan = hitung_total_laporan();
	ambulansfree = hitung_ambulans_free();

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	ambiltanggal();

	posisi(5, 3);
	printf("Tanggal sekarang  : %s\n", date);

	posisi(5, 12);
	printf("Jumlah User Terdaftar   : %d", totaluser);

	posisi(5, 14);
	printf("Jumlah Rumah Sakit      : %d", totalrs);

	posisi(5, 16);
	printf("Jumlah Ambulans         : %d", totalambulans);

	posisi(5, 18);
	printf("Jumlah Ambulans Free    : %d", ambulansfree);

	posisi(5, 20);
	printf("Jumlah Laporan Berjalan : %d", totallaporan);;
}

void tampilanakun() {
	menu_akun();
}

void tambah_admin() {
	kotak(121, 13, 7, 7, 211, 211, 211, 211, 211, 211);
	posisi(48, 7);
	rgbtext(255, 0, 0);
	rgbbgt(211, 211, 211);
	printf("FORM PENAMBAHAN ADMIN");

	posisi(22, 9);
	printf("Masukkan Nama     : ");
	posisi(22, 10);

	posisi(22, 12);
	printf("Masukkan Username : ");
	posisi(22, 13);

	posisi(22, 14);
	printf("Masukkan Password : ");
	posisi(22, 15);

	posisi(43, 9);
	if(!val_nama()) return;
	posisi(43, 12);
	if(!val_uname()) return;
	posisi(43, 14);
	if(!val_pass_admin()) return;
	tambahadminsql();

	kotak(121, 13, 7, 7, 211, 211, 211, 211, 211, 211);
}

void edit_admin() {
	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	edit_adminsql();
}

void hapus_admin() {
	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	hapus_adminsql();
}

void tampilan_ambulans() {

	kotak(75, 13, 60, 7, 211, 211, 211, 211, 211, 211);
	tampil_supir_ambulans(60, 7);
	menu_ambulansabal();
}

void tambah_ambulans() {
	tambah_ambulans_dan_supir();
}

void edit_ambulans() {
	edit_ambulans_dan_supir();
}

void hapus_ambulans() {
	hapus_ambulans_dan_supir();
}

void menu_rumah_sakit()
{
	int pilihanMenu = 1;
	char key;

	while (1) {
		tampil_menu_rs(pilihanMenu);

		key = getch();

		if (key == 72 && pilihanMenu > 1) {
			pilihanMenu--;   // ↑
		}
		else if (key == 80 && pilihanMenu < 4) {
			pilihanMenu++;   // ↓
		}
		else if (key == 13) { // ENTER
			if (pilihanMenu == 1) tambah_rs();
			else if (pilihanMenu == 2) edit_rs();
			else if (pilihanMenu == 3) hapus_rs();
			else if (pilihanMenu == 4) tampil_rs_pagination(60, 7, 1);
		}
		else if (key == 27) { // ESC
			return;
		}
	}
}
