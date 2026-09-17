#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 


void borderhorizontal(int x, int y, int type) {
	// type = 0 -> border atas
	// type = 1 -> border bawah
	posisi(x, y);

	for (int i = 1; i <= 142; i++) {
		if (i == 1)
		{
			printf("╠");
		}
		if (i == 142)
		{
			printf("╣");
		}
		if (i % 3 == 0) {
			if (type == 0) {
				printf("╦");
			}
			else {
				printf("╩");
			}
		}
		else if (i > 1 && i < 142) {
			printf("═");
		}
	}
}

void kotak(int panjang, int lebar, int x, int y,
	int rdal, int gdal, int bdal,
	int rlu, int glu, int blu)
{
	int i, j;

	/* Baris atas */
	posisi(x, y);
	rgbtext(rdal, gdal, bdal);
	for (j = 0; j < panjang; j++)
		printf("█");

	for (i = 1; i < lebar - 1; i++) {
		posisi(x, y + i);

		rgbtext(rdal, gdal, bdal);
		printf("█");

		rgbtext(rlu, glu, blu);
		for (j = 0; j < panjang - 2; j++)
			printf("█");

		rgbtext(rdal, gdal, bdal);
		printf("█");
	}

	if (lebar > 1) {
		posisi(x, y + lebar - 1);
		rgbtext(rdal, gdal, bdal);
		for (j = 0; j < panjang; j++)
			printf("█");
	}

	resetcolor();
	resetbg();
}


void bordercs(int panjang, int lebar, int x, int y, int rdal, int gdal, int bdal, int rlu, int glu, int blu) {
	for (int i = 1; i <= lebar; i++) {
		posisi(x, y + i - 1);

		for (int j = 1; j <= panjang; j++) {

			if (i == 1 || i == lebar || j == 1 || j == panjang) {
				if (i == 1 && j == 1)
				{
					rgbtext(rdal, gdal, bdal);
					rgbbgt(rlu, glu, blu);
					printf("╔");
				}
				else if (j == 1 && i == lebar)
				{
					rgbtext(rdal, gdal, bdal);
					rgbbgt(rlu, glu, blu);
					printf("╚");
				}
				else if (i == 1 && j == panjang)
				{
					rgbtext(rdal, gdal, bdal);
					rgbbgt(rlu, glu, blu);
					printf("╗");
				}
				else if (i == lebar && j == panjang)
				{
					rgbtext(rdal, gdal, bdal);
					rgbbgt(rlu, glu, blu);
					printf("╝");
				}
				else if (i == 1 || i == lebar)
				{
					rgbbgt(rlu, glu, blu);
					rgbtext(rdal, gdal, bdal);
					printf("═");
					resetcolor();
				}
				else if (j == 1 || j == panjang)
				{
					rgbbgt(rlu, glu, blu);
					rgbtext(rdal, gdal, bdal);
					printf("║");
					resetcolor();
				}
			}
			else {
				rgbtext(rlu, glu, blu);
				printf("█");
				resetcolor();
			}
		}
	}
}


void borderutama() {
	rgbbgt(107, 129, 140);
	for (int x = 0; x <= 37; x++)
	{
		for (int y = 0; y <= 141; y++)
		{
			if (x == 0)
			{
				posisi(y, x);
				if (y == 0 && x == 0)
				{
					printf("╔");
				}
				else if (y == 141 && x == 0)
				{
					printf("╗");
				}
				else
				{
					printf("═");
				}
			}
			else
			{
				posisi(y, x);
				if (y == 0 && x <= 36 || y == 141 && x <= 36)
				{
					printf("║");
				}
				else if (x == 37 && y > 0 && y < 141)
				{
					printf("═");
				}
				else if (y == 0 && x == 37)
				{
					posisi(y, x);
					printf("╚");
				}
				else if (y == 141 && x == 37)
				{
					printf("╝");
				}
				else {
					printf(" ");
				}
			}
		}
	}
	resetcolor();
}

