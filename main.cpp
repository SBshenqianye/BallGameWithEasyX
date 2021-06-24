
#include "HeadersForGame.h"
#define OPTIONBAR_WIDTH WINDOW_WIDTH*3/20
#define OPTIONBAR_HEIGHT WINDOW_HEIGHT/15
#define OPTIONBAR_GAP WINDOW_HEIGHT/10
#define TEXT_HEIGHT WINDOW_HEIGHT/20
#define TEXT_GAP WINDOW_HEIGHT/40

FILE *fp_data;
GAMEDATA *HeadofData = NULL;

int main()
{
	int system_time = 0;
	/*准备阶段*/
	initialization();
	debugAndTest();
	fp_debug = createDebugFile();
	/*准备阶段*/

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE);
	mainMenu();


	_getch();    /*暂时还没体现出用处*/
	fclose(fp_debug);
	return 0;
}

void BlackScreen()
{
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void mainMenuDisplay(int flag)
{
	BeginBatchDraw();
	LOGFONT titleFont = {0}, optionFont = {0}, tipsFont = {0};
	titleFont.lfHeight = 120;
	titleFont.lfWeight = 1000;
	titleFont.lfUnderline = true;
	optionFont.lfHeight = OPTIONBAR_HEIGHT;
	optionFont.lfWeight = 1000;
	tipsFont.lfHeight = OPTIONBAR_HEIGHT/2;
	tipsFont.lfWeight = 1000;

	BlackScreen();

	settextstyle(&titleFont);	/*绘制标题*/
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - 6 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), _T("弹力球"));

	settextstyle(&optionFont);		/*绘制选项*/
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 4 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		_T("开始游戏"));
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 3 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		_T("排行榜"));
	optionFont.lfStrikeOut = true;
	settextstyle(&optionFont);
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 2 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		_T("设置"));
	optionFont.lfStrikeOut = false;
	settextstyle(&optionFont);
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - OPTIONBAR_GAP, 
		_T("退出"));

	settextstyle(&tipsFont);	/*绘制提示*/
	settextcolor(BLUE);
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 40, 
		_T("tips: "));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 20, 
		_T("按W/S以使光标移动"));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT, 
		_T("按回车/空格以确定"));

	setlinecolor(RED);
	setfillcolor(RED);
	switch(flag)		/*绘制选项指针*/
	{
	case 3:
		fillrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH*2/5, 
			WINDOW_HEIGHT - OPTIONBAR_HEIGHT - OPTIONBAR_GAP + OPTIONBAR_WIDTH/15, 
			WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH/5, 
			WINDOW_HEIGHT - OPTIONBAR_HEIGHT - OPTIONBAR_GAP + OPTIONBAR_WIDTH/15 + OPTIONBAR_WIDTH/5);
		break;
	case 4:
		solidrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH*2/5, 
			WINDOW_HEIGHT - 2 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP) + OPTIONBAR_WIDTH/15, 
			WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH/5, 
			WINDOW_HEIGHT - 2 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP) + OPTIONBAR_WIDTH/15 + OPTIONBAR_WIDTH/5);
		break;
	case 2:
		solidrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH*2/5, 
			WINDOW_HEIGHT - 3 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP) + OPTIONBAR_WIDTH/15, 
			WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH/5, 
			WINDOW_HEIGHT - 3 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP) + OPTIONBAR_WIDTH/15 + OPTIONBAR_WIDTH/5);
		break;
	case 1:
		solidrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH*2/5, 
			WINDOW_HEIGHT - 4 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP) + OPTIONBAR_WIDTH/15, 
			WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2 - OPTIONBAR_WIDTH/5, 
			WINDOW_HEIGHT - 4 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP) + OPTIONBAR_WIDTH/15 + OPTIONBAR_WIDTH/5);
		break;
	}
	FlushBatchDraw();
}

