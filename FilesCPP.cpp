#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
// #pragma warning(disable : 4996)

using namespace std;
/*
int filesDemo()
{
	//	clrscr();
	setlocale(0, "Rus");

	int handle1 = -1, handle2 = -1, nrd = 0, nwr = 0, trd = 0, twr = 0, fsize = 0;
	const char* name1 = ".//Debug//sourceFile.txt", * name2 = ".//Debug//copy2.cpp";
	char msg[1024] = "";

	// 1st way
	if ((handle1 = open(name1, O_RDONLY | O_TEXT)) == -1)
	{
		perror("Ошибка открытия для чтения файла №1 (исходного)");
		return 1;
	}
	else
	{
		if ((handle2 = open(".//Debug//copy1.cpp", O_CREAT | O_WRONLY | O_TRUNC | O_TEXT, S_IREAD | S_IWRITE)) == -1)
		{
			perror("Ошибка открытия для записи файла №2 (целевого)");
			return 2;
		}
		else
		{
			while ((nrd = read(handle1, msg, 1024)) > 0)
			{
				nwr = write(handle2, msg, nrd);
				trd += nrd;
				twr += nwr;
			}

			fsize = lseek(handle1, 0L, SEEK_END);

			close(handle2);

			printf_s("\n1) Копирование содержимого файла files.txt блоками по 1 кБ (1024 Б) при помощи функции OPEN в файл copy1.cpp\n");
			printf_s("Всего считано:\t\t%10d Б\nВсего записано:\t\t%10d Б\nРазмер файла:\t\t%10d Б\n\n", trd, twr, fsize);
		}
		close(handle1);
	}

	// 2nd way
	FILE* f_in, * f_out;
	char ch;

	if ((f_in = fopen(name1, "rb")) == NULL)
	{
		perror("Ошибка открытия для чтения файла №1 (исходного)");
		return 3;
	}
	else
	{
		if ((f_out = fopen(name2, "wb")) == NULL)
		{
			perror("Ошибка открытия для записи файла №3 (целевого)");
			return 4;
		}
		else
		{
			fsize = 0;
			while (!feof(f_in))
			{
				ch = fgetc(f_in);

				if (!feof(f_in))
				{
					fsize++;
					fputc(ch, f_out);
				}
			}

			fclose(f_out);

			printf_s("\n2)  Копирование содержимого файла files.txt по 1 символу при помощи функции FOPEN в файл copy2.cpp\n");
			printf_s("Всего записано:\t\t%10d Б\n\n", fsize);
		}

		// 3rd way
		name2 = ".//Debug//copy3.cpp";
		if ((f_out = fopen(name2, "wb")) == NULL)
		{
			perror("Ошибка открытия для записи файла №4 (целевого)");
			return 5;
		}
		else
		{
			fsize = 0;
			fseek(f_in, 0L, SEEK_SET);

			while (!feof(f_in))
			{
				if (fgets(msg, 1024, f_in) != NULL)
				{
					fputs(msg, f_out);
					fsize++;
				}
			}

			fclose(f_in);
			fclose(f_out);

			printf_s("\n3) Копирование файла files.txt по 1 строке при помощи функции FOPEN в файл copy3.cpp\n");
			printf_s("Всего считано:\t\t%10d строк\n\n", fsize);
		}
	}

	return 0;
}


void array_fill_from_file(const char* filename)
{
	FILE* f_in, * f_out;

	printf_s("\nСчитывание чисел для заполнения элементов массива:\n");
	int a[10], i = 0;

	if ((f_in = fopen(filename, "r")) == NULL)
	{
		perror("Ошибка открытия для чтения файла №5 с данными для массива");
		return;
	}
	else
	{
		int k = 0;
		while (!feof(f_in) && (i < 10))
		{
			k = fscanf(f_in, "%d", &a[i]);
			if (k > 0)
				printf_s("a[%d]=%d, ", i - 1, a[i++]);
		}
		fclose(f_in);
	}
}


void files_secured()
{
	FILE* f = NULL;
	string s2 = "123456789012345678901234567890";

	char s[10] = "qwertyiop";
	char s1[31];
	if (!fopen_s(&f, ".//Debug//test.txt", "w+"))
	{
		cout << fwrite(s2.c_str(), 1, s2.length(), f) << endl;
		fclose(f);

		fopen_s(&f, ".//Debug//test.txt", "r");
		size_t n = fread(s1, 1, sizeof(s1) - 1, f);
		cout << n << endl;
		s1[n] = '\0';
		cout << s1 << endl;
		fclose(f);
	}
	return;
}
*/

int openfile(const char* filename, int flags)
{
	int fd;

	_sopen_s(&fd, filename, flags, _SH_DENYNO, _S_IREAD | _S_IWRITE);

	return fd;
}

void secured_files(const char* filename)
{
	int fd = -1, nrd = 0, trd = 0;
	char buffer[1024] = "";

	if ((fd = openfile(filename, O_RDONLY | O_TEXT)) == -1)
	{
		perror("Ошибка открытия файла для чтения");
		return;
	}
	else
	{
		while ((nrd = _read(fd, buffer, 1024)) > 0)
		{
			trd += nrd;
			buffer[nrd] = '\0';
			cout << buffer;
		}

		_lseek(fd, 0L, SEEK_END);
	}
	_close(fd);
}

int main()
{
	setlocale(0, "ru");
	// cout << filesDemo();
	secured_files(".//Debug//copy1.cpp");
	// array_fill_from_file(".//Debug//numbers_array.txt");
	// files_secured();

	return 0;
}