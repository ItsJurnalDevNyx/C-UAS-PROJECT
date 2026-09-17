#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 

int text = 7, background = 0;

//gasak posisi 
void posisi(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//gasak warna non rgb
void tekswarna(int textcolor, int bgtext)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textcolor + background * 16);
	text = textcolor;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text + bgtext * 16);
	background = bgtext;
}

void backgroundcolor(int new_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text + new_color * 16);
	background = new_color;
}

// warna teks rgb
void rgbtext(int rt, int gt, int bt)
{
	printf("\033[38;2;%d;%d;%dm", rt, gt, bt);
}

// warna background rgb teks
void rgbbgt(int rb, int gb, int bb)
{
	printf("\033[48;2;%d;%d;%dm", rb, gb, bb);
}

// reset warna ke default
void resetcolor()
{
	printf("\033[0m");
}

// reset background ke default
void resetbg() {
	printf("\033[49m");
}

int menu_user() {
	int pilihan = 1;
	char key;

	//system("cls");


	kotak(140, 29, 1, 1, 36, 191, 165, 211, 211, 211);
	while (1) {
		tampilbuttonuser(pilihan);

		key = getch();

		if (key == 0 || key == -32) {
			key = getch();

			if (key == 77) {
				if (pilihan == 3) pilihan = 0;
				else if (pilihan == 0) pilihan = 1;
				else pilihan++;
			}

			else if (key == 75) {
				if (pilihan == 1) pilihan = 0;
				else if (pilihan == 0) pilihan = 3;
				else pilihan--;
			}
		}

		else if (key == 13) {
			return pilihan;
			kotak(138, 20, 3, 2, 211, 211, 211, 211, 211, 211);
		}
		else if (key == 27) {
			kotak(138, 20, 3, 2, 211, 211, 211, 211, 211, 211);
			break;
		}
	}
}

int menu_supir() {
	int pilihan = 1;
	char key;

	//system("cls");


	kotak(140, 29, 1, 1, 36, 191, 165, 211, 211, 211);
	while (1) {
		tampilbuttonsupir(pilihan);

		key = getch();

		if (key == 0 || key == -32) {
			key = getch();

			if (key == 77) {
				if (pilihan == 2) pilihan = 0;
				else if (pilihan == 0) pilihan = 1;
				else pilihan++;
			}

			else if (key == 75) {
				if (pilihan == 1) pilihan = 0;
				else if (pilihan == 0) pilihan = 2;
				else pilihan--;
			}
		}

		else if (key == 13) {
			return pilihan;
			kotak(138, 20, 3, 2, 211, 211, 211, 211, 211, 211);
		}
		else if (key == 27) {
			kotak(138, 20, 3, 2, 211, 211, 211, 211, 211, 211);
			break;
		}
	}
}


int menu_admin(int fakepilihan) {
	int pilihan = 1;
	char key;

	if (fakepilihan == 2)
	{
		pilihan = fakepilihan;
	}
	//system("cls");

	while (1) {
		kotak(140, 29, 1, 1, 36, 191, 165, 211, 211, 211);
		tampilbuttonadmin(pilihan);

		key = getch();

		if (key == 0 || key == -32) {
			key = getch();

			// PANAH KANAN
			if (key == 77) {
				if (pilihan == 4) pilihan = 0;
				else if (pilihan == 0) pilihan = 1;
				else pilihan++;
			}

			// PANAH KIRI
			else if (key == 75) {
				if (pilihan == 1) pilihan = 0;
				else if (pilihan == 0) pilihan = 4;
				else pilihan--;
			}
		}

		// ENTER
		else if (key == 13) {
			return pilihan;
		}
		else if (key == 27) {
			return pilihan;
		}

	}
}

int menu_utama() {
	int pilihanutama = 1;
	char key;

	tampilmenuutama(pilihanutama);

	while (1) {
		int old = pilihanutama;
		int valid = 0;

		key = getch();

		// Tombol panah
		if (key == 0 || key == -32) {
			key = getch();

			if (key == 77) {               // PANAH KANAN
				if (pilihanutama == 4) pilihanutama = 1;
				else pilihanutama++;
				valid = 1;
			}
			else if (key == 75) {          // PANAH KIRI
				if (pilihanutama == 1) pilihanutama = 4;
				else pilihanutama--;
				valid = 1;
			}

		}
		else if (key == 13) {              // ENTER
			resetcolor();
			return pilihanutama;
		}

		if (valid && old != pilihanutama) {
			tampilmenuutama(pilihanutama);
		}
	}

}