void bordertop() {
	for (int x = 0; x < 30; x++)
	{
		for (int y = 0; y <= 141; y++)
		{
			if (x == 0)
			{
				posisi(y, x);
				if (y == 0)
				{
					printf("╒");
				}
				else if (y == 141)
				{
					printf("╕");
				}
				else
				{
					printf("═");
				}
			}
			else
			{
				posisi(y, x);
				if (y == 0 && x < 29 || y == 141 && x < 29)
				{
					printf("│");
				}
				else if (x == 29 && y > 0 && y < 141)
				{
					printf("─");
				}
				else if (y == 0 && x == 29)
				{
					printf("└");
				}
				else if (y == 141 && x == 29)
				{
					printf("┘");
				}
				else {
					printf(" ");
				}
			}
		}
	}
}

void frisa() {
	rgbbgt(107, 129, 140);
	rgbtext(128, 0, 0);
	posisi(25, 2);	printf("  F A S T   R E S C U E S   I N T E L L I G E N C E   S M A R T   A M B U L A N C E   \n");
	posisi(25, 2 + 1);	printf("╔════════════╗   ╔════════════════╗    ╔════╗    ╔═══════════════╗    ╔══════════════╗\n");
	posisi(25, 2 + 2);	printf("║ ████████████|  ║ ████████████████|   ║ ████|   ║ ███████████████|   ║ ██████████████|\n");
	posisi(25, 2 + 3);	printf("║ ████████████:  ║ ████████████████:   ║ ████:   ║ ███████████████:   ║ ██████████████:\n");
	posisi(25, 2 + 4);	printf("║ ████|          ║ █████      █████|   ║ ████|   ║ ████|              ║ █████    █████|\n");
	posisi(25, 2 + 5);	printf("║ ████████████:  ║ █████      █████:   ║ ████:   ║ ████:              ║ █████    █████:\n");
	posisi(25, 2 + 6);	printf("║ ████████████:  ║ ████████████████:   ║ ████:   ║ ███████████████:   ║ ██████████████:\n");
	posisi(25, 2 + 7);	printf("║ ████|          ║ ████████████████|   ║ ████|   ║ ███████████████|   ║ ██████████████|\n");
	posisi(25, 2 + 8);	printf("║ ████:          ║ ███  ╚╗████:        ║ ████:   ╚══════════╗ ████:   ║ ██████████████:\n");
	posisi(25, 2 + 9);	printf("║ ████|          ║ ███   ╚═╗████|      ║ ████|   ╔══════════╝ ████|   ║ █████  ║ █████|\n");
	posisi(25, 2 + 10);	printf("║ ████:          ║ ███     ╚═╗████:    ║ ████:   ║ ███████████████:   ║ █████  ║ █████:\n");
	posisi(25, 2 + 11);	printf("╚═████|          ╚═███       ╚═████|   ╚═████|   ╚═███████████████|   ╚═█████  ╚═█████|\n");
	resetcolor();
}


void btn_hover(int x, int y, const char* textbtn)
{
	int width = 9;
	int len = strlen(textbtn);
	if (len > width) len = width;

	int left = (width - len) / 2;
	int right = width - len - left;

	posisi(x + 1, y);
	printf("╔════╦═════════╗");

	posisi(x, y + 1);
	printf("╔╝ █  ║         ║");

	posisi(x, y + 2);
	printf("║ ███ ║");

	for (int i = 0; i < left; i++)
		printf(" ");

	printf("%.*s", len, textbtn);

	for (int i = 0; i < right; i++)
		printf(" ");

	printf("║");

	posisi(x, y + 3);
	printf("╚╗ █  ║         ║");

	posisi(x + 1, y + 4);
	printf("╚════╩═════════╝");
}



