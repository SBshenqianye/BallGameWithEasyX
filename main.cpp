/*���ߣ���̱�*/
/*���ڣ�2021/6/1*/
/*����������������󲿷ֺ���*/
/*�汾�������˰汾Ϊv1.4*/
/*����޸����ڣ�2021/6/29*/
/*����������717*/
#include "HeadersForGame.h"
#define OPTIONBAR_WIDTH WINDOW_WIDTH*3/20	/*ѡ��������		-	���ɸ���*/
#define OPTIONBAR_HEIGHT WINDOW_HEIGHT/15	/*ѡ������߶�		-	���ɸ���*/
#define OPTIONBAR_GAP WINDOW_HEIGHT/10		/*ѡ�������϶		-	���ɸ���*/
#define TEXT_HEIGHT WINDOW_HEIGHT/20		/*���а�����߶�	-	���ɸ���*/
#define TEXT_GAP WINDOW_HEIGHT/40			/*���а������϶	-	���ɸ���*/

FILE *fp_data;								/*�����ļ��ṹ��ָ��*/
GAMEDATA *HeadofData = NULL;				/*��������ͷ���ʻ�*/

int main()
{
	int system_time = 0;
	/*׼���׶�*/
	initialization();
	debugAndTest();
	fp_debug = createDebugFile();
	/*׼���׶�*/

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE);
	mainMenu();


	_getch();    /*��ʱ��û���ֳ��ô�*/
	fclose(fp_debug);
	return 0;
}

void BlackScreen()
{
	/*��������	Ϳ����Ļ*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	�������*/
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void mainMenuDisplay(int flag)
{
	/*��������	��ʾ���˵�*/
	/*�������	ѡ��*/
	/*����ֵ	��*/
	/*���ù�ϵ	ֻ��mainMenu()����*/
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

	settextstyle(&titleFont);	/*���Ʊ���*/
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - 6 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), _T("������"));

	settextstyle(&optionFont);		/*����ѡ��*/
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 4 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		_T("��ʼ��Ϸ"));
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 3 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		_T("���а�"));
	optionFont.lfStrikeOut = true;
	settextstyle(&optionFont);
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - 2 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), 
		_T("����"));
	optionFont.lfStrikeOut = false;
	settextstyle(&optionFont);
	outtextxy(WINDOW_WIDTH/2 - OPTIONBAR_WIDTH/2, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - OPTIONBAR_GAP, 
		_T("�˳�"));

	settextstyle(&tipsFont);	/*������ʾ*/
	settextcolor(BLUE);
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 40, 
		_T("tips: "));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 20, 
		_T("��W/S��ʹ����ƶ�"));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT, 
		_T("���س�/�ո���ȷ��"));

	setlinecolor(RED);
	setfillcolor(RED);
	switch(flag)		/*����ѡ��ָ��*/
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
	/*��������	�������˵�ѡ��*/
	/*�������	ѡ���������	�������	ѡ��*/
	/*����ֵ	��*/
	/*���ù�ϵ	ֻ��mainMenu()����*/
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
	/*��������	���ÿ��Ʋ˵�����ʾ�˵�����*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	ֻ��mainMenu()����*/
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
	/*��������	��ʾ��Ϸ��������*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	��gaming()����*/
	LOGFONT titleFont = {0};
	titleFont.lfHeight = 30;
	titleFont.lfWeight = 1000;
	titleFont.lfUnderline = true;

	BeginBatchDraw();
	BlackScreen();

	settextstyle(&titleFont);		/*����*/
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - 6 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), _T("���л�������̨������������"));
	FlushBatchDraw();
}

void rankMenuDisplay(int flag)
{
	/*��������	��ʾ���а�*/
	/*�������	��һ����ʾ������*/
	/*����ֵ	��*/
	/*���ù�ϵ	��rankMenu()����*/
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

	settextstyle(&titleFont);		/*����*/
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - 6 * (OPTIONBAR_HEIGHT + OPTIONBAR_GAP), _T("���а�"));

	settextstyle(&tipsFont);	/*������ʾ*/
	settextcolor(BLUE);
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 40, 
		_T("tips: "));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT - 20, 
		_T("��W/S��ʹҳ���ƶ�"));
	outtextxy(WINDOW_WIDTH/2 - 3*OPTIONBAR_WIDTH, WINDOW_HEIGHT - OPTIONBAR_HEIGHT, 
		_T("���س�/�ո��Է���"));

	settextstyle(&optionFont);
	settextcolor(RED);
	outtextxy(WINDOW_WIDTH*5/16 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*10 - TEXT_GAP, _T("����"));
	outtextxy(WINDOW_WIDTH/2 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*10 - TEXT_GAP, _T("����"));
	outtextxy(WINDOW_WIDTH*11/16 - 2*TEXT_GAP, WINDOW_HEIGHT - (TEXT_HEIGHT + TEXT_GAP)*10 - TEXT_GAP, _T("����"));
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
		outtextxy(WINDOW_WIDTH*5/16, WINDOW_HEIGHT - TEXT_HEIGHT - TEXT_GAP, _T("����û���ˣ�"));
	}

	FlushBatchDraw();
}

