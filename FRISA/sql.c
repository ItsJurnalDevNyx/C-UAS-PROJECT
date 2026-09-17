#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 

int SESSION_LOGIN = 0;
int SESSION_ID_USER = 0;
int SESSION_ID_SUPIR = 0;
char SESSION_NAMA[100];
int SESSION_ID_LAPORAN = 0;
int SESSION_ADMIN_LOGIN = 0;
int SESSION_ID_ADMIN = 0;
char SESSION_ADMIN_NAMA[100];


int total_rs = 0;

MYSQL* conn = NULL;


MYSQL* koneksiDB() {

	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("mysql_init gagal\n");
		return NULL;
	}

	if (mysql_real_connect(
		conn,
		"localhost",   // host
		"root",        // user
		"root12",      // password
		"frisa",     // NAMA DATABASE
		0,
		NULL,
		0) == NULL)
	{
		mysql_close(conn);
		return NULL;
	}

	return conn;
}


void putusKoneksi(MYSQL* conn) {
	if (conn != NULL) {
		mysql_close(conn);
	}
}

void registersql() {
	char query[600];

	sprintf(query,
		"INSERT INTO user "
		"(nik, nama, tanggallahir, bpjs, nohp, email, password) "
		"VALUES ('%s','%s','%s','%s','%s','%s','%s')",
		nik,
		get_nama,
		tanggallahir,
		bpjsval,
		hp,
		get_email,
		get_password
	);

	if (mysql_query(conn, query)) {
		printf("Insert gagal: %s\n", mysql_error(conn));
	}
	else {
		printf("Data berhasil masuk\n");
	}
}



int loginsql() {
	char query[300];
	MYSQL_RES* res;
	MYSQL_ROW row;

	sprintf(query,
		"SELECT id_user, nama FROM user "
		"WHERE email='%s' AND password='%s'",
		input_email, input_password
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row) {
		SESSION_LOGIN = 1;
		SESSION_ID_USER = atoi(row[0]);
		strcpy(SESSION_NAMA, row[1]);
		mysql_free_result(res);
		return 1;
	}

	mysql_free_result(res);
	return 0;
}

int loginsupir_sql()
{
	char query[300];
	MYSQL_RES* res;
	MYSQL_ROW row;

	sprintf(query,
		"SELECT id_supir, nama_supir "
		"FROM supir "
		"WHERE email='%s' AND password='%s'",
		input_email, input_password
	);

	if (mysql_query(conn, query)) {
		return 0;
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row)
	{
		SESSION_LOGIN = 1;
		SESSION_ID_SUPIR = atoi(row[0]);
		strcpy(SESSION_NAMA, row[1]);

		mysql_free_result(res);
		return 1;
	}

	mysql_free_result(res);
	return 0;
}




int listrs(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;

	int cursor = 0, offset = 0, ch;
	total_rs = 0;

	mysql_query(conn, "SELECT id_rs, nama_rs FROM rumah_sakit");
	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res))) {
		id_rs[total_rs] = atoi(row[0]);
		strcpy(nama_rs[total_rs], row[1]);
		total_rs++;
	}
	mysql_free_result(res);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	if (total_rs == 0) return -1;

	while (1) {
		// clear area
		for (int i = 0; i < SHOW_ITEM; i++) {
			posisi(x, y + i);
			printf("                              ");
		}

		// draw dropdown
		for (int i = 0; i < SHOW_ITEM; i++) {
			int index = offset + i;
			if (index >= total_rs) break;

			posisi(x, y + i);
			if (index == cursor)
				printf("> %s", nama_rs[index]);
			else
				printf("  %s", nama_rs[index]);
		}

		ch = getch();

		if (ch == 72 && cursor > 0) {
			cursor--;
			if (cursor < offset) offset--;
		}
		else if (ch == 80 && cursor < total_rs - 1) {
			cursor++;
			if (cursor >= offset + SHOW_ITEM) offset++;
		}
		else if (ch == 13) { // ENTER
			return id_rs[cursor];
		}
		else if (ch == 27) { // ESC
			return -1;
		}
	}
}

char* getNamaRSById(int id) {
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	for (int i = 0; i < total_rs; i++) {
		if (id_rs[i] == id) {
			return nama_rs[i];
		}
	}
	return "(Tidak ditemukan)";
}

void logout() {
	SESSION_LOGIN = 0;
}

void tampil_semua_user(int x, int y) {
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];
	char key;
	int halaman = 0;
	int totalData, totalHalaman;
	int row_y;

	// HITUNG TOTAL DATA
	mysql_query(conn, "SELECT COUNT(*) FROM user");
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	totalData = atoi(row[0]);
	mysql_free_result(res);

	totalHalaman = (totalData + 9) / 10;

	while (1) {
		int offset = halaman * 10;
		row_y = y + 3;

		sprintf(query,
			"SELECT id_user, nik, nama, tanggallahir, bpjs, nohp, email "
			"FROM user LIMIT 10 OFFSET %d", offset
		);

		if (mysql_query(conn, query)) return;
		res = mysql_store_result(conn);
		if (!res) return;

		//system("cls"); PAGINATION
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);

		posisi(x, y);
		printf("=============================================================================================================================");
		posisi(x, y + 1);
		printf("| ID | NIK             | NAMA                          | TGL LAHIR | BPJS    | NO HP        | EMAIL                         |");
		posisi(x, y + 2);
		printf("=============================================================================================================================");

		while ((row = mysql_fetch_row(res))) {
			posisi(x, row_y++);
			printf("| %3s| %16s| %30s| %10s| %8s| %13s| %30s|",
				row[0], row[1], row[2], row[3],
				row[4], row[5], row[6]
			);
		}

		posisi(x, row_y);
		printf("============================================================================================");
		posisi(x, row_y + 1);
		printf("Halaman %d / %d  (↑ ↓ navigasi | ESC keluar)",
			halaman + 1, totalHalaman);

		mysql_free_result(res);

		key = getch();

		if (key == 27) break;           // ESC
		else if (key == 72 && halaman > 0) halaman--;              // ↑
		else if (key == 80 && halaman < totalHalaman - 1) halaman++; // ↓

		kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
	}
	kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
}


void tampil_user(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[200];
	int row_y = y + 3;
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	strcpy(query,
		"SELECT id_user, nik, nama, tanggallahir, bpjs, nohp, email FROM user"
	);

	if (mysql_query(conn, query)) {
		printf("Query error: %s\n", mysql_error(conn));
		return;
	}

	res = mysql_store_result(conn);
	if (!res) {
		printf("Gagal ambil data\n");
		return;
	}


	posisi(x, y);
	printf("=============================================================================================================================");

	posisi(x, y + 1);
	printf("| ID | NIK             | NAMA                          | TGL LAHIR | BPJS    | NO HP        | EMAIL                         |");
	posisi(x, y + 2);
	printf("=============================================================================================================================");



	while ((row = mysql_fetch_row(res))) {
		posisi(x, row_y);
		printf("| %3s| %16s| %30s| %10s| %8s| %13s| %30s|",
			row[0],
			row[1],
			row[2],
			row[3],
			row[4],
			row[5],
			row[6]
		);
		row_y++;
	}
	posisi(x, row_y);
	printf("=============================================================================================================================");

	mysql_free_result(res);
}