void btn_iddle(int x, int y, const char* text) {
	int width = 9; // lebar area teks
	int len = strlen(text);
	if (len > width) len = width; // kalau lebih panjang, potong

	int left = (width - len) / 2;          // spasi kiri
	int right = width - len - left;        // spasi kanan

	posisi(x + 1, y);
	printf("┌────┬─────────┐");

	posisi(x, y + 1);
	printf("┌┘ ░  │         │");

	posisi(x, y + 2);
	printf("│ ░░░ │");


	for (int i = 0; i < left; i++) printf(" ");

	printf("%.*s", len, text);

	for (int i = 0; i < right; i++) printf(" ");



	printf("│");

	posisi(x, y + 3);
	printf("└┐ ░  │         │");

	posisi(x + 1, y + 4);
	printf("└────┴─────────┘");
}


void tampilbuttonuser(int pilihan) {

	// DASHBOARD
	if (pilihan == 1) {
		rgbbgt(0, 79, 255);
		btn_hover(21, 32, "PANGGIL");
		tampilanpanggil();
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(21, 32, "PANGGIL");
		resetcolor();
	}

	// AKUN
	if (pilihan == 2) {
		rgbbgt(0, 79, 255);
		btn_hover(47, 32, "LAPORAN");
		tampilanlaporan();
		tampilan_laporan_user(30, 6);
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(47, 32, "LAPORAN");
		resetcolor();
	}

	// AMBULANS		  
	if (pilihan == 3) {
		rgbbgt(0, 79, 255);
		btn_hover(73, 32, "PROFIL");
		tampilan_profil_user();
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(73, 32, "PROFIL");
		resetcolor();
	}

	// LAPORAN		  
	if (pilihan == 0) {
		rgbbgt(0, 79, 255);
		btn_hover(99, 32, "EXIT");
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(99, 32, "EXIT");
		resetcolor();
	}
}

void tampilbuttonsupir(int pilihan) {

	// DASHBOARD
	if (pilihan == 1) {
		rgbbgt(0, 79, 255);
		btn_hover(21, 32, "TUGAS");
		tampil_tugas_supir(3, 3);
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(21, 32, "TUGAS");
		resetcolor();
	}

	// AKUN
	if (pilihan == 2) {
		rgbbgt(0, 79, 255);
		tampilan_profil_supir();
		btn_hover(47, 32, "PROFIL");
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(47, 32, "PROFIL");
		resetcolor();
	}

	// LAPORAN		  
	if (pilihan == 0) {
		rgbbgt(0, 79, 255);
		btn_hover(73, 32, "EXIT");
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(73, 32, "EXIT");
		resetcolor();
	}
}

void tampilbuttonadmin(int pilihan) {

	// DASHBOARD
	if (pilihan == 1) {
		rgbbgt(0, 79, 255);
		btn_hover(10, 32, "DASHBOARD");
		tampilandashboard();
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(10, 32, "DASHBOARD");
		resetcolor();
	}

	// AKUN
	if (pilihan == 2) {
		rgbbgt(0, 79, 255);
		btn_hover(36, 32, "AKUN");
		menuakunabal();
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(36, 32, "AKUN");
		resetcolor();
	}

	// AMBULANS
	if (pilihan == 3) {
		rgbbgt(0, 79, 255);
		btn_hover(62, 32, "AMBULANS");
		kotak(75, 13, 60, 7, 211, 211, 211, 211, 211, 211);
		menu_ambulansabal();
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(62, 32, "AMBULANS");
		resetcolor();
	}

	// RS
	if (pilihan == 4) {
		rgbbgt(0, 79, 255);
		btn_hover(88, 32, "RS");
		menurshover();
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(88, 32, "RS");
		resetcolor();
	}

	// EXIT
	if (pilihan == 0) {
		rgbbgt(0, 79, 255);
		btn_hover(114, 32, "EXIT");
		resetcolor();
	}
	else {
		rgbbgt(49, 175, 212);
		btn_iddle(114, 32, "EXIT");
		resetcolor();
	}
}




