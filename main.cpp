/*作者：彭程斌*/
/*日期：2021/6/1*/
/*描述：包含程序绝大部分函数*/
/*版本声明：此版本为v1.4*/
/*最后修改日期：2021/6/29*/
/*代码行数：717*/
#include "HeadersForGame.h"
#define OPTIONBAR_WIDTH WINDOW_WIDTH*3/20	/*选项字体宽度		-	不可更改*/
#define OPTIONBAR_HEIGHT WINDOW_HEIGHT/15	/*选项字体高度		-	不可更改*/
#define OPTIONBAR_GAP WINDOW_HEIGHT/10		/*选项字体间隙		-	不可更改*/
#define TEXT_HEIGHT WINDOW_HEIGHT/20		/*排行榜字体高度	-	不可更改*/
#define TEXT_GAP WINDOW_HEIGHT/40			/*排行榜字体间隙	-	不可更改*/

FILE *fp_data;								/*数据文件结构体指针*/
GAMEDATA *HeadofData = NULL;				/*数据链表头舒适化*/

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
	/*函数功能	涂黑屏幕*/
	/*输入参数	无*/
	/*返回值	无*/
	/*调用关系	随意调用*/
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void mainMenuDisplay(int flag)
{
	/*函数功能	显示主菜单*/
	/*输入参数	选项*/
	/*返回值	无*/
	/*调用关系	只被mainMenu()调用*/
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
	/*函数功能	控制主菜单选择*/
	/*输入参数	选项、键盘输入	输出参数	选项*/
	/*返回值	无*/
	/*调用关系	只被mainMenu()调用*/
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
	/*函数功能	调用控制菜单与显示菜单函数*/
	/*输入参数	无*/
	/*返回值	无*/
	/*调用关系	只被mainMenu()调用*/
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
	/*函数功能	显示游戏结束画面*/
	/*输入参数	无*/
	/*返回值	无*/
	/*调用关系	被gaming()调用*/
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
	/*函数功能	显示排行榜*/
	/*输入参数	第一个显示的数据*/
	/*返回值	无*/
	/*调用关系	被rankMenu()调用*/
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
	/*函数功能	控制排行榜第一个显示的数据*/
	/*输入参数	第一个显示的数据、键盘信息、退出菜单判断	输出参数	第一个显示的数据、退出菜单判断*/
	/*返回值	无*/
	/*调用关系	被rankMenu()调用*/
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
	/*函数功能	集中调用排行榜控制与显示函数*/
	/*输入参数	无*/
	/*输出参数	无*/
	/*返回值	无*/
	/*调用关系	被mainMenu()调用*/
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
	/*函数功能	装被丢弃或者可能有用的语句*/
	/*输入参数	无*/
	/*输出参数	无*/
	/*返回值	无*/
	/*调用关系	随便调用*/
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
	/*函数功能	调试与测试*/
	/*输入参数	无*/
	/*输出参数	无*/
	/*返回值	无*/
	/*调用关系	随便调用*/

	system("title %time%");

}

FILE *createDebugFile()
{
	/*函数功能	创建存放debug消息的文件*/
	/*输入参数	无*/
	/*输出参数	无*/
	/*返回值	指向FILE类型的指针*/
	/*调用关系	被initialization()调用*/
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
	/*函数功能	初始化文件信息（包括debug文件夹与data文件夹等等）*/
	/*输入参数	无*/
	/*输出参数	无*/
	/*返回值	无*/
	/*调用关系	被main()调用*/
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
	else 
	{
		cout << "初始化成功" << endl;
		fclose(fp);
	}
	/*检测rank.txt是否存在*/
}

void Gameing()
{
	/*函数功能	游戏主体函数*/
	/*输入参数	无*/
	/*输出参数	无*/
	/*返回值	无*/
	/*调用关系	被main()调用*/
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
	/*函数功能	生成砖块*/
	/*输入参数	砖块链表头*/
	/*输出参数	无*/
	/*返回值	新砖块链表头*/
	/*调用关系	被gaming()调用*/
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
	/*函数功能	使所有砖块运动*/
	/*输入参数	转块链表头*/
	/*输出参数	无*/
	/*返回值	判断停止游戏*/
	/*调用关系	被gaming()调用*/
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
	/*函数功能	从链表中移除被打掉的砖块*/
	/*输入参数	砖块链表头*/
	/*输出参数	无*/
	/*返回值	新砖块链表头*/
	/*调用关系	被gaming()调用*/
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
	/*函数功能	读取排行榜信息到链表*/
	/*输入参数	无*/
	/*输出参数	无*/
	/*返回值	排行榜链表头*/
	/*调用关系	被多个函数调用*/
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
	/*函数功能	释放内存*/
	/*输入参数	排行榜链表头*/
	/*输出参数	无*/
	/*返回值	无*/
	/*调用关系	无*/
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
	/*函数功能	将排行榜链表写入到文件*/
	/*输入参数	排行榜链表头*/
	/*输出参数	无*/
	/*返回值	无*/
	/*调用关系	被gaming()调用*/
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
	/*函数功能	给排行榜排序*/
	/*输入参数	排行榜链表头*/
	/*输出参数	无*/
	/*返回值	新排行榜链表头*/
	/*调用关系	被多个函数调用*/
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