void tampil_supir(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	char query[200];
	int row_y = y + 3;

	strcpy(query,
		"SELECT id_supir, nama_supir, email, no_hp FROM supir"
	);

	if (mysql_query(conn, query)) {
		printf("Query error: %s\n", mysql_error(conn));
		return;
	}

	res = mysql_store_result(conn);
	if (!res) {
		printf("Gagal ambil data\n");
		return;
	}


	posisi(x, y);
	printf("====================================================================================");

	posisi(x, y + 1);
	printf("| ID | NAMA SUPIR                   | NO HP        | EMAIL                         |");
	posisi(x, y + 2);
	printf("====================================================================================");



	while ((row = mysql_fetch_row(res))) {
		posisi(x, row_y);
		printf("| %3s| %29s| %13s| %30s|",
			row[0],
			row[1],
			row[3],
			row[2]
		);
		row_y++;
	}
	posisi(x, row_y);
	printf("====================================================================================");

	mysql_free_result(res);
}

void tampil_semua_supir(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];
	char key;
	int halaman = 0;
	int totalData, totalHalaman;
	int row_y;
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	mysql_query(conn, "SELECT COUNT(*) FROM supir");
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	totalData = atoi(row[0]);
	mysql_free_result(res);

	totalHalaman = (totalData + 9) / 10;

	while (1) {
		int offset = halaman * 10;
		row_y = y + 3;

		sprintf(query,
			"SELECT id_supir, nama_supir, email, no_hp "
			"FROM supir LIMIT 10 OFFSET %d", offset
		);

		if (mysql_query(conn, query)) return;
		res = mysql_store_result(conn);
		if (!res) return;

		//system("cls"); PAGINATION

		// HEADER
		posisi(x, y);
		printf("====================================================================================");
		posisi(x, y + 1);
		printf("| ID | NAMA SUPIR                   | NO HP        | EMAIL                         |");
		posisi(x, y + 2);
		printf("====================================================================================");

		// DATA (maks 10)
		while ((row = mysql_fetch_row(res))) {
			posisi(x, row_y++);
			printf("| %3s| %29s| %13s| %30s|",
				row[0],
				row[1],
				row[3],
				row[2]
			);
		}

		// FOOTER
		posisi(x, row_y);
		printf("====================================================================================");
		posisi(x, row_y + 1);
		printf("Halaman %d / %d  (↑ ↓ navigasi | ESC keluar)",
			halaman + 1, totalHalaman);

		mysql_free_result(res);

		key = getch();

		if (key == 27) break;                       // ESC
		else if (key == 72 && halaman > 0) halaman--;                // ↑
		else if (key == 80 && halaman < totalHalaman - 1) halaman++; // ↓
		kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
	}
	kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
}


void tampil_admin(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[200];
	int row_y = y + 3;

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	strcpy(query,
		"SELECT id_admin, nama_admin, username FROM admin"
	);

	if (mysql_query(conn, query)) {
		printf("Query error: %s\n", mysql_error(conn));
		return;
	}

	res = mysql_store_result(conn);
	if (!res) {
		printf("Gagal ambil data\n");
		return;
	}


	posisi(x, y);
	printf("======================================================");

	posisi(x, y + 1);
	printf("| ID | NAMA ADMIN                   | USERNAME       |");
	posisi(x, y + 2);
	printf("======================================================");



	while ((row = mysql_fetch_row(res))) {
		posisi(x, row_y);
		printf("| %3s| %29s| %15s|",
			row[0],
			row[1],
			row[2]
		);
		row_y++;
	}
	posisi(x, row_y);
	printf("======================================================");

	mysql_free_result(res);
}


void tampil_semua_admin(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];
	char key;
	int halaman = 0;
	int totalData, totalHalaman;
	int row_y;


	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	// HITUNG TOTAL DATA ADMIN
	mysql_query(conn, "SELECT COUNT(*) FROM admin");
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	totalData = atoi(row[0]);
	mysql_free_result(res);

	// kalau data kosong
	if (totalData == 0) {
		//system("cls");
		posisi(x, y);
		printf("Data admin masih kosong!");
		getch();
		return;
	}

	totalHalaman = (totalData + 9) / 10;

	while (1) {
		int offset = halaman * 10;
		row_y = y + 3;

		sprintf(query,
			"SELECT id_admin, nama_admin, username "
			"FROM admin LIMIT 10 OFFSET %d", offset
		);

		if (mysql_query(conn, query)) return;
		res = mysql_store_result(conn);
		if (!res) return;

		//system("cls"); PAGINATION

		// HEADER
		posisi(x, y);
		printf("======================================================");
		posisi(x, y + 1);
		printf("| ID | NAMA ADMIN                   | USERNAME       |");
		posisi(x, y + 2);
		printf("======================================================");

		// DATA (maks 10)
		while ((row = mysql_fetch_row(res))) {
			posisi(x, row_y++);
			printf("| %3s| %-29s| %-15s|",
				row[0],   // id
				row[1],   // nama
				row[2]    // username
			);
		}

		// FOOTER
		posisi(x, row_y);
		printf("======================================================");
		posisi(x, row_y + 1);
		printf("Halaman %d / %d  (↑ ↓ navigasi | ESC keluar)",
			halaman + 1, totalHalaman);

		mysql_free_result(res);

		key = getch();

		if (key == 27) break;                       // ESC
		else if (key == 72 && halaman > 0) halaman--;                // ↑
		else if (key == 80 && halaman < totalHalaman - 1) halaman++; // ↓
		kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
	}
	kotak(125, 13, 7, 7, 211, 211, 211, 211, 211, 211);
}

int hitung_total_user() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int total = 0;

	if (mysql_query(conn, "SELECT COUNT(*) FROM user")) {
		printf("Query error: %s\n", mysql_error(conn));
		return 0;
	}

	res = mysql_store_result(conn);
	if (res) {
		row = mysql_fetch_row(res);
		if (row && row[0])
			total = atoi(row[0]);
		mysql_free_result(res);
	}

	return total;
}

int hitung_total_rs() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int total = 0;

	if (mysql_query(conn, "SELECT COUNT(*) FROM rumah_sakit")) {
		printf("Query error: %s\n", mysql_error(conn));
		return 0;
	}

	res = mysql_store_result(conn);
	if (res) {
		row = mysql_fetch_row(res);
		if (row && row[0])
			total = atoi(row[0]);
		mysql_free_result(res);
	}

	return total;
}


