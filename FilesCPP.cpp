#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <io.h>
#include <time.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <fstream>
#include <string>
#pragma warning(disable : 4996)

using namespace std;

struct students
{
	string			first_name;
	string			second_name;
	unsigned short	age = 0;
	unsigned short	height = 0;
	unsigned short	weight = 0;
	string			address;
};


int filesDemo()
{
	long t1 = time(NULL), t2;
	cout << t1 << endl;
	//	clrscr();
	setlocale(0, "Rus");

	int handle1 = -1, handle2 = -1, nrd = 0, nwr = 0, trd = 0, twr = 0, fsize = 0;
	const char* name1 = "arc.zip", * name2 = "arc2.zip", * name3 = "arc3.zip", * name4 = "arc4.zip";
	char msg[1024] = "";

	// 1st way
	if ((handle1 = open(name1, O_RDONLY | O_BINARY)) == -1)
	{
		perror("Ошибка открытия для чтения файла №1 (исходного)");
		return 1;
	}
	else
	{
		if ((handle2 = open(name2, O_CREAT | O_WRONLY | O_TRUNC | O_BINARY, S_IREAD | S_IWRITE)) == -1)
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

			printf_s("\n1) Копирование содержимого файла files.txt блоками по 1 кБ (1024 Б) при помощи функции OPEN в файл arc1.zip\n");
			printf_s("Всего считано:\t\t%10d Б\nВсего записано:\t\t%10d Б\nРазмер файла:\t\t%10d Б\n\n", trd, twr, fsize);
		}
		close(handle1);
		t2 = time(NULL);
		cout << "1: " << t2 - t1 << endl;
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
		t1 = time(NULL);
		if ((f_out = fopen(name3, "wb")) == NULL)
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
			t2 = time(NULL);
			cout << "2: " << t2 - t1 << endl;

			printf_s("\n2)  Копирование содержимого файла files.txt по 1 символу при помощи функции FOPEN в файл arc2.zip\n");
			printf_s("Всего записано:\t\t%10d Б\n\n", fsize);
		}

		// 3rd way
		if ((f_out = fopen(name4, "wb")) == NULL)
		{
			perror("Ошибка открытия для записи файла №4 (целевого)");
			return 5;
		}
		else
		{
			t1 = time(NULL);
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
			t2 = time(NULL);
			cout << "3: " << t2 - t1 << endl;

			printf_s("\n3) Копирование файла по 1 строке при помощи функции FOPEN в файл arc3.zip\n");
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

void filestreams()
{
	unsigned short N = 1;

	setlocale(0, "Rus");

	cout << "Введите кол-во студентов в группе: ";
	if (cin >> N)
	{
		cout << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // очистка буфера ввода перед считыванием строки с пробелами

		ofstream file1("students.txt", ios::out | ios::trunc | ios::binary);
		students* st1 = new students[N];

		file1 << N << endl;
		for (char i = 0; i < N; i++)
		{
			cout << "\nИмя: ";
			getline(cin, st1[i].first_name, '\n');
			file1 << st1[i].first_name << endl;
			cout << "\nФамилия: ";
			getline(cin, st1[i].second_name, '\n');
			file1 << st1[i].second_name << endl;
			cout << "\nВозраст: ";
			cin >> st1[i].age;
			file1 << st1[i].age << endl;
			cout << "\nРост: ";
			cin >> st1[i].height;
			file1 << st1[i].height << endl;
			cout << "\nВес: ";
			cin >> st1[i].weight;
			file1 << st1[i].weight << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера ввода перед считыванием строки с пробелами
			cout << "\nАдрес: ";
			getline(cin, st1[i].address, '\n');
			file1 << st1[i].address << endl;
		}
		file1.close();

		cout << "\n\nReading data from file:\n";
		ifstream file2("students.txt");
		file2 >> N;
		string temp;
		getline(file2, temp);  // считывание дополнительного разделителя после считанного нестрокового значения

		students* st2 = new students[N];

		for (char i = 0; i < N; i++)
		{
			getline(file2, st2[i].first_name);
			cout << "\nИмя: ";
			cout << st2[i].first_name;
			getline(file2, st2[i].second_name);
			cout << "\nФамилия: ";
			cout << st2[i].second_name;
			file2 >> st2[i].age;
			cout << "\nВозраст: ";
			cout << st2[i].age;
			file2 >> st2[i].height;
			cout << "\nРост: ";
			cout << st2[i].height;
			file2 >> st2[i].weight;
			cout << "\nВес: ";
			cout << st2[i].weight;
			getline(file2, temp);  // считывание дополнительного разделителя после считанного нестрокового значения
			getline(file2, st2[i].address);
			cout << "\nАдрес: ";
			cout << st2[i].address;
			cout << '\n';

			// Проверка достижения конца файла 
			getline(file2, temp);  // считывание дополнительного разделителя после считанного нестрокового значения
			if (file2.eof())
				break;
			file2.seekg(-2, ios_base::cur);
		}
		file2.close();

		cout << endl << endl;
	}
	else
	{
		cout << "Error input for number N";
	}
}

int main()
{
	setlocale(0, "ru");
	cout << filesDemo();
	secured_files("copy1.cpp");
	files_secured();

	array_fill_from_file("numbers_array.txt");



	return 0;
}