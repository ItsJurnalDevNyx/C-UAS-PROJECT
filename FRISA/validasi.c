#include "header.h"
#include "lib.h"
#include "tampilan.h"
#include "validasi.h"
#include "sql.h"
#include "session.h" 


int valtgl(int imin, int imax, int batas)
{
    int ch, i = 0;
    char temp[10];

    while (1)
    {
        ch = getch();

        if (ch == 27)
            return 0;

        else if (ch == 13 && i > 0)
        {
            temp[i] = '\0';
            int nilai = atoi(temp);
            if (nilai >= imin && nilai <= imax)
                return nilai;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (isdigit(ch) && i < batas)
        {
            temp[i++] = ch;
            printf("%c", ch);
        }
    }
}

int val_nama()
{
    int ch, i = 0;
    int valid;

    while (1)
    {
        ch = getch();
        valid = 1;

        if (ch == 27) 
            return 0;

        else if (ch == 13 && i >= 7) 
        {
            get_nama[i] = '\0';
            return 1;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (ch >= 32 && ch <= 126 && i < 30) 
        {

            if (i >= 2 &&
                get_nama[i - 1] == ch &&
                get_nama[i - 2] == ch)
            {
                valid = 0;
            }

            if (ch >= 'A' && ch <= 'Z')
            {
                if (i != 0 && get_nama[i - 1] != ' ')
                {
                    valid = 0;
                }
            }


            if (valid)
            {
                get_nama[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}



int val_nik()
{
    int ch, i = 0;

    while (1)
    {
        ch = getch();

        if (ch == 27)
            return 0;

        else if (isdigit(ch) && i < 16)
        {
            nik[i++] = ch;
            printf("%c", ch);
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (ch == 13 && i == 16)
        {
            nik[i] = '\0';
            return 1;
        }
    }
}


int valemail()
{
    int ch, i = 0;
    int ada_at = 0;
    int valid;

    while (1)
    {
        ch = getch();
        valid = 1;

        if (ch == 27) 
            return 0;

        else if (ch == 13 && ada_at && i <= 25) 
        {
            get_email[i] = '\0';
            return 1;
        }
        else if (ch == 8 && i > 0) 
        {
            i--;
            printf("\b \b");

            if (get_email[i] == '@')
                ada_at = 0;
        }
        else if (i < 25)
        {
            if (ada_at && (ch == 'y' || ch == 'Y'))
            {
                char domain[] = "yahoo.com";
                int j = 0;

                while (domain[j] && i < 25)
                {
                    get_email[i++] = domain[j];
                    printf("%c", domain[j]);
                    j++;
                }
                valid = 0;
            }
            else if (ada_at && (ch == 'g' || ch == 'G'))
            {
                char domain[] = "gmail.com";
                int j = 0;

                while (domain[j] && i < 25)
                {
                    get_email[i++] = domain[j];
                    printf("%c", domain[j]);
                    j++;
                }
                valid = 0;
            }

            if (valid)
            {
                if (
                    (ch >= '0' && ch <= '9') ||
                    (ch >= 'a' && ch <= 'z') ||
                    (ch >= 'A' && ch <= 'Z') ||
                    ch == '@' || ch == '.'
                    )
                {
                    if (ch == '@' && !ada_at)
                        ada_at = 1;

                    if (!(ch == '@' && ada_at && i > 0 && get_email[i - 1] == '@'))
                    {
                        get_email[i++] = ch;
                        printf("%c", ch);
                    }
                }
            }
        }
    }
}


int valnohp()
{
    int ch, i = 0;

    while (1)
    {
        ch = getch();

        if (ch == 27)
            return 0;

        else if (isdigit(ch) && i < 13)
        {
            hp[i++] = ch;
            printf("%c", ch);
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (ch == 13 && i >= 10)
        {
            hp[i] = '\0';
            return 1;
        }
    }
}

int validasi_password()
{
    int ch, i = 0;
    int huruf = 0, angka = 0, simbol = 0;
    char temp[21];

    while (1)
    {
        ch = getch();

        if (ch == 27)
            return 0;

        else if (ch == 13)
        {
            if (i >= 8 && huruf && angka && simbol)
            {
                temp[i] = '\0';
                strcpy(get_password, temp);
                return 1;
            }
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (i < 20)
        {
            temp[i++] = ch;
            printf("*");

            if (isalpha(ch)) huruf = 1;
            else if (isdigit(ch)) angka = 1;
            else simbol = 1;
        }
    }
}

int val_pass_admin()
{
    return validasi_password();
}

int val_pass()
{
    return validasi_password();
}

int val_uname()
{
    int ch, i = 0;

    while (1)
    {
        ch = getch();

        if (ch == 27)
            return 0;

        else if (ch == 13 && i >= 8)
        {
            get_username[i] = '\0';
            return 1;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (isalnum(ch) && i < 19)
        {
            get_username[i++] = ch;
            printf("%c", ch);
        }
    }
}

int val_plat(char* plat)
{
    int ch, i = 0;

    while (1)
    {
        ch = getch();

        if (ch == 27)
            return 0;

        else if (ch == 13 && i >= 9)
        {
            plat[i] = '\0';
            return 1;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (i < 11 && (isdigit(ch) || isupper(ch) || ch == ' '))
        {
            plat[i++] = ch;
            printf("%c", ch);
        }
    }
}

int val_alamat()
{
    int ch, i = 0;

    while (1)
    {
        ch = getch();

        if (ch == 27)
            return 0;

        else if (ch == 13 && i >= 7)
        {
            get_alamat[i] = '\0';
            return 1;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (i < 30)
        {
            get_alamat[i++] = ch;
            printf("%c", ch);
        }
    }
}

int val_id()
{
    int ch, i = 0;
    char temp[4];

    while (1)
    {
        ch = getch();

        if (ch == 27)       
            return 0;

        else if (ch == 13)    
        {
            if (i > 0)
            {
                temp[i] = '\0';
                return atoi(temp);
            }
        }

        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }

        else if (isdigit(ch) && i < 3)
        {
            temp[i++] = ch;
            printf("%c", ch);
        }
    }
}