int hitung_total_ambulans() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int total = 0;

	if (mysql_query(conn, "SELECT COUNT(*) FROM ambulans")) {
		printf("Query error: %s\n", mysql_error(conn));
		return 0;
	}

	res = mysql_store_result(conn);
	if (res) {
		row = mysql_fetch_row(res);
		if (row && row[0])
			total = atoi(row[0]);
		mysql_free_result(res);
	}

	return total;
}

int hitung_total_laporan() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int total = 0;

	if (mysql_query(conn, "SELECT COUNT(*) FROM laporan")) {
		printf("Query error: %s\n", mysql_error(conn));
		return 0;
	}

	res = mysql_store_result(conn);
	if (res) {
		row = mysql_fetch_row(res);
		if (row && row[0])
			total = atoi(row[0]);
		mysql_free_result(res);
	}

	return total;
}

void tambah_supir() {

}

void tambahadminsql() {
	char query[600];

	sprintf(query,
		"INSERT INTO admin "
		"(nama_admin, username, password) "
		"VALUES ('%s','%s','%s')",
		get_nama,
		get_username,
		get_password
	);

	if (mysql_query(conn, query)) {
		posisi(43, 14);
		printf("Insert gagal: %s\n", mysql_error(conn));
		Sleep(2000);
	}
	else {
		posisi(43, 14);
		printf("Data berhasil masuk\n");
		Sleep(2000);
	}
}

int hitung_ambulans_free() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int total = 0;

	if (mysql_query(conn,
		"SELECT COUNT(*) FROM ambulans WHERE status = 'TERSEDIA'")) {
		printf("Query error: %s\n", mysql_error(conn));
		return 0;
	}

	res = mysql_store_result(conn);
	if (res) {
		row = mysql_fetch_row(res);
		if (row && row[0])
			total = atoi(row[0]);
		mysql_free_result(res);
	}

	return total;
}

int cari_admin_by_nama(
	char* nama_cari,
	int* id_admin,
	char* nama,
	char* username,
	char* password
) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];

	sprintf(query,
		"SELECT id_admin, nama_admin, username, password "
		"FROM admin WHERE nama_admin LIKE '%%%s%%' LIMIT 1",
		nama_cari
	);

	if (mysql_query(conn, query)) return 0;

	res = mysql_store_result(conn);
	if (!res) return 0;

	row = mysql_fetch_row(res);
	if (!row) {
		mysql_free_result(res);
		return 0;
	}

	*id_admin = atoi(row[0]);
	strcpy(nama, row[1]);
	strcpy(username, row[2]);
	strcpy(password, row[3]);

	mysql_free_result(res);
	return 1;
}

void edit_adminsql() {


	int id_admin;
	char nama[50], username[30], password[30];
	char query[400];

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	posisi(31, 23);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	printf("Masukkan Nama Admin : ");
	posisi(31, 52);
	val_nama();

	if (!cari_admin_by_nama(
		get_nama,
		&id_admin,
		nama,
		username,
		password
	)) {
		posisi(31, 28);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		printf("Admin tidak ditemukan!");
		return;
	}

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	posisi(32, 23);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	printf("Nama ditemukan !!");
	Sleep(2000);

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	posisi(31, 23); printf("Nama Baru     : ");
	posisi(47, 23);
	
	val_nama();

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	posisi(31, 23); printf("Username Baru : ");
	posisi(47, 23);
	if(!val_uname()) return;

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	posisi(31, 23); printf("Password Baru : ");
	posisi(47, 23);
	if(!val_pass()) return;

	sprintf(query,
		"UPDATE admin SET "
		"nama_admin='%s', username='%s', password='%s' "
		"WHERE id_admin=%d",
		get_nama, get_username, get_password, id_admin
	);

	if (mysql_query(conn, query)) {
		kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
		posisi(32, 23);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		printf("Gagal update admin!");
		Sleep(2000);
	}
	else {
		kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
		posisi(31, 23);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		printf("Admin berhasil diupdate!");
		Sleep(2000);
	}
	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
}

void hapus_adminsql() {

	int id_admin;
	char nama[50], username[30], password[30];
	char query[300];
	char konfirmasi;;

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	posisi(32, 23);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	printf("Masukkan Nama Admin : ");
	if(!val_nama()) return;

	if (!cari_admin_by_nama(
		get_nama,
		&id_admin,
		nama,
		username,
		password
	)) {
		kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
		posisi(32, 23);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		printf("Admin tidak ditemukan!");
		getch();
		return;
	}
	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	posisi(32, 23);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	printf("Nama Ditemukan !!");
	Sleep(2000);

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
	posisi(32, 23);
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	printf("Yakin hapus admin ini? (y/n) : ");
	konfirmasi = getch();

	if (konfirmasi != 'y' && konfirmasi != 'Y') {
		kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
		posisi(32, 23);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		printf("Penghapusan dibatalkan.");
		kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
		return;
	}


	sprintf(query,
		"DELETE FROM admin WHERE id_admin = %d",
		id_admin
	);

	if (mysql_query(conn, query)) {
		kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
		posisi(32, 23);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		printf("Gagal menghapus admin!");
	}
	else {
		kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
		posisi(32, 23);
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);
		printf("Admin berhasil dihapus!");
	}

	kotak(72, 3, 29, 22, 211, 211, 211, 211, 211, 211);
}

int idterakhir_supir() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int id = 0;

	mysql_query(conn, "SELECT LAST_INSERT_ID()");
	res = mysql_store_result(conn);

	if (res) {
		row = mysql_fetch_row(res);
		if (row && row[0])
			id = atoi(row[0]);
		mysql_free_result(res);
	}
	return id;
}



void tampil_supir_ambulans(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];
	int row_y = y + 3;

	strcpy(query,
		"SELECT s.nama_supir, a.plat_nomor, a.status "
		"FROM ambulans a "
		"JOIN supir s ON a.id_supir = s.id_supir"
	);

	if (mysql_query(conn, query)) {
		printf("Query error: %s\n", mysql_error(conn));
		return;
	}

	res = mysql_store_result(conn);
	if (!res) {
		printf("Gagal ambil data\n");
		return;
	}

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	// HEADER
	posisi(x, y);
	printf("========================================================================");
	posisi(x, y + 1);
	printf("| NO | NAMA SUPIR                     | PLAT AMBULANS     | STATUS     |");
	posisi(x, y + 2);
	printf("========================================================================");

	int no = 1;

	// DATA
	while ((row = mysql_fetch_row(res))) {
		posisi(x, row_y);
		printf("| %2d | %-30s | %-17s | %-10s |",
			no++,
			row[0],   // nama_supir
			row[1],   // plat_nomor
			row[2]    // status
		);
		row_y++;
	}

	// FOOTER
	posisi(x, row_y);
	printf("========================================================================");

	mysql_free_result(res);
}

