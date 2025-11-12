#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
int x = 50, y = 25, xx, yy, fx, fy, score = 0, speed = 101, lvl = 1, xp = 5, bx, by, bonus, con;
bool eat = true, eatb = true, ex = false;
char snake = '^', ch, tmp = 'w';
enum {
	clBlack, clNavy, clGreen, clTeal, clBrown,
	clPurple, clOlive, clGray, clSilver, clBlue,
	clLime, clCyan, clRed, clMagneta, clYellow,
	clWhite
};
void SetConsoleColorTextBackground(unsigned short Tex = clWhite, unsigned short Bg = clBlack)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Bg = Bg << 4 | Tex;
	SetConsoleTextAttribute(hConsole, Bg);
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
	COORD bufferSize = { width + 1 , heigth + 1 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}
void SetConsoleCursorPosition(short x_position, short y_position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position , y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}
void CreateField()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (i == 0 && (j != 0 && j != 99) || i == 49 && (j != 0 && j != 99))
			{
				SetConsoleCursorPosition(j, i);
				SetConsoleColorTextBackground(clRed);
				cout << "-";
			}
			if (j == 0 && (i != 0 && i != 49) || j == 99 && (i != 0 && i != 49))
			{
				SetConsoleCursorPosition(j, i);
				cout << "|";
			}
		}
	}
	SetConsoleCursorPosition(0, 0);
	cout << "+";
	SetConsoleCursorPosition(99, 0);
	cout << "+";
	SetConsoleCursorPosition(0, 49);
	cout << "+";
	SetConsoleCursorPosition(99, 49);
	cout << "+";
}
void SnakeCtrl()
{
	if (_kbhit())
		ch = _getch();
	if (ch == 'w')
	{
		--y;
		snake = '^';
		tmp = ch;
	}
	if (ch == 's')
	{
		++y;
		snake = 'v';
		tmp = ch;
	}
	if (ch == 'a')
	{
		--x;
		snake = '<';
		tmp = ch;
	}
	if (ch == 'd')
	{
		++x;
		snake = '>';
		tmp = ch;
	}
}
void Food()
{
	srand((unsigned)time(NULL));
	for (;;)
	{
		fx = rand() % 99;
		fy = rand() % 49;
		if (fx == 0)
			fx++;
		if (fy == 0)
			fy++;
		if (fx != x && fy != y)
		{
			SetConsoleCursorPosition(fx, fy);
			SetConsoleColorTextBackground(clBlue);
			cout << "O";
			eat = false;
		}
		bonus = rand() % 2;
		if (bonus == 0 && eatb == true)
		{
			bx = rand() % 99;
			by = rand() % 49;
			if (bx == 0)
				bx++;
			if (by == 0)
				by++;
			if (bx != x && by != y && bx != fx && by != fy)
			{
				SetConsoleCursorPosition(bx, by);
				SetConsoleColorTextBackground(clYellow);
				cout << "$";
			}
			eatb = false;
		}
		if (eat == false)
			break;
	}
}
void SnakeEat()
{
	if (fx == x && fy == y)
	{
		score++;
		eat = true;
	}
	if (bx == x && by == y)
	{
		score += 5;
		bx = 0; by = 0;
		eatb = true;
	}
}
void NextLvl()
{
	if (xp <= score)
	{
		xp *= 2;
		speed -= 10;
		lvl++;
	}
}
void main()
{
	SetConsoleOutputCP(1251);
	SetConsoleWinSizePosition(99, 50);
	SetConsoleColorTextBackground(clOlive);
	cout <<
		"\n\n\n\n\n\n\n\t\t      $$$$$$$    $$     $$$          $$   $$$   $$$$  $$$$$$$$\n" <<
		"\t\t     $$$$$$$$$$ $$$$$   $$$        $$$$$  $$$  $$$    $$$$$$$$$\n" <<
		"\t\t      $$$$      $$$$$$  $$$       $$$$$$  $$$ $$$     $$$\n" <<
		"\t\t        $$$$    $$$ $$$_$$$      $$$ $$$  $$$ $$$     $$$ $$$\n" <<
		"\t\t          $$$$  $$$  $$$$$$    $$$$$$$$$  $$$  $$$    $$$\n" <<
		"\t\t     $$$$$$$$$$ $$$   $$$$$   $$$$$$$$$$  $$$   $$$   $$$$$$$$$$\n" <<
		"\t\t      $$$$$$$$$ $$$     $$   $$$     $$$  $$$    $$$$ $$$$$$$$ (kinda)\n";
	SetConsoleCursorPosition(35, 37);
	cout << "Для керування використовуй WASD.";
	CreateField();
	SetConsoleCursorPosition(x, y);
	SetConsoleColorTextBackground(clGreen);
	cout << snake;
	ch = _getch();
	if (ch != 'w' && ch != 'a' && ch != 's' && ch != 'd')
		ch = tmp;
	system("cls");
	CreateField();
	for (;;)
	{
		if (eat == true)
			Food();
		SnakeEat();
		SetConsoleCursorPosition(x, y);
		if (x == 0 || y == 0 || x == 99 || y == 49)
		{
			SetConsoleCursorPosition(43, 25);
			SetConsoleColorTextBackground(clTeal);
			cout << "Кінець гри!";
			SetConsoleCursorPosition(30, 37);
			cout << "WASD - продовжити | Esc - вихід з гри";
			for (;;)
			{
				con = _getch();
				if (con == 27)
				{
					ex = true;
					break;
				}
				if (con == 'w' || con == 'a' || con == 's' || con == 'd')
				{
					system("cls");
					x = 50; y = 25; eat = true; eatb = true; bx = 0; by = 0; score = 0; speed = 101; lvl = 1; xp = 5;
					CreateField();
					ch = con;
					break;
				}
			}
		}
		if (ex == true)
			break;
		SetConsoleColorTextBackground(clGreen);
		cout << snake;
		if (ch == 'a' || ch == 'd')
			Sleep(speed);
		if (ch == 'w' || ch == 's')
			Sleep(speed * 1.5);
		xx = x; yy = y;
		SetConsoleCursorPosition(xx, yy);
		cout << " ";
		if (ch != 'w' && ch != 'a' && ch != 's' && ch != 'd')
			ch = tmp;
		SnakeCtrl();
		SetConsoleCursorPosition(0, 50);
		NextLvl();
		SetConsoleColorTextBackground(clWhite);
		cout << "\t\t\t     SCORE: " << score << " | Рівень: " << lvl << " | Залишилось зібрати: " << xp - score << "    ";
	}
	SetConsoleCursorPosition(0, 50);
	cout << "\t\t\t     ";
}