void tampilmenuutama(int pilihan) {

	// Login
	if (pilihan == 1) {
		kotak(19, 9, 15, 20, 128, 0, 0, 0, 0, 0);
		posisi(20, 24);
		rgbtext(128, 0, 0);
		printf("L O G I N");
		resetcolor();
	}
	else {
		kotak(19, 9, 15, 20, 255, 255, 255, 0, 0, 0);
		posisi(22, 24);
		rgbtext(255, 255, 255);
		printf("LOGIN");
		resetcolor();
	}

	// Daftar
	if (pilihan == 2) {
		kotak(19, 9, 45, 20, 128, 0, 0, 0, 0, 0);
		posisi(49, 24);
		rgbtext(128, 0, 0);
		printf("S I G N  U P");
		resetcolor();
	}
	else {
		kotak(19, 9, 45, 20, 255, 255, 255, 0, 0, 0);
		posisi(52, 24);
		printf("SIGNUP");
		resetcolor();
	}

	// About		  
	if (pilihan == 3) {
		kotak(19, 9, 75, 20, 128, 0, 0, 0, 0, 0);
		posisi(80, 24);
		rgbtext(128, 0, 0);
		printf("A B O U T");
		resetcolor();
	}
	else {
		kotak(19, 9, 75, 20, 255, 255, 255, 0, 0, 0);
		posisi(82, 24);
		printf("ABOUT");
		resetcolor();
	}

	// Exit		  
	if (pilihan == 4) {
		kotak(19, 9, 105, 20, 128, 0, 0, 0, 0, 0);
		posisi(111, 24);
		rgbtext(128, 0, 0);
		printf("E X I T");
		resetcolor();
	}
	else {
		kotak(19, 9, 105, 20, 255, 255, 255, 0, 0, 0);
		posisi(113, 24);
		printf("EXIT");
		resetcolor();
	}

}