void tampil_semua_supir_ambulans(int x, int y) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[400];
	char key;
	int halaman = 0;
	int totalData, totalHalaman;
	int row_y;

	/* ===============================
	   HITUNG TOTAL DATA
	   =============================== */
	mysql_query(conn, "SELECT COUNT(*) FROM ambulans");
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	totalData = atoi(row[0]);
	mysql_free_result(res);

	if (totalData == 0) {
		//system("cls");
		posisi(x, y);
		printf("Data supir & ambulans masih kosong!");
		getch();
		return;
	}

	totalHalaman = (totalData + 9) / 10;

	/* ===============================
	   LOOP SCROLL
	   =============================== */
	while (1) {
		int offset = halaman * 10;
		row_y = y + 3;

		sprintf(query,
			"SELECT s.nama_supir, a.plat_nomor, a.status "
			"FROM ambulans a "
			"JOIN supir s ON a.id_supir = s.id_supir "
			"LIMIT 10 OFFSET %d",
			offset
		);

		if (mysql_query(conn, query)) {
			printf("Query error: %s\n", mysql_error(conn));
			return;
		}

		res = mysql_store_result(conn);
		if (!res) return;

		//system("cls");
		rgbtext(0, 79, 255);
		rgbbgt(211, 211, 211);

		posisi(x, y);
		printf("========================================================================");
		posisi(x, y + 1);
		printf("| NO | NAMA SUPIR                     | PLAT AMBULANS     | STATUS     |");
		posisi(x, y + 2);
		printf("========================================================================");

		int no = offset + 1;

		while ((row = mysql_fetch_row(res))) {
			posisi(x, row_y++);
			printf("| %2d | %-30s | %-17s | %-10s |",
				no++,
				row[0],
				row[1],
				row[2]
			);
		}

		posisi(x, row_y);
		printf("========================================================================");
		posisi(x, row_y + 1);
		printf("Halaman %d / %d  (↑ ↓ navigasi | ESC keluar)",
			halaman + 1, totalHalaman);

		mysql_free_result(res);

		key = getch();

		if (key == 27) break;                      // ESC
		else if (key == 72 && halaman > 0) halaman--;                // ↑
		else if (key == 80 && halaman < totalHalaman - 1) halaman++; // ↓
		kotak(75, 15, 60, 7, 211, 211, 211, 211, 211, 211);
	}
	kotak(75, 15, 60, 7, 211, 211, 211, 211, 211, 211);
}

void tambah_ambulans_dan_supir() {
	char plat[15];
	char query[500];
	int id_supir;

	
	kotak(34, 18, 2, 5, 211, 211, 211, 211, 211, 211);

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	posisi(5, 5);
	printf("=== DATA SUPIR ===");
	posisi(5, 7);
	printf("Nama Supir : ");

	posisi(5, 9);
	printf("No HP      : ");

	posisi(5, 11);
	printf("Email      : ");

	posisi(5, 13);
	printf("Password   : ");

	posisi(18, 7);
	if (!val_nama()) return;
	posisi(18, 9);
	if(!valnohp()) return;
	posisi(18, 11);
	if(!valemail()) return;
	posisi(18, 13);
	if(!val_pass_admin()) return;
	// INSERT SUPIR
	sprintf(query,
		"INSERT INTO supir (nama_supir, no_hp, email, password) "
		"VALUES ('%s','%s','%s','%s')",
		get_nama, hp, get_email, get_password
	);

	if (mysql_query(conn, query)) {
		printf("Gagal tambah supir: %s\n", mysql_error(conn));
		return;
	}

	id_supir = mysql_insert_id(conn);

	posisi(5, 15);
	printf("=== DATA AMBULANS ===");
	posisi(5, 17);
	printf("Plat Nomor : ");
	if (!val_plat(plat)) return;

	// INSERT AMBULANS + SUPIR
	sprintf(query,
		"INSERT INTO ambulans (plat_nomor, id_supir, status) "
		"VALUES ('%s', %d, 'TERSEDIA')",
		plat, id_supir
	);

	if (mysql_query(conn, query)) {
		printf("Gagal tambah ambulans: %s\n", mysql_error(conn));
		return;
	}

	posisi(5, 19);
	printf("Supir & Ambulans berhasil");
	posisi(5, 20);
	printf("ditambahkan dan langsung dipasangkan!\n");
	Sleep(2000);
	kotak(43, 18, 2, 5, 211, 211, 211, 211, 211, 211);
}

void edit_ambulans_dan_supir()
{
	char plat[15];
	char query[500];

	MYSQL_RES* res;
	MYSQL_ROW row;

	int id_supir;

	kotak(45, 20, 2, 5, 211, 211, 211, 211, 211, 211);

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	posisi(5, 5);
	printf("=== EDIT AMBULANS & SUPIR ===");


	posisi(5, 7);
	printf("Cari Plat Ambulans : ");
	posisi(28, 7);
	if (!val_plat(plat)) return;


	sprintf(query,
		"SELECT s.id_supir, s.nama_supir, s.no_hp, s.email "
		"FROM ambulans a "
		"JOIN supir s ON a.id_supir = s.id_supir "
		"WHERE a.plat_nomor = '%s'",
		plat
	);

	if (mysql_query(conn, query))
	{
		posisi(5, 9);
		printf("Query error!");
		Sleep(2000);
		return;
	}

	res = mysql_store_result(conn);
	if (mysql_num_rows(res) == 0)
	{
		posisi(5, 9);
		printf("Ambulans tidak ditemukan!");
		mysql_free_result(res);
		Sleep(2000);
		return;
	}

	row = mysql_fetch_row(res);
	id_supir = atoi(row[0]);
	mysql_free_result(res);

	/* FORM EDIT SUPIR */
	posisi(5, 9);
	printf("=== DATA SUPIR (EDIT) ===");

	posisi(5, 11);
	printf("Nama Supir : ");
	posisi(20, 11);
	if(!val_nama()) return;

	posisi(5, 13);
	printf("No HP      : ");
	posisi(20, 13);
	if(!valnohp()) return;

	posisi(5, 15);
	printf("Email      : ");
	posisi(20, 15);
	if(!valemail()) return;

	posisi(5, 17);
	printf("Password   : ");
	posisi(20, 17);
	if(!val_pass_admin()) return;

	/* UPDATE SUPIR */
	sprintf(query,
		"UPDATE supir SET "
		"nama_supir='%s', "
		"no_hp='%s', "
		"email='%s', "
		"password='%s' "
		"WHERE id_supir=%d",
		get_nama, hp, get_email, get_password, id_supir
	);

	if (mysql_query(conn, query))
	{
		posisi(5, 19);
		printf("Gagal update data supir!");
		Sleep(2000);
		return;
	}

	posisi(5, 19);
	printf("Data supir berhasil diperbarui!");
	Sleep(2000);

	kotak(45, 20, 2, 5, 211, 211, 211, 211, 211, 211);
}