void rankMenuControl(int *flag, int getKey, bool *quit)
{
	/*��������	�������а��һ����ʾ������*/
	/*�������	��һ����ʾ�����ݡ�������Ϣ���˳��˵��ж�	�������	��һ����ʾ�����ݡ��˳��˵��ж�*/
	/*����ֵ	��*/
	/*���ù�ϵ	��rankMenu()����*/
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
	/*��������	���е������а��������ʾ����*/
	/*�������	��*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	��mainMenu()����*/
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
	/*��������	װ���������߿������õ����*/
	/*�������	��*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	������*/
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
	/*��������	���������*/
	/*�������	��*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	������*/

	system("title %time%");

}

FILE *createDebugFile()
{
	/*��������	�������debug��Ϣ���ļ�*/
	/*�������	��*/
	/*�������	��*/
	/*����ֵ	ָ��FILE���͵�ָ��*/
	/*���ù�ϵ	��initialization()����*/
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
		printf("����debug�ļ�ʧ�ܣ�\n");
		exit(1);
	}
	return fp;
}

void initialization()
{
	/*��������	��ʼ���ļ���Ϣ������debug�ļ�����data�ļ��еȵȣ�*/
	/*�������	��*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	��main()����*/
	int flag;
	FILE *fp;
	/*����bin�ļ���*/
	if( (flag = _access(".\\bin", 0)) == -1)
	{
		cout << ".\\bin\\debug�ļ��в�����" << endl;
		if((flag = mkdir(".\\bin")) == -1)
		{
		cout << "�����ļ�ʧ��" << endl;
		}
		else cout << "�����ļ��гɹ���" << endl;
	}
	/*����bin�ļ���*/

	/*����debug�ļ���*/
	if( (flag = _access(".\\bin\\debug", 0)) == -1)
	{
		cout << ".\\bin\\debug�ļ��в�����" << endl;
		if((flag = mkdir(".\\bin\\debug")) == -1)
		{
		cout << "�����ļ�ʧ��" << endl;
		}
		else cout << "�����ļ��гɹ���" << endl;
	}
	/*����debug�ļ���*/

	/*����data�ļ���*/
	if( (flag = _access(".\\bin\\data", 0)) == -1)
	{
		cout << ".\\bin\\data�ļ��в�����" << endl;
		if((flag = mkdir(".\\bin\\data")) == -1)
		{
		cout << "�����ļ�ʧ��" << endl;
		}
		else cout << "�����ļ��гɹ���" << endl;
	}
	/*����data�ļ���*/

	/*���rank.txt�Ƿ����*/
	if( (fp = fopen(".\\bin\\data\\rank.txt", "r")) == NULL)
	{
		cout << ".\\bin\\data\\rank.txt�ļ������ڻ��޷�������" << endl;
		if( (fp = fopen(".\\bin\\data\\rank.txt", "w")) == NULL)
		{
			cout << "�����ļ�ʧ��" << endl;
			exit(1);
		}
		else
		{
			cout << "��ʼ���ɹ�" << endl;
			fclose(fp);
			if( (fp = fopen(".\\bin\\data\\rank.txt", "r")) == NULL)
			{
				cout << "�޷����ļ�.\\bin\\data\\rank.txt" << endl;
			}
			else fclose(fp);
		}
	}
	else 
	{
		cout << "��ʼ���ɹ�" << endl;
		fclose(fp);
	}
	/*���rank.txt�Ƿ����*/
}

