#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
int x = 30, y = 18, lx = 39, ly = 23, sx, sy, ctrl, xx, yy, enemys_killed[18], key_drop[18], key_got[18], ex[10], ey[10], enemy_sprite_col[10], enemy_sprite_bg[10], exdel, eydel, fire_col = 0, enemy_walk_chance[10] = { 0 }, llife = 3, save_enemy_walk = 1, esx[10], esy[10], llife_buf = 3, llife_tmp = 3, current_location, door_col;
int all_killed_check = 0, items[24][79] = { 0 }, rupees = 0, keys = 0, rupees_tmp = 0, keys_tmp = 0, elife[10], locked_doors[18][4], secret[5] = { 0 }, boss_balls = 0, complete = 0;
int hp_batngoo = 1, hp_skeleton = 2, hp_pig = 3, hp_boss = 20, move_speed = 50, gotsword = 0, YOU_DIED = 0, link_col = 2, sword_col = 15;
char link = char(31), clink, enemy_sprite[10], sword, esword;
FILE* f;
bool stop[24][79] = { false }, enemy_on_board[10] = { false }, gotcompass = false, gotmap = false, basement = false, lil_bonus = false, YOU_DEFEATED = false, dragon_heart = false, triforce = false;
bool bad_karma = false, game_complete = false, special_bonus = false, /*gotsword=false,*/ /*YOU_DIED=false,*/ text = false, attack = false, delsword = false, kbh = false, enemy_walk_done = false, l_back_step = false, eattack = false;
enum {
	clBlack, clNavy, clGreen, clTeal, clBrown,
	clPurple, clOlive, clGray, clSilver, clBlue,
	clLime, clCyan, clRed, clMagneta, clYellow,
	clWhite
};
void Warp();
void StatusBar();
void Game_Over();
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
void SetConsoleColorTextBackground(unsigned short Tex = clWhite, unsigned short Bg = clBlack)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Bg = Bg << 4 | Tex;
	SetConsoleTextAttribute(hConsole, Bg);
}
void SetConsoleCursorPosition(short x_position, short y_position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position , y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}
void RedText(const char prr[])
{
	for (int i = x, n = 0; i < 50; i++)
	{
		int xx = x, yy = y;
		SetConsoleCursorPosition(xx, yy);
		cout << " ";
		x++;
		SetConsoleColorTextBackground(clOlive);
		SetConsoleCursorPosition(x, y);
		cout << char(196) << "|";
		SetConsoleColorTextBackground(clWhite);
		cout << "==>";
		if (x > 36 && x <= 36 + strlen(prr))
		{
			SetConsoleCursorPosition(x - 1, y);
			SetConsoleColorTextBackground(clRed);
			cout << prr[n];
			n++;
		}
		Sleep(25);
	}
}
void Frame()
{
	SetConsoleColorTextBackground(clWhite);
	SetConsoleCursorPosition(15, 7);
	for (int i = 0; i < 2; i++)
	{

		for (int j = 15; j < 63; j++)
		{
			cout << char(205);
		}
		SetConsoleCursorPosition(15, 24);
	}
	for (int i = 7; i < 25; i++)
	{
		for (int j = 15; j <= 63; j++)
		{

			if (j == 15 || j == 63)
			{
				SetConsoleCursorPosition(j, i);
				cout << char(186);
			}
		}
	}
	SetConsoleCursorPosition(15, 7);
	cout << char(201);
	SetConsoleCursorPosition(63, 7);
	cout << char(187);
	SetConsoleCursorPosition(15, 24);
	cout << char(200);
	SetConsoleCursorPosition(63, 24);
	cout << char(188);
}
void Wall()
{
	SetConsoleColorTextBackground(clTeal, clBlack);
	SetConsoleCursorPosition(16, 9);
	for (int i = 16; i < 63; i++)
	{
		for (int j = 8; j < 24; j++)
		{
			if ((j > 7 && j < 10 || j>21 && j < 24) || (i > 15 && i < 19 || i>59 && i < 63))
			{
				SetConsoleCursorPosition(i, j);
				cout << char(177);
			}
		}
	}
	SetConsoleColorTextBackground(clGray, clBlack);
}
void NoWay()
{
	for (int i = 8; i < 25; i++)
		for (int j = 16; j <= 62; j++)
			if (i < 10 || i>21 || j < 19 || j>59)
				stop[i][j] = true;
			else
				stop[i][j] = false;
}
void AddTexture(int x, int y, int color, int color_back, char sym)
{
	SetConsoleCursorPosition(x, y);
	SetConsoleColorTextBackground(color, color_back);
	cout << sym;
	stop[y][x] = true;
}
void AddMultTexture(int x1, int y1, int x2, int y2, int color, int color_back, char sym)
{
	for (int i = y1; i <= y2; i++)
	{
		for (int j = x1; j <= x2; j++)
		{
			SetConsoleCursorPosition(j, i);
			SetConsoleColorTextBackground(color, color_back);
			cout << sym;
			stop[i][j] = true;
		}
	}
}
void DeleteTexture(int x, int y)
{
	SetConsoleCursorPosition(x, y);
	SetConsoleColorTextBackground(clBlack, clBlack);
	cout << " ";
	stop[y][x] = false;
}
void DeleteMultTexture(int x1, int y1, int x2, int y2)
{
	for (int i = y1; i <= y2; i++)
	{
		for (int j = x1; j <= x2; j++)
		{
			SetConsoleCursorPosition(j, i);
			SetConsoleColorTextBackground(0, 0);
			cout << " ";
			stop[i][j] = false;
		}
	}
}
void AddDoor(char addwhere, char addwhat)
{
	if (addwhere == 'l')
	{
		DeleteTexture(17, 16);
		DeleteTexture(18, 16);
		if (addwhat == 'l')
		{
			door_col = clTeal;
			AddTexture(18, 16, clBlack, door_col, 6);
			AddTexture(17, 16, clTeal, door_col, 5);
		}
		if (addwhat == 'o')
		{
			door_col = clBlack;
		}
		if (addwhat == 'c')
		{
			door_col = clTeal;
			AddTexture(17, 16, clTeal, door_col, 223);
			AddTexture(18, 16, clTeal, door_col, 223);
		}
		AddTexture(16, 15, clTeal, door_col, 219);
		AddTexture(17, 15, clTeal, door_col, 223);
		AddTexture(18, 15, clTeal, door_col, 223);
		AddTexture(16, 16, clTeal, door_col, 219);
		AddTexture(16, 17, clTeal, door_col, 219);
		AddTexture(17, 17, clTeal, door_col, 220);
		AddTexture(18, 17, clTeal, door_col, 220);
	}
	if (addwhere == 'r')
	{
		DeleteTexture(60, 16);
		DeleteTexture(61, 16);
		if (addwhat == 'l')
		{
			door_col = clTeal;
			AddTexture(60, 16, clBlack, door_col, 6);
			AddTexture(61, 16, clTeal, door_col, 5);
		}
		if (addwhat == 'o')
		{
			door_col = clBlack;
		}
		if (addwhat == 'c')
		{
			door_col = clTeal;
			AddTexture(60, 16, clTeal, door_col, 223);
			AddTexture(61, 16, clTeal, door_col, 223);
		}
		AddTexture(60, 15, clTeal, door_col, 223);
		AddTexture(61, 15, clTeal, door_col, 223);
		AddTexture(62, 15, clTeal, door_col, 219);
		AddTexture(62, 16, clTeal, door_col, 219);
		AddTexture(62, 17, clTeal, door_col, 219);
		AddTexture(61, 17, clTeal, door_col, 220);
		AddTexture(60, 17, clTeal, door_col, 220);
	}
	if (addwhere == 'd')
	{
		DeleteTexture(38, 22);
		DeleteTexture(39, 22);
		DeleteTexture(40, 22);
		if (addwhat == 'l')
		{
			door_col = clTeal;
			AddTexture(40, 22, clTeal, door_col, 223);
			AddTexture(38, 22, clTeal, door_col, 223);
			AddTexture(39, 22, clBlack, door_col, 6);
		}
		if (addwhat == 'o')
		{
			door_col = clBlack;
		}
		if (addwhat == 'c')
		{
			door_col = clTeal;
			AddTexture(39, 22, clTeal, door_col, 223);
			AddTexture(40, 22, clTeal, door_col, 223);
			AddTexture(38, 22, clTeal, door_col, 223);
		}
		AddTexture(39, 23, clTeal, door_col, 220);
		AddTexture(40, 23, clTeal, door_col, 220);
		AddTexture(38, 23, clTeal, door_col, 220);
		AddTexture(37, 23, clTeal, door_col, 219);
		AddTexture(41, 23, clTeal, door_col, 219);
		AddTexture(37, 22, clTeal, door_col, 219);
		AddTexture(41, 22, clTeal, door_col, 219);
	}
	if (addwhere == 'u')
	{
		DeleteTexture(38, 9);
		DeleteTexture(39, 9);
		DeleteTexture(40, 9);
		if (addwhat == 'l')
		{
			door_col = clTeal;
			AddTexture(40, 9, clTeal, door_col, 223);
			AddTexture(38, 9, clTeal, door_col, 223);
			AddTexture(39, 9, clBlack, door_col, 6);
		}
		if (addwhat == 'o')
		{
			door_col = clBlack;
		}
		if (addwhat == 'c')
		{
			door_col = clTeal;
			AddTexture(39, 9, clTeal, door_col, 223);
			AddTexture(40, 9, clTeal, door_col, 223);
			AddTexture(38, 9, clTeal, door_col, 223);
		}
		AddTexture(39, 8, clTeal, door_col, 223);
		AddTexture(40, 8, clTeal, door_col, 223);
		AddTexture(38, 8, clTeal, door_col, 223);
		AddTexture(37, 8, clTeal, door_col, 219);
		AddTexture(41, 8, clTeal, door_col, 219);
		AddTexture(37, 9, clTeal, door_col, 219);
		AddTexture(41, 9, clTeal, door_col, 219);
	}
}
void EnemyWalk(int& ex, int& ey, int& esx, int& esy, int& hp, bool& eob, int& ewc, char sym, int& sym_col, int bg_col)
{
	if (eattack == true)
		eattack = false;
	if (sx == ex && sy == ey && attack == true && hp == 1)
	{
		int item_drop_chance = rand() % 40 + 1;
		if (item_drop_chance > 0 && item_drop_chance <= 10 && llife < llife_buf)
		{
			items[ey][ex] = 1; //+1 сердечко
			SetConsoleCursorPosition(ex, ey);
			SetConsoleColorTextBackground(clRed);
			cout << char(3);
		}
		if (item_drop_chance > 10 && item_drop_chance <= 20)
		{
			items[ey][ex] = 2; //+1 рупія
			SetConsoleCursorPosition(ex, ey);
			SetConsoleColorTextBackground(clYellow);
			cout << char(4);
		}
		if (item_drop_chance > 20 && item_drop_chance <= 25)
		{
			items[ey][ex] = 3; //+5 рупій
			SetConsoleCursorPosition(ex, ey);
			SetConsoleColorTextBackground(clBlue);
			cout << char(4);
		}
		ey = 0; ex = 0;
		hp--;
		eob = false;
	}
	if (sx == ex && sy == ey && attack == true && hp > 1)
	{
		hp--;
		SetConsoleCursorPosition(ex, ey);
		SetConsoleColorTextBackground(clRed);
		cout << sym;
		Sleep(20);
		SetConsoleCursorPosition(ex, ey);
		SetConsoleColorTextBackground(sym_col);
		cout << sym;
		SetConsoleColorTextBackground(clGray);
	}
	if (eob == true)
	{
		exdel = ex; eydel = ey;
		if (ewc == 2099999999)
			ewc = 0;
		ewc++;
		if (ewc % move_speed == 0 && sym != 15)
		{
			do
			{
				int enemy_ctrl_chance = rand() % 10 + 1;
				if (sym == 'w')
					enemy_ctrl_chance = rand() % 15 + 1;
				if (enemy_ctrl_chance > 5 && sym != 'w')
				{
					enemy_ctrl_chance = save_enemy_walk;
				}
				if ((enemy_ctrl_chance > 9 || enemy_ctrl_chance == 5) && sym == 'w')
				{
					enemy_ctrl_chance = save_enemy_walk;
				}
				if (enemy_ctrl_chance == 1 && stop[ey - 1][ex] == false && items[ey - 1][ex] == 0)
				{
					ey--;
					save_enemy_walk = enemy_ctrl_chance;
					enemy_walk_done = true;
				}
				if (enemy_ctrl_chance == 2 && stop[ey + 1][ex] == false && items[ey + 1][ex] == 0)
				{
					ey++;
					save_enemy_walk = enemy_ctrl_chance;
					enemy_walk_done = true;
				}
				if (enemy_ctrl_chance == 3 && stop[ey][ex - 1] == false && items[ey][ex - 1] == 0)
				{
					ex--;
					save_enemy_walk = enemy_ctrl_chance;
					enemy_walk_done = true;
				}
				if (enemy_ctrl_chance == 4 && stop[ey][ex + 1] == false && items[ey][ex + 1] == 0)
				{
					ex++;
					save_enemy_walk = enemy_ctrl_chance;
					enemy_walk_done = true;
				}


				if (sym == 'w')
				{
					if (enemy_ctrl_chance == 6 && stop[ey + 1][ex - 1] == false && items[ey + 1][ex - 1] == 0)
					{
						ey++; ex--;
						save_enemy_walk = enemy_ctrl_chance;
						enemy_walk_done = true;
					}
					if (enemy_ctrl_chance == 7 && stop[ey + 1][ex + 1] == false && items[ey + 1][ex + 1] == 0)
					{
						ey++; ex++;
						save_enemy_walk = enemy_ctrl_chance;
						enemy_walk_done = true;
					}
					if (enemy_ctrl_chance == 8 && stop[ey - 1][ex - 1] == false && items[ey - 1][ex - 1] == 0)
					{
						ex--; ey--;
						save_enemy_walk = enemy_ctrl_chance;
						enemy_walk_done = true;
					}
					if (enemy_ctrl_chance == 9 && stop[ey - 1][ex + 1] == false && items[ey - 1][ex + 1] == 0)
					{
						ex++; ey--;
						save_enemy_walk = enemy_ctrl_chance;
						enemy_walk_done = true;
					}
				}


				if (enemy_ctrl_chance == 5 && sym != 'w' && sym != char(249) && current_location != 15)
				{
					if (save_enemy_walk == 1 && stop[ey - 1][ex] == false && items[ey - 1][ex] == 0)
					{
						esx = ex; esy = ey - 1;
						esword = char(179);
						eattack = true;
						enemy_walk_done = true;
					}
					if (save_enemy_walk == 2 && stop[ey + 1][ex] == false && items[ey + 1][ex] == 0)
					{
						esx = ex; esy = ey + 1;
						esword = char(179);
						eattack = true;
						enemy_walk_done = true;
					}
					if (save_enemy_walk == 3 && stop[ey][ex - 1] == false && items[ey][ex - 1] == 0)
					{
						esx = ex - 1; esy = ey;
						esword = char(196);
						eattack = true;
						enemy_walk_done = true;
					}
					if (save_enemy_walk == 4 && stop[ey][ex + 1] == false && items[ey][ex + 1] == 0)
					{
						esx = ex + 1; esy = ey;
						esword = char(196);
						eattack = true;
						enemy_walk_done = true;
					}
					enemy_ctrl_chance = save_enemy_walk;
				}

			} while (enemy_walk_done == false);

		}
		//boss attack if
		if (sym == 15 && ewc % 5 == 0)
		{
			boss_balls = rand() % 10 + 1;
			if (boss_balls == 1 && stop[ey + 1][ex] == false)
			{
				ey++;
			}
			if (boss_balls == 2 && stop[ey - 1][ex] == false)
			{
				ey--;
			}
			ex--;
			sym_col++;
			if (sym_col == 2)
				sym_col++;
			if (sym_col == 15)
				sym_col = 1;
			enemy_walk_done = true;
		}
		//BOSS head if
		if (current_location == 15 && sym == 2)
		{
			ex = 52; ey = 13;
		}
		if (enemy_walk_done == true && eattack == false && sym_col != clGreen)
		{
			SetConsoleCursorPosition(exdel, eydel);
			cout << " ";
			enemy_walk_done = false;
			SetConsoleCursorPosition(ex, ey);
			SetConsoleColorTextBackground(sym_col, bg_col);
			cout << sym;
		}
		if (eattack == true)
		{
			SetConsoleCursorPosition(esx, esy);
			SetConsoleColorTextBackground(clWhite);
			cout << esword;
			Sleep(30);
			SetConsoleCursorPosition(esx, esy);
			cout << " ";
		}
	}
}
void LinkCtrl()
{
	if (attack == true)
		attack = false;
	if (_kbhit())
		ctrl = _getch();
	xx = lx, yy = ly;

	//PAUSE
	if (ctrl == 13)
	{
		int comebackpls = 0;
		do
		{
			comebackpls = _getch();
		} while (comebackpls != 13);
	}

	//MOVE
	if (ctrl == 80 && stop[ly + 1][lx] == false)
	{
		ly++;
		link = char(30);
		kbh = true;
	}
	if (ctrl == 72 && stop[ly - 1][lx] == false)
	{
		ly--;
		link = char(31);
		kbh = true;
	}
	if (ctrl == 77 && stop[ly][lx + 1] == false)
	{
		lx++;
		link = char(17);
		kbh = true;
	}
	if (ctrl == 75 && stop[ly][lx - 1] == false)
	{
		lx--;
		link = char(16);
		kbh = true;
	}

	//відкриття дверей
	if (ctrl == 72 && locked_doors[current_location][1] == true && lx == 39 && ly == 10 && keys > 0)
	{
		keys--;
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(35, 5);
		cout << "   ";
		SetConsoleCursorPosition(35, 5);
		cout << keys;
		AddDoor('u', 'o');
		locked_doors[current_location][1] = false;
	}
	if (ctrl == 75 && locked_doors[current_location][0] == true && lx == 19 && ly == 16 && keys > 0)
	{
		keys--;
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(35, 5);
		cout << "   ";
		SetConsoleCursorPosition(35, 5);
		cout << keys;
		AddDoor('l', 'o');
		locked_doors[current_location][0] = false;
	}
	if (ctrl == 77 && locked_doors[current_location][2] == true && lx == 59 && ly == 16 && keys > 0)
	{
		keys--;
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(35, 5);
		cout << "   ";
		SetConsoleCursorPosition(35, 5);
		cout << keys;
		AddDoor('r', 'o');
		locked_doors[current_location][2] = false;
	}

	//АТАКА (кнопка A)
	if (ctrl == char(97) && gotsword == true && link == char(30) && stop[ly + 1][lx] == false)
	{
		sy = ly + 1;
		sx = lx;
		sword = char(179);
		attack = true;
		kbh = true;
	}
	if (ctrl == char(97) && gotsword == true && link == char(31) && stop[ly - 1][lx] == false)
	{
		sy = ly - 1;
		sx = lx;
		sword = char(179);
		attack = true;
		kbh = true;
	}
	if (ctrl == char(97) && gotsword == true && link == char(17) && stop[ly][lx + 1] == false)
	{
		sy = ly;
		sx = lx + 1;
		sword = char(196);
		attack = true;
		kbh = true;
	}
	if (ctrl == char(97) && gotsword == true && link == char(16) && stop[ly][lx - 1] == false)
	{
		sy = ly;
		sx = lx - 1;
		sword = char(196);
		attack = true;
		kbh = true;
	}
	if (attack == false && kbh == true)
	{
		SetConsoleColorTextBackground(clBlack, clBlack);
		SetConsoleCursorPosition(xx, yy);
		if (special_bonus == true)
		{
			SetConsoleColorTextBackground(link_col, clBlack);
			cout << char(176);
		}
		else
			cout << " ";
	}
	if (attack == true)
	{
		SetConsoleCursorPosition(sx, sy);
		SetConsoleColorTextBackground(sword_col, clBlack);
		cout << sword;
		Sleep(30);
		SetConsoleColorTextBackground(clBlack, clBlack);
		SetConsoleCursorPosition(sx, sy);
		if (special_bonus == true)
		{
			SetConsoleColorTextBackground(sword_col, clBlack);
			cout << char(176);
		}
		else
			cout << " ";
	}

	//збір предметів
	if ((items[ly][lx] == 1) || (attack == true && items[sy][sx] == 1))
	{
		if (llife < llife_buf)
		{
			if (llife < 7)
			{
				SetConsoleColorTextBackground(clRed);
				SetConsoleCursorPosition(49 + (llife * 2), 5);
				cout << char(3);
			}
			if (llife >= 7)
			{
				SetConsoleColorTextBackground(clRed);
				SetConsoleCursorPosition(49 + ((llife - 7) * 2), 4);
				cout << char(3);
			}
			llife++;
		}
		if (attack == true && items[sy][sx] == 1)
			items[sy][sx] = 0;
		else
			items[ly][lx] = 0;
	}
	if (items[ly][lx] == 2 || attack == true && items[sy][sx] == 2)
	{
		if (rupees < 255)
			rupees++;
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(35, 2);
		cout << rupees;
		if (attack == true && items[sy][sx] == 2)
			items[sy][sx] = 0;
		else
			items[ly][lx] = 0;
	}
	if (items[ly][lx] == 3 || attack == true && items[sy][sx] == 3)
	{
		if (rupees + 5 <= 255)
			rupees += 5;
		else
			rupees = 255;
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(35, 2);
		cout << rupees;
		if (attack == true && items[sy][sx] == 3)
			items[sy][sx] = 0;
		else
			items[ly][lx] = 0;
	}
	if (items[ly][lx] == 4 || attack == true && items[sy][sx] == 4) //4 - key
	{
		if (keys < 255)
			keys++;
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(35, 5);
		cout << keys;
		if (attack == true && items[sy][sx] == 4)
			items[sy][sx] = 0;
		else
			items[ly][lx] = 0;
		key_got[current_location] = 1;
	}
	if (items[ly][lx] == 5 || attack == true && items[sy][sx] == 5) //5 - compass
	{
		SetConsoleColorTextBackground(clRed, 0);
		if (gotmap == true)
			SetConsoleColorTextBackground(clRed, clBlue);
		SetConsoleCursorPosition(28, 2);
		cout << char(222) << char(221);
		if (attack == true && items[sy][sx] == 5)
			items[sy][sx] = 0;
		else
			items[ly][lx] = 0;
		gotcompass = true;
	}
	if (items[ly][lx] == 6 || attack == true && items[sy][sx] == 6) //6 - map
	{
		gotmap = true;
		StatusBar();
		SetConsoleColorTextBackground(clGreen, clBlue);
		SetConsoleCursorPosition(22, 3);
		cout << char(222) << char(221);
		if (attack == true && items[sy][sx] == 6)
			items[sy][sx] = 0;
		else
			items[ly][lx] = 0;
	}

	if (kbh == true)
	{
		SetConsoleCursorPosition(lx, ly);
		SetConsoleColorTextBackground(link_col, clBlack);
		cout << link;
		SetConsoleColorTextBackground(clGray);
		kbh = false;
	}
	ctrl = -1;
}
void LinkLifeCheck(int ex, int ey, int esx, int esy, bool eob, char sym, int sym_col, int bg_col)
{
	if ((eob == true && lx == ex && ly == ey) || (eob == true && eattack == true && lx == esx && ly == esy))
	{
		llife--;
		if (eob == true && lx == ex && ly == ey)
		{
			SetConsoleCursorPosition(ex, ey);
			SetConsoleColorTextBackground(sym_col, bg_col);
			cout << sym;
		}
		if (stop[ly][lx - 1] == false && l_back_step == false)
		{
			lx--;
			l_back_step = true;
		}
		if (stop[ly][lx + 1] == false && l_back_step == false)
		{
			lx++;
			l_back_step = true;
		}
		if (stop[ly - 1][lx] == false && l_back_step == false)
		{
			ly--;
			l_back_step = true;
		}
		if (stop[ly + 1][lx] == false && l_back_step == false)
		{
			ly++;
			l_back_step = true;
		}
		if (l_back_step == true)
		{
			SetConsoleCursorPosition(lx, ly);
			SetConsoleColorTextBackground(clRed);
			cout << link;
			Sleep(20);
			SetConsoleCursorPosition(lx, ly);
			SetConsoleColorTextBackground(link_col);
			cout << link;
			SetConsoleColorTextBackground(clGray);
			l_back_step = false;
		}
		if (llife < 7)
		{
			SetConsoleColorTextBackground(clGray);
			SetConsoleCursorPosition(49 + (llife * 2), 5);
			cout << char(3);
		}
		if (llife >= 7)
		{
			SetConsoleColorTextBackground(clGray);
			SetConsoleCursorPosition(49 + ((llife - 7) * 2), 4);
			cout << char(3);
		}
		if (llife == 0)
		{
			Game_Over();
		}
		kbh = false;
	}
}
void StatusBar()
{
	SetConsoleCursorPosition(33, 2);
	SetConsoleColorTextBackground(clYellow);
	cout << char(4);
	SetConsoleCursorPosition(35, 2);
	cout << "   ";
	SetConsoleCursorPosition(34, 2);
	SetConsoleColorTextBackground(clWhite);
	cout << "x" << rupees;
	SetConsoleCursorPosition(33, 5);
	SetConsoleColorTextBackground(clOlive);
	cout << char(198);
	SetConsoleCursorPosition(35, 5);
	cout << "   ";
	SetConsoleCursorPosition(34, 5);
	SetConsoleColorTextBackground(clWhite);
	cout << "x" << keys;
	SetConsoleCursorPosition(39, 1);
	SetConsoleColorTextBackground(clBlue);
	cout << char(201) << char(205);
	SetConsoleColorTextBackground(clWhite);
	cout << " A ";
	SetConsoleColorTextBackground(clBlue);
	cout << char(205) << char(187);
	for (int i = 2; i < 6; i++)
	{
		SetConsoleCursorPosition(39, i);
		cout << char(186);
		SetConsoleCursorPosition(45, i);
		cout << char(186);
	}
	SetConsoleCursorPosition(39, 6);
	SetConsoleColorTextBackground(clBlue);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);
	SetConsoleCursorPosition(49, 2);
	SetConsoleColorTextBackground(clRed);
	cout << char(196) << "  L I F E  " << char(196);
	if (llife_buf <= 7)
	{
		SetConsoleCursorPosition(49, 5);
		for (int i = 0; i < llife_buf; i++)
		{
			SetConsoleColorTextBackground(clGray);
			cout << char(3) << " ";
		}
		SetConsoleCursorPosition(49, 5);
		for (int i = 0; i < llife; i++)
		{
			SetConsoleColorTextBackground(clRed);
			cout << char(3) << " ";
		}
	}
	else
	{
		SetConsoleCursorPosition(49, 5);
		for (int i = 0; i < 7; i++)
		{
			SetConsoleColorTextBackground(clGray);
			cout << char(3) << " ";
		}
		SetConsoleCursorPosition(49, 4);
		for (int i = 0; i < llife_buf - 7; i++)
		{
			SetConsoleColorTextBackground(clGray);
			cout << char(3) << " ";
		}
		if (llife <= 7)
		{
			SetConsoleCursorPosition(49, 5);
			for (int i = 0; i < llife; i++)
			{
				SetConsoleColorTextBackground(clRed);
				cout << char(3) << " ";
			}
		}
		if (llife > 7)
		{
			SetConsoleCursorPosition(49, 5);
			for (int i = 0; i < 7; i++)
			{
				SetConsoleColorTextBackground(clRed);
				cout << char(3) << " ";
			}
			SetConsoleCursorPosition(49, 4);
			for (int i = 0; i < llife - 7; i++)
			{
				SetConsoleColorTextBackground(clRed);
				cout << char(3) << " ";
			}
		}
	}
	if (gotsword == true)
	{
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(42, 3);
		cout << char(179);
		SetConsoleColorTextBackground(clOlive);
		SetConsoleCursorPosition(42, 4);
		cout << char(210);
	}
	if (current_location != 0)
	{
		SetConsoleColorTextBackground(clWhite, clBlack);
		SetConsoleCursorPosition(17, 0);
		cout << "L E V E L - 1";
	}
	if (gotmap == true)
	{
		SetConsoleColorTextBackground(clBlue, clBlue);
		SetConsoleCursorPosition(20, 6);
		cout << "      ";
		SetConsoleCursorPosition(22, 5);
		cout << "  ";
		SetConsoleCursorPosition(20, 4);
		cout << "      ";
		SetConsoleCursorPosition(18, 3);
		cout << "          ";
		SetConsoleCursorPosition(22, 2);
		cout << "  ";
		SetConsoleCursorPosition(26, 2);
		cout << "    ";
		SetConsoleCursorPosition(20, 1);
		cout << "    ";
	}
	if (gotcompass == true)
	{
		SetConsoleColorTextBackground(clRed, clBlack);
		if (gotmap == true)
			SetConsoleColorTextBackground(clRed, clBlue);
		SetConsoleCursorPosition(28, 2);
		cout << char(222) << char(221);
	}
}
void AddEnemies(int num_of_enemy, int hp, char sym, int col_sym, int col_bg)
{
	for (int i = 0; i < num_of_enemy; i++)
	{
		bool enemy_cor_check = false;
		do
		{
			int rand_x = rand() % 41 + 19, rand_y = rand() % 12 + 10;
			if (stop[rand_y][rand_x] == false && items[rand_y][rand_x] == 0)
			{
				ex[i] = rand_x; ey[i] = rand_y;
				esx[i] = 0; esy[i] = 0;
				elife[i] = hp;
				enemy_sprite[i] = sym;
				enemy_sprite_col[i] = col_sym;
				enemy_sprite_bg[i] = col_bg;
				enemy_walk_chance[i] = 0;
				enemy_cor_check = true;
				enemy_on_board[i] = true;
			}
		} while (enemy_cor_check == false);
		SetConsoleCursorPosition(ex[i], ey[i]);
		SetConsoleColorTextBackground(enemy_sprite_col[i], enemy_sprite_bg[i]);
		cout << enemy_sprite[i];
	}
}
void EnemyActionCheck(int enemy_num)
{
	if (enemys_killed[current_location] == 0)
	{
		all_killed_check = 0;
		for (int i = 0; i < enemy_num; i++)
		{
			LinkLifeCheck(ex[i], ey[i], esx[i], esy[i], enemy_on_board[i], enemy_sprite[i], enemy_sprite_col[i], enemy_sprite_bg[i]);
		}
		for (int i = 0; i < enemy_num; i++)
		{
			EnemyWalk(ex[i], ey[i], esx[i], esy[i], elife[i], enemy_on_board[i], enemy_walk_chance[i], enemy_sprite[i], enemy_sprite_col[i], enemy_sprite_bg[i]);
		}
		for (int i = 0; i < enemy_num; i++)
		{
			if (enemy_on_board[i] == true)
			{
				all_killed_check = -1;
			}
		}
		if (all_killed_check == 0)
			enemys_killed[current_location] = 1;
		Sleep(10);
	}
}
void NewGame() //тут я використовую інтові масиви, тому що булеві чомусь працюють некоректно (умови не виконуються там, де повинні. Використовуючи ж інтові масиви з такими ж умовами все працює як треба) або ж я щось роблю не так 
{
	//чистимо потрібні масиви
	for (int i = 0; i < 18; i++)
	{
		key_drop[i] = 0;
		key_got[i] = 0;
		enemys_killed[i] = 0;
	}
	//ініціалізуємо двері...
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 4; j++) // 0 - двері ліворуч, 1 - вгорі, 2 - праворуч, 3 - внизу
		{
			locked_doors[i][j] = 0;
		}
	}
	//...закриваємо потрібні
	locked_doors[1][1] = 1;
	locked_doors[7][1] = 1;
	locked_doors[10][1] = 1;
	locked_doors[11][0] = 1;
	locked_doors[9][2] = 1;
	locked_doors[14][1] = 1;
	//змінюємо значення змінних для повторного проходження
	llife_buf = llife_tmp;
	llife = llife_buf;
	rupees = rupees_tmp;
	keys = keys_tmp;
	lx = 39; ly = 23;
	secret[0] = 0;
	secret[1] = 0;
	gotsword = false;
	gotcompass = false;
	gotmap = false;
	basement = false;
	lil_bonus = false;
	YOU_DEFEATED = false;
	dragon_heart = false;
	triforce = false;
	bad_karma = false;
	text = false;
	delsword = false;
	YOU_DIED = false;
}
void NewLocation()
{
	//очищаємо координати всіх можливих предметів
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 79; j++)
		{
			items[i][j] = 0;
		}
	}
	//чистимо координати ворогів
	for (int i = 0; i < 10; i++)
	{
		ex[i] = 0; ey[i] = 0;
		esx[i] = 0; esy[i] = 0;
	}
}
void HowToPlay()
{
	system("cls");
	SetConsoleColorTextBackground(clGreen, 0);
	SetConsoleCursorPosition(23, 1);
	cout << char(201) << char(205) << char(205) << char(205) << char(205);
	SetConsoleColorTextBackground(clRed, 0);
	cout << "  H O W   T O   P L A Y  ";
	SetConsoleColorTextBackground(clGreen, 0);
	cout << char(205) << char(205) << char(205) << char(205) << char(187);
	for (int i = 2; i < 25; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			if (j == 23 || j == 57)
			{
				SetConsoleColorTextBackground(clGreen, 0);
				SetConsoleCursorPosition(j, i);
				cout << char(186);
			}
		}
	}
	SetConsoleCursorPosition(23, 25);
	cout << char(200);
	for (int i = 23; i < 56; i++)
	{
		cout << char(205);
	}
	cout << char(188);
	SetConsoleColorTextBackground(clTeal, 0);
	SetConsoleCursorPosition(28, 3);
	cout << char(214) << char(196) << char(191);
	SetConsoleCursorPosition(28, 4);
	cout << char(186) << char(24) << char(179);
	SetConsoleCursorPosition(28, 5);
	cout << char(200) << char(205) << char(190);
	SetConsoleCursorPosition(25, 6);
	cout << char(214) << char(196) << char(191);
	cout << char(214) << char(196) << char(191);
	cout << char(214) << char(196) << char(191);
	SetConsoleCursorPosition(25, 7);
	cout << char(186) << '<' << char(27) << char(179) << char(179);
	cout << char(186) << char(25) << char(179);
	cout << char(186) << char(26) << char(179);
	SetConsoleCursorPosition(25, 8);
	cout << char(200) << char(205) << char(190);
	cout << char(200) << char(205) << char(190);
	cout << char(200) << char(205) << char(190);
	SetConsoleColorTextBackground(clBrown, 0);
	SetConsoleCursorPosition(28, 13);
	cout << char(214) << char(196) << char(191);
	SetConsoleCursorPosition(28, 14);
	cout << char(186) << "A" << char(179) << "        A T T A C K";
	SetConsoleCursorPosition(28, 15);
	cout << char(200) << char(205) << char(190);
	SetConsoleColorTextBackground(clOlive, 0);
	SetConsoleCursorPosition(26, 20);
	cout << char(214) << char(196) << char(196) << char(196) << char(196) << char(196) << char(191);
	SetConsoleCursorPosition(26, 21);
	cout << char(186) << "ENTER" << char(179) << "       P A U S E";
	SetConsoleCursorPosition(26, 22);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(190);
	SetConsoleColorTextBackground(clTeal, 0);
	SetConsoleCursorPosition(40, 5);
	cout << "M O V E  /";
	SetConsoleCursorPosition(35, 6);
	cout << "U N L O C K   D O O R";
	_getch();
}
void Adventure_Begin()
{
	system("cls");
	SetConsoleColorTextBackground(clGreen, 0);
	SetConsoleCursorPosition(14, 1);
	cout << char(201) << char(205) << char(205) << char(205) << char(205);
	SetConsoleColorTextBackground(clRed, 0);
	cout << "  T H E   L E G E N D   O F   Z E L D A  ";
	SetConsoleColorTextBackground(clGreen, 0);
	cout << char(205) << char(205) << char(205) << char(205) << char(187);
	for (int i = 2; i < 25; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			if (j == 14 || j == 64)
			{
				SetConsoleColorTextBackground(clGreen, 0);
				SetConsoleCursorPosition(j, i);
				cout << char(186);
			}
		}
	}
	SetConsoleCursorPosition(14, 25);
	cout << char(200);
	for (int i = 15; i < 64; i++)
	{
		cout << char(205);
	}
	cout << char(188);
	SetConsoleColorTextBackground(clWhite, 0);
	char mainstory[] = "M A N Y     Y E A R S     A G O     P R I N C ED A R K N E S S    \" G A N N O N \"    S T O L EO N E   O F   T H E   T R I F O R C E   W I T HP O W E R .         P R I N C E S S   Z E L D AH A D    O N E   O F   T H E    T R I F O R C EW I T H   W I S D O M .     S H E   P U T   I TI N    T H E    D U N G E O N    T O    H I D EI T   F R O M    \" G A N N O N \"    B E F O R ES H E   W A S   C A P T U R E D .";
	int abc = 0;
	for (int i = 3; i < 24; i += 2)
	{
		if (abc > 408)
			break;
		for (int j = 16; j < 63; j++)
		{
			SetConsoleCursorPosition(j, i);
			cout << mainstory[abc];
			abc++;
			if (abc > 408)
				break;
		}
	}
	SetConsoleColorTextBackground(clBrown, 0);
	SetConsoleCursorPosition(35, 5);
	cout << "\" G A N N O N \"";
	SetConsoleColorTextBackground(clTeal, 0);
	SetConsoleCursorPosition(38, 7);
	cout << "T R I F O R C E";
	SetConsoleColorTextBackground(clBrown, 0);
	SetConsoleCursorPosition(54, 9);
	cout << "Z E L D A";
	SetConsoleColorTextBackground(clTeal, 0);
	SetConsoleCursorPosition(48, 11);
	cout << "T R I F O R C E";
	SetConsoleColorTextBackground(clTeal, 0);
	SetConsoleCursorPosition(32, 15);
	cout << "D U N G E O N";
	SetConsoleColorTextBackground(clBrown, 0);
	SetConsoleCursorPosition(33, 17);
	cout << "\" G A N N O N \"";
	SetConsoleColorTextBackground(clRed, 0);
	SetConsoleCursorPosition(16, 22);
	cout << " EXPLORE ONE DUNGEON AND BUY THE FULL VERSION!";
	SetConsoleCursorPosition(15, 23);
	cout << "(NOW AVAILABLE ON";
	SetConsoleColorTextBackground(clGray, 0);
	cout << " NINTENDO ";
	SetConsoleColorTextBackground(clYellow, 0);
	cout << "ESHOP";
	SetConsoleColorTextBackground(clRed, 0);
	cout << " ONLY FOR $4.99!)";
	_getch();
}
void Game_Over()
{
	for (int i = 0; i < 3; i++)
	{
		SetConsoleColorTextBackground(link_col, 0);
		SetConsoleCursorPosition(lx, ly);
		cout << char(16);
		Sleep(200);
		SetConsoleColorTextBackground(link_col, 0);
		SetConsoleCursorPosition(lx, ly);
		cout << char(17);
		Sleep(200);
	}
	SetConsoleColorTextBackground(clGray, 0);
	SetConsoleCursorPosition(lx, ly);
	cout << char(30);
	Sleep(300);
	for (int i = 0; i < 2; i++)
	{
		SetConsoleCursorPosition(lx, ly);
		cout << "\\";
		Sleep(100);
		SetConsoleCursorPosition(lx, ly);
		cout << "|";
		Sleep(100);
		SetConsoleCursorPosition(lx, ly);
		cout << "/";
		Sleep(100);
		SetConsoleCursorPosition(lx, ly);
		cout << char(196);
		Sleep(100);
	}
	SetConsoleCursorPosition(lx, ly);
	cout << char(249);
	Sleep(500);
	SetConsoleCursorPosition(lx, ly);
	cout << char(250);
	Sleep(500);
	system("cls");
	SetConsoleCursorPosition(32, 12);
	SetConsoleColorTextBackground(clWhite, 0);
	cout << "G A M E   O V E R";
	YOU_DIED = true;
	int enterpls = 0;
	do
	{
		enterpls = _getch();
	} while (enterpls != 13);

}
void FirstStepWall()
{
	//NoWay
	NewLocation();
	for (int i = 8; i < 25; i++)
		for (int j = 16; j <= 62; j++)
			if (i < 13 || i>23 || (i > 21 && j < 37 || i>21 && j > 41) || j < 19 || j>59)
				stop[i][j] = true;
			else
				stop[i][j] = false;
	system("cls");
	Frame();
	current_location = 0;
	SetConsoleColorTextBackground(clBrown);
	for (int i = 8; i < 24; i++)
	{
		for (int j = 16; j <= 62; j++)
		{
			if (i < 10 || (i > 21 && j < 37 || i>21 && j > 41) || j < 19 || j>59)
			{
				SetConsoleCursorPosition(j, i);
				cout << char(178);
			}
		}
	}
	StatusBar();
	ex[0] = 39; ey[0] = 14;
	enemy_on_board[0] = true;
	SetConsoleCursorPosition(ex[0], ey[0]);
	SetConsoleColorTextBackground(clGray);
	cout << char(2);
	AddTexture(39, 16, clWhite, clBlack, char(179));
	SetConsoleCursorPosition(39, 17);
	SetConsoleColorTextBackground(clOlive);
	cout << char(210);
	AddTexture(28, 14, clYellow, clBlack, char(176));
	AddTexture(29, 14, clYellow, clBlack, char(176));
	AddTexture(49, 14, clYellow, clBlack, char(176));
	AddTexture(50, 14, clYellow, clBlack, char(176));
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(39, 23);
	cout << char(31);
	SetConsoleColorTextBackground(clWhite);
	char too_dungerous[100] = "I T ' S   D A N G E R O U S   T O   G OA L O N E !   T A K E   T H I S .";
	SetConsoleCursorPosition(20, 11);
	for (int i = 0; i < strlen(too_dungerous); i++)
	{
		fire_col++;
		if (fire_col % 7 == 0)
		{
			AddTexture(28, 14, clYellow, clBlack, char(176));
			AddTexture(29, 14, clYellow, clBlack, char(176));
			AddTexture(49, 14, clYellow, clBlack, char(176));
			AddTexture(50, 14, clYellow, clBlack, char(176));
		}
		if (fire_col % 14 == 0)
		{
			AddTexture(28, 14, clRed, clBlack, char(176));
			AddTexture(29, 14, clRed, clBlack, char(176));
			AddTexture(49, 14, clRed, clBlack, char(176));
			AddTexture(50, 14, clRed, clBlack, char(176));
		}
		SetConsoleColorTextBackground(clWhite);
		if (i <= 38)
		{
			SetConsoleCursorPosition(20 + i, 11);
			cout << too_dungerous[i];
		}
		if (i > 38)
		{
			SetConsoleCursorPosition(i - 15, 12);
			cout << too_dungerous[i];
		}
		if (too_dungerous[i] != ' ')
			Sleep(50);
		if (_kbhit())
			int missclick = _getch();
	}
	while (1)
	{
		LinkCtrl();
		if (bad_karma == false && lx == 39 && ly == 14)
		{
			llife--;
			lx--;
			SetConsoleCursorPosition(lx, ly);
			SetConsoleColorTextBackground(clRed);
			cout << link;
			Sleep(20);
			SetConsoleCursorPosition(lx, ly);
			SetConsoleColorTextBackground(link_col);
			cout << link;
			SetConsoleCursorPosition(39, 14);
			SetConsoleColorTextBackground(clGray);
			cout << char(2);
			if (llife < 7)
			{
				SetConsoleColorTextBackground(clGray);
				SetConsoleCursorPosition(49 + (llife * 2), 5);
				cout << char(3);
			}
			if (llife >= 7)
			{
				SetConsoleColorTextBackground(clGray);
				SetConsoleCursorPosition(49 + ((llife - 7) * 2), 4);
				cout << char(3);
			}
		}
		if (sx == 39 && sy == 14 && attack == true && bad_karma == false)
		{
			ex[0] = 1; ey[0] = 1;
			SetConsoleCursorPosition(20, 11);
			for (int i = 0; i < 78; i++)
			{
				cout << " ";
				if (i == 38)
					SetConsoleCursorPosition(20, 12);
			}

			SetConsoleCursorPosition(31, 11);
			SetConsoleColorTextBackground(clWhite);
			cout << "Y O U   G O T   A";
			if (llife_buf < 14)
			{
				SetConsoleCursorPosition(25, 12);
				SetConsoleColorTextBackground(clRed);
				cout << "H E A R T   C O N T A I N E R ";
			}
			else
			{
				SetConsoleCursorPosition(20, 12);
				SetConsoleColorTextBackground(clRed);
				cout << "B L O O D   O N   Y O U R   H A N D S ";
			}
			SetConsoleColorTextBackground(clWhite);
			cout << "!";


			SetConsoleColorTextBackground(clRed);
			if (llife_buf < 14)
				llife_buf++;
			llife = llife_buf;
			StatusBar();
			bad_karma = true;
		}
		if (lx == 39 && ly == 17 && gotsword == false)
		{
			SetConsoleCursorPosition(39, 16);
			cout << " ";
			SetConsoleCursorPosition(20, 11);
			for (int i = 0; i < 73; i++)
			{
				cout << " ";
				if (i == 38)
					SetConsoleCursorPosition(23, 12);
			}
			gotsword = true;
			stop[16][39] = false;
			SetConsoleColorTextBackground(clWhite);
			SetConsoleCursorPosition(42, 3);
			cout << char(179);
			SetConsoleColorTextBackground(clOlive);
			SetConsoleCursorPosition(42, 4);
			cout << char(210);

			strcpy_s(too_dungerous, "E n t e r   t h e   P o r t a l   t o f o l l o w   y o u r   d e s t i n y !");
			_strupr(too_dungerous);
			SetConsoleCursorPosition(20, 11);
			for (int i = 0; i < 77; i++)
			{
				SetConsoleColorTextBackground(clWhite);
				if (i <= 37)
				{
					SetConsoleCursorPosition(21 + i, 11);
					cout << too_dungerous[i];
				}
				if (i > 37)
				{
					SetConsoleCursorPosition(i - 18, 12);
					cout << too_dungerous[i];
				}
			}
		}
		if (gotsword == true && lx == 39 && ly == 20)
		{
			ex[0] = 0; ey[0] = 0;
			break;
		}
		fire_col++;
		if (fire_col == 2099999999)
			fire_col = 0;
		if (gotsword == true)
		{
			SetConsoleColorTextBackground(rand() % 15 + 1);
			SetConsoleCursorPosition(39, 20);
			cout << "0";
		}
		if (fire_col % 5 == 0)
		{
			AddTexture(28, 14, clYellow, clBlack, char(176));
			AddTexture(29, 14, clYellow, clBlack, char(176));
			AddTexture(49, 14, clYellow, clBlack, char(176));
			AddTexture(50, 14, clYellow, clBlack, char(176));
		}
		Sleep(5);
		if (fire_col % 10 == 0)
		{
			AddTexture(28, 14, clRed, clBlack, char(176));
			AddTexture(29, 14, clRed, clBlack, char(176));
			AddTexture(49, 14, clRed, clBlack, char(176));
			AddTexture(50, 14, clRed, clBlack, char(176));
		}
		Sleep(5);
		if (llife == 0)
		{
			Game_Over();
			break;
		}
	}
	if (YOU_DIED == true)
		return;
	Warp();
}
void Room_1()
{
	system("cls");
	current_location = 1;
	NoWay();
	NewLocation();
	StatusBar();
	Frame();
	Wall();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(22, 6);
	cout << char(222) << char(221);
	AddMultTexture(54, 13, 55, 13, 1, 9, 177);
	AddMultTexture(44, 13, 45, 13, 1, 9, 177);
	AddMultTexture(33, 13, 34, 13, 1, 9, 177);
	AddMultTexture(23, 13, 24, 13, 1, 9, 177);
	AddMultTexture(54, 16, 55, 16, 1, 9, 177);
	AddMultTexture(44, 16, 45, 16, 1, 9, 177);
	AddMultTexture(33, 16, 34, 16, 1, 9, 177);
	AddMultTexture(23, 16, 24, 16, 1, 9, 177);
	AddMultTexture(54, 19, 55, 19, 1, 9, 177);
	AddMultTexture(44, 19, 45, 19, 1, 9, 177);
	AddMultTexture(33, 19, 34, 19, 1, 9, 177);
	AddMultTexture(23, 19, 24, 19, 1, 9, 177);
	if (locked_doors[current_location][1] == 1)
		AddDoor('u', 'l');
	else
		AddDoor('u', 'o');
	AddDoor('r', 'o'); AddDoor('l', 'o');
	if (basement == true)
	{
		SetConsoleColorTextBackground(clBlack, clGray);
		SetConsoleCursorPosition(19, 21);
		cout << char(176);
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		if (lx > 60 || lx < 18 || ly < 10 || (((lx == 19 && ly == 21) || (attack == true && sx == 19 && sy == 21)) && basement == true))
			break;
	}
	Warp();
}
void Room_2()
{
	system("cls");
	current_location = 2;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(24, 6);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddMultTexture(26, 14, 31, 18, clBlue, clTeal, 176);
	AddMultTexture(47, 14, 52, 18, clBlue, clTeal, 176);
	AddDoor('l', 'o');
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(5, hp_skeleton, 2, clWhite, 0);
	}
	if (key_got[current_location] == 0)
	{
		key_drop[current_location] = 0;
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(5);
		if (enemys_killed[current_location] == 1 && key_drop[current_location] == 0)
		{
			items[16][39] = 4;
			SetConsoleCursorPosition(39, 16);
			SetConsoleColorTextBackground(clOlive);
			cout << char(198);
			key_drop[current_location] = 1;
		}
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_3()
{
	system("cls");
	current_location = 3;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(20, 6);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddDoor('r', 'o');
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(3, hp_batngoo, 'w', clBlue, 0);
	}
	if (key_got[current_location] == 0)
	{
		key_drop[current_location] = 0;
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(3);
		if (enemys_killed[current_location] == 1 && key_drop[current_location] == 0)
		{
			items[21][45] = 4;
			SetConsoleCursorPosition(45, 21);
			SetConsoleColorTextBackground(clOlive);
			cout << char(198);
			key_drop[current_location] = 1;
		}
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_4()
{
	system("cls");
	current_location = 4;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(22, 5);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddDoor('u', 'o');
	AddDoor('d', 'o');
	AddMultTexture(36, 13, 42, 18, clBlue, clTeal, 176);
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(3, hp_skeleton, 2, clWhite, 0);
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(3);
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_5()
{
	system("cls");
	current_location = 5;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(22, 4);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddDoor('l', 'o');
	AddDoor('r', 'o');
	AddDoor('d', 'o');
	AddMultTexture(26, 13, 27, 13, clBlue, clTeal, 176);
	AddMultTexture(26, 18, 27, 18, clBlue, clTeal, 176);
	AddMultTexture(51, 13, 52, 13, clBlue, clTeal, 176);
	AddMultTexture(51, 18, 52, 18, clBlue, clTeal, 176);
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(5, hp_skeleton, 2, clWhite, 0);
	}
	if (key_got[current_location] == 0)
	{
		key_drop[current_location] = 0;
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(5);
		if (enemys_killed[current_location] == 1 && key_drop[current_location] == 0)
		{
			items[12][41] = 4;
			SetConsoleCursorPosition(41, 12);
			SetConsoleColorTextBackground(clOlive);
			cout << char(198);
			key_drop[current_location] = 1;
		}
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_6()
{
	system("cls");
	current_location = 6;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(24, 4);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddMultTexture(52, 19, 53, 19, clBlue, clTeal, 176);
	AddMultTexture(52, 12, 53, 12, clBlue, clTeal, 176);
	AddMultTexture(26, 19, 27, 19, clBlue, clTeal, 176);
	AddMultTexture(26, 12, 27, 12, clBlue, clTeal, 176);
	AddDoor('l', 'o');
	if (gotcompass == false)
	{
		items[16][55] = 5;
		SetConsoleCursorPosition(55, 16);
		SetConsoleColorTextBackground(clOlive);
		cout << char(15);
	}
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(8, hp_batngoo, 'w', clBlue, 0);
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(8);
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_7()
{
	system("cls");
	current_location = 7;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(20, 4);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddMultTexture(36, 13, 42, 18, clBlue, clTeal, 176);
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(6, hp_batngoo, 'w', clBlue, 0);
		if (ly == 16)
			lx--;
		AddDoor('r', 'c');
	}
	if (locked_doors[current_location][1] == 1)
		AddDoor('u', 'l');
	else
		AddDoor('u', 'o');
	if (key_drop[current_location] == 1)
		AddDoor('r', 'o');
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(6);
		if (enemys_killed[current_location] == 1 && key_drop[current_location] == 0) //у цій кімнаті не випадає ключ, але я використовую key_drop[current_location] для того, щоб відімкнути зачинені двері після вбивства всіх ворогів (і не створювати додаткову змінну)
		{
			AddDoor('r', 'o');
			key_drop[current_location] = 1;
		}
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_8()
{
	system("cls");
	current_location = 8;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(20, 3);
	cout << char(222) << char(221);
	Frame();
	Wall();
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(3, hp_batngoo, 249, clGray, 0);
		AddTexture(38, 16, clBlue, clTeal, 176);
	}
	else
	{
		SetConsoleColorTextBackground(clBlue, clTeal);
		SetConsoleCursorPosition(38, 16);
		cout << char(176);
	}
	AddDoor('l', 'c');
	AddDoor('d', 'o');
	AddDoor('r', 'o');
	secret[0] = 0;
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(3);
		if (enemys_killed[current_location] == 1 && key_drop[current_location] == 0) //не дивуйтеся використанню key_drop[current_location]. ключ тут не з'являється, але це особливий випадок (як і, напевно, в наступних локаціях). тому, щоб не створювати додаткові змінні, я користуюся цією
		{
			DeleteTexture(38, 16);
			SetConsoleColorTextBackground(clBlue, clTeal);
			SetConsoleCursorPosition(38, 16);
			cout << char(176);
			key_drop[current_location] = 1;
		}
		if (((lx == 38 && ly == 16) || (sx == 38 && sy == 16 && attack == true)) && secret[0] == 0)
		{
			if (link == char(16))
			{
				AddTexture(37, 16, clBlue, clTeal, 176);
			}
			if (link == char(17))
			{
				AddTexture(39, 16, clBlue, clTeal, 176);
			}
			if (link == char(30))
			{
				AddTexture(38, 17, clBlue, clTeal, 176);
			}
			if (link == char(31))
			{
				AddTexture(38, 15, clBlue, clTeal, 176);
			}
			AddDoor('l', 'o');
			secret[0] = 1;
		}
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void STORE()
{
	system("cls");
	bool buy_one = false, clrStore = false;
	current_location = 99;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(18, 3);
	cout << char(222) << char(221);
	Frame();
	Wall();
	for (int i = 8; i < 25; i++)
		for (int j = 16; j <= 62; j++)
			if (i < 16)
				stop[i][j] = true;
	SetConsoleCursorPosition(39, 13);
	SetConsoleColorTextBackground(clOlive);
	cout << char(2);
	AddTexture(28, 13, clYellow, clBlack, char(176));
	AddTexture(29, 13, clYellow, clBlack, char(176));
	AddTexture(49, 13, clYellow, clBlack, char(176));
	AddTexture(50, 13, clYellow, clBlack, char(176));
	AddDoor('r', 'o');
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	AddTexture(24, 15, clBlue, clBlack, 4);
	AddTexture(25, 15, clWhite, clBlack, 'x');
	SetConsoleCursorPosition(38, 15);
	SetConsoleColorTextBackground(clWhite);
	cout << "100";
	SetConsoleCursorPosition(31, 15);
	SetConsoleColorTextBackground(clWhite);
	cout << "50";
	SetConsoleCursorPosition(46, 15);
	SetConsoleColorTextBackground(clWhite);
	cout << "25";
	if (rupees < 100)
		AddTexture(39, 16, clOlive, clBlack, 198);
	else
	{
		SetConsoleCursorPosition(39, 16);
		SetConsoleColorTextBackground(clOlive);
		cout << char(198);
	}
	if (rupees < 50)
		AddTexture(31, 16, clRed, clWhite, 3);
	else
	{
		SetConsoleCursorPosition(31, 16);
		SetConsoleColorTextBackground(clRed, clWhite);
		cout << char(3);
	}
	if (rupees < 25)
		AddTexture(47, 16, clRed, clBlack, 3);
	else
	{
		SetConsoleCursorPosition(47, 16);
		SetConsoleColorTextBackground(clRed, clBlack);
		cout << char(3);
	}
	SetConsoleColorTextBackground(clWhite);
	char text[] = "B U Y   S O M E T H I N '   W I L L   Y A";
	SetConsoleCursorPosition(19, 11);
	for (int i = 0; i < strlen(text); i++)
	{
		fire_col++;
		if (fire_col % 7 == 0)
		{
			AddTexture(28, 13, clYellow, clBlack, char(176));
			AddTexture(29, 13, clYellow, clBlack, char(176));
			AddTexture(49, 13, clYellow, clBlack, char(176));
			AddTexture(50, 13, clYellow, clBlack, char(176));
		}
		if (fire_col % 14 == 0)
		{
			AddTexture(28, 13, clRed, clBlack, char(176));
			AddTexture(29, 13, clRed, clBlack, char(176));
			AddTexture(49, 13, clRed, clBlack, char(176));
			AddTexture(50, 13, clRed, clBlack, char(176));
		}
		SetConsoleColorTextBackground(clWhite);
		SetConsoleCursorPosition(19 + i, 11);
		cout << text[i];
		if (text[i] != ' ')
			Sleep(50);
		if (_kbhit())
			int missclick = _getch();
	}
	while (1)
	{
		LinkCtrl();
		if (((lx == 47 && ly == 16) || (sx == 47 && sy == 16)) && buy_one == false)
		{
			if (llife < llife_buf)
				llife++;
			rupees -= 25;
			StatusBar();
			DeleteTexture(31, 16); DeleteTexture(39, 16);
			buy_one = true;
		}
		if (((lx == 39 && ly == 16) || (sx == 39 && sy == 16)) && buy_one == false)
		{
			if (keys < 255)
				keys++;
			rupees -= 100;
			StatusBar();
			DeleteTexture(31, 16); DeleteTexture(47, 16);
			buy_one = true;
		}
		if (((lx == 31 && ly == 16) || (sx == 31 && sy == 16)) && buy_one == false)
		{
			if (llife_buf < 14)
				llife_buf++;
			llife = llife_buf;
			rupees -= 50;
			StatusBar();
			DeleteTexture(39, 16); DeleteTexture(47, 16);
			buy_one = true;
		}
		if (buy_one == true && clrStore == false)
		{
			for (int i = 10; i < 16; i++)
			{
				for (int j = 19; j < 60; j++)
				{
					stop[i][j] = false;
				}
				SetConsoleColorTextBackground(clBlack, clBlack);
				SetConsoleCursorPosition(19, i);
				cout << text;
			}
			SetConsoleColorTextBackground(link_col, clBlack);
			if (gotmap == true)
				SetConsoleColorTextBackground(link_col, clBlue);
			SetConsoleCursorPosition(18, 3);
			cout << char(222) << char(221);
			clrStore = true;
		}
		fire_col++;
		if (fire_col == 2099999999)
			fire_col = 0;
		if (fire_col % 5 == 0)
		{
			AddTexture(28, 13, clYellow, clBlack, char(176));
			AddTexture(29, 13, clYellow, clBlack, char(176));
			AddTexture(49, 13, clYellow, clBlack, char(176));
			AddTexture(50, 13, clYellow, clBlack, char(176));
		}
		Sleep(5);
		if (fire_col % 10 == 0)
		{
			AddTexture(28, 13, clRed, clBlack, char(176));
			AddTexture(29, 13, clRed, clBlack, char(176));
			AddTexture(49, 13, clRed, clBlack, char(176));
			AddTexture(50, 13, clRed, clBlack, char(176));
		}
		Sleep(5);
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_9()
{
	system("cls");
	current_location = 9;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(22, 3);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddMultTexture(52, 19, 55, 19, clBlue, clTeal, 176);
	AddMultTexture(52, 12, 55, 12, clBlue, clTeal, 176);
	AddMultTexture(24, 19, 27, 19, clBlue, clTeal, 176);
	AddMultTexture(24, 12, 27, 12, clBlue, clTeal, 176);
	AddMultTexture(37, 16, 41, 16, clBlue, clTeal, 176);
	AddDoor('l', 'o');
	AddDoor('u', 'o');
	if (locked_doors[current_location][2] == true)
		AddDoor('r', 'l');
	else
		AddDoor('r', 'o');
	if (gotmap == false)
	{
		items[16][55] = 6;
		SetConsoleCursorPosition(55, 16);
		SetConsoleColorTextBackground(clOlive, clWhite);
		cout << char(219);
	}
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(5, hp_batngoo, 249, clGray, 0);
	}
	SetConsoleColorTextBackground(link_col, clBlack);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(5);
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_10()
{
	system("cls");
	current_location = 10;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(22, 2);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddMultTexture(19, 10, 59, 21, clBlue, clBlue, 176);
	AddDoor('d', 'o');
	if (locked_doors[current_location][1] == 1)
		AddDoor('u', 'l');
	else
		AddDoor('u', 'o');
	DeleteMultTexture(37, 20, 41, 21);
	DeleteMultTexture(40, 16, 41, 19);
	DeleteMultTexture(37, 10, 41, 11);
	DeleteMultTexture(37, 12, 38, 15);
	DeleteMultTexture(37, 15, 41, 16);
	DeleteMultTexture(42, 11, 49, 11);
	DeleteMultTexture(29, 20, 36, 20);
	DeleteMultTexture(48, 11, 49, 20);
	DeleteMultTexture(29, 11, 30, 20);
	DeleteMultTexture(50, 20, 57, 20);
	DeleteMultTexture(21, 11, 28, 11);
	DeleteMultTexture(56, 11, 57, 20);
	DeleteMultTexture(21, 11, 22, 20);
	DeleteMultTexture(58, 16, 59, 16);
	DeleteMultTexture(19, 15, 20, 15);
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(3, hp_skeleton, 2, clWhite, 0);
	}
	if (key_got[current_location] == 0)
	{
		key_drop[current_location] = 0;
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(3);
		if (enemys_killed[current_location] == 1 && key_drop[current_location] == 0)
		{
			items[15][19] = 4;
			SetConsoleCursorPosition(19, 15);
			SetConsoleColorTextBackground(clOlive);
			cout << char(198);
			key_drop[current_location] = 1;
		}
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_11()
{
	system("cls");
	current_location = 11;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(22, 1);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddMultTexture(31, 16, 47, 16, clBlue, clBlue, 176);
	AddMultTexture(21, 13, 22, 19, clBlue, clBlue, 176);
	AddMultTexture(56, 13, 57, 19, clBlue, clBlue, 176);
	AddMultTexture(23, 13, 32, 13, clBlue, clBlue, 176);
	AddMultTexture(23, 19, 32, 19, clBlue, clBlue, 176);
	AddMultTexture(46, 13, 57, 13, clBlue, clBlue, 176);
	AddMultTexture(46, 19, 57, 19, clBlue, clBlue, 176);
	AddDoor('d', 'o');
	if (locked_doors[current_location][0] == 1)
		AddDoor('l', 'l');
	else
		AddDoor('l', 'o');
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(3, hp_pig, 2, clMagneta, 0);
	}
	if (key_got[current_location] == 0)
	{
		key_drop[current_location] = 0;
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(3);
		if (enemys_killed[current_location] == 1 && key_drop[current_location] == 0)
		{
			items[13][40] = 4;
			SetConsoleCursorPosition(40, 13);
			SetConsoleColorTextBackground(clOlive);
			cout << char(198);
			key_drop[current_location] = 1;
		}
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_12()
{
	system("cls");
	current_location = 12;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(20, 1);
	cout << char(222) << char(221);
	Frame();
	Wall();
	secret[1] = 0;
	AddDoor('r', 'o');
	AddMultTexture(38, 14, 39, 14, clBlue, clTeal, 176);
	AddMultTexture(40, 15, 41, 15, clBlue, clTeal, 176);
	AddMultTexture(36, 15, 37, 15, clBlue, clTeal, 176);
	AddMultTexture(42, 16, 43, 16, clBlue, clTeal, 176);
	AddMultTexture(40, 17, 41, 17, clBlue, clTeal, 176);
	AddMultTexture(36, 17, 37, 17, clBlue, clTeal, 176);
	AddMultTexture(38, 18, 39, 18, clBlue, clTeal, 176);
	AddTexture(19, 10, clBlue, 0, 253);
	AddTexture(59, 10, clBlue, 0, 253);
	AddTexture(19, 21, clBlue, 0, 253);
	AddTexture(59, 21, clBlue, 0, 253);
	SetConsoleColorTextBackground(clBlue, clTeal);
	SetConsoleCursorPosition(35, 16);
	cout << char(176);
	SetConsoleColorTextBackground(clBlack, clGray);
	SetConsoleCursorPosition(38, 16);
	cout << char(176) << char(176);
	SetConsoleColorTextBackground(link_col, 0);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		if (((lx == 35 && ly == 16) || (sx == 35 && sy == 16 && attack == true)) && secret[1] == 0)
		{
			if (link == char(16))
			{
				AddTexture(34, 16, clBlue, clTeal, 176);
			}
			if (link == char(17))
			{
				AddTexture(36, 16, clBlue, clTeal, 176);
			}
			if (link == char(30))
			{
				AddTexture(35, 17, clBlue, clTeal, 176);
			}
			if (link == char(31))
			{
				AddTexture(35, 15, clBlue, clTeal, 176);
			}
			secret[1] = 1;
		}
		if (lx > 60 || lx < 18 || ly < 10 || ly>21 || (lx == 38 && ly == 16) || (attack == true && sx == 38 && sy == 16))
			break;
	}
	Warp();
}
void Room_13()
{
	system("cls");
	current_location = 13;
	NoWay();
	NewLocation();
	StatusBar();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(24, 3);
	cout << char(222) << char(221);
	Frame();
	Wall();
	AddMultTexture(26, 13, 27, 13, clBlue, clTeal, 176);
	AddMultTexture(26, 18, 27, 18, clBlue, clTeal, 176);
	AddMultTexture(51, 13, 52, 13, clBlue, clTeal, 176);
	AddMultTexture(51, 18, 52, 18, clBlue, clTeal, 176);
	AddDoor('l', 'o');
	AddDoor('r', 'o');
	if (enemys_killed[current_location] == 0)
	{
		AddEnemies(3, hp_pig, 2, clMagneta, 0);
	}
	SetConsoleColorTextBackground(link_col);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		EnemyActionCheck(3);
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_14()
{
	system("cls");
	current_location = 14;
	NoWay();
	NewLocation();
	StatusBar();
	Frame();
	Wall();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(26, 3);
	cout << char(222) << char(221);
	AddMultTexture(54, 13, 55, 13, 9, 3, 176);
	AddMultTexture(23, 13, 24, 13, 9, 3, 176);
	AddMultTexture(54, 16, 55, 16, 9, 3, 176);
	AddMultTexture(23, 16, 24, 16, 9, 3, 176);
	AddMultTexture(54, 19, 55, 19, 9, 3, 176);
	AddMultTexture(23, 19, 24, 19, 9, 3, 176);
	AddMultTexture(47, 13, 48, 13, 9, 3, 176);
	AddMultTexture(47, 16, 48, 16, 9, 3, 176);
	AddMultTexture(47, 19, 48, 19, 9, 3, 176);
	AddMultTexture(30, 13, 31, 13, 9, 3, 176);
	AddMultTexture(30, 16, 31, 16, 9, 3, 176);
	AddMultTexture(30, 19, 31, 19, 9, 3, 176);
	AddMultTexture(37, 13, 41, 13, 9, 3, 176);
	AddMultTexture(37, 16, 41, 16, 9, 3, 176);
	AddMultTexture(37, 19, 41, 19, 9, 3, 176);
	AddDoor('l', 'o');
	if (locked_doors[current_location][1] == 1)
		AddDoor('u', 'l');
	else
		AddDoor('u', 'o');
	if (key_got[current_location] == 0)
	{
		items[20][48] = 4;
		SetConsoleCursorPosition(48, 20);
		SetConsoleColorTextBackground(clOlive);
		cout << char(198);
	}
	if (lil_bonus == false)
	{
		items[20][30] = 1;
		SetConsoleCursorPosition(30, 20);
		SetConsoleColorTextBackground(clRed);
		cout << char(3);
	}
	SetConsoleColorTextBackground(link_col, 0);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		if ((lx == 30 && ly == 20) || (attack == true && sx == 30 && sy == 20))
			lil_bonus = true;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_15()
{
	system("cls");
	current_location = 15;
	NoWay();
	NewLocation();
	StatusBar();
	Frame();
	Wall();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(26, 2);
	cout << char(222) << char(221);
	AddMultTexture(42, 21, 59, 21, clBlue, clTeal, 176);
	AddMultTexture(47, 20, 59, 20, clBlue, clTeal, 176);
	AddMultTexture(52, 19, 59, 19, clBlue, clTeal, 176);
	AddMultTexture(57, 18, 59, 18, clBlue, clTeal, 176);
	AddMultTexture(42, 10, 59, 10, clBlue, clTeal, 176);
	AddMultTexture(47, 11, 59, 11, clBlue, clTeal, 176);
	AddMultTexture(52, 12, 59, 12, clBlue, clTeal, 176);
	AddMultTexture(57, 13, 59, 13, clBlue, clTeal, 176);
	AddTexture(52, 17, clGreen, 0, 'I');
	AddTexture(52, 14, clWhite, clGreen, ' ');
	AddMultTexture(52, 16, 57, 16, 0, clGreen, ' ');
	AddTexture(58, 16, clGreen, 0, '\\');
	AddTexture(57, 17, clGreen, 0, 'I');
	AddMultTexture(52, 15, 53, 15, 0, clGreen, ' ');
	if (YOU_DEFEATED == true)
	{
		AddTexture(52, 14, clRed, clRed, 177);
		AddTexture(52, 15, clRed, clGreen, 177);
		AddTexture(52, 16, clRed, clGreen, 176);
		AddTexture(52, 17, clRed, 0, 'I');
		AddDoor('r', 'o');
		if (dragon_heart == false)
		{
			SetConsoleColorTextBackground(clRed, clWhite);
			SetConsoleCursorPosition(39, 16);
			cout << char(3);
		}
	}
	AddDoor('d', 'o');
	if (YOU_DEFEATED == false)
	{
		for (int i = 1; i < 4; i++)
		{
			ex[i] = 51; ey[i] = 12 + i;
			elife[i] = 10;
			enemy_walk_chance[i] = 0;
			enemy_sprite[i] = 15;
			enemy_sprite_col[i] = 1;
			enemy_sprite_bg[i] = 0;
			enemy_on_board[i] = true;
		}
		ex[0] = 52; ey[0] = 13;
		elife[0] = hp_boss;
		enemy_sprite[0] = 2;
		enemy_sprite_col[0] = clGreen;
		enemy_sprite_bg[0] = 0;
		enemy_on_board[0] = true;

		SetConsoleColorTextBackground(clGreen, 0);
		SetConsoleCursorPosition(52, 13);
		cout << char(2);
		AddDoor('r', 'c');
	}
	SetConsoleColorTextBackground(link_col, 0);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		for (int i = 0; i < 4; i++)
		{
			LinkLifeCheck(ex[i], ey[i], esx[i], esy[i], enemy_on_board[i], enemy_sprite[i], enemy_sprite_col[i], enemy_sprite_bg[i]);
		}
		for (int i = 0; i < 4; i++)
		{
			EnemyWalk(ex[i], ey[i], esx[i], esy[i], elife[i], enemy_on_board[i], enemy_walk_chance[i], enemy_sprite[i], enemy_sprite_col[i], enemy_sprite_bg[i]);
			if (ex[i] == 19)
			{
				SetConsoleColorTextBackground(clGreen, 0);
				SetConsoleCursorPosition(ex[i], ey[i]);
				cout << " ";
				ex[i] = 51; ey[i] = 12 + i;
				elife[i] = 10;
				enemy_walk_chance[i] = 0;
				enemy_sprite[i] = 15;
				enemy_sprite_col[i] = 1;
				enemy_sprite_bg[i] = 0;
				enemy_on_board[i] = true;
			}
		}
		if (enemy_on_board[0] == false && YOU_DEFEATED == false)
		{
			for (int i = 1; i < 4; i++)
			{
				SetConsoleColorTextBackground(clGreen, 0);
				SetConsoleCursorPosition(ex[i], ey[i]);
				cout << " ";
				enemy_on_board[i] = false;
			}
			AddTexture(52, 14, clRed, clGreen, 176);
			Sleep(400);
			AddTexture(52, 14, clRed, clGreen, 177);
			AddTexture(52, 15, clRed, clGreen, 176);
			Sleep(400);
			AddTexture(52, 14, clRed, clRed, 177);
			AddTexture(52, 15, clRed, clGreen, 177);
			AddTexture(52, 16, clRed, clGreen, 176);
			Sleep(400);
			AddTexture(52, 17, clRed, 0, 'I');
			Sleep(400);
			SetConsoleColorTextBackground(clRed, 0);
			SetConsoleCursorPosition(51, 17);
			cout << "_";
			AddDoor('r', 'o');
			SetConsoleColorTextBackground(clRed, clWhite);
			SetConsoleCursorPosition(39, 16);
			cout << char(3);
			YOU_DEFEATED = true;
		}
		if (YOU_DEFEATED == true && dragon_heart == false && ((lx == 39 && ly == 16) || (attack == true && sx == 39 && sy == 16)))
		{
			if (llife_buf < 14)
				llife_buf++;
			llife = llife_buf;
			StatusBar();
			SetConsoleColorTextBackground(link_col, clBlack);
			if (gotmap == true)
				SetConsoleColorTextBackground(link_col, clBlue);
			SetConsoleCursorPosition(26, 2);
			cout << char(222) << char(221);
			dragon_heart = true;
		}
		Sleep(1);
		if (YOU_DIED == true)
			return;
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	Warp();
}
void Room_16()
{
	system("cls");
	current_location = 16;
	NoWay();
	NewLocation();
	StatusBar();
	Frame();
	Wall();
	SetConsoleColorTextBackground(link_col, clBlack);
	if (gotmap == true)
		SetConsoleColorTextBackground(link_col, clBlue);
	SetConsoleCursorPosition(28, 2);
	cout << char(222) << char(221);
	AddMultTexture(23, 13, 55, 13, 9, 3, 176);
	AddMultTexture(23, 13, 24, 19, 9, 3, 176);
	AddMultTexture(54, 13, 55, 19, 9, 3, 176);
	AddMultTexture(23, 19, 36, 19, 9, 3, 176);
	AddMultTexture(42, 19, 55, 19, 9, 3, 176);
	AddMultTexture(32, 14, 35, 15, 1, 9, 177);
	AddMultTexture(43, 14, 46, 15, 1, 9, 177);
	AddMultTexture(28, 16, 31, 17, 1, 9, 177);
	AddMultTexture(47, 16, 50, 17, 1, 9, 177);
	AddDoor('l', 'o');
	SetConsoleColorTextBackground(clYellow, 0);
	SetConsoleCursorPosition(39, 15);
	cout << char(30);
	SetConsoleCursorPosition(38, 16);
	cout << char(30) << " " << char(30);
	SetConsoleColorTextBackground(link_col, 0);
	SetConsoleCursorPosition(lx, ly);
	cout << link;
	while (1)
	{
		LinkCtrl();
		if (((ly == 16 && lx >= 38 && lx <= 40) || (attack == true && sy == 16 && sx >= 38 && sx <= 40)) || ((ly == 15 && lx == 39) || (attack == true && sy == 15 && sx == 39)))
		{
			SetConsoleColorTextBackground(link_col, 0);
			SetConsoleCursorPosition(lx, ly);
			cout << " ";
			lx = 39; ly = 17;
			SetConsoleColorTextBackground(link_col, 0);
			SetConsoleCursorPosition(39, 17);
			cout << char(31);
			for (int del_l = 15, del_r = 63; del_l <= del_r;)
			{
				for (int i = 0; i < 25; i++)
				{
					SetConsoleCursorPosition(del_l, i);
					cout << " ";
					SetConsoleCursorPosition(del_r, i);
					cout << " ";
				}
				del_l++; del_r--;
				SetConsoleColorTextBackground(clOlive, 0);
				SetConsoleCursorPosition(39, 15);
				cout << char(30);
				SetConsoleCursorPosition(38, 16);
				cout << char(30) << " " << char(30);
				SetConsoleColorTextBackground(link_col, 0);
				SetConsoleCursorPosition(39, 17);
				cout << char(31);
				Sleep(100);
				for (int i = 0; i < 25; i++)
				{
					SetConsoleCursorPosition(del_l, i);
					cout << " ";
					SetConsoleCursorPosition(del_r, i);
					cout << " ";
				}
				del_l++; del_r--;
				SetConsoleColorTextBackground(clYellow, 0);
				SetConsoleCursorPosition(39, 15);
				cout << char(30);
				SetConsoleCursorPosition(38, 16);
				cout << char(30) << " " << char(30);
				SetConsoleColorTextBackground(link_col, 0);
				SetConsoleCursorPosition(39, 17);
				cout << char(31);
				Sleep(100);
			}
			triforce = true;
			complete++;
			llife_tmp = llife_buf;
			keys_tmp = keys;
			rupees_tmp = rupees;
			hp_batngoo++;
			hp_skeleton++;
			hp_pig++;
			hp_boss += 5;
			if (move_speed > 30)
				move_speed--;
		}
		if (triforce == true)
		{
			break;
		}
		if (lx > 60 || lx < 18 || ly < 10 || ly>21)
			break;
	}
	if (triforce == false)
		Warp();
	SetConsoleColorTextBackground(clTeal, 0);
	SetConsoleCursorPosition(18, 4);
	cout << char(214);
	for (int i = 0; i < 41; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	for (int i = 5; i < 10; i++)
	{
		SetConsoleCursorPosition(18, i);
		cout << char(186);
		SetConsoleCursorPosition(60, i);
		cout << char(179);
	}
	SetConsoleCursorPosition(18, 10);
	cout << char(200);
	for (int i = 0; i < 41; i++)
	{
		cout << char(205);
	}
	cout << char(190);
	SetConsoleColorTextBackground(clWhite, 0);
	SetConsoleCursorPosition(21, 6);
	cout << "T H A N K S   L I N K ,   Y O U ' R E";
	SetConsoleCursorPosition(21, 8);
	cout << "T H E   H E R O   O F   H Y R U L E .";

	if (complete == 1)
	{
		SetConsoleCursorPosition(27, 20);
		SetConsoleColorTextBackground(clWhite, 0);
		cout << "NEW GAME ";
		SetConsoleColorTextBackground(link_col, 0);
		cout << "+ ";
		SetConsoleColorTextBackground(clRed, 0);
		cout << "IS NOW AVAILABLE!";
		game_complete = true;
		SetConsoleCursorPosition(13, 21);
		cout << "COLLECT ALL 14 HEART CONTAINERS TO OPEN A SPECIAL BONUS!";
		SetConsoleCursorPosition(27, 22);
		cout << "YOUR GAME PROGRESS IS SAVED.";
	}
	if (complete > 1 && special_bonus == false && llife_buf < 14)
	{
		SetConsoleCursorPosition(26, 20);
		SetConsoleColorTextBackground(clWhite, 0);
		cout << "YOU COMPLETED THE GAME " << complete << " TIMES.";
		SetConsoleColorTextBackground(clRed, 0);
		SetConsoleCursorPosition(13, 21);
		cout << "COLLECT ALL 14 HEART CONTAINERS TO OPEN A SPECIAL BONUS!";
		SetConsoleCursorPosition(27, 22);
		cout << "YOUR GAME PROGRESS IS SAVED.";
	}
	if (complete > 1 && special_bonus == true)
	{
		SetConsoleCursorPosition(26, 20);
		SetConsoleColorTextBackground(clWhite, 0);
		cout << "YOU COMPLETED THE GAME " << complete << " TIMES.";
		SetConsoleColorTextBackground(clRed, 0);
		SetConsoleCursorPosition(27, 21);
		cout << "YOUR GAME PROGRESS IS SAVED.";
	}
	if (llife_buf == 14 && special_bonus == false)
	{
		link_col = 12;
		sword_col = 12;
		SetConsoleCursorPosition(26, 19);
		SetConsoleColorTextBackground(clWhite, 0);
		cout << "YOU COMPLETED THE GAME " << complete << " TIMES.";
		SetConsoleColorTextBackground(clRed, 0);
		SetConsoleCursorPosition(19, 20);
		cout << "YOU HAVE COLLECTED ALL 14 HEART CONTAINERS!";
		SetConsoleCursorPosition(15, 21);
		cout << "SPECIAL BONUS IS WAITING FOR YOU IN THE ";
		SetConsoleColorTextBackground(clWhite, 0);
		cout << "NEW GAME ";
		SetConsoleColorTextBackground(link_col, 0);
		cout << "+";
		SetConsoleColorTextBackground(clRed, 0);
		SetConsoleCursorPosition(27, 22);
		cout << "YOUR GAME PROGRESS IS SAVED.";
		special_bonus = true;
	}
	f = fopen("zelda.save", "w");
	if (f)
	{
		fwrite(&complete, sizeof(int), 1, f);
		fwrite(&llife_tmp, sizeof(int), 1, f);
		fwrite(&rupees_tmp, sizeof(int), 1, f);
		fwrite(&keys_tmp, sizeof(int), 1, f);
		fwrite(&hp_batngoo, sizeof(int), 1, f);
		fwrite(&hp_skeleton, sizeof(int), 1, f);
		fwrite(&hp_pig, sizeof(int), 1, f);
		fwrite(&special_bonus, sizeof(bool), 1, f);
		fwrite(&link_col, sizeof(int), 1, f);
		fwrite(&sword_col, sizeof(int), 1, f);
		fwrite(&hp_boss, sizeof(int), 1, f);
		fclose(f);
	}
	int enterpls = 0;
	do
	{
		enterpls = _getch();
	} while (enterpls != 13);
}
void Warp()
{
	if (current_location == 0 && lx == 39 && ly == 20)
	{
		lx = 39; ly = 20;
		Room_1();
	}
	if (current_location == 1)
	{
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_2();
		}
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_3();
		}
		if (ly < 10)
		{
			lx = 39; ly = 21;
			link = char(31);
			Room_4();
		}
		if (((lx == 19 && ly == 21) || (attack == true && sx == 19 && sy == 21)) && basement == true)
		{
			lx = 37; ly = 16;
			Room_12();
		}
	}
	if (current_location == 2)
	{
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_1();
		}
	}
	if (current_location == 3)
	{
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_1();
		}
	}
	if (current_location == 4)
	{
		if (ly > 21)
		{
			lx = 39; ly = 10;
			link = char(30);
			Room_1();
		}
		if (ly < 10)
		{
			lx = 39; ly = 21;
			link = char(31);
			Room_5();
		}
	}
	if (current_location == 5)
	{
		if (ly > 21)
		{
			lx = 39; ly = 10;
			link = char(30);
			Room_4();
		}
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_7();
		}
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_6();
		}
	}
	if (current_location == 6)
	{
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_5();
		}
	}
	if (current_location == 7)
	{
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_5();
		}
		if (ly < 10)
		{
			lx = 39; ly = 21;
			link = char(31);
			Room_8();
		}
	}
	if (current_location == 8)
	{
		if (ly > 21)
		{
			lx = 39; ly = 10;
			link = char(30);
			Room_7();
		}
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			STORE();
		}
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_9();
		}
	}
	if (current_location == 99)
	{
		if (lx > 60)
		{
			lx = 19; ly = 16;
			link = char(17);
			Room_8();
		}
	}
	if (current_location == 9)
	{
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_8();
		}
		if (ly < 10)
		{
			lx = 39; ly = 21;
			link = char(31);
			Room_10();
		}
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_13();
		}
	}
	if (current_location == 10)
	{
		if (ly > 21)
		{
			lx = 39; ly = 10;
			link = char(30);
			Room_9();
		}
		if (ly < 10)
		{
			lx = 39; ly = 21;
			link = char(31);
			Room_11();
		}
	}
	if (current_location == 11)
	{
		if (ly > 21)
		{
			lx = 39; ly = 10;
			link = char(30);
			Room_10();
		}
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_12();
		}
	}
	if (current_location == 12)
	{
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_11();
		}
		if ((lx == 38 && ly == 16) || (attack == true && sx == 38 && sy == 16))
		{
			lx = 20; ly = 21;
			basement = true;
			Room_1();
		}
	}
	if (current_location == 13)
	{
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_9();
		}
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_14();
		}
	}
	if (current_location == 14)
	{
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_13();
		}
		if (ly < 10)
		{
			lx = 39; ly = 21;
			link = char(31);
			Room_15();
		}
	}
	if (current_location == 15)
	{
		if (ly > 21)
		{
			lx = 39; ly = 10;
			link = char(30);
			Room_14();
		}
		if (lx > 60)
		{
			lx = 18; ly = 16;
			link = char(17);
			Room_16();
		}
	}
	if (current_location == 16)
	{
		if (lx < 18)
		{
			lx = 60; ly = 16;
			link = char(16);
			Room_15();
		}
	}
}
void main()
{
	f = fopen("zelda.save", "r");
	if (f)
	{
		fread(&complete, sizeof(int), 1, f);
		fread(&llife_tmp, sizeof(int), 1, f);
		fread(&rupees_tmp, sizeof(int), 1, f);
		fread(&keys_tmp, sizeof(int), 1, f);
		fread(&hp_batngoo, sizeof(int), 1, f);
		fread(&hp_skeleton, sizeof(int), 1, f);
		fread(&hp_pig, sizeof(int), 1, f);
		fread(&special_bonus, sizeof(bool), 1, f);
		fread(&link_col, sizeof(int), 1, f);
		fread(&sword_col, sizeof(int), 1, f);
		fread(&hp_boss, sizeof(int), 1, f);
		fclose(f);
	}
	while (1)
	{
		system("cls");
		x = 30;
		srand((unsigned)time(NULL));
		SetConsoleWinSizePosition(80, 25);
		SetConsoleColorTextBackground(clWhite, clBlack);
		cout << "     + ";
		for (int i = 0; i < 66; i++)
			cout << char(196);
		cout << " +\n\n";
		SetConsoleColorTextBackground(clRed);
		cout << "                      T  H  E     L  E  G  E  N  D     O  F\n\n";
		cout << "                ##############\n";
		cout << "               ############## ######## #####    ######   ######\n";
		cout << "              ##        ####   ##   ##  ##       ##  ##   #####\n";
		cout << "                       ####    ## #  #  ##       ##   ##  ## ###\n";
		cout << "                     ####      ####     ##       ##   ##  ######\n";
		cout << "                    ####       ## #  #  ##    #  ##   ## ###  ###\n";
		cout << "                  ####         ##   ##  ##   ##  ##  ##  ###  ###\n";
		cout << "                 ####      ## ######## ######## ######  ####  ####\n";
		cout << "               ##############\n";
		cout << "              ##############   ";
		SetConsoleColorTextBackground(clSilver);
		cout << "A S C I I    A D V E N T U R E\n\n";
		SetConsoleColorTextBackground(clWhite);
		cout << "     + ";
		for (int i = 0; i < 66; i++)
			cout << char(196);
		cout << " +\n\n\n";
		SetConsoleColorTextBackground(clWhite);
		cout << "\t\t\t\t    NEW GAME";
		if (complete >= 1)
		{
			SetConsoleColorTextBackground(link_col);
			cout << " +";
		}
		SetConsoleColorTextBackground(clWhite);
		cout << "\n\n\t\t\t\t    HOW TO PLAY\n\n\t\t\t\t    EXIT\n\n";
		SetConsoleCursorPosition(x, y);
		SetConsoleColorTextBackground(clOlive);
		cout << char(196) << "|";
		SetConsoleColorTextBackground(clWhite);
		cout << "==>";
		while (1)
		{
			int k = _getch(), xx = x, yy = y;
			SetConsoleCursorPosition(xx, yy);
			cout << "     ";
			if (k == 13)
				break;
			if (k == 80 && y != 22)
				y += 2;
			if (k == 72 && y != 18)
				y -= 2;
			SetConsoleColorTextBackground(clOlive);
			SetConsoleCursorPosition(x, y);
			cout << char(196) << "|";
			SetConsoleColorTextBackground(clWhite);
			cout << "==>";
		}
		if (y == 18)
		{
			if (complete == 0)
				RedText("NEW GAME");
			else
				RedText("NEW GAME +");
			NewGame();
			Adventure_Begin();
			FirstStepWall();
		}
		if (y == 20)
		{
			RedText("HOW TO PLAY");
			HowToPlay();
		}
		if (y == 22)
		{
			RedText("EXIT");
			SetConsoleCursorPosition(20, 25);
			break;
		}
	}
}