void tampil_menu_ambulans(int pilihanMenu) {

	// ===== MENU 1 : TAMBAH AMBULANS =====
	if (pilihanMenu == 1) {
		kotak(30, 3, 4, 6, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 6, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(7, 7); printf("Tambah Ambulans");


	// ===== MENU 2 : EDIT AMBULANS =====
	if (pilihanMenu == 2) {
		kotak(30, 3, 4, 10, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 10, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(8, 11); printf("Edit Ambulans");


	// ===== MENU 3 : HAPUS AMBULANS =====
	if (pilihanMenu == 3) {
		kotak(30, 3, 4, 14, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 14, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(8, 15); printf("Hapus Ambulans");


	// ===== MENU 4 : LIHAT TABEL =====
	if (pilihanMenu == 4) {
		kotak(30, 3, 4, 18, 0, 79, 255, 250, 250, 250);
		rgbtext(0, 79, 255);
	}
	else {
		kotak(30, 3, 4, 18, 36, 191, 165, 250, 250, 250);
		rgbtext(36, 191, 165);
	}
	posisi(9, 19); printf("Lihat Tabel");
}


void tampilmenurole(int pilihanrole) {

	// Login
	if (pilihanrole == 1) {
		kotak(19, 9, 15, 20, 128, 0, 0, 0, 0, 0);
		posisi(20, 24);
		rgbtext(128, 0, 0);
		printf("A D M I N");
		resetcolor();
	}
	else {
		kotak(19, 9, 15, 20, 255, 255, 255, 0, 0, 0);
		posisi(22, 24);
		rgbtext(255, 255, 255);
		printf("ADMIN");
		resetcolor();
	}

	// Daftar
	if (pilihanrole == 2) {
		kotak(19, 9, 45, 20, 128, 0, 0, 0, 0, 0);
		posisi(49, 24);
		rgbtext(128, 0, 0);
		printf("S U P I R");
		resetcolor();
	}
	else {
		kotak(19, 9, 45, 20, 255, 255, 255, 0, 0, 0);
		posisi(52, 24);
		printf("SUPIR");
		resetcolor();
	}

	// About		  
	if (pilihanrole == 3) {
		kotak(19, 9, 75, 20, 128, 0, 0, 0, 0, 0);
		posisi(80, 24);
		rgbtext(128, 0, 0);
		printf("U S E R");
		resetcolor();
	}
	else {
		kotak(19, 9, 75, 20, 255, 255, 255, 0, 0, 0);
		posisi(82, 24);
		printf("USER");
		resetcolor();
	}
}

void border() {

	rgbbgt(255, 255, 255);
	rgbtext(0, 0, 0);
	bordertop();
	resetcolor();

	rgbbgt(212, 211, 192);
	rgbtext(0, 0, 0);
	posisi(0, 30);
	printf("╔");
	borderhorizontal(1, 30, 0);
	posisi(141, 30);
	printf("╗");

	posisi(0, 31);
	printf("╠");
	borderhorizontal(1, 31, 1);
	posisi(141, 31);
	printf("╣");

	resetcolor();


}

void ambulance1(int r, int g, int b, int x, int y, int rdal, int gdal, int bdal) {
	rgbtext(255, 255, 255);
	posisi(x, y);	 printf("████████████████║═"); rgbtext(r, g, b); printf("███"); resetcolor(); rgbbgt(rdal, gdal, bdal); rgbtext(255, 255, 255); printf("╗");
	rgbtext(255, 255, 255);
	posisi(x, y + 1); printf("██████"); rgbtext(128, 0, 0); printf("█"); resetcolor(); rgbtext(255, 255, 255); printf("█████████║█████");
	posisi(x, y + 2); printf("█████");  rgbtext(128, 0, 0); printf("███");resetcolor(); rgbtext(255, 255, 255); printf("████████║    █");
	posisi(x, y + 3); printf("██████"); rgbtext(128, 0, 0); printf("█"); resetcolor(); rgbtext(255, 255, 255); printf("█████████║    ████");
	posisi(x, y + 4); printf("████████████████║████████");
	rgbtext(0, 0, 0);
	rgbbgt(rdal, gdal, bdal);
	posisi(x, y + 5); printf("█ ▐███▌ ████████ ▐███▌ ███");
	posisi(x, y + 6); printf("  █   █          █   █");
	posisi(x, y + 7); printf("  ▐███▌          ▐███▌");
	resetcolor();
}

void ambulance2(int r, int g, int b, int x, int y, int rdal, int gdal, int bdal) {
	rgbtext(255, 255, 255);
	posisi(x, y);	 printf("████████████████║═"); rgbtext(r, g, b); printf("███"); resetcolor(); rgbbgt(rdal, gdal, bdal); rgbtext(255, 255, 255); printf("╗");
	rgbtext(255, 255, 255);
	posisi(x, y + 1); printf("██████"); rgbtext(128, 0, 0); printf("█"); resetcolor(); rgbtext(255, 255, 255); printf("█████████║█████");
	posisi(x, y + 2); printf("█████");  rgbtext(128, 0, 0); printf("███");resetcolor(); rgbtext(255, 255, 255); printf("████████║    █");
	posisi(x, y + 3); printf("██████"); rgbtext(128, 0, 0); printf("█"); resetcolor(); rgbtext(255, 255, 255); printf("█████████║    ████");
	posisi(x, y + 4); printf("████████████████║████████");
	rgbtext(0, 0, 0);
	rgbbgt(rdal, gdal, bdal);
	posisi(x, y + 5); printf("█ ▄▄▄▄▄ ████████ ▄▄▄▄▄ ███");
	posisi(x, y + 6); printf("  █   █          █   █");
	posisi(x, y + 7); printf("  ▐███▌          ▐███▌");
	resetcolor();
}

void ambulance3(int r, int g, int b, int x, int y, int rdal, int gdal, int bdal) {
	rgbtext(255, 255, 255);
	posisi(x, y);	 printf("████████████████║═"); rgbtext(r, g, b); printf("███"); resetcolor(); rgbbgt(rdal, gdal, bdal); rgbtext(255, 255, 255); printf("╗");
	rgbtext(255, 255, 255);
	posisi(x, y + 1); printf("██████"); rgbtext(128, 0, 0); printf("█"); resetcolor(); rgbtext(255, 255, 255); printf("█████████║█████");
	posisi(x, y + 2); printf("█████");  rgbtext(128, 0, 0); printf("███");resetcolor(); rgbtext(255, 255, 255); printf("████████║    █");
	posisi(x, y + 3); printf("██████"); rgbtext(128, 0, 0); printf("█"); resetcolor(); rgbtext(255, 255, 255); printf("█████████║    ████");
	posisi(x, y + 4); printf("████████████████║████████");
	rgbtext(0, 0, 0);
	rgbbgt(rdal, gdal, bdal);
	posisi(x, y + 5); printf("█ ▐███▌ ████████ ▐███▌ ███");
	posisi(x, y + 6); printf("  █   █          █   █");
	posisi(x, y + 7); printf("  ▀▀▀▀▀          ▀▀▀▀▀");
	resetcolor();
}

void daftarlogo(int x, int y) {
	rgbtext(128, 0, 0);
	rgbbgt(107, 129, 140);
	posisi(x, y + 0);  printf("╔═══════╗    ╔══════╗  ╔══════╗ ╔══════╗    ╔══════╗   ╔═══════╗");
	posisi(x, y + 1);  printf("║███████▌█  ╔╝███████  ║███████ ║████████  ╔╝███████   ║█████████");
	posisi(x, y + 2);  printf("║██      ██ ║██     ██ ║██      ╚══╗██     ║██     ██  ║██     ██");
	posisi(x, y + 3);  printf("║██      ██ ║██     ██ ║███████    ║██     ║██     ██  ║██     ██");
	posisi(x, y + 4);  printf("║██      ██ ║█████████ ║██         ║██     ║█████████  ║█████████");
	posisi(x, y + 5);  printf("║██      ██ ║██     ██ ║██         ║██     ║██     ██  ║██   ██");
	posisi(x, y + 6);  printf("╚███████▌█  ╚██     ██ ╚██         ╚██     ╚██     ██  ╚██     ██");
	resetcolor();
}

void loginlogo(int x, int y) {
	rgbtext(128, 0, 0);
	rgbbgt(107, 129, 140);

	posisi(x, y + 0); printf("██╗      ██████╗   ██████╗  ██╗ ███╗   ██╗");
	posisi(x, y + 1); printf("██║     ██╔═══██╗ ██╔════╝  ██║ ████╗  ██║");
	posisi(x, y + 2); printf("██║     ██║   ██║ ██║  ███╗ ██║ ██╔██╗ ██║");
	posisi(x, y + 3); printf("██║     ██║   ██║ ██║   ██║ ██║ ██║╚██╗██║");
	posisi(x, y + 4); printf("██╚═╗   ██║   ██║ ██║   ██║ ██║ ██║ ╚████║");
	posisi(x, y + 5); printf("██████  ╚██████╔╝ ╚██████╔╝ ██║ ██║  ╚███║");
	posisi(x, y + 6); printf("         ╚═════╝   ╚═════╝  ╚═╝ ╚═╝   ╚══╝");

	resetcolor();
}



int daftar()
{
	daftarlogo(40, 2);
	bordercs(110, 25, 15, 10, 49, 175, 212, 216, 228, 255);

	if (!formdaftar())
	tampilan();
		return 0;   // ⬅️ ESC naik ke menu

	resetcolor();
	return 1;
}


void ceklis(int bpjs) {
	if (bpjs == 1) {
		posisi(51, 20);
		printf("√");
	}
	else {
		posisi(51, 20);
		printf(" ");
	}

	if (bpjs == 2) {
		posisi(62, 20);
		printf("√");
	}
	else {
		posisi(62, 20);
		printf(" ");
	}
}

void warning_daftar() {

	for (int i = 0; i < 7; i++)
	{
		if (i == 0 || i == 2 || i == 4)
		{
			posisi(41, 27);
			rgbbgt(215, 227, 254);
			rgbtext(255, 0, 0);
			printf("!! Password minimal terdiri dari huruf, angka, simbol, dan minimal 10 karakter !!");
			Sleep(500);
		}
		else if (i == 6)
		{
			posisi(41, 27);
			rgbtext(215, 227, 254);
			printf("█████████████████████████████████████████████████████████████████████████████████");
			Sleep(500);
		}
		else
		{
			posisi(41, 27);
			rgbtext(0, 0, 0);
			rgbbgt(215, 227, 254);
			printf("!! Password minimal terdiri dari huruf, angka, simbol, dan minimal 10 karakter !!");
			Sleep(500);
		}
	}
}

int formdaftar() {
	int bpjs = 1;
	char key;

	posisi(55, 11);
	printf("Form Pendaftaran Pengguna Baru");
	posisi(55, 12);
	printf("==============================");
	posisi(20, 14);
	printf("NIK                : ");
	posisi(20, 15);
	printf("                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
	posisi(20, 16);
	printf("Nama               : ");
	posisi(20, 17);
	printf("                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
	posisi(20, 18);

	printf("Tanggal Lahir      : ");
	posisi(44, 18); printf("/"); posisi(49, 18); printf("/");
	posisi(41, 19); printf("¯¯"); posisi(46, 19); printf("¯¯"); posisi(51, 19); printf("¯¯¯¯");

	posisi(20, 20);
	printf("Apakah Anda Memiliki BPJS??\tYa\tTidak");
	posisi(20, 22);
	printf("Masukkan No Hp     : ");
	posisi(20, 23);
	printf("                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
	posisi(20, 24);
	printf("Masukkan email     : ");
	posisi(20, 25);
	printf("                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
	posisi(20, 26);
	printf("Masukkan Password  : ");
	posisi(20, 27);
	printf("Password untuk Akun  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
	kotak(1, 1, 51, 20, 250, 250, 250, 250, 250, 250);
	kotak(1, 1, 62, 20, 250, 250, 250, 250, 250, 250);

	/*Bagian Inputan*/
	rgbbgt(215, 227, 254);
	rgbtext(49, 175, 212);
	posisi(41, 14); if(!val_nik()) return;
	posisi(41, 16); if(!val_nama()) return;


	posisi(41, 18);	tanggal = valtgl(1, 31, 2); if (tanggal == 0) return;
	posisi(46, 18);	bulan = valtgl(1, 12, 2); if (bulan == 0) return;
	posisi(51, 18);	tahun = valtgl(1950, 2026, 4); if (tahun == 0) return;
	sprintf(tanggallahir, "%04d-%02d-%02d", tahun, bulan, tanggal);

	rgbtext(0, 0, 0);
	rgbbgt(250, 250, 250);

	while (1) {
		ceklis(bpjs);

		key = getch();

		if (key == 0 || key == -32) {
			key = getch();

			// PANAH KANAN
			if (key == 77) {
				if (bpjs == 2) bpjs = 1;
				else if (bpjs == 2) bpjs = 1;
				else bpjs++;
			}

			// PANAH KIRI
			else if (key == 75) {
				if (bpjs == 1) bpjs = 0;
				else if (bpjs == 0) bpjs = 4;
				else bpjs--;
			}
		}

		// ENTER
		else if (key == 13) {
			break;
		}
	}

	if (bpjs == 1)
	{
		strcpy(bpjsval, "BPJS");
	}
	else
	{
		strcpy(bpjsval, "NON BPJS");
	}

	rgbbgt(215, 227, 254);
	rgbtext(49, 175, 212);
	posisi(41, 22);
	if(!valnohp()) return;

	posisi(41, 24);
	if(!valemail()) return;

	posisi(41, 26);
	if(!val_pass()) return;
	registersql();
}