void Gameing()
{
	/*��������	��Ϸ���庯��*/
	/*�������	��*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	��main()����*/
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
			cout << "��û��סС����ʧ���ˣ�" << endl;
			break;
		}
		else if(stopGame_brick == true)
		{
			cout << "��û��������ש�飬��ʧ���ˣ�" << endl;
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
			if(times%(2700/BRICK_DROP_SPEED) == 0)		/*Ĭ��Ϊ2700/BRICK_DROP_SPEED*/
			{
				stopGame_brick = allBrickMove(HeadOfBricks);
			}
			if(times%13500 == 0){		/*���⼼��ʧЧ*/
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
	/*��������*/
	writeIntoFile(HeadofData);
	/*��������*/
}

Brick *createBrick(Brick *head)
{
	/*��������	����ש��*/
	/*�������	ש������ͷ*/
	/*�������	��*/
	/*����ֵ	��ש������ͷ*/
	/*���ù�ϵ	��gaming()����*/
	Brick *thisNode, *item = head;
	int Pos_x = rand() % 10;
	bool foundPos = false;			/*foundPosΪfalse��ζ��û�и�ש���ҵ����ʵ�λ��*/
	if(head == NULL)
	{
		foundPos = true;
	}
	else
	{
	int arr[10] = {0};
		while(item != NULL)
		{
			if(item->Pos_y == 0) arr[item->Pos_x] = 1;		/*ֵΪ1������λ����ש��*/
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
			while(item->next != NULL)		/*��ѭ�����ڽ�itemָ������β��*/
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
	/*��������	ʹ����ש���˶�*/
	/*�������	ת������ͷ*/
	/*�������	��*/
	/*����ֵ	�ж�ֹͣ��Ϸ*/
	/*���ù�ϵ	��gaming()����*/
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
	/*��������	���������Ƴ��������ש��*/
	/*�������	ש������ͷ*/
	/*�������	��*/
	/*����ֵ	��ש������ͷ*/
	/*���ù�ϵ	��gaming()����*/
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
			{						/*Ҫɾ����ͷ*/
				
//				cout << "head(1): 0x" << head;
				head = head->next;
//				cout << "head(2): 0x" << head;
				delete item;
				break;
			}
			else if(item->next == NULL)
			{						/*Ҫɾ����β��*/
				lastItem->next = NULL;
				delete item;
				break;
			}
			else 
			{						/*Ҫɾ��������*/
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
	/*��������	��ȡ���а���Ϣ������*/
	/*�������	��*/
	/*�������	��*/
	/*����ֵ	���а�����ͷ*/
	/*���ù�ϵ	�������������*/
	GAMEDATA *head = NULL;
	GAMEDATA *gamedata, *thisNode, *lastNode;
	gamedata = new GAMEDATA;
	if( (fp_data = fopen(".\\bin\\data\\rank.txt", "r")) == NULL)
	{
		cout << "���ļ�ʧ�ܣ����ķ�ʽ��" << endl;
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
				cout << "����������: \n\t"
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
	/*��������	�ͷ��ڴ�*/
	/*�������	���а�����ͷ*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	��*/
	GAMEDATA *item = head, *temp = head->next;
	if(head == NULL)
	{
		cout << "ֱ��return" << endl;
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
	/*��������	�����а�����д�뵽�ļ�*/
	/*�������	���а�����ͷ*/
	/*�������	��*/
	/*����ֵ	��*/
	/*���ù�ϵ	��gaming()����*/
	GAMEDATA *gamedata, *lastNode, *item;
	lastNode = head;
	gamedata = new GAMEDATA;

	if( (fp_data = fopen(".\\bin\\data\\rank.txt", "w")) == NULL)
	{
		cout << "���ļ�ʧ�ܣ�д�ķ�ʽ��" << endl;
		exit(1);
	}
	cout << "������������֣�" << endl;
	cin >> name;
	saveToDebugFile("����Ϊ��");
	saveToDebugFile(name);
	
	system("cls");
	cout << "����ɹ��������л�����Ϸ������" << endl;
	if(head == NULL)
	{
//		cout << "����\t" << "����\t" << "����" << endl;
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
//		cout << "����\t" << "����\t" << "����" << endl;
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
	/*��������	�����а�����*/
	/*�������	���а�����ͷ*/
	/*�������	��*/
	/*����ֵ	�����а�����ͷ*/
	/*���ù�ϵ	�������������*/
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
	}	/*����������������*/

	thisNode = head;
	while(thisNode != NULL)
	{
		thisNode->Data.rank = i;
		i++;
		thisNode = thisNode->next;
	}		/*����*/
	return head;
}