void mainMenuControl(int *flag, int getKey)
{
	switch(getKey)
	{
	case 'W':
	case 'w':
	case 72:
		if(*flag <= 1 || *flag > 3)
		{
			(*flag) = 3;
		}
		else if(*flag > 1 || *flag <= 3)
		{
			(*flag)--;
		}
		break;
	case 'S':
	case 's':
	case 80:
		if(*flag < 1 || *flag >= 3)
		{
			(*flag) = 1;
		}
		else if(*flag >= 1 || *flag < 3)
		{
			(*flag)++;
		}
		break;
	case 32:
	case 13:
		switch(*flag)
		{
		case 1:
			Gameing();
			break;
		case 2:
			rankMenu();
			break;
		case 3:
			exit(0);
			break;
		case 4:
			exit(0);
			break;
		}
		break;
	}
}

void mainMenu()
{
	int flag = 1, getKey;
	for(;;)
	{
		mainMenuDisplay( flag);
		getKey = _getch();
//		cout << "getKey: " << getKey << endl;
		mainMenuControl(&flag, getKey);
	}
}

void gameOverDisplay()
{
	LOGFONT titleFont = {0};
	titleFont.lfHeight = 30;
	titleFont.lfWeight = 1000;
	titleFont.lfUnderline = true;

	BeginBatchDraw();
	BlackScreen();

	settextstyle(&titleFont);		/*标题*/
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - 6 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), _T("请切换到控制台输入您的名字"));
	FlushBatchDraw();
}

void rankMenuDisplay(int flag)
{
	GAMEDATA *item = HeadofData;
	LOGFONT titleFont = {0}, optionFont = {0}, tipsFont = {0};
	int i;
	char score[10], rank[4];
	titleFont.lfHeight = 120;
	titleFont.lfWeight = 1000;
	titleFont.lfUnderline = true;
	optionFont.lfHeight = OPTIONBAR_HEIGHT;
	optionFont.lfWeight = 1000;
	tipsFont.lfHeight = OPTIONBAR_HEIGHT/2;
	tipsFont.lfWeight = 1000;

	BeginBatchDraw();
	BlackScreen();

	settextstyle(&titleFont);		/*标题*/
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - 6 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), _T("排行榜"));

	settextstyle(&tipsFont);	/*绘制提示*/
	settextcolor(BLUE);
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 40, 
		_T("tips: "));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 20, 
		_T("按W/S以使页面移动"));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT, 
		_T("按回车/空格以返回"));

	settextstyle(&optionFont);
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*10 - TEXT_GAP, _T("姓名"));
	outtextxy(WINDOW_WIDTH/2 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*10 - TEXT_GAP, _T("分数"));
	outtextxy(WINDOW_WIDTH*11/16 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*10 - TEXT_GAP, _T("排名"));
	for( i = 1; i < flag && item != NULL; i++)
	{
		item = item->next;
	}
	for( i = 0; i < 10 && item != NULL; i++)
	{
		outtextxy(WINDOW_WIDTH*5/16 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*(9 - i) - TEXT_GAP, item->Data.name);
		itoa(item->Data.score, score, 10);
		itoa(item->Data.rank, rank, 10);
		outtextxy(WINDOW_WIDTH/2 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*(9 - i) - TEXT_GAP, score);
		outtextxy(WINDOW_WIDTH*11/16, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*(9 - i) - TEXT_GAP, rank);
		item = item->next;
	}

	if(i < 9)
	{
		outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - TEXT_HEIGHT - TEXT_GAP, _T("下面没有了！"));
	}

	FlushBatchDraw();
}

void rankMenuControl(int *flag, int getKey, bool *quit)
{
	switch(getKey)
	{
	default:
		break;
	case 'W':
	case 'w':
		if(*flag > 1)
		{
			(*flag)--;
		}
		else if(*flag <= 1)
		{
			(*flag) = 1;
		}
		break;
	case 'S':
	case 's':
		(*flag)++;
		break;
	case 32:
	case 13:
		*quit = true;
		break;
	}
}

