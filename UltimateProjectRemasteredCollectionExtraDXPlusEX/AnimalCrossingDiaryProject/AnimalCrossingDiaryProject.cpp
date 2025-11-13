#define _CRT_SECURE_NO_WARNINGS
#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define RUS SetConsoleOutputCP(1251)
#define ENG SetConsoleOutputCP(866)

#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <fstream>
using namespace std;

class Profile
{
	char* name;
	int favcol;

public:

	Profile()
	{
		name = _strdup("Мер");
		favcol = 14;
	}
	Profile(const Profile& obj)
	{
		name = _strdup(obj.name);
		favcol = obj.favcol;
	}

	void SetFavcol(int col)
	{
		favcol = col;
	}
	void SetName(char* change)
	{
		delete[]name;
		name = _strdup(change);
	}
	char* getname() const
	{
		return name;
	}
	int getcol() const
	{
		return favcol;
	}

	friend istream& operator>>(istream& is, Profile& P)
	{
		char setname[20];
		cin.getline(setname, 20);
		if (P.name)
			delete[]P.name;
		P.name = _strdup(setname);
		return is;
	}
	friend ostream& operator<<(ostream& os, const Profile& P)
	{
		RUS;
		os << P.name;
		return os;
	}

	~Profile() { delete[]name; }
};
class Villager
{
	int stat;
	int num;
	char name[50];
	int bean[5];
	int milk[5];
	int sug[5];

public:
};

enum {
	Black, DBlue, DGreen, Teal, DRed,
	Purple, Olive, Gray, DGray, Blue,
	Green, LBlue, Red, Pink, Yellow,
	White
};

void WinSize(int width = 0, int heigth = 0, int x_position = 0, int y_position = 0)
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
	COORD bufferSize = { width + 1 , heigth + 1 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}
void CursorPos(int x_position, int y_position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position , y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}
void CursorShow(bool on = true)
{
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = on;
	CCI.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}
