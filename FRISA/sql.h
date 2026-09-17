#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "session.h" 

#define MAX_RS 50
#define SHOW_ITEM 3


// TAMBAHKAN DI ATAS
extern char input_email[35];
extern char input_password[30];
char nama_rs[MAX_RS][100];
int id_rs[MAX_RS];
extern int total_rs;

extern MYSQL* conn;

MYSQL* koneksiDB();
void putusKoneksi(MYSQL* conn);
void registersql();
int loginsql();
int listrs(x,y);
char* getNamaRSById(id);
void tambahadminsql();
int hitung_ambulans_free();
int cari_admin_by_nama(
	char* nama_cari,
	int* id_admin,
	char* nama,
	char* username,
	char* password
);
void edit_adminsql();
void hapus_adminsql();
void tampil_supir_ambulans( x, y);
void tampil_semua_supir_ambulans(int x, int y);
void tambah_ambulans_dan_supir();
int hapus_ambulans_dan_supir();
void edit_ambulans_dan_supir();
int get_biaya_user();
int pilih_ambulans();
int hitung_biaya();
void pesan_ambulans();
int pilih_ambulans_dropdown(x, y);
void proses_pesan_ambulans(id_rs, id_amb);
int cek_laporan_aktif_user();
void tampilan_laporan_aktif();
void batal_laporan();
void tampilan_laporan_user(x, y);
void tampilan_total_laporan(x, y);
void tampil_semua_laporan(x, y);
void tambah_rs();
void edit_rs();
void hapus_rs();
void tampil_rs_pagination(x, y, halaman);
int loginsql_admin(char* username, char* password);
void logout_admin();
int loginsupir_sql();
void tampil_tugas_supir(int x, int y);
void tampilan_profil_supir();