void rankMenu()
{
	int flag = 1, getKey;
	bool quit = false;

//	freeMemory(HeadofData);
	HeadofData = readFromFile();

	for(;quit != true;)
	{
		rankMenuDisplay( flag);
		getKey = _getch();
//		cout << "getKey: " << getKey << endl;
		rankMenuControl(&flag, getKey, &quit);
	}
}

void Bin()
{
	setfillcolor(YELLOW);
	solidrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		WINDOW_WIDTH/2 + OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - OPTIONBAR_GAP);

	solidrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 2 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		WINDOW_WIDTH/2 + OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - (OPTIONBAR_GAP + OPTIONBAR_HEIGHT) - OPTIONBAR_GAP);

	solidrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 3 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		WINDOW_WIDTH/2 + OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 2 *(OPTIONBAR_GAP + OPTIONBAR_HEIGHT) - OPTIONBAR_GAP);

	solidrectangle(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 4 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		WINDOW_WIDTH/2 + OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 3 *(OPTIONBAR_GAP + OPTIONBAR_HEIGHT) - OPTIONBAR_GAP);
}

void debugAndTest()
{

	system("title %time%");

}

FILE *createDebugFile()
{
	FILE *fp;
	time_t rawtime;
	struct tm *info;
	char buffer[30];
	time( &rawtime );
	info = localtime( &rawtime );
	strftime(buffer, 30, "%Y-%m-%d-%H-%M-%S.txt", info);
	strcat(pathname_debug, buffer);
//	cout << pathname_debug << endl;
	if((fp = fopen(pathname_debug, "w")) == NULL)
	{
		printf("创建debug文件失败！\n");
		exit(1);
	}
	return fp;
}

void initialization()
{
	int flag;
	FILE *fp;
	/*创建bin文件夹*/
	if( (flag = _access(".\\bin", 0)) == -1)
	{
		cout << ".\\bin\\debug文件夹不存在" << endl;
		if((flag = mkdir(".\\bin")) == -1)
		{
		cout << "创建文件失败" << endl;
		}
		else cout << "创建文件夹成功！" << endl;
	}
	/*创建bin文件夹*/

	/*创建debug文件夹*/
	if( (flag = _access(".\\bin\\debug", 0)) == -1)
	{
		cout << ".\\bin\\debug文件夹不存在" << endl;
		if((flag = mkdir(".\\bin\\debug")) == -1)
		{
		cout << "创建文件失败" << endl;
		}
		else cout << "创建文件夹成功！" << endl;
	}
	/*创建debug文件夹*/

	/*创建data文件夹*/
	if( (flag = _access(".\\bin\\data", 0)) == -1)
	{
		cout << ".\\bin\\data文件夹不存在" << endl;
		if((flag = mkdir(".\\bin\\data")) == -1)
		{
		cout << "创建文件失败" << endl;
		}
		else cout << "创建文件夹成功！" << endl;
	}
	/*创建data文件夹*/

	/*检测rank.txt是否存在*/
	if( (fp = fopen(".\\bin\\data\\rank.txt", "r")) == NULL)
	{
		cout << ".\\bin\\data\\rank.txt文件不存在或无法正常打开" << endl;
		if( (fp = fopen(".\\bin\\data\\rank.txt", "w")) == NULL)
		{
			cout << "创建文件失败" << endl;
			exit(1);
		}
		else
		{
			cout << "初始化成功" << endl;
			fclose(fp);
			if( (fp = fopen(".\\bin\\data\\rank.txt", "r")) == NULL)
			{
				cout << "无法打开文件.\\bin\\data\\rank.txt" << endl;
			}
			else fclose(fp);
		}
	}
	else fclose(fp);
	/*检测rank.txt是否存在*/
}