void TextColor(unsigned int Tex = White, unsigned int Bg = Black)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Bg = Bg << 4 | Tex;
	SetConsoleTextAttribute(hConsole, Bg);
}
void TextMagic(signed int x, int y, int tcol, int bcol, const char str[])
{
	int n = 0;
	for (signed int i = x; i < x + strlen(str) + 2; i++)
	{
		SetConsoleOutputCP(866);
		TextColor(Blue, White);
		if (i < x + strlen(str))
		{
			CursorPos(i, y);
			cout << char(178);
		}
		Sleep(75);

		if (i - x >= 0 && i < x + strlen(str))
		{
			CursorPos(i, y);
			cout << char(177);
		}
		if (i - x >= 1 && i < x + strlen(str) + 1)
		{
			CursorPos(i - 1, y);
			cout << char(176);
		}

		if (i - 2 >= x)
		{
			SetConsoleOutputCP(1251);
			TextColor(tcol, bcol);
			CursorPos(i - 2, y);
			cout << str[n];
			n++;
		}
	}
}
void TextAlign(int y, int col, const char* title, int bcol = White)
{
	int x;
	if (strlen(title) % 2 != 0)
		x = (50 - (strlen(title))) / 2 + 1;
	else
		x = (50 - (strlen(title))) / 2;
	SetConsoleOutputCP(1251);
	TextColor(col, bcol);
	CursorPos(x, y);
	cout << title;
}
int TextCenter(const char* title)
{
	int x;
	if (strlen(title) % 2 != 0)
		x = (50 - (strlen(title))) / 2 + 1;
	else
		x = (50 - (strlen(title))) / 2;
	return x;
}
void DrawBackground()
{
	int wi = 51, hi = 41, col = Green;
	char sym = ' ';
	bool check[41][51];
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			check[i][j] = false;
		}
	}
	check[hi - 1][wi - 1] = true;

	while (1)
	{
		// Перевірка на промальовування всіх символів
		bool DrawDone = true;
		for (int i = 0; i < hi; i++)
		{
			for (int j = 0; j < wi; j++)
			{
				if (check[i][j] == false)
				{
					DrawDone = false;
					break;
				}
			}
			if (DrawDone == false)
				break;
		}
		if (DrawDone == true)
			break;

		bool onesym = false;
		do
		{
			int qwi = rand() % wi, qhi = rand() % hi;
			if (check[qhi][qwi] == false)
			{
				CursorPos(qwi, qhi);
				TextColor(col, col);
				if ((qhi % 2 == 0 && qwi % 2 == 0) || (qhi % 2 != 0 && qwi % 2 != 0))
				{
					TextColor(DGreen, col);
					sym = '|';
				}
				cout << sym;
				check[qhi][qwi] = true;
				sym = ' ';
				onesym = true;
			}
		} while (onesym == false);
	}
}
void DrawGround(int col)
{
	int wi = 35, hi = 25;
	char sym = ' ';
	bool check[25][35];
	for (int i = 15; i < hi; i++)
	{
		for (int j = 15; j < wi; j++)
		{
			check[i][j] = false;
		}
	}

	while (1)
	{
		// Перевірка на промальовування всіх символів
		bool DrawDone = true;
		for (int i = 15; i < hi; i++)
		{
			for (int j = 15; j < wi; j++)
			{
				if (check[i][j] == false)
				{
					DrawDone = false;
					break;
				}
			}
			if (DrawDone == false)
				break;
		}
		if (DrawDone == true)
			break;

		bool onesym = false;
		do
		{
			int qwi = rand() % 20 + 15, qhi = rand() % 10 + 15;
			if (check[qhi][qwi] == false)
			{
				CursorPos(qwi, qhi);
				TextColor(col, col);
				if (col == Green)
				{
					if ((qhi % 2 == 0 && qwi % 2 == 0) || (qhi % 2 != 0 && qwi % 2 != 0))
					{
						TextColor(DGreen, col);
						sym = '|';
					}
				}
				cout << sym;
				check[qhi][qwi] = true;
				sym = ' ';
				onesym = true;
			}
		} while (onesym == false);
		Sleep(5);
	}
}
void DrawBook(Profile User, bool first = false)
{
	//Створення книги
	int tcol[39][54], bcol[39][54];
	char book[39][54];
	SetConsoleOutputCP(866);
	for (int i = 0; i <= 53; i++)
	{
		for (int j = 2; j <= 38; j++)
		{
			if (j < 37 && i <= 50)
			{
				tcol[j][i] = 4;
				bcol[j][i] = 4;
				book[j][i] = ' ';
			}
			if (j > 6 && i > 10 && j < 14 && i < 40)
			{
				tcol[j][i] = DGray;
				bcol[j][i] = White;
				if (j % 2 == 0 && i > 11 && i < 39)
					book[j][i] = char(196);
				else
					book[j][i] = ' ';
			}
			if (((j == 6 || j == 14) && i >= 10 && i <= 40) || j == 38)
			{
				tcol[j][i] = 5;
				bcol[j][i] = 4;
				if (j == 6)
					book[j][i] = char(220);
				if (j == 14)
					book[j][i] = char(223);
				if (j == 38 && i <= 53)
				{
					tcol[j][i] = 4;
					bcol[j][i] = Green;
					book[j][i] = char(223);
				}
			}
			if ((i == 10 || i == 40) && j > 6 && j < 14)
			{
				tcol[j][i] = 5;
				bcol[j][i] = 5;
				book[j][i] = ' ';
			}
			if ((j > 21 && i > 15) && (j < 31 && i < 35))
			{
				tcol[j][i] = DGray;
				bcol[j][i] = White;
				if (j % 2 == 0 && i > 16 && i < 34 && j != 22 && j != 30)
					book[j][i] = '~';
				else
					book[j][i] = ' ';
			}
			if ((j == 37 && i <= 50) || ((i == 51 || i == 52) && j < 38))
			{
				tcol[j][i] = DGray;
				bcol[j][i] = White;
				book[j][i] = char(176);
			}
			if (i == 53 && j < 38)
			{
				tcol[j][i] = 4;
				bcol[j][i] = 4;
				book[j][i] = ' ';
			}
		}
	}

	//Висновок книги (у двох різних випадках)
	int wi = 51, hi = 39, num = 0;
	if (first == false)
	{
		wi = 54;
	}
	bool check[39][54];
	for (int i = 2; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			check[i][j] = false;
		}
	}

	if (first == true)
	{
		while (1)
		{
			// Перевірка на промальовування всіх символів
			bool DrawDone = true;
			for (int i = 2; i < hi; i++)
			{
				for (int j = 0; j < wi; j++)
				{
					if (check[i][j] == false)
					{
						DrawDone = false;
						break;
					}
				}
				if (DrawDone == false)
					break;
			}
			if (DrawDone == true)
				break;

			bool onesym = false;
			do
			{
				int qwi = rand() % 51, qhi = rand() % 37 + 2;
				if (check[qhi][qwi] == false)
				{
					CursorPos(qwi, qhi);
					TextColor(tcol[qhi][qwi], bcol[qhi][qwi]);
					cout << book[qhi][qwi];
					check[qhi][qwi] = true;
					onesym = true;
				}
			} while (onesym == false);
			if (num++ % 10 == 0)
				Sleep(10);
		}
		Sleep(500);
		TextMagic(TextCenter("\"Diary Project\""), 9, User.getcol(), White, "\"Diary Project\"");
		TextMagic(TextCenter(User.getname()), 11, User.getcol(), White, User.getname());
		TextMagic(TextCenter("Додати запис"), 23, 0, White, "Додати запис");
		TextMagic(TextCenter("Знайти запис"), 25, 0, White, "Знайти запис");
		TextMagic(TextCenter("Відкрити довідку"), 27, 0, White, "Відкрити довідку");
		TextMagic(TextCenter("Вийти"), 29, 0, White, "Вийти");
	}
	if (first == false)
	{
		for (int h = 0; h <= 53; h++)
		{
			for (int j = h, col = 53; j >= 0; j--, col--)
			{
				for (int i = hi - 1; i >= 2; i--)
				{
					if (j > 50 && ((i >= 2 && i <= 5) || (i >= 15 && i <= 21) || (i >= 31 && i <= 38)))
						continue;
					if (j <= 50 && col >= 50 && col <= 53)
					{
						CursorPos(j, i);
						TextColor(tcol[i][col], bcol[i][col]);
						cout << book[i][col];
					}
					if ((i >= 6 && i <= 14) && ((col >= 9 && col <= 11) || (col >= 38 && col <= 40)))
					{
						CursorPos(j, i);
						TextColor(tcol[i][col], bcol[i][col]);
						cout << book[i][col];
					}
					if ((i > 21 && i < 31) && ((col > 14 && col < 17) || (col > 32 && col < 35)))
					{
						CursorPos(j, i);
						TextColor(tcol[i][col], bcol[i][col]);
						cout << book[i][col];
					}
				}
			}
		}
		TextAlign(9, User.getcol(), "\"Diary Project\"");
		TextAlign(11, User.getcol(), User.getname());
		TextAlign(23, 0, "Додати запис");
		TextAlign(25, 0, "Знайти запис");
		TextAlign(27, 0, "Відкрити довідку");
		TextAlign(29, 0, "Вийти");
	}

	//if(animation==false&&first==false)
	//{
	//	for (int i = 0; i < 51; i++)
	//	{
	//		for (int j = 2; j < 39; j++)
	//		{
	//			CursorPos(i,j);
	//			TextColor(tcol[j][i],bcol[j][i]);
	//			cout << book[j][i];
	//		}
	//	}
	//}
}
void DrawPage(bool right = true)
{
	ENG;
	if (right == true)
	{
		for (int i = 50; i >= 0; i--)
		{
			for (int j = 2; j < 37; j++)
			{
				CursorPos(i, j);
				TextColor(0, White);
				cout << ' ';
			}
			Sleep(15);
		}
	}
	if (right == false)
	{
		for (int i = 0; i <= 50; i++)
		{
			for (int j = 2; j < 37; j++)
			{
				CursorPos(i, j);
				TextColor(0, White);
				cout << ' ';
			}
			Sleep(15);
		}
	}
}
void LetsStart(Profile& User)
{
	SetConsoleOutputCP(866);
	for (int i = 0; i < 35; i++)
	{
		for (int j = 15; j < 25; j++)
		{
			TextColor(DGray, White);
			CursorPos(i, j);
			if (j % 2 != 0 && j != 15)
				cout << char(196);
			else
				cout << ' ';
			if (i >= 20)
			{
				CursorPos(i - 20, j);
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0))
				{
					TextColor(DGreen, Green);
					cout << '|';
				}
				else
				{
					TextColor(Black, Green);
					cout << ' ';
				}
			}
		}
		Sleep(30);
	}

	TextMagic(17, 16, Black, White, "Напиши своє ім'я.");
	CursorPos(17, 18);
	TextColor(1, 15);
	CursorShow();
	cin >> User;
	CursorShow(false);
	TextMagic(19, 20, Black, White, "Вибери колір.");
	SetConsoleOutputCP(866);
	CursorPos(17, 22);
	TextColor(9, 15);
	cout << char(254) << "  ";
	TextColor(13, 15);
	cout << char(254) << "  ";
	TextColor(14, 15);
	cout << char(254) << "  ";
	TextColor(7, 15);
	cout << char(254) << "  ";
	TextColor(11, 15);
	cout << char(254) << "  ";
	TextColor(3, 15);
	cout << char(254);

	int ok = 1, x = 16;
	TextColor(DGray, White);
	CursorPos(x, 21);
	cout << char(210) << char(196) << char(210);
	CursorPos(x, 22);
	cout << char(186);
	CursorPos(x + 2, 22);
	cout << char(186);
	CursorPos(x, 23);
	cout << char(208) << char(196) << char(208);

	while (1)
	{
		int k = _getch();
		if (k == ENTER)
			break;
		if (k == RIGHT && ok != 6)
		{
			k = -1;
			ok++;
			x += 3;
		}
		if (k == LEFT && ok != 1)
		{
			k = -1;
			ok--;
			x -= 3;
		}
		if (k == -1)
		{
			for (int i = 16; i < 34; i++)
			{
				CursorPos(i, 23);
				cout << char(196);
				CursorPos(i, 21);
				cout << char(196);
				CursorPos(i, 22);
				if (i % 3 == 0 && i != 33)
					cout << "  ";
				if (i == 16 || i == 33)
					cout << ' ';
			}
			CursorPos(x, 21);
			cout << char(210) << char(196) << char(210);
			CursorPos(x, 22);
			cout << char(186);
			CursorPos(x + 2, 22);
			cout << char(186);
			CursorPos(x, 23);
			cout << char(208) << char(196) << char(208);
		}
	}
	if (ok == 1) User.SetFavcol(9);
	if (ok == 2) User.SetFavcol(13);
	if (ok == 3) User.SetFavcol(14);
	if (ok == 4) User.SetFavcol(7);
	if (ok == 5) User.SetFavcol(11);
	if (ok == 6) User.SetFavcol(3);

	DrawGround(DRed);
	DrawGround(Olive);
	DrawGround(Green);
	Sleep(500);
}
void ShowList(Profile& User)
{
	ENG;
	TextColor(1, White);
	CursorPos(2, 2);
	cout << char(201) << char(205) << char(203) << char(205) << char(205) << char(205) << char(203);
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 26; i++)
			cout << char(205);
		CursorPos(9, 6);
	}
	CursorPos(33, 2);
	for (int i = 0; i < 3; i++)
	{
		cout << char(203);
		for (int j = 0; j < 4; j++)
		{
			cout << char(205);
		}
	}
	cout << char(187);

	for (int i = 0; i < 3; i++)
	{
		CursorPos(2, 3 + i);
		for (int j = 0; j < 3; j++)
		{
			if (j < 1)
				cout << char(186) << ' ';
			else
				cout << char(186) << "   ";
		}
	}

	CursorPos(19, 4);
	cout << "NAME";
	CursorPos(3, 4);
	cout << 'S';
	CursorPos(6, 4);
	cout << '#';
	CursorPos(33, 3);
	cout << char(186) << "BEAN";
	cout << char(186) << "MILK";
	cout << char(186) << "SUG." << char(186);

	CursorPos(33, 4);
	cout << char(204);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << char(205);
		}
		if (i == 2)
			cout << char(185);
		else
			cout << char(206);
	}

	CursorPos(33, 5);
	for (int i = 0; i < 3; i++)
	{
		cout << char(186) << "1234";
	}
	cout << char(186);

	CursorPos(2, 6);
	cout << char(200) << char(205) << char(202) << char(205) << char(205) << char(205) << char(202);
	CursorPos(33, 6);
	cout << char(202);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << char(205);
		}
		if (i == 2)
			cout << char(188);
		else
			cout << char(202);
	}


	//
	TextColor(0, White);
	for (int i = 7; i < 32; i++)
	{
		CursorPos(2, i);
		cout << char(179) << ' ' << char(179) << i - 6;
		CursorPos(8, i);
		cout << char(179) << "Broccolo";
		CursorPos(33, i);
		for (int i = 0; i < 4; i++)
		{
			cout << char(179) << "    ";
		}
	}
	CursorPos(2, 32);
	cout << char(192) << char(196) << char(193) << char(196) << char(196) << char(196) << char(193);
	for (int i = 0; i < 24; i++)
		cout << char(196);
	//CursorPos(33,32);
	cout << char(193);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << char(196);
		}
		if (i == 2)
			cout << char(217);
		else
			cout << char(193);
	}
	TextAlign(34, 0, "___");
	TextAlign(35, 0, "1");
	//
	_getch();
}

