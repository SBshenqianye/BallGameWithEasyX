
#ifndef _HEADERANDDEFS_H
#define _HEADERANDDEFS_H
/*开始*/

/*包含了标准/非标准库函数、easyX库函数等*/

/*Headers*/
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#include <windows.h>
#include <string.h>

#include <iostream>
using namespace std;

/*Defines*/
#define OVERALL_RUNNING_SPEED 4			/*整体运行速度	-	默认为3, 3-6*/
#define BRICK_COL_NUM 10				/*砖块列数		-	默认为10*/
#define BRICK_DROP_TIME_NUM 30			/*砖块掉落次数	-	默认为30*/
#define BRICK_DROP_SPEED 3				/*砖块下落速度	-	默认为1, 1-3*/
#define BALL_INITIAL_RADIUS 8			/*小球初始半径	-	默认为8*/
#define BALL_INITIAL_SPEED 1			/*小球初始速度	-	默认为1*/
#define BORAD_INITIAL_LENGTH 120		/*木板初始长度	-	默认为120*/

/*Global Defines*/
const int WINDOW_HEIGHT = 600;				/*默认为600*/
const int WINDOW_WIDTH = 800;				/*默认为800*/
FILE *fp_debug;
char pathname_debug[50] = ".\\bin\\debug\\";
int count = 0;
float score = 0;
int numKnock = 0;
int times = 0;
int rank = 1;
float DegreeofDifficulty = OVERALL_RUNNING_SPEED*1/2 * BRICK_DROP_SPEED;
char name[21] = "\0";

/*Fuction in Objects*/
extern void saveToDebugFile(char *sentence)
{
	fprintf(fp_debug, sentence);
	fclose(fp_debug);
	if((fp_debug = fopen(pathname_debug, "a+")) == NULL)
	{
		printf("打开debug文件失败！\n");
		exit(1);
	}
}

/*Struct Defines*/
typedef struct MyTime
{
	char year[5], month[3], day[3];
	char hour[3], minute[3], second[3];
} MyTime;

typedef struct DATA
{
	char name[21];
	int gamingTime;
	int rank;
	float score;
	int brick_summonPos, brick_colNum, brick_dropTimeNum, brick_dropSpeed;
	int ball_initialRadius, ball_initialSpeed;
	int borad_initialLength, overall_runningSpeed;
} DATA;

typedef struct GAMEDATA
{
	DATA Data;
	GAMEDATA *next;
} GAMEDATA;

typedef enum COLOR {yellow = 1, red, blue} COLOR;
/*Class Defines*/
class Brick
{
public:
	int num;
	int Pos_x, Pos_y;
	int totalNumOfCol;
	int Height, Width;
	bool exist;
	bool stopGame;
	COLOR type;
	Brick *next;
	Brick(int getPos_x)
	{
		int temp;
		srand(time(0));
		temp = rand()%10;
	//	cout << "砖块生成码为：" << temp << endl;
		switch(temp)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			type = yellow;
			break;
		case 8:
			type = red;
			break;
		case 9:
			type = blue;
			break;
		default:
			type = yellow;
			break;
		}
		exist = true;					/*默认为true*/
		stopGame = false;				/*默认为false*/
		Pos_x = getPos_x;
		Pos_y = 0;						/*默认为0*/
		totalNumOfCol = BRICK_COL_NUM;
		Height = WINDOW_HEIGHT / BRICK_DROP_TIME_NUM;
		Width = WINDOW_WIDTH / totalNumOfCol;
		drawBrick();
	}
	~Brick()
	{
		char num_t[10];
		char sentence[40] = "执行Brick的析构函数(brick ";
//		cout << "执行Brick的析构函数(brick " << num << ")\n" << endl;
		itoa(num, num_t, 10);
		saveToDebugFile(strcat(strcat(sentence, num_t), ")\n"));
	}
	void drawBrick()					/*显示砖块位置完全取决于 pos_x和 pos_y*/
	{
		if(exist == true)
		{
			if( type == blue)
			{
				setfillcolor(BLUE);
				setlinecolor(BLACK);
				fillrectangle(Pos_x*Width, Pos_y*Height, (Pos_x+1)*Width, (Pos_y+1)*Height);
			}
			else if(type == red)
			{
				setfillcolor(RED);
				setlinecolor(BLACK);
				fillrectangle(Pos_x*Width, Pos_y*Height, (Pos_x+1)*Width, (Pos_y+1)*Height);
			}
			else
			{
				setfillcolor(YELLOW);
				setlinecolor(BLACK);
				fillrectangle(Pos_x*Width, Pos_y*Height, (Pos_x+1)*Width, (Pos_y+1)*Height);
			}
		}
		else
		{
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillrectangle(Pos_x*Width, Pos_y*Height, (Pos_x+1)*Width, (Pos_y+1)*Height);
		}
	}
	bool Move()
	{
		setfillcolor(BLACK);		/*涂黑*/
		fillrectangle(Pos_x*Width, Pos_y*Height, (Pos_x+1)*Width, (Pos_y+1)*Height);

		Pos_y += 1;
		if(next == NULL)
		{
	//		cout << "system_Brick:\n\t砖块\"" << num << "\"下移一格!\n" << endl;
		}
		if(Pos_y >= WINDOW_HEIGHT / Height) stopGame = true;
		drawBrick();
		return stopGame;
	}
};