int hapus_ambulans_dan_supir()
{
	char plat[15];	
	char query[500];

	MYSQL_RES* res;
	MYSQL_ROW row;

	int id_supir;

	kotak(45, 16, 2, 5, 211, 211, 211, 211, 211, 211);

	rgbtext(255, 0, 0);
	rgbbgt(211, 211, 211);

	posisi(5, 5);
	printf("=== HAPUS AMBULANS & SUPIR ===");

	/* INPUT PLAT */
	posisi(5, 7);
	printf("Plat Ambulans : ");
	posisi(25, 7);
	if (!val_plat(plat)) return;

	/* CEK DATA */
	sprintf(query,
		"SELECT id_supir FROM ambulans WHERE plat_nomor='%s'",
		plat
	);

	if (mysql_query(conn, query))
	{
		posisi(5, 9);
		printf("Query error!");
		Sleep(2000);
		return;
	}

	res = mysql_store_result(conn);
	if (mysql_num_rows(res) == 0)
	{
		posisi(5, 9);
		printf("Ambulans tidak ditemukan!");
		mysql_free_result(res);
		Sleep(2000);
		return;
	}

	row = mysql_fetch_row(res);
	id_supir = atoi(row[0]);
	mysql_free_result(res);

	/* KONFIRMASI */
	posisi(5, 9);
	printf("Yakin hapus data ini? (Y/N): ");

	char konfirmasi = _getch();
	if (konfirmasi != 'Y' && konfirmasi != 'y')
	{
		posisi(5, 11);
		printf("Dibatalkan");
		kotak(75, 15, 60, 7, 211, 211, 211, 211, 211, 211);
		Sleep(1500);
		return;
	}

	/* HAPUS AMBULANS */
	sprintf(query,
		"DELETE FROM ambulans WHERE plat_nomor='%s'",
		plat
	);

	if (mysql_query(conn, query))
	{
		posisi(5, 11);
		printf("Gagal hapus ambulans!");
		Sleep(2000);
		return;
	}

	/* HAPUS SUPIR */
	sprintf(query,
		"DELETE FROM supir WHERE id_supir=%d",
		id_supir
	);

	if (mysql_query(conn, query))
	{
		posisi(5, 11);
		printf("Gagal hapus supir!");
		Sleep(2000);
		return;
	}

	posisi(5, 11);
	printf("Ambulans & Supir berhasil dihapus!");
	Sleep(2000);

	kotak(45, 16, 2, 5, 211, 211, 211, 211, 211, 211);
}

int get_biaya_user()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[200];

	sprintf(query,
		"SELECT bpjs FROM user WHERE id_user=%d",
		SESSION_ID_USER
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	int biaya = 50000; // default NON BPJS

	if (row && strcmp(row[0], "BPJS") == 0) {
		biaya = 0;
	}

	mysql_free_result(res);
	return biaya;
}

int pilih_ambulans() {
	MYSQL_RES* res;
	MYSQL_ROW row;

	int id[50], supir[50], total = 0;
	char plat[50][20];
	int cursor = 0, ch;

	mysql_query(conn,
		"SELECT id_ambulans, plat_nomor, id_supir "
		"FROM ambulans WHERE status='TERSEDIA'"
	);
	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res))) {
		id[total] = atoi(row[0]);
		strcpy(plat[total], row[1]);
		supir[total] = row[2] ? atoi(row[2]) : 0;
		total++;
	}
	mysql_free_result(res);

	if (total == 0) return -1;

	while (1) {
		// tampilkan dropdown (panah)
		ch = getch();
		if (ch == 13) {
			SESSION_ID_SUPIR = supir[cursor];
			return id[cursor];
		}
		if (ch == 27) return -1;
	}
}

int hitung_biaya() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[100];

	sprintf(query,
		"SELECT bpjs FROM user WHERE id_user=%d",
		SESSION_ID_USER
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	int biaya = 50000;
	if (row && strcmp(row[0], "BPJS") == 0)
		biaya = 0;

	mysql_free_result(res);
	return biaya;
}

void pesan_ambulans(int id_rs) {
	int id_amb;

	// pilih ambulans tersedia
	id_amb = pilih_ambulans();
	if (id_amb == -1) return;

	int biaya = hitung_biaya();

	char query[300];
	sprintf(query,
		"INSERT INTO laporan "
		"(id_user, id_ambulans, id_supir, id_rs, biaya, status_laporan) "
		"VALUES (%d,%d,%d,%d,%d,'MENUNGGU')",
		SESSION_ID_USER,
		id_amb,
		SESSION_ID_SUPIR,
		id_rs,
		biaya
	);
	mysql_query(conn, query);

	sprintf(query,
		"UPDATE ambulans SET status='DIPAKAI' "
		"WHERE id_ambulans=%d",
		id_amb
	);
	mysql_query(conn, query);

	// notifikasi
	kotak(40, 10, 30, 4, 211, 211, 211, 211, 211, 211);
	posisi(42, 12);
	printf("Ambulans berhasil dipesan!");
	getch();
}

int pilih_ambulans_dropdown(int x, int y)
{
	MYSQL_RES* res;
	MYSQL_ROW row;

	int id_amb[20], id_supir[20];
	char plat[20][20], nama_supir[20][50];
	int total = 0;

	int cursor = 0, offset = 0, ch;

	mysql_query(conn,
		"SELECT a.id_ambulans, a.plat_nomor, s.id_supir, s.nama_supir "
		"FROM ambulans a "
		"JOIN supir s ON a.id_supir = s.id_supir "
		"WHERE a.status='TERSEDIA'"
	);

	res = mysql_store_result(conn);
	while ((row = mysql_fetch_row(res))) {
		id_amb[total] = atoi(row[0]);
		strcpy(plat[total], row[1]);
		id_supir[total] = atoi(row[2]);
		strcpy(nama_supir[total], row[3]);
		total++;
	}
	mysql_free_result(res);

	if (total == 0) return -1;

	while (1) {
		// clear area
		for (int i = 0; i < total; i++) {
			posisi(x, y + i);
			printf("                                  ");
		}

		// draw dropdown
		for (int i = 0; i < total; i++) {
			posisi(x, y + i);
			if (i == cursor)
				printf("> %-12s | %-15s", plat[i], nama_supir[i]);
			else
				printf("  %-12s | %-15s", plat[i], nama_supir[i]);
		}

		ch = getch();

		if (ch == 72 && cursor > 0) cursor--;        // ↑
		else if (ch == 80 && cursor < total - 1) cursor++; // ↓
		else if (ch == 13) { // ENTER
			SESSION_ID_SUPIR = id_supir[cursor];   
			return id_amb[cursor];
		}
		else if (ch == 27) return -1; // ESC
	}
}