void main()
{
	WinSize(50, 40);
	int test = 9;
	RUS;
	SetConsoleCP(1251);
	srand((unsigned)time(NULL));
	CursorShow(false);
	DrawBackground();

	Sleep(5000);
	Profile User;
	bool first = false;
	FILE* f = fopen("profile.save", "r");
	if (f)
	{
		int favcoltmp, namesize;
		fread(&namesize, sizeof(int), 1, f);
		char* nametmp = new char[namesize];
		fread(nametmp, sizeof(char), namesize, f);
		fread(&favcoltmp, sizeof(int), 1, f);
		User.SetFavcol(favcoltmp);
		User.SetName(nametmp);
		delete[]nametmp;
		fclose(f);
	}
	else
	{
		first = true;
		LetsStart(User);
		f = fopen("profile.save", "w");
		if (f)
		{
			int favcoltmp = User.getcol(), namesize = strlen(User.getname()) + 1;
			char* nametmp = new char[namesize];
			strcpy(nametmp, User.getname());
			fwrite(&namesize, sizeof(int), 1, f);
			fwrite(nametmp, sizeof(char), namesize, f);
			fwrite(&favcoltmp, sizeof(int), 1, f);
			delete[]nametmp;
			fclose(f);
		}
	}
	DrawBook(User, first);
	int menu = 1, y = 23, x = 17;
	TextColor(0, User.getcol());
	CursorPos(x, y);
	cout << "                 ";
	TextAlign(y, 0, "Додати запис", User.getcol());
	while (1)
	{
		int k = _getch();
		bool click = false;
		if (k == ENTER)
			break;
		if (k == RIGHT)
		{
			DrawPage();
			menu = 0;
			break;
		}
		if (k == UP && menu != 1)
		{
			menu--;
			y -= 2;
			click = true;
		}
		if (k == DOWN && menu != 4)
		{
			menu++;
			y += 2;
			click = true;
		}
		if (click == true)
		{
			TextColor(0, White);
			CursorPos(x, 23);
			cout << " ";
			CursorPos(x + 16, 23);
			cout << " ";
			CursorPos(x, 25);
			cout << "  ";
			CursorPos(x + 15, 25);
			cout << "  ";
			CursorPos(x, 27);
			cout << " ";
			CursorPos(x + 16, 27);
			cout << " ";
			CursorPos(x, 29);
			cout << "      ";
			CursorPos(x + 11, 29);
			cout << "      ";
			TextAlign(23, 0, "Додати запис");
			TextAlign(25, 0, "Знайти запис");
			TextAlign(27, 0, "Відкрити довідку");
			TextAlign(29, 0, "Вийти");
			TextColor(0, User.getcol());
			CursorPos(x, y);
			cout << "                 ";
			if (menu == 1)
			{
				TextAlign(y, 0, "Додати запис", User.getcol());
			}
			if (menu == 2)
			{
				TextAlign(y, 0, "Знайти запис", User.getcol());
			}
			if (menu == 3)
			{
				TextAlign(y, 0, "Відкрити довідку", User.getcol());
			}
			if (menu == 4)
			{
				TextAlign(y, 0, "Вийти", User.getcol());
			}
		}
	}
	if (menu == 0)
	{
		ShowList(User);
	}
	//LetsStart(User);
	//DrawBook(User,true);
	TextColor(White, DRed);
	CursorPos(4, 34);
}