class Borad
{
public:
	int x, y;
	int Width, Height;
	bool Lauch;
	Borad()
	{
		Width = BORAD_INITIAL_LENGTH;
		Height = 15;				/*默认为15*/
		Lauch = false;				/*默认为false*/
		x = WINDOW_WIDTH/2 - Width/2;
		y = WINDOW_HEIGHT - Height;
		setfillcolor(BLUE);
		solidrectangle(x, y, x + Width, y + Height);
		drawBorad();
	}
	void drawBorad()
	{
		setfillcolor(BLUE);
		solidrectangle(x, y, x + Width, y + Height);
	}
	void antidrawBorad()
	{
		setfillcolor(BLACK);
		solidrectangle(x, y, x + Width, y + Height);
	}
	int Move()
	{
		int pressedKey;
		pressedKey = _getch();

		antidrawBorad();

		switch(pressedKey)
		{
		case 75:
		case 'a':
		case 'A':
			x -= Width/3;
	//		cout << "system_Borad:\n\t木板左移一格!\n" << endl;
			break;
		case 77:
		case 'd':
		case 'D':
			x += Width/3;
	//		cout << "system_Borad:\n\t木板右移一格!\n" << endl;
			break;
		case 32:
			if(Lauch == false)
			{
				Lauch = true;
	//			cout << "system_Borad:\n\t小球发射！\n" << endl;
				saveToDebugFile("system_Borad:\n\t小球发射！\n");
				break;
			}
			else break;
		}

		if(x <= 0) x = 0;
		if(x + Width >= WINDOW_WIDTH) x = WINDOW_WIDTH - Width;

		drawBorad();

		return pressedKey;
	}
};
class Ball
{
public:
	bool stopGame;
	bool rebound;
	int ball_x, ball_y, Radius;
	int speed;
	int ball_vx, ball_vy;
	/*速度方向*/
	Ball(Borad &borad)
	{
		stopGame = false;				/*默认为false*/
		rebound = true;					/*默认为true*/
		ball_vx = 1;					/*默认为1*/
		ball_vy = -1;	/*速度方向*/	/*默认为-1*/
		Radius = BALL_INITIAL_RADIUS;
		speed = BALL_INITIAL_SPEED;
		setfillcolor(RED);
		solidcircle(ball_x, ball_y, Radius);
	}
	void drawBall()
	{
		setfillcolor(RED);
		solidcircle(ball_x, ball_y, Radius);
	}
	void antidrawBall()
	{
		setfillcolor(BLACK);
		solidcircle(ball_x, ball_y, Radius);
	}
	bool Move(Brick *brickHead, Borad &borad)
	{
		int x;
		
		if(count < 10) x = 6-OVERALL_RUNNING_SPEED;
		else if(count < 100) x = 5-OVERALL_RUNNING_SPEED;
		else if(count < 500) x = 4-OVERALL_RUNNING_SPEED;
		else if(count < 1000) x = 3-OVERALL_RUNNING_SPEED;
		if(x < 0) x = 0;
		Sleep(x);
		/*运动前后的绘制*/
		BeginBatchDraw();
		antidrawBall();
		if(borad.Lauch == true)
		{
			ball_x += ball_vx * speed;
			ball_y += ball_vy * speed;
		}
		else if(borad.Lauch == false)
		{
			ball_x = borad.x + borad.Width/2;
			ball_y = WINDOW_HEIGHT - borad.Height - Radius - 1;
		}
		drawBall();
		FlushBatchDraw();
		/*运动前后的绘制*/

		/*球与边界的交互*/
		if(ball_x >= WINDOW_WIDTH - Radius || ball_x <= Radius)
		{
			/*左右边界*/
			ball_vx *= -1;							
//			cout << "system_Ball:\n\t小球碰到左/右边界反弹\n" << endl;
		}
		if(ball_y <= Radius)						
		{
			/*上边界*/
			ball_vy *= -1;
//			cout << "system_Ball:\n\t小球碰到上边界反弹\n" << endl;
		}
		if(ball_y + Radius >= WINDOW_HEIGHT)		
		{
			/*下边界*/
//			ball_vy *= -1;
			stopGame = true;								
//			cout << "system_Ball:\n\t小球碰到下边界退出游戏\n" << endl;
		}
		/*球与边界的交互*/

		/*球与木板的交互*/
		if(borad.Lauch == true)
		{
			if( (ball_y + Radius == borad.y - 1) && ( ball_x + Radius >= borad.x && ball_x - Radius <= borad.x + borad.Width ) )
			{	/*球下切等于板上端*/					/*球右切大于板左端	且	球左切小于板右端*/
				/*木板上边缘*/
				ball_vy *= -1;				
//				cout << "system_Ball:\n\t小球碰到木板上边缘反弹\n" << endl;
//				saveToDebugFile("system_Ball:\n\t小球碰到木板上边缘反弹\n");
			}
			else if( ball_x >= borad.x - Radius - 1 && ball_x <= borad.x && ball_y >= borad.y - Radius - 1)
			{	/*球右切大于板左端	且	球右切小于板左端靠右*/						/*球下切大于板上端*/

				/*木板左边缘*/
				ball_vx *= -1;				
//				cout << "system_Ball:\n\t小球碰到木板左边缘反弹\n" << endl;
//				saveToDebugFile("system_Ball:\n\t小球碰到木板左边缘反弹\n");
			}
			else if( ball_x <= borad.x + borad.Width + Radius + 1 && ball_x >= borad.x + borad.Width && ball_y >= borad.y - Radius - 1)
			{	/*球左切小于板右端	且	球左切大于板右端靠左*/											/*球下切大于板上端*/

				/*木板右边缘*/
				ball_vx *= -1;				
//				cout << "system_Ball:\n\t小球碰到木板右边缘反弹\n" << endl;
//				saveToDebugFile("system_Ball:\n\t小球碰到木板右边缘反弹\n");
			}
		}
		/*球与木板的交互*/

		/*球与砖块的交互*/
		while(brickHead != NULL && borad.Lauch == true)
		{
			if( ball_x >= brickHead->Pos_x * brickHead->Width - Radius 
				&& ball_x <= (brickHead->Pos_x + 1) * brickHead->Width + Radius 
				&& ball_y >= brickHead->Pos_y * brickHead->Height - Radius 
				&& ball_y <= (brickHead->Pos_y + 1) * brickHead->Height + Radius)
				/*这一大串表示球心进入到砖块范围内*/
			{
				if(ball_y < brickHead->Pos_y * brickHead->Height -1)
				{
					/*砖块上边缘*/
					if(rebound == true) ball_vy *= -1;
	//				cout << "system_Ball:\n\t小球碰到砖块\"" << brickHead->num << "\"上边缘反弹" << endl;
				}
				else if(ball_y > (brickHead->Pos_y + 1) * brickHead->Height +1)
				{
					/*砖块下边缘*/
					if(rebound == true) ball_vy *= -1;
	//				cout << "system_Ball:\n\t小球碰到砖块\"" << brickHead->num << "\"下边缘反弹" << endl;	
				}
				else if(ball_x < brickHead->Pos_x * brickHead->Width -1)
				{
					/*砖块左边缘*/
					if(rebound == true) ball_vx *= -1;
	//				cout << "system_Ball:\n\t小球碰到砖块\"" << brickHead->num << "\"左边缘反弹" << endl;	
				}
				else if(ball_x > (brickHead->Pos_x + 1) * brickHead->Width +1)
				{
					/*砖块右边缘*/
					if(rebound == true) ball_vx *= -1;		
	//				cout << "system_Ball:\n\t小球碰到砖块\"" << brickHead->num << "\"右边缘反弹" << endl;		
				}
				else
				{
					/*砖块其他细小部分*/
				}
				if(brickHead->type == blue)
				{
					borad.Width += 60;
				}
				else if(brickHead->type == red)
				{
					ball_y += 8;
					Radius += 8;
				}
				brickHead->exist = false;
				setfillcolor(BLACK);
				setlinecolor(BLACK);
				fillrectangle(brickHead->Pos_x*brickHead->Width, brickHead->Pos_y*brickHead->Height, 
					(brickHead->Pos_x+1)*brickHead->Width, (brickHead->Pos_y+1)*brickHead->Height);
			}
			brickHead = brickHead->next;
		}
		/*球与砖块的交互*/
		return stopGame;
	}//void Move();
};

/*Function Defines*/
extern void Gameing();
extern Brick *createBrick(Brick *head);
extern bool allBrickMove(Brick *head);
extern Brick *removeBrick(Brick *head);

extern void initialization();
extern void debugAndTest();
extern FILE *createDebugFile();

extern GAMEDATA *readFromFile();
extern void freeMemory(GAMEDATA *head);
extern void writeIntoFile(GAMEDATA *head);
extern GAMEDATA *Rankthem(GAMEDATA *head);
extern void inputName();

extern void BlackScreen();
extern void mainMenu();
extern void mainMenuDisplay(int flag);
extern void mainMenuControl(int *flag, int getKey);
extern void rankMenu();
extern void rankMenuDisplay(int flag);
extern void rankMenuControl(int *flag, int getKey, bool *quit);
extern void gameOverDisplay();
/*结尾*/
#endif