void proses_pesan_ambulans(int id_rs, int id_amb)
{
	char query[500];
	int biaya;
	char konfirmasi;

	// ===== HITUNG BIAYA =====
	biaya = hitung_biaya();   // BPJS = 0 | NON = 50000

	// ===== TAMPILKAN KONFIRMASI =====
	kotak(40, 14, 35, 7, 211, 211, 211, 211, 211, 211);

	posisi(42, 15);
	printf("Konfirmasi Pemesanan Ambulans");

	posisi(42, 16);
	printf("Biaya : %s",
		biaya == 0 ? "GRATIS (BPJS)" : "Rp 50.000");

	posisi(42, 18);
	printf("Yakin pesan ambulans? (Y/T): ");

	konfirmasi = getch();

	if (konfirmasi != 'Y' && konfirmasi != 'y') {
		posisi(42, 20);
		printf("Pemesanan dibatalkan.");
		Sleep(1000);
		return;
	}

	// ===== INSERT KE LAPORAN =====
	sprintf(query,
		"INSERT INTO laporan "
		"(id_user, id_ambulans, id_supir, id_rs, biaya, status_laporan) "
		"VALUES (%d, %d, %d, %d, %d, 'MENUNGGU_SUPIR')",
		SESSION_ID_USER,
		id_amb,
		SESSION_ID_SUPIR,
		id_rs,
		biaya
	);

	if (mysql_query(conn, query)) {
		posisi(42, 20);
		printf("Gagal memesan ambulans!");
		getch();
		return;
	}

	// ===== UPDATE STATUS AMBULANS =====
	sprintf(query,
		"UPDATE ambulans SET status='DIPAKAI' "
		"WHERE id_ambulans=%d",
		id_amb
	);
	mysql_query(conn, query);

	// ===== BERHASIL =====
	posisi(42, 20);
	printf("Ambulans berhasil dipesan!");
	getch();
}


int cek_laporan_aktif_user()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];

	sprintf(query,
		"SELECT id_laporan, status_laporan "
		"FROM laporan "
		"WHERE id_user=%d "
		"AND status_laporan IN ('MENUNGGU_SUPIR','DIPROSES') "
		"ORDER BY id_laporan DESC LIMIT 1",
		SESSION_ID_USER
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);

	if ((row = mysql_fetch_row(res))) {
		SESSION_ID_LAPORAN = atoi(row[0]);
		mysql_free_result(res);
		return 1;
	}

	mysql_free_result(res);
	SESSION_ID_LAPORAN = 0;
	return 0;
}

void tampilan_laporan_aktif()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[400];

	sprintf(query,
		"SELECT a.plat_nomor, s.nama_supir, l.status_laporan "
		"FROM laporan l "
		"JOIN ambulans a ON l.id_ambulans = a.id_ambulans "
		"JOIN supir s ON l.id_supir = s.id_supir "
		"WHERE l.id_laporan=%d",
		SESSION_ID_LAPORAN
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (!row) {
		mysql_free_result(res);
		return;
	}

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);
	posisi(4, 5);
	printf("🚑 Ambulans Dalam Perjalanan");

	posisi(5, 8);
	printf("Plat  : %s", row[0]);

	posisi(5, 10);
	printf("Supir : %s", row[1]);

	posisi(5, 12);
	printf("Status: %s", row[2]);

	mysql_free_result(res);
}

void batal_laporan()
{
	char query[300];
	char konfirmasi;

	posisi(5, 15);
	printf("Batalkan laporan? (Y/T): ");
	konfirmasi = getch();

	if (konfirmasi != 'Y' && konfirmasi != 'y')
		return;

	sprintf(query,
		"UPDATE laporan SET status_laporan='DITOLAK_SUPIR' "
		"WHERE id_laporan=%d",
		SESSION_ID_LAPORAN
	);
	mysql_query(conn, query);

	sprintf(query,
		"UPDATE ambulans SET status='TERSEDIA' "
		"WHERE id_ambulans = "
		"(SELECT id_ambulans FROM laporan WHERE id_laporan=%d)",
		SESSION_ID_LAPORAN
	);
	mysql_query(conn, query);

	SESSION_ID_LAPORAN = 0;

	posisi(5, 19);
	printf("Laporan dibatalkan.");
	getch();
}



void tampilan_laporan_user(int x, int y)
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[600];
	int row_y = y + 3;
	int no = 1;

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	sprintf(query,
		"SELECT u.nama, s.nama_supir, a.plat_nomor, r.nama_rs, "
		"l.biaya, l.tanggal, l.status_laporan "
		"FROM laporan l "
		"JOIN user u ON l.id_user = u.id_user "
		"JOIN ambulans a ON l.id_ambulans = a.id_ambulans "
		"JOIN supir s ON l.id_supir = s.id_supir "
		"JOIN rumah_sakit r ON l.id_rs = r.id_rs "
		"WHERE l.id_user = %d "
		"ORDER BY l.tanggal DESC "
		"LIMIT 10",
		SESSION_ID_USER
	);

	if (mysql_query(conn, query)) {
		posisi(x, y);
		printf("MySQL Error: %s", mysql_error(conn));
		getch();
		return;
	}

	res = mysql_store_result(conn);
	if (!res || mysql_num_rows(res) == 0) {
		posisi(x, y);
		printf("Belum ada laporan.");
		getch();
		return;
	}

	posisi(x, y);
	printf("==========================================================================================================");
	posisi(x, y + 1);
	printf("| NO | USER                     | SUPIR              | RUMAH SAKIT          | BIAYA    | STATUS          |");
	posisi(x, y + 2);
	printf("==========================================================================================================");
	while ((row = mysql_fetch_row(res))) {
		posisi(x, row_y++);
		printf("| %2d | %24s | %18s | %20s | %8s | %15s |",
			no++,      // NO
			row[0],    // USER
			row[1],    // SUPIR
			row[3],    // RUMAH SAKIT
			row[4],    // BIAYA
			row[6]     // STATUS
		);
	}


	// ===== FOOTER =====
	posisi(x, row_y);
	printf("==========================================================================================================");
	posisi(x, row_y + 1);

	mysql_free_result(res);
}

