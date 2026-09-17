#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 

int tampilan()
{
	int chooseutama, role;

	SetConsoleOutputCP(65001);
	// pilihrole(1);

	do
	{
		borderutama();
		frisa();
		chooseutama = menu_utama();

		switch (chooseutama)
		{
		case 2:
			borderutama();
			daftar();
			loginuser();
			break;
		case 1:
			borderutama();
			role = menu_role();
			switch (role)
			{
			case 3:
				loginuser();
				halamanuser();
				break;
			case 1:
				loginadmin();
				halamanadmin();
				break;
			case 2:
				loginsupir();
				halamansupir();
				break;
			}
		case 3: system("cls"); borderutama(); about("about.txt"); getch();break;
		case 4: bye();
			break;
		}
	} while (1);
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(oldCP);
}

int bye() {
	system("cls"); printf("BYEE...."); exit(0);
}