int menu_ambulans() {
	int pilihanMenu = 1;
	char key;

	while (1) {
		kotak(75, 13, 60, 7, 211, 211, 211, 211, 211, 211);
		tampil_supir_ambulans(60, 7);
		tampil_menu_ambulans(pilihanMenu);

		key = getch();

		if (key == 72 && pilihanMenu > 1) {
			pilihanMenu--;
		}
		else if (key == 80 && pilihanMenu < 4) {
			pilihanMenu++;
		}
		else if (key == 13) {
			switch (pilihanMenu) {
			case 1:
				tambah_ambulans();
				break;
			case 2:
				edit_ambulans();
				break;
			case 3:
				hapus_ambulans();
				break;
			case 4:
				tampil_semua_supir_ambulans(60, 7);
				break;
			}
		}
		else if (key == 27) {                         // ESC
			kotak(75, 13, 60, 7, 211, 211, 211, 211, 211, 211);
			return 0;
		}
	}
}


int menu_role() {
	int pilihanrole = 1;
	char key;

	tampilmenurole(pilihanrole);

	while (1) {
		int old = pilihanrole;
		int valid = 0;

		key = getch();

		// Tombol panah
		if (key == 0 || key == -32) {
			key = getch();

			if (key == 77) {               // PANAH KANAN
				if (pilihanrole == 3) pilihanrole = 1;
				else pilihanrole++;
				valid = 1;
			}
			else if (key == 75) {          // PANAH KIRI
				if (pilihanrole == 1) pilihanrole = 3;
				else pilihanrole--;
				valid = 1;
			}

		}
		else if (key == 13) {              // ENTER
			resetcolor();
			return pilihanrole;
		}

		if (valid && old != pilihanrole) {
			tampilmenurole(pilihanrole);
		}
	}

}

void starshow() {
	int i = 0;
	char ch;

	while (1) {
		ch = getch();

		if (ch == 13) {
			input_password[i] = '\0';
			break;
		}
		else if (ch == 8) {
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		}
		else {
			if (i < sizeof(input_password) - 1) {
				input_password[i++] = ch;
				printf("*");
			}
		}
	}
	//printf("%s", input_password);
}


void mailput() {


	char ch;
	int i = 0, valid = 0, email_valid = 0;
	int ukuran_Et = 0;

	while ((ch = getch()) != 13 || i < 6 || email_valid == 0)
	{
		if ((ch >= 33 && ch <= 126) && i < 34)   // terima karakter printable
		{
			/* ===== SEBELUM @ ===== */
			if (email_valid == 0)
			{
				if ((ch >= 'A' && ch <= 'Z') ||
					(ch >= 'a' && ch <= 'z') ||
					(ch >= '0' && ch <= '9'))
				{
					valid++;
					input_email[i++] = ch;
					printf("%c", ch);
				}
				else if (ch == '@' && i > 6 && valid > 0)
				{
					email_valid = 1;
					input_email[i++] = ch;
					printf("@");
				}
			}

			/* ===== SETELAH @ (DOMAIN OTOMATIS, LOWERCASE) ===== */
			else if (email_valid == 1)
			{
				if (ch == 'g' || ch == 'G')
				{
					ukuran_Et = 9;
					strcpy(&input_email[i], "gmail.com");
					printf("gmail.com");
					i += ukuran_Et;
					email_valid = 2;
				}
				else if (ch == 'y' || ch == 'Y')
				{
					ukuran_Et = 9;
					strcpy(&input_email[i], "yahoo.com");
					printf("yahoo.com");
					i += ukuran_Et;
					email_valid = 2;
				}
				else if (ch == 'e' || ch == 'E')
				{
					ukuran_Et = 9;
					strcpy(&input_email[i], "email.com");
					printf("email.com");
					i += ukuran_Et;
					email_valid = 2;
				}
			}
		}

		/* ===== BACKSPACE ===== */
		else if (ch == 8 && i > 0)
		{
			if (email_valid == 2)
			{
				for (int k = 0; k < ukuran_Et; k++)
					printf("\b \b");

				i -= ukuran_Et;
				input_email[i] = '\0';
				email_valid = 1;
			}
			else
			{
				i--;
				printf("\b \b");

				if (input_email[i] == '@')
					email_valid = 0;

				input_email[i] = '\0';
			}
		}
	}
	input_email[i] = '\0';
	//printf("%s", input_email);
}

void ambiltanggal() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(date, "%d-%02d-%02d",
		tm.tm_year + 1900,
		tm.tm_mon + 1,
		tm.tm_mday);
}


int about(const char* nama_file)
{
	FILE* fp;
	char line[512];

	fp = fopen(nama_file, "r");
	if (fp == NULL) {
		printf("File tidak ditemukan!\n");
		return 0;
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		printf("%s", line); 
	}

	fclose(fp);
	return 1;
}


//Untuk penahan program
void end() {
	getchar();
	system("cls");
}


