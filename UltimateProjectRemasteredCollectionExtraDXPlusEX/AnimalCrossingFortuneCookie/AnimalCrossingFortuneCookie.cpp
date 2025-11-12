#define _CRT_SECURE_NO_WARNINGS
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <time.h>
#include <string>

using namespace std;

int num[51] = { NULL };
char fortune[51][75] = { NULL }, prize[51][20] = { NULL }, addtime[51][80] = { NULL };

//Цвета:
enum {
	clBlack, clNavy, clGreen, clTeal, clBrown,
	clPurple, clOlive, clGray, clSilver, clBlue,
	clLime, clCyan, clRed, clMagneta, clYellow,
	clWhite
};

void ShowList();
void ShowCookie(int);

void CursorShow(bool on = true)
{
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = on;
	CCI.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}
void SetConsoleWinSizePosition(int width = 0, int heigth = 0, short x_position = 0, short y_position = 0)
{
	HWND hWnd = GetForegroundWindow();

	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetWindowPos(hWnd, NULL, x_position, y_position, 0, 0, NULL);
	SMALL_RECT windowSize;
	windowSize.Bottom = heigth;
	windowSize.Left = 0;
	windowSize.Right = width;
	windowSize.Top = 0;
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	COORD bufferSize = { width + 1, heigth + 1 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}
void SetConsoleColorTextBackground(unsigned short Tex = clWhite, unsigned short Bg = clBlack)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Bg = Bg << 4 | Tex;
	SetConsoleTextAttribute(hConsole, Bg);
}
void SetConsoleCursorPosition(short x_position, short y_position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position, y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}
void AddFrame(int col, const char title[])
{
	int x = (75 - (strlen(title) + 8)) / 2;
	SetConsoleOutputCP(866);
	SetConsoleColorTextBackground(col);
	SetConsoleCursorPosition(x, 1);
	cout << char(201);
	for (int i = 0; i < strlen(title) + 6; i++)
	{
		cout << char(205);
	}
	cout << char(187);
	SetConsoleCursorPosition(x, 2);
	cout << char(186);
	SetConsoleOutputCP(1251);
	SetConsoleColorTextBackground(clGray);
	if (title == "A N I M A L    C R O S S I N G")
	{
		SetConsoleOutputCP(866);
		SetConsoleColorTextBackground(clYellow);
	}
	cout << "   " << title << "   ";
	SetConsoleOutputCP(866);
	SetConsoleColorTextBackground(col);
	cout << char(186);
	SetConsoleCursorPosition(x, 3);
	cout << char(200);
	for (int i = 0; i < strlen(title) + 6; i++)
	{
		cout << char(205);
	}
	SetConsoleColorTextBackground(col);
	cout << char(188) << "\n\n\n";
	SetConsoleOutputCP(1251);
}
void AddButton(int x, int y, int col, const char title[])
{
	SetConsoleOutputCP(866);
	int f1 = 214, h1 = 196, h2 = 205, f2 = 191, v2 = 179, v1 = 186, f3 = 200, f4 = 190;
	//if(col!=7)
	//{
	//	f1=218; h2=196; f2=191; v1=179; f3=192; f4=217;
	//}
	SetConsoleCursorPosition(x, y);
	SetConsoleColorTextBackground(col);
	cout << char(f1);
	for (int i = 0; i < strlen(title) + 6; i++)
	{
		cout << char(h1);
	}
	cout << char(f2);
	SetConsoleCursorPosition(x, y + 1);
	cout << char(v1);
	SetConsoleOutputCP(1251);
	SetConsoleColorTextBackground(clGray);
	cout << "   " << title << "   ";
	SetConsoleOutputCP(866);
	SetConsoleColorTextBackground(col);
	cout << char(v2);
	SetConsoleCursorPosition(x, y + 2);
	cout << char(f3);
	for (int i = 0; i < strlen(title) + 6; i++)
	{
		cout << char(h2);
	}
	SetConsoleColorTextBackground(col);
	cout << char(f4);
	SetConsoleOutputCP(1251);
}
void TextAlign(int y, int col, const char title[])
{
	int x = (75 - (strlen(title))) / 2;
	SetConsoleOutputCP(1251);
	SetConsoleColorTextBackground(col);
	SetConsoleCursorPosition(x, y);
	cout << title;
}
void StrAlign(int y, int col, const char title[])
{
	int x = (75 - (strlen(title))) / 2;
	SetConsoleOutputCP(866);
	SetConsoleColorTextBackground(col);
	SetConsoleCursorPosition(x, y);
	cout << title;
}
void Villiger()
{
	CursorShow(false);
	char tmpstr[31] = { NULL };
	for (int i = 0; i < 28; i++)
	{
		tmpstr[i] = '_';
	}
	StrAlign(11, clOlive, tmpstr);
	StrAlign(17, clGray, "_____           _____");
	StrAlign(18, clGray, "/     \\         /     \\");
	StrAlign(19, clGray, "|     |         |     |");
	StrAlign(20, clGray, "|     |         |     |");
	StrAlign(21, clGray, "|_____|         |_____|");
	SetConsoleCursorPosition(37, 22);
	SetConsoleColorTextBackground(clPurple);
	cout << char(30);
	SetConsoleColorTextBackground(clTeal, clNavy);
	SetConsoleCursorPosition(46, 19);
	cout << "  ";
	SetConsoleCursorPosition(46, 20);
	cout << "  ";
	SetConsoleCursorPosition(30, 19);
	cout << "  ";
	SetConsoleCursorPosition(30, 20);
	cout << "  ";
	SetConsoleColorTextBackground(clOlive, clBlack);
	SetConsoleCursorPosition(22, 12);
	cout << "/";
	SetConsoleCursorPosition(22 + 29, 12);
	cout << "\\";
	SetConsoleCursorPosition(21, 13);
	cout << "/";
	SetConsoleCursorPosition(22 + 30, 13);
	cout << "\\";
	SetConsoleCursorPosition(21, 14);
	cout << "|";
	SetConsoleCursorPosition(21 + 31, 14);
	cout << "|";
	SetConsoleCursorPosition(21, 15);
	cout << "|/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\|";
	SetConsoleColorTextBackground(clSilver);
	for (int i = 16; i <= 22; i++)
	{
		SetConsoleCursorPosition(21, i);
		cout << "|";
		SetConsoleCursorPosition(52, i);
		cout << "|";
	}
}
void SaveCookie()
{
	FILE* f = fopen("cookie.save", "w");
	if (f)
	{
		for (int i = 1; i < 51; i++)
		{
			fwrite(&num[i], sizeof(int), 1, f);
			int tmp = strlen(fortune[i]) + 1;
			fwrite(&tmp, sizeof(int), 1, f);
			fwrite(&fortune[i], sizeof(char), tmp, f);
			tmp = strlen(prize[i]) + 1;
			fwrite(&tmp, sizeof(int), 1, f);
			fwrite(&prize[i], sizeof(char), tmp, f);
			tmp = strlen(addtime[i]) + 1;
			fwrite(&tmp, sizeof(int), 1, f);
			fwrite(&addtime[i], sizeof(char), tmp, f);
		}
		fclose(f);
	}
}
void AddCookie()
{
	int fin = 1;
	while (1)
	{
		CursorShow(true);
		system("cls");
		bool allcookies = true;
		for (int i = 1; i < 51; i++)
		{
			if (num[i] == NULL)
			{
				allcookies = false;
			}
		}
		if (allcookies == true)
		{
			TextAlign(2, 2, "Вітаю, все печиво зібрані!");
			TextAlign(4, 2, "Ти можеш коли завгодно переглянути інформацію про них у \"Список печива\".");
			AddButton(18, 6, 2, "Назад!");
			AddButton(34, 6, 7, "Список печива.");
			Villiger();
			SetConsoleColorTextBackground(clSilver, clBlack);
			while (1)
			{
				int k = _getch();
				if (k == 13)
					break;
				if (k == RIGHT && fin != 2)
				{
					fin = 2;
					AddButton(18, 6, 7, "Назад.");
					AddButton(34, 6, 3, "Список печива!");
				}
				if (k == LEFT && fin != 1)
				{
					fin = 1;
					AddButton(18, 6, 2, "Назад!");
					AddButton(34, 6, 7, "Список печива.");
				}
			}
			break;
		}
		AddFrame(clGreen, "Додавання печива");
		int tmp;
		SetConsoleOutputCP(1251);
		SetConsoleColorTextBackground(clGray);
		cout << "1. Введи номер виграшу: ";
		TextAlign(22, clYellow, "Якщо ти вибрав це поле випадково і хочеш вийти - введи 0.");
		SetConsoleColorTextBackground(clGray);
		SetConsoleCursorPosition(25, 6);
		cin >> tmp;
		cin.ignore();
		if (tmp == 0)
		{
			break;
		}
		SetConsoleCursorPosition(0, 22);
		cout << "                                                                       ";
		SetConsoleCursorPosition(0, 7);
		if (num[tmp] != NULL)
		{
			SetConsoleColorTextBackground(clGreen);
			TextAlign(9, 2, "Печиво з таким номером вже було додано раніше.");
			TextAlign(10, 2, "Дані про неї можна переглянути в \"Списку печива\".");
			/*AddButton(26, 12, clGreen, "В главное меню!");*/
			int sel = 2;
			AddButton(10 + 3, 12, clGray, "Назад.");
			AddButton(26 + 3, 12, clGreen, "Додати!");
			AddButton(48, 12, clGray, "Переглянути.");
			while (1)
			{
				int k = _getch();
				if (k == 13)
					break;
				if (k == RIGHT && sel != 3)
				{
					++sel;
				}
				if (k == LEFT && sel != 1)
				{
					--sel;
				}
				if (sel == 1)
				{
					AddButton(10 + 3, 12, clOlive, "Назад!");
					AddButton(26 + 3, 12, clGray, "Додати.");
					AddButton(48, 12, clGray, "Переглянути.");
				}
				if (sel == 2)
				{
					AddButton(10 + 3, 12, clGray, "Назад.");
					AddButton(26 + 3, 12, clGreen, "Додати!");
					AddButton(48, 12, clGray, "Переглянути.");
				}
				if (sel == 3)
				{
					AddButton(10 + 3, 12, clGray, "Назад.");
					AddButton(26 + 3, 12, clGray, "Додати.");
					AddButton(48, 12, clTeal, "Переглянути!");
				}
			}
			if (sel == 1)
				break;
			if (sel == 2)
				continue;
			if (sel == 3)
			{
				ShowCookie(tmp);
				break;
			}
		}
		if (tmp > 50 || tmp < 0)
		{
			SetConsoleColorTextBackground(clYellow);
			cout << "\n\n Хм... Мабуть, ти помилився. Номер виграшу повинен бути в межах від 1 до 50.\n\t\t\tХочеш спробувати ще раз?\n";
			AddButton(24, 13, 2, "Так!");
			AddButton(39, 13, 7, "Ні.");
			int sel = 1;
			while (1)
			{
				int k = _getch();
				if (k == 13)
					break;
				if (k == RIGHT && sel != 2)
				{
					sel = 2;
					AddButton(24, 13, 7, "Так.");
					AddButton(39, 13, 12, "Ні!");
				}
				if (k == LEFT && sel != 1)
				{
					sel = 1;
					AddButton(24, 13, 2, "Так!");
					AddButton(39, 13, 7, "Ні.");
				}
			}
			if (sel == 1)
				continue;
			if (sel == 2)
				break;
		}
		num[tmp] = tmp;
		SetConsoleColorTextBackground(clGray);
		cout << "\n2. Введи опис виграшу (фортуни).\n\n   ";
		cin.getline(fortune[tmp], 75);
		cout << "\n3. Введи назву призу: ";
		cin.getline(prize[tmp], 20);
		// время
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(addtime[tmp], 80, "%x | %X", timeinfo);
		//
		FILE* f = fopen("cookie.save", "w");
		if (f)
		{
			for (int i = 1; i < 51; i++)
			{
				fwrite(&num[i], sizeof(int), 1, f);
				int tmp = strlen(fortune[i]) + 1;
				fwrite(&tmp, sizeof(int), 1, f);
				fwrite(&fortune[i], sizeof(char), tmp, f);
				tmp = strlen(prize[i]) + 1;
				fwrite(&tmp, sizeof(int), 1, f);
				fwrite(&prize[i], sizeof(char), tmp, f);
				tmp = strlen(addtime[i]) + 1;
				fwrite(&tmp, sizeof(int), 1, f);
				fwrite(&addtime[i], sizeof(char), tmp, f);
			}
			fclose(f);
			SetConsoleColorTextBackground(clGreen);
			cout << "\n\n\t\t     Ура! Дані про печиво додані!\n\t\t\t Хочеш додати ще одну?";
			AddButton(24, 18, 2, "Так!");
			AddButton(39, 18, 7, "Ні.");
			int sel = 1;
			while (1)
			{
				int k = _getch();
				if (k == 13)
					break;
				if (k == RIGHT && sel != 2)
				{
					sel = 2;
					AddButton(24, 18, 7, "Так.");
					AddButton(39, 18, 12, "Ні!");
				}
				if (k == LEFT && sel != 1)
				{
					sel = 1;
					AddButton(24, 18, 2, "Так!");
					AddButton(39, 18, 7, "Ні.");
				}
			}
			if (sel == 1)
				continue;
			if (sel == 2)
				break;
		}
		else
		{
			SetConsoleColorTextBackground(clYellow);
			cout << "\nХмм... не вдалося зберегти дані.\nСпробуйте звільнити пам'ять на жорсткому диску і спробуй ще раз.\n";
			SetConsoleColorTextBackground(clGray);
			break;
		}
	}
	if (fin == 2)
		ShowList();
}
void ShowCookie(int ch)
{
	CursorShow(false);
	system("cls");
	AddFrame(clTeal, "Дані про печиво.");
	SetConsoleOutputCP(1251);
	SetConsoleColorTextBackground(clGray);
	cout << "\n1. Номер: " << ch << "\n\n";
	cout << "2. Опис:\n\n   ";
	if (fortune[ch][0] != NULL)
		cout << fortune[ch] << "\n\n";
	else
		cout << "???\n\n";
	cout << "3. Приз: ";
	if (prize[ch][0] != NULL)
		cout << prize[ch] << "\n\n";
	else
		cout << "???\n\n";
	cout << "Додано: ";
	if (addtime[ch][0] != NULL)
		cout << addtime[ch];
	else
		cout << "???";
	if (num[ch] == NULL)
	{
		AddButton(30, 17, clTeal, "Назад!");
		while (1)
		{
			int k = _getch();
			if (k == 13)
				break;
		}
	}
	else
	{
		int sel = 1;
		bool skip = 0;
		AddButton(10, 17, clTeal, "Назад!");
		AddButton(26, 17, clGray, "Редагувати.");
		AddButton(50, 17, clGray, "Видалити.");
		while (1)
		{
			while (1)
			{
				int k;
				if (skip == 0)
					k = _getch();
				else
					k = 0;
				if (k == 13)
					break;
				if (k == RIGHT && sel != 3)
				{
					sel += 1;
				}
				if (k == LEFT && sel != 1)
				{
					sel -= 1;
				}
				if (sel == 1)
				{
					AddButton(10, 17, clTeal, "Назад!");
					AddButton(26, 17, clGray, "Редагувати.");
					AddButton(50, 17, clGray, "Видалити.");
				}
				if (sel == 2)
				{
					AddButton(10, 17, clGray, "Назад.");
					AddButton(26, 17, clOlive, "Редагувати!");
					AddButton(50, 17, clGray, "Видалити.");
				}
				if (sel == 3)
				{
					AddButton(10, 17, clGray, "Назад.");
					AddButton(26, 17, clGray, "Редагувати.");
					AddButton(50, 17, clBrown, "Видалити!");
				}
				if (skip == 1)
					skip = 0;
			}
			if (sel == 1)
				break;
			if (sel == 2)
			{
				int ok = 1;
				SetConsoleColorTextBackground(clTeal);
				SetConsoleCursorPosition(0, 7);
				cout << "1. Номер:";
				while (1)
				{
					int k = _getch();
					if (k == 13)
						break;
					if (k == RIGHT && sel != 3)
					{
						sel += 1;
						skip = 1;
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 7);
						cout << "1. Номер:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 9);
						cout << "2. Опис:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 13);
						cout << "3. Приз:";
						break;
					}
					if (k == LEFT && sel != 1)
					{
						sel -= 1;
						skip = 1;
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 7);
						cout << "1. Номер:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 9);
						cout << "2. Опис:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 13);
						cout << "3. Приз:";
						break;
					}
					if (k == DOWN && ok != 3) //вниз
					{
						ok += 1;
					}
					if (k == UP && ok != 1) // вгору
					{
						ok -= 1;
					}
					if (ok == 1)
					{
						SetConsoleColorTextBackground(clTeal);
						SetConsoleCursorPosition(0, 7);
						cout << "1. Номер:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 9);
						cout << "2. Опис:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 13);
						cout << "3. Приз:";
					}
					if (ok == 2)
					{
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 7);
						cout << "1. Номер:";
						SetConsoleColorTextBackground(clTeal);
						SetConsoleCursorPosition(0, 9);
						cout << "2. Опис:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 13);
						cout << "3. Приз:";
					}
					if (ok == 3)
					{
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 7);
						cout << "1. Номер:";
						SetConsoleColorTextBackground(clGray);
						SetConsoleCursorPosition(0, 9);
						cout << "2. Опис:";
						SetConsoleColorTextBackground(clTeal);
						SetConsoleCursorPosition(0, 13);
						cout << "3. Приз:";
					}
				}
				if (skip == 1)
				{
					continue;
				}
				int tmp = 0;
				CursorShow(true);
				if (ok == 1)
				{
					SetConsoleCursorPosition(10, 7);
					cout << "  ";
					SetConsoleCursorPosition(10, 7);
					SetConsoleColorTextBackground(clGray);
					cin >> tmp;
					cin.ignore();
					if (tmp < 1 || tmp>50)
					{
						SetConsoleColorTextBackground(clBrown);
						SetConsoleCursorPosition(20, 7);
						char strtmp[] = "Помилка! Номер повинен бути в межах від 1 до 50.";
						for (int i = 0; i < strlen(strtmp); i++)
						{
							cout << strtmp[i];
							Sleep(20);
						}
						_getch();
						SetConsoleCursorPosition(0, 7);
						SetConsoleColorTextBackground(clGray);
						cout << "1. Номер: " << ch << "                                                              ";
					}
					if (tmp > 0 && tmp <= 50)
					{
						num[tmp] = tmp;
						num[ch] = NULL;
						strcpy(fortune[tmp], fortune[ch]);
						strcpy(prize[tmp], prize[ch]);
						for (int i = 0; i < 75; i++)
						{
							fortune[ch][i] = NULL;
							if (i < 20)
							{
								prize[ch][i] = NULL;
							}
						}
						strcpy(addtime[tmp], addtime[ch]);
						for (int i = 0; i < 80; i++)
						{
							addtime[ch][i] = NULL;
						}
						SetConsoleCursorPosition(0, 7);
						SetConsoleColorTextBackground(clGray);
						cout << "1. Номер: " << tmp;
						SaveCookie();
						continue;
					}

				}
				if (ok == 2)
				{
					SetConsoleCursorPosition(3, 11);
					cout << "                                                                          ";
					SetConsoleCursorPosition(3, 11);
					SetConsoleColorTextBackground(clGray);
					cin.getline(fortune[ch], 75);
					SaveCookie();
					SetConsoleCursorPosition(0, 9);
					cout << "2. Опис: ";
				}
				if (ok == 3)
				{
					SetConsoleCursorPosition(9, 13);
					cout << "                     ";
					SetConsoleCursorPosition(9, 13);
					SetConsoleColorTextBackground(clGray);
					cin.getline(prize[ch], 20);
					SaveCookie();
					SetConsoleCursorPosition(0, 13);
					cout << "3. Приз: ";
				}
				CursorShow(false);
			}
			if (sel == 3)
			{
				int del = 0;
				AddButton(50, 17, clBrown, "Видалити?");
				while (1)
				{
					int k = _getch();
					if (k == 13)
					{
						num[ch] = NULL;
						for (int i = 0; i < 75; i++)
						{
							fortune[ch][i] = NULL;
							if (i < 20)
							{
								prize[ch][i] = NULL;
							}
						}
						for (int i = 0; i < 80; i++)
						{
							addtime[ch][i] = NULL;
						}
						SaveCookie();
						del = 1;
						break;
					}
					if (k == RIGHT && sel == 3)
					{

						skip = 1;
						break;
					}
					if (k == LEFT && sel != 1)
					{
						sel -= 1;
						skip = 1;
						break;
					}
				}
				if (del == 1)
					break;
			}
		}
	}
}
void ShowList()
{
	int ax = 4, ay = 7;
	int ch = 1, numtmp = ch;
	while (1)
	{
		CursorShow(false);
		system("cls");
		AddFrame(clTeal, "Перегляд списку печива");
		SetConsoleOutputCP(866);
		int x = 4, y = 5;
		for (int i = 1; i < 51; i++)
		{
			if ((i - 1) % 5 == 0 && i != 1)
			{
				x += 7;
				y = 5;
			}
			y += 2;
			SetConsoleCursorPosition(x, y);
			SetConsoleColorTextBackground(clGray);
			cout << i << ": ";
			if (num[i] == NULL)
			{
				SetConsoleColorTextBackground(clRed);
				cout << "x";
			}
			else
			{
				SetConsoleColorTextBackground(clGreen);
				cout << char(251);
			}
		}
		AddButton(26, 18, clGray, "У головне меню.");
		SetConsoleColorTextBackground(clTeal);
		SetConsoleCursorPosition(ax, ay);
		cout << ch << ":";
		while (1)
		{
			int k = _getch(), xx = ax, yy = ay;
			bool scr = false;
			SetConsoleCursorPosition(xx, yy);
			SetConsoleColorTextBackground(clGray);
			if (ch != -1)
				cout << ch << ":";
			if (k == 13)
				break;

			//
			if (k == UP && ch == -1 && scr == false)
			{
				ch = numtmp;
				scr = true;
				AddButton(26, 18, clGray, "У головне меню.");
			}
			if (k == DOWN && ch == -1 && scr == false)
			{
				ch = numtmp - 4;
				ay -= 8;
				scr = true;
				AddButton(26, 18, clGray, "У головне меню.");
			}
			if (k == DOWN && ch % 5 == 0 && scr == false)
			{
				numtmp = ch;
				ch = -1;
				scr = true;
				AddButton(26, 18, clTeal, "У головне меню!");
			}
			//

			if (k == DOWN && ch % 5 != 0 && ch != -1 && scr == false) //вниз
			{
				ay += 2; ch += 1; scr = true;
			}
			if (k == UP && (ch - 1) % 5 != 0 && ch != -1 && scr == false) // вгору
			{
				ay -= 2; ch -= 1; scr = true;
			}
			if (k == LEFT && ch > 5 && ch != -1 && scr == false) //вліво
			{
				ax -= 7; ch -= 5; scr = true;
			}
			if (k == RIGHT && ch < 46 && ch != -1 && scr == false) // вправо
			{
				ax += 7; ch += 5; scr = true;
			}

			// 
			if (k == LEFT && ch <= 5 && ch != -1 && scr == false) //вліво
			{
				ax += 63; ch += 45; scr = true;
			}
			if (k == RIGHT && ch >= 46 && ch != -1 && scr == false) // вправо
			{
				ax -= 63; ch -= 45; scr = true;
			}
			if (k == UP && (ch - 1) % 5 == 0 && ch != -1 && scr == false) // вгору
			{
				numtmp = ch + 4;
				ay += 8;
				ch = -1;
				scr = true;
				AddButton(26, 18, clTeal, "У головне меню!");
			}
			//

			SetConsoleColorTextBackground(clTeal);
			SetConsoleCursorPosition(ax, ay);
			if (ch != -1)
				cout << ch << ":";
		}
		if (ch == -1)
			break;
		else
			ShowCookie(ch);
	}
}
void main()
{
	FILE* f = fopen("cookie.save", "r");
	if (f)
	{
		for (int i = 1; i < 51; i++)
		{
			fread(&num[i], sizeof(int), 1, f);
			int tmp;
			fread(&tmp, sizeof(int), 1, f);
			fread(&fortune[i], sizeof(char), tmp, f);
			fread(&tmp, sizeof(int), 1, f);
			fread(&prize[i], sizeof(char), tmp, f);
			fread(&tmp, sizeof(int), 1, f);
			fread(&addtime[i], sizeof(char), tmp, f);
		}
		fclose(f);
	}
	srand((unsigned)time(NULL));
	while (1)
	{
		CursorShow(false);
		SetConsoleOutputCP(866);
		SetConsoleWinSizePosition(75, 22);
		system("cls");
		AddFrame(clTeal, "A N I M A L    C R O S S I N G");
		SetConsoleCursorPosition(36, 3);
		SetConsoleColorTextBackground(clOlive);
		cout << " FORTUNE  COOKIE ";
		SetConsoleOutputCP(1251);
		SetConsoleColorTextBackground(clGray);
		SetConsoleCursorPosition(0, 11);
		cout << "\t\t\t  Додати печиво.\n\n";
		cout << "\t\t\t  Переглянути список печива.\n\n";
		cout << "\t\t\t  Вийти.";
		SetConsoleOutputCP(866);
		int x = 22, y = 11;
		SetConsoleColorTextBackground(clGreen);
		SetConsoleCursorPosition(x, y);
		cout << char(5);
		while (1)
		{
			int k = _getch(), xx = x, yy = y;
			SetConsoleCursorPosition(xx, yy);
			cout << " ";
			if (k == 13)
				break;
			if (k == DOWN && y != 15)
				y += 2;
			if (k == UP && y != 11)
				y -= 2;
			SetConsoleColorTextBackground(clGreen);
			SetConsoleCursorPosition(x, y);
			cout << char(5);
		}
		SetConsoleOutputCP(1251);
		if (y == 11)
		{
			SetConsoleColorTextBackground(clGreen);
			SetConsoleCursorPosition(x + 4, y);
			cout << "Додати печиво.";
			Sleep(100);
			AddCookie();
		}
		if (y == 13)
		{
			SetConsoleColorTextBackground(clTeal);
			SetConsoleCursorPosition(x + 4, y);
			cout << "Переглянути список печива.";
			Sleep(100);
			ShowList();
		}
		if (y == 15)
		{
			SetConsoleColorTextBackground(clRed);
			SetConsoleCursorPosition(x + 4, y);
			cout << "Вийти.";
			Sleep(100);
			SetConsoleColorTextBackground(clGray);
			SetConsoleCursorPosition(x + 4, y);
			cout << "Вийти.";
			SetConsoleCursorPosition(18, 22);
			break;
		}
	}
}