void Gameing()
{
	BlackScreen();
	Brick *HeadOfBricks = NULL;
	Borad borad;
	Ball ball(borad);
	bool stopGame_ball = false, stopGame_brick = false;
	count = 0;
	score = 0;
	times = 0;

	HeadofData = readFromFile();
	HeadOfBricks = NULL;

	srand(time(0));
	for(;;)
	{
		times++;
		stopGame_ball = ball.Move(HeadOfBricks, borad);
		if(stopGame_ball == true)
		{
			cout << "你没接住小球，你失败了！" << endl;
			break;
		}
		else if(stopGame_brick == true)
		{
			cout << "你没能清理完砖块，你失败了！" << endl;
			break;
		}
		if(_kbhit())
		{
			borad.Move();
		}
		if(borad.Lauch == true)
		{
			if(ball.Radius > 20) ball.rebound = false;
			else if(ball.Radius <= 20) ball.rebound = true;
			if(times%300 == 0)
			{
				HeadOfBricks = createBrick(HeadOfBricks);
			}
			if(times%(2700/BRICK_DROP_SPEED) == 0)		/*默认为2700/BRICK_DROP_SPEED*/
			{
				stopGame_brick = allBrickMove(HeadOfBricks);
			}
			if(times%13500 == 0){		/*特殊技能失效*/
				borad.antidrawBorad();
				if(borad.Width > BORAD_INITIAL_LENGTH) borad.Width -= 60;
				borad.drawBorad();

				ball.antidrawBall();
				if(ball.Radius > BALL_INITIAL_RADIUS) ball.Radius -= 8;
				ball.drawBall();
			}
			HeadOfBricks = removeBrick(HeadOfBricks);
		}
	}/*for*/
	
	gameOverDisplay();
	/*后续处理*/
	writeIntoFile(HeadofData);
	/*后续处理*/
}

Brick *createBrick(Brick *head)
{
	Brick *thisNode, *item = head;
	int Pos_x = rand() % 10;
	bool foundPos = false;			/*foundPos为false意味着没有给砖块找到合适的位置*/
	if(head == NULL)
	{
		foundPos = true;
	}
	else
	{
	int arr[10] = {0};
		while(item != NULL)
		{
			if(item->Pos_y == 0) arr[item->Pos_x] = 1;		/*值为1表明该位置有砖块*/
			item = item->next;
		}
		if(arr[Pos_x] == 0) foundPos = true;
	}
	if(foundPos == true)
	{
		thisNode = new Brick(Pos_x);
		thisNode->next = NULL;
		thisNode->num = count;
		count++;
		if(head == NULL)
		{
			head = thisNode;
		}
		else
		{
			item = head;
			while(item->next != NULL)		/*此循环用于将item指向链表尾端*/
			{
				item = item->next;
			}
			item->next = thisNode;
		}
	}
	return head;
}

bool allBrickMove(Brick *head)
{
	bool stopGame = false;
	while(head != NULL)
	{
		if((stopGame = head->Move()) == true) break;
		head = head->next;
	}
	return stopGame;
}

Brick *removeBrick(Brick *head)
{
	Brick *temp;
	Brick *lastItem;
	Brick *item;

	item = head;
	while(item != NULL)
	{
		temp = item->next;
		if(item->exist == false)
		{
			score++;
			if(item == head)
			{						/*要删的是头*/
				
//				cout << "head(1): 0x" << head;
				head = head->next;
//				cout << "head(2): 0x" << head;
				delete item;
				break;
			}
			else if(item->next == NULL)
			{						/*要删的是尾巴*/
				lastItem->next = NULL;
				delete item;
				break;
			}
			else 
			{						/*要删的是身体*/
				lastItem->next = item->next;
				delete item;
				break;
			}
//			cout << "head(3): 0x" << head;
		}	
		lastItem = item;
		item = temp; 
//		cout << "head(4): 0x" << head;
	}
//	cout << "head(5): 0x" << head;
	return head;
}

