//̰���ߣ�
//���ݵķ�������Ա����
/*****************************************
*                     ������
*                     ������
*                     ʳ������
*                     ��������
******************************************/

//���̵ķ���������ʵ��
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
//���ԵĶ���
//��������
typedef struct point
{
	int x;
	int y;
}mypoint;
//�ߵ�����
struct Snake
{
	int len;
	mypoint body[100];    //100�ĳ���
	char direction;  //����
	int grade;
}snake;
//ʳ�������
struct Food
{
	mypoint body;
	int existence;       //ʳ���Ƿ����
}food ;
 //ö�ٷ���ֵ
enum Direction       //�õĴ�д��WASD
{
	up = 87,
	down=83,
	right=68,
	left=65
 };


//���̺���
void initsnake();                 //��ʼ����
void drawsnake();                 //����
void initfood();                  //��ʼ��ʳ��
void move();                      //�ߵ��ƶ�
void eatfood();                   //��ʳ��
int snakedie();                   //������
void presskey_and_wheel();        //��ȡ������תͷ
void showgrade();                 //�ó�����
HWND hwnd = NULL;

int main()
{
	hwnd=initgraph(640, 480);//��Ļ��С�����أ�
	cleardevice();   //ˢ����Ļ
	setbkcolor(WHITE); //��ɫ��Ļ
	initsnake();     //��ʼ��һ����
	while (1)
	{
		cleardevice();   //ˢ����Ļ
		drawsnake();
		initfood();      //�ų�ʳ��
		move();          //�߶���
		while(_kbhit())        //kbhit������������Ƿ��û����̣�keyboard hit��
		presskey_and_wheel();  //��ȡ������ת��
		eatfood();
		Sleep(100);
		if (snakedie() == 1) break;
	}
	getchar();             //��������ֵֹĴ�С��ֹ����
	printf("\n\n\n\n\n           /*********************************************\n");
	printf("                           �������ˣ��� %d ��\n",snake.grade);
	printf("            *********************************************/\n\n\n\n\n\n\n");       
	return 0;
}

void initsnake()
{
	snake.len = 3;
	snake.body[0].x = 60;
	snake.body[0].y = 0;
	snake.body[1].x = 40;
	snake.body[1].y = 0;
	snake.body[2].x = 20;
	snake.body[2].y = 0;
	snake.direction = right;
}
	void initfood()
{
		if (food.existence == 0)
		{
			food.body.x = rand() % 32 * 20;
			food.body.y = rand() % 24 * 20;
		}
	setlinecolor(BLACK);
	setfillcolor(RGB(0, 100, 150) );
	fillrectangle(food.body.x, food.body.y, food.body.x+20, food.body.y+20);
	food.existence = 1;
}
void drawsnake()
{
	setlinecolor(BLACK);

	for (int i = 0; i < snake.len; i++)
	{
		setfillcolor(RGB(rand() % 255 , rand() % 255 , rand() % 255 ));
		fillrectangle(snake.body[i].x, snake.body[i].y, snake.body[i].x + 20, snake.body[i].y + 20);
	}
}
void move()
{
	for (int i = snake.len - 1; i > 0; i--)  //ͷ�����
	{
		
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
		
	}
		switch (snake.direction)  //ͷ��
		{
		case up:
			snake.body[0].y -= 20;
			break;
		case down:
			snake.body[0].y += 20;
			break;
		case right:
			snake.body[0].x += 20;
			break;
		case left:
			snake.body[0].x -= 20;
			break;
		default:
			break;
		}
}
void presskey_and_wheel()
{
	char key = _getch();    //_getch������ȡ�����е��ַ�������ʾ
	switch (key)
	{
	case up:
		if (snake.direction == left || snake.direction == right)
		{
			snake.body[0].y =snake.body[1].y-20;
			snake.body[0].x = snake.body[1].x;
			snake.direction = up;
		}
		break;
	case down:
		if (snake.direction == left || snake.direction == right)
		{
			snake.body[0].y =snake.body[1].y+20;
			snake.body[0].x = snake.body[1].x ;
			snake.direction = down;
		}
		break;
	case right:
		if (snake.direction == up || snake.direction == down)
		{
			snake.body[0].x =snake.body[1].x+20;
			snake.body[0].y = snake.body[1].y;
			snake.direction = right;
		}	
		break;
	case left:
		if (snake.direction == up || snake.direction == down)
		{
			snake.body[0].x =snake.body[1].x-20;
			snake.body[0].y = snake.body[1].y;
			snake.direction = left;
		}	
		break;
	default:
		break;
	}
}
void eatfood()
{
	if (snake.body[0].x == food.body.x&&snake.body[0].y==food.body.y) //��ͷ��ʳ��xyֵ����
	{
		food.existence=0;
		snake.len++;
	}
}
int snakedie()
{
	//��ͷxyֵ��������
	if (snake.body[0].x < 0 || snake.body[0].x >640 || snake.body[0].y < 0 || snake.body[0].y>480)
	{
		MessageBox(hwnd,"��ǽ�㶼��ײ��", "ײǽ����",  MB_OK);       //MessageBox��������������ʾ�Ի���
		return 1;
	}
	for (int i = 1; i < snake.len; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			MessageBox(hwnd, "�ֲ����þ;��˰�~~", "��β����", MB_OK);    
			return 1;
		}
			
	}
	
}
void showgrade()
{
	snake.grade = (snake.len - 3) * 10;           
}