void tampilan_total_laporan(int x, int y)
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[700];
	char key;

	int halaman = 0;
	int totalData = 0;
	int totalHalaman = 0;
	int row_y;
	int no;

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	/* ===== HITUNG TOTAL DATA ===== */
	sprintf(query,
		"SELECT COUNT(*) FROM laporan WHERE id_user = %d",
		SESSION_ID_USER
	);

	if (mysql_query(conn, query)) {
		posisi(x, y);
		printf("MySQL Error: %s", mysql_error(conn));
		getch();
		return;
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	totalData = atoi(row[0]);
	mysql_free_result(res);

	if (totalData == 0) {
		posisi(x, y);
		printf("Belum ada laporan.");
		getch();
		return;
	}

	totalHalaman = (totalData + 9) / 10;

	/* ===== LOOP PAGINATION ===== */
	while (1) {
		//system("cls");

		row_y = y + 3;
		no = halaman * 10 + 1;

		sprintf(query,
			"SELECT u.nama, s.nama_supir, a.plat_nomor, r.nama_rs, "
			"l.biaya, DATE(l.tanggal), l.status_laporan "
			"FROM laporan l "
			"JOIN user u ON l.id_user = u.id_user "
			"JOIN ambulans a ON l.id_ambulans = a.id_ambulans "
			"JOIN supir s ON l.id_supir = s.id_supir "
			"JOIN rumah_sakit r ON l.id_rs = r.id_rs "
			"WHERE l.id_user = %d "
			"ORDER BY l.tanggal DESC "
			"LIMIT 10 OFFSET %d",
			SESSION_ID_USER,
			halaman * 10
		);

		if (mysql_query(conn, query)) {
			posisi(x, y);
			printf("MySQL Error: %s", mysql_error(conn));
			getch();
			return;
		}

		res = mysql_store_result(conn);

		/* ===== HEADER ===== */
		posisi(x, y);
		printf("==========================================================================================================");
		posisi(x, y + 1);
		printf("| NO | USER                     | SUPIR              | RUMAH SAKIT          | BIAYA    | STATUS          |");
		posisi(x, y + 2);
		printf("==========================================================================================================");

		/* ===== DATA ===== */
		while ((row = mysql_fetch_row(res))) {
			posisi(x, row_y++);
			printf("| %2d | %-24s | %-18s | %-20s | %8s | %-15s |",
				no++,
				row[0],   // user
				row[1],   // supir
				row[3],   // rs
				row[4],   // biaya
				row[6]    // status
			);
		}

		/* ===== FOOTER ===== */
		posisi(x, row_y);
		printf("==========================================================================================================");
		posisi(x, row_y + 1);
		printf("Halaman %d / %d  (↑ ↓ navigasi | ESC keluar)",
			halaman + 1, totalHalaman);

		mysql_free_result(res);

		key = getch();

		if (key == 27) break;                           // ESC
		else if (key == 72 && halaman > 0) halaman--;   // ↑
		else if (key == 80 && halaman < totalHalaman - 1) halaman++; // ↓
	}
}


void tampilan_profil_user()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];

	
	sprintf(query,
		"SELECT nik, nama, tanggallahir, bpjs, nohp, email "
		"FROM user WHERE id_user = %d",
		SESSION_ID_USER
	);

	if (mysql_query(conn, query)) {
		posisi(5, 5);
		printf("MySQL Error: %s", mysql_error(conn));
		getch();
		return;
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (!row) {
		posisi(5, 5);
		printf("Data profil tidak ditemukan.");
		getch();
		mysql_free_result(res);
		return;
	}

	/* ===== TAMPILAN ===== */
	kotak(60, 15, 4, 4, 211, 211, 211, 211, 211, 211);

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	posisi(6, 6);
	printf("=== PROFIL PENGGUNA ===");

	posisi(6, 8);
	printf("NIK            : %s", row[0]);

	posisi(6, 10);
	printf("Nama           : %s", row[1]);

	posisi(6, 12);
	printf("Tanggal Lahir  : %s", row[2]);

	posisi(6, 13);
	printf("Status BPJS    : %s", row[3]);

	posisi(6, 15);
	printf("No HP          : %s", row[4]);

	posisi(6, 17);
	printf("Email          : %s", row[5]);

	mysql_free_result(res);
}


void tampil_semua_laporan(int x, int y)
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[700];
	char key;

	int halaman = 0;
	int totalData = 0;
	int totalHalaman;
	int row_y;
	int no;

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	/* ===== HITUNG TOTAL DATA ===== */
	if (mysql_query(conn, "SELECT COUNT(*) FROM laporan")) {
		posisi(x, y);
		printf("MySQL Error: %s", mysql_error(conn));
		getch();
		return;
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	totalData = atoi(row[0]);
	mysql_free_result(res);

	if (totalData == 0) {
		posisi(x, y);
		printf("Belum ada laporan.");
		getch();
		return;
	}

	totalHalaman = (totalData + 9) / 10;

	/* ===== LOOP PAGINATION ===== */
	while (1) {
		//system("cls");

		row_y = y + 3;
		no = halaman * 10 + 1;

		sprintf(query,
			"SELECT u.nama, s.nama_supir, a.plat_nomor, r.nama_rs, l.status_laporan "
			"FROM laporan l "
			"JOIN user u ON l.id_user = u.id_user "
			"JOIN ambulans a ON l.id_ambulans = a.id_ambulans "
			"JOIN supir s ON l.id_supir = s.id_supir "
			"JOIN rumah_sakit r ON l.id_rs = r.id_rs "
			"ORDER BY l.id_laporan DESC "
			"LIMIT 10 OFFSET %d",
			halaman * 10
		);

		if (mysql_query(conn, query)) {
			posisi(x, y);
			printf("MySQL Error: %s", mysql_error(conn));
			getch();
			return;
		}

		res = mysql_store_result(conn);

		posisi(x, y);
		printf("==========================================================================================================");
		posisi(x, y + 1);
		printf("| NO | USER                 | SUPIR              | PLAT AMBULANS | RUMAH SAKIT          | STATUS         |");
		posisi(x, y + 2);
		printf("==========================================================================================================");

		while ((row = mysql_fetch_row(res))) {
			posisi(x, row_y++);
			printf("| %2d | %20s | %18s | %13s | %20s | %14s |",
				no++,
				row[0], // nama user
				row[1], // nama supir
				row[2], // plat ambulans
				row[3], // rumah sakit
				row[4]  // status laporan
			);
		}

		posisi(x, row_y);
		printf("=========================================================================================================");
		posisi(x, row_y + 1);
		printf("Halaman %d / %d   (↑ ↓ navigasi | ESC keluar)",
			halaman + 1, totalHalaman);

		mysql_free_result(res);

		key = getch();
		if (key == 27) break;                          // ESC
		else if (key == 72 && halaman > 0) halaman--;  // ↑
		else if (key == 80 && halaman < totalHalaman - 1) halaman++; // ↓
	}
}
void tambah_rs()
{
	char nama[50], alamat[100], query[300];

	kotak(50, 12, 2, 5, 211, 211, 211, 211, 211, 211);

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	posisi(5, 5);
	printf("=== TAMBAH RUMAH SAKIT ===");

	posisi(5, 7);
	printf("Nama RS   : ");
	posisi(18, 7);
	if(!val_nama()) return;

	posisi(5, 9);
	printf("Alamat RS : ");
	posisi(18, 9);
	if(!val_alamat()) return;

	sprintf(query,
		"INSERT INTO rumah_sakit (nama_rs, alamat) VALUES ('%s','%s')",
		get_nama, get_alamat
	);

	if (mysql_query(conn, query)) {
		posisi(5, 11);
		printf("Gagal menambahkan rumah sakit!");
	}
	else {
		posisi(5, 11);
		printf("Rumah sakit berhasil ditambahkan!");
	}

	getch();
	kotak(50, 12, 2, 5, 211, 211, 211, 211, 211, 211);
}