GAMEDATA *readFromFile()
{
	GAMEDATA *head = NULL;
	GAMEDATA *gamedata, *thisNode, *lastNode;
	gamedata = new GAMEDATA;
	if( (fp_data = fopen(".\\bin\\data\\rank.txt", "r")) == NULL)
	{
		cout << "打开文件失败（读的方式）" << endl;
		exit(1);
	}
	while(!feof(fp_data))
	{
		if(fscanf(fp_data, "%s %f %d", gamedata->Data.name, 
			&gamedata->Data.score, &gamedata->Data.rank) == 3)
		{
			thisNode = new GAMEDATA;
			*thisNode = *gamedata;

				/*
				cout << "读到的数据: \n\t"
				<< " " << gamedata->Data.name 
				<< " " << gamedata->Data.score 
				<< " " << gamedata->Data.rank << endl;
				*/
			thisNode->next = NULL;
			if(head == NULL)
			{
				head = thisNode;
			}
			else
			{
				lastNode->next = thisNode;
			}
			lastNode = thisNode;
		}
	}
	delete gamedata;
	fclose(fp_data);
	head = Rankthem(head);
	return head;
}

void freeMemory(GAMEDATA *head)
{
	GAMEDATA *item = head, *temp = head->next;
	if(head == NULL)
	{
		cout << "直接return" << endl;
		return;
	}
	else
	{
		while(item != NULL)
		{
			cout << "item: " << item << endl;
			temp = item->next;
			delete item;
			item = temp;
		}
	}
}
void writeIntoFile(GAMEDATA *head)
{
	GAMEDATA *gamedata, *lastNode, *item;
	lastNode = head;
	gamedata = new GAMEDATA;

	if( (fp_data = fopen(".\\bin\\data\\rank.txt", "w")) == NULL)
	{
		cout << "打开文件失败（写的方式）" << endl;
		exit(1);
	}
	cout << "请输入你的名字：" << endl;
	cin >> name;
	saveToDebugFile("名字为：");
	saveToDebugFile(name);
	
	system("cls");
	cout << "输入成功，可以切换回游戏界面了" << endl;
	if(head == NULL)
	{
//		cout << "姓名\t" << "分数\t" << "排名" << endl;
//		printf("%s\t%.2f\t%d\n", name, score * DegreeofDifficulty, rank);
		fprintf(fp_data, "%s %f %d", name, score * DegreeofDifficulty, rank);
		delete gamedata;
	}
	else
	{
		while(lastNode->next != NULL)
		{
			lastNode = lastNode->next;
		}
		strcpy(gamedata->Data.name, name);
		gamedata->Data.score = score * DegreeofDifficulty;
		gamedata->next = NULL;
		lastNode->next = gamedata;
//		cout << "姓名\t" << "分数\t" << "排名" << endl;
		item = Rankthem(head);
		while(item != NULL)
		{
//			printf("%s\t%4.6f\t%4d\n", item->Data.name, item->Data.score, item->Data.rank);
			fprintf(fp_data, "%s %f %d\n", item->Data.name, item->Data.score, item->Data.rank);
			item = item->next;
		}
	}
	fclose(fp_data);
}

GAMEDATA *Rankthem(GAMEDATA *head)
{
	GAMEDATA *thisNode, *nextNode;
	DATA temp;
	int i = 1;

	thisNode = head;
	while(thisNode != NULL)
	{
		nextNode = thisNode->next;
		while(nextNode != NULL)
		{
			if(nextNode->Data.score > thisNode->Data.score)
			{
				temp = nextNode->Data;
				nextNode->Data = thisNode->Data;
				thisNode->Data = temp;
			}
			else if(nextNode->Data.score < thisNode->Data.score)
			{
				;
			}
			else if(nextNode->Data.score == thisNode->Data.score)
			{
				if(strcmp(nextNode->Data.name, thisNode->Data.name) < 0)
				{
					temp = nextNode->Data;
					nextNode->Data = thisNode->Data;
					thisNode->Data = temp;
				}
			}
			nextNode = nextNode->next;
		}
		thisNode = thisNode->next;
	}	/*按分数、姓名排序*/

	thisNode = head;
	while(thisNode != NULL)
	{
		thisNode->Data.rank = i;
		i++;
		thisNode = thisNode->next;
	}		/*赋序*/
	return head;
}
