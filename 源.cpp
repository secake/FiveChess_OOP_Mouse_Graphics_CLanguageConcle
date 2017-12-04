#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<string>
using namespace std;
class Spot//点基类
{
protected:
	int x, y;
public:
	void setXY(int, int);//设置坐标
	virtual	void showSpot() = 0;//显示点
};
void Spot::setXY(int x1, int y1)
{
	x = x1;
	y = y1;
}
enum play_er
{
	null, play1, play2
};
class Chess :public Spot//棋子类
{
public:
	int state;//当前棋子状态
	void showSpot();//显示棋子
};
void Chess::showSpot()
{
	switch (state)//设置棋子颜色
	{
	case null:
		break;
	case play1:
		setfillcolor(BLACK);
		break;
	case play2:
		setfillcolor(WHITE);
		break;
	default:
		break;
	}
	solidcircle(x * 30 + 15, y * 30 + 15, 13);
}
class Board
{
public:
	Chess chess[20][20];
	Board *next;
	Board() {
		setChess();
	}
	void setBoard();//画棋盘
	void setChess();//设置棋子坐标
	void showBoard(int, int);//显示棋子
};
void Board::setBoard()
{
	setfillcolor(RGB(125, 125, 255));
	fillrectangle(0, 0, 800, 600);
	setfillcolor(RGB(255, 255, 125));
	fillrectangle(0, 0, 600, 600);
	setlinecolor(BLACK);
	for (int i = 15;i < 600;i += 30)
	{
		line(i, 15, i, 585);
		line(15, i, 585, i);
	}
}
void Board::setChess()
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			chess[i][j].setXY(i, j);
			chess[i][j].state = null;
		}
	}
}
void Board::showBoard(int x1, int y1)
{
	chess[x1][y1].showSpot();
}
MOUSEMSG m;
class Player
{
public:
	int num;
	int foot;
	MOUSEMSG Get();
};
MOUSEMSG Player::Get()
{
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			break;
		}
		if (m.uMsg == WM_RBUTTONDOWN)
		{
			break;
		}
	}
	return m;
}
class Game
{
protected:
	int x, y;
	MOUSEMSG m1;
public:
	Game() {
		playerone.num = play1;
		playertwo.num = play2;
	}
	Player playerone, playertwo;
	Board *boardH, *p, *q, *r;
	int winer;
	void starGame();
	int Game_();//GAME
	bool exam(Board *a);//检查
};
void Game::starGame()
{
	setbkmode(TRANSPARENT);//设置字符背景透明
	settextcolor(BLACK);
	while (true)
	{
		Game_();
	}
}
bool Game::exam(Board *a)
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			if (a->chess[i][j].state != null)
			{
				if (i != 0 && i != 1 && i != 18 && i != 19)
				{
					if (a->chess[i][j].state == a->chess[i - 1][j].state &&a->chess[i][j].state == a->chess[i - 2][j].state &&a->chess[i][j].state == a->chess[i + 1][j].state &&a->chess[i][j].state == a->chess[i + 2][j].state)
					{
						winer = a->chess[i][j].state;
						return true;
					}
				}
				if (j != 0 && j != 1 && j != 18 && j != 19)
				{
					if (a->chess[i][j].state == a->chess[i][j - 1].state &&a->chess[i][j].state == a->chess[i][j - 2].state &&a->chess[i][j].state == a->chess[i][j + 1].state &&a->chess[i][j].state == a->chess[i][j + 2].state)
					{
						winer = a->chess[i][j].state;
						return true;
					}
				}
				if (j != 0 && j != 1 && j != 18 && j != 19 && i != 0 && i != 1 && i != 18 && i != 19)
				{
					if (
						(a->chess[i][j].state == a->chess[i - 1][j - 1].state&&a->chess[i][j].state == a->chess[i - 2][j - 2].state &&a->chess[i][j].state == a->chess[i + 1][j + 1].state &&a->chess[i][j].state == a->chess[i + 2][j + 2].state) ||
						(a->chess[i][j].state == a->chess[i + 1][j - 1].state &&a->chess[i][j].state == a->chess[i + 2][j - 2].state &&a->chess[i][j].state == a->chess[i - 1][j + 1].state &&a->chess[i][j].state == a->chess[i - 2][j + 2].state)
						)
					{
						winer = a->chess[i][j].state;
						return true;
					}
				}
			}
		}
	}
	return false;
}
int Game::Game_()
{
	playerone.foot = 0;
	playertwo.foot = 0;
	playerone.num = play1;
	playertwo.num = play2;
	boardH = p = q = r = new Board;
	p->setBoard();
	outtextxy(660, 90, L"五子棋");
	boardH->next = p->next = q->next = NULL;
	Player player;
	player.num = playerone.num;
	while (true)
	{
		q = p;
		p = new Board;
	c:	*p = *q;
		q->next = p;
		p->next = NULL;
		if (player.num == playerone.num)
		{
		a:		m1 = playerone.Get();
			x = m1.x / 30;
			y = m1.y / 30;
			if (m1.uMsg == WM_RBUTTONDOWN)
			{
				goto c;
			}
			if (p->chess[x][y].state != null)
				goto a;
			playerone.foot++;
			p->chess[x][y].state = playerone.num;
			p->showBoard(x, y);
			player.num = playertwo.num;
		}
		else if (player.num == playertwo.num)
		{
		b:		m1 = playertwo.Get();
			x = m1.x / 30;
			y = m1.y / 30;
			if (m1.uMsg == WM_RBUTTONDOWN)
			{
				goto c;
			}
			if (p->chess[x][y].state != null)
				goto b;
			playertwo.foot++;
			p->chess[x][y].state = playertwo.num;
			p->showBoard(x, y);
			player.num = playerone.num;
		}

		else {}
		if (exam(p) == true)
		{
			if (winer == playerone.num)
			{
				outtextxy(100, 100, L"BLACK IS WINER");
			}
			else
			{
				outtextxy(100, 100, L"WHITE IS WINER");
			}
			Sleep(3000);
			return 0;
		}

	}
	return 1;
}
int main()
{
	initgraph(800, 600);
	Game one;
	one.starGame();
	system("pause");
	return 0;
}