void edit_rs()
{
	int id;
	char nama[50], alamat[100], query[400];

	kotak(50, 14, 2, 5, 211, 211, 211, 211, 211, 211);

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	posisi(5, 5);
	printf("=== EDIT RUMAH SAKIT ===");

	posisi(5, 7);
	printf("ID RS     : ");
	posisi(18, 7);
	id = val_id();
	getchar();

	posisi(5, 9);
	printf("Nama Baru : ");
	posisi(18, 9);
	if(!val_nama()) return;

	posisi(5, 11);
	printf("Alamat    : ");
	posisi(18, 11);
	if(!val_alamat()) return;

	sprintf(query,
		"UPDATE rumah_sakit SET nama_rs='%s', alamat='%s' WHERE id_rs=%d",
		get_nama, get_alamat, id
	);

	if (mysql_query(conn, query)) {
		posisi(5, 13);
		printf("Gagal update data!");
	}
	else {
		posisi(5, 13);
		printf("Data rumah sakit berhasil diperbarui!");
	}

	getch();
	kotak(50, 14, 2, 5, 211, 211, 211, 211, 211, 211);
}


void hapus_rs()
{
	int id;
	char query[200];

	kotak(50, 12, 2, 5, 211, 211, 211, 211, 211, 211);

	rgbtext(255, 0, 0);
	rgbbgt(211, 211, 211);

	posisi(5, 5);
	printf("=== HAPUS RUMAH SAKIT ===");

	posisi(5, 7);
	printf("ID RS : ");
	posisi(18, 7);
	id = val_id();
	getchar();

	sprintf(query,
		"DELETE FROM rumah_sakit WHERE id_rs=%d",
		id
	);

	if (mysql_query(conn, query)) {
		posisi(5, 9);
		printf("Gagal menghapus data!");
	}
	else {
		posisi(5, 9);
		printf("Data rumah sakit berhasil dihapus!");
	}

	getch();
	kotak(50, 12, 2, 5, 211, 211, 211, 211, 211, 211);
}

void tampil_rs_pagination(int x, int y, int halaman)
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];
	int row_y = y + 3;

	int offset = halaman * 10;

	sprintf(query,
		"SELECT id_rs, nama_rs, alamat "
		"FROM rumah_sakit "
		"LIMIT 10 OFFSET %d",
		offset
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);

	// HEADER
	posisi(x, y);
	printf("==============================================================");
	posisi(x, y + 1);
	printf("| ID | NAMA RUMAH SAKIT           | ALAMAT                  |");
	posisi(x, y + 2);
	printf("==============================================================");

	while ((row = mysql_fetch_row(res))) {
		posisi(x, row_y++);
		printf("| %2s | %-25s | %-23s |",
			row[0], row[1], row[2]
		);
	}

	posisi(x, row_y);
	printf("==============================================================");

	mysql_free_result(res);
}

int loginsql_admin(char* username, char* password)
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[300];

	sprintf(query,
		"SELECT id_admin, nama_admin "
		"FROM admin "
		"WHERE username='%s' AND password='%s'",
		username, password
	);

	if (mysql_query(conn, query)) {
		printf("Query error: %s", mysql_error(conn));
		return 0;
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row) {
		SESSION_ADMIN_LOGIN = 1;
		SESSION_ID_ADMIN = atoi(row[0]);
		strcpy(SESSION_ADMIN_NAMA, row[1]);

		mysql_free_result(res);
		return 1;
	}

	mysql_free_result(res);
	return 0;
}

void logout_admin()
{
	SESSION_ADMIN_LOGIN = 0;
	SESSION_ID_ADMIN = 0;
	strcpy(SESSION_ADMIN_NAMA, "");
}

void tampil_tugas_supir(int x, int y)
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[600];
	int row_y = y + 3;
	int no = 1;

	sprintf(query,
		"SELECT l.id_laporan, u.nama, a.plat_nomor, r.nama_rs, l.status_laporan "
		"FROM laporan l "
		"JOIN user u ON l.id_user = u.id_user "
		"JOIN ambulans a ON l.id_ambulans = a.id_ambulans "
		"JOIN rumah_sakit r ON l.id_rs = r.id_rs "
		"WHERE l.id_supir = %d "
		"ORDER BY l.tanggal DESC",
		SESSION_ID_SUPIR
	);

	mysql_query(conn, query);
	res = mysql_store_result(conn);

	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	posisi(x, y);
	printf("===========================================================================================");
	posisi(x, y + 1);
	printf("| NO | ID | USER                    | PLAT       | RUMAH SAKIT        | STATUS           |");
	posisi(x, y + 2);
	printf("===========================================================================================");

	while ((row = mysql_fetch_row(res)))
	{
		posisi(x, row_y++);
		printf("| %2d | %2s | %-23s | %-10s | %-18s | %-16s |",
			no++,
			row[0], // id laporan
			row[1], // user
			row[2], // plat
			row[3], // rs
			row[4]  // status
		);
	}

	posisi(x, row_y);
	printf("===========================================================================================");

	mysql_free_result(res);
}

void tampilan_profil_supir()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[400];

	sprintf(query,
		"SELECT s.nama_supir, s.no_hp, s.email, "
		"IFNULL(a.plat_nomor,'-'), IFNULL(a.status,'-') "
		"FROM supir s "
		"LEFT JOIN ambulans a ON s.id_supir = a.id_supir "
		"WHERE s.id_supir=%d",
		SESSION_ID_SUPIR
	);

	if (mysql_query(conn, query))
	{
		posisi(5, 5);
		printf("Gagal mengambil data profil supir!");
		getch();
		return;
	}

	res = mysql_store_result(conn);
	if (!res || mysql_num_rows(res) == 0)
	{
		posisi(5, 5);
		printf("Data supir tidak ditemukan!");
		getch();
		return;
	}

	row = mysql_fetch_row(res);

	// ===== TAMPILAN =====
	rgbtext(0, 79, 255);
	rgbbgt(211, 211, 211);

	kotak(60, 14, 10, 5, 211, 211, 211, 250, 250, 250);

	posisi(12, 6);
	printf("PROFIL SUPIR");

	posisi(12, 8);
	printf("Nama Supir     : %s", row[0]);

	posisi(12, 9);
	printf("No HP          : %s", row[1]);

	posisi(12, 10);
	printf("Email          : %s", row[2]);

	posisi(12, 11);
	printf("Plat Ambulans  : %s", row[3]);

	posisi(12, 12);
	printf("Status         : %s", row[4]);

	posisi(12, 14);
	printf("ESC : Kembali");

	mysql_free_result(res);

	// ===== INPUT =====
	while (1)
	{
		int ch = getch();
		if (ch == 27) break;
	}
}
