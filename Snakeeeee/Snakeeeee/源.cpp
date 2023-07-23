//贪吃蛇：
//数据的分析：成员属性
/*****************************************
*                     背景板
*                     蛇属性
*                     食物属性
*                     坐标属性
******************************************/

//过程的分析：函数实现
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
//属性的定义
//坐标属性
typedef struct point
{
	int x;
	int y;
}mypoint;
//蛇的属性
struct Snake
{
	int len;
	mypoint body[100];    //100的长度
	char direction;  //方向
	int grade;
}snake;
//食物的属性
struct Food
{
	mypoint body;
	int existence;       //食物是否存在
}food ;
 //枚举方向值
enum Direction       //用的大写的WASD
{
	up = 87,
	down=83,
	right=68,
	left=65
 };


//过程函数
void initsnake();                 //初始化蛇
void drawsnake();                 //画蛇
void initfood();                  //初始化食物
void move();                      //蛇的移动
void eatfood();                   //吃食物
int snakedie();                   //蛇死亡
void presskey_and_wheel();        //读取按键并转头
void showgrade();                 //得出分数
HWND hwnd = NULL;

int main()
{
	hwnd=initgraph(640, 480);//屏幕大小（像素）
	cleardevice();   //刷新屏幕
	setbkcolor(WHITE); //白色屏幕
	initsnake();     //初始化一条蛇
	while (1)
	{
		cleardevice();   //刷新屏幕
		drawsnake();
		initfood();      //放出食物
		move();          //蛇动了
		while(_kbhit())        //kbhit函数可以设别是否敲击键盘（keyboard hit）
		presskey_and_wheel();  //读取按键并转弯
		eatfood();
		Sleep(100);
		if (snakedie() == 1) break;
	}
	getchar();             //吸收奇奇怪怪的大小防止闪屏
	printf("\n\n\n\n\n           /*********************************************\n");
	printf("                           你弱爆了！才 %d 分\n",snake.grade);
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
	for (int i = snake.len - 1; i > 0; i--)  //头以外的
	{
		
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
		
	}
		switch (snake.direction)  //头动
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
	char key = _getch();    //_getch函数读取键盘中的字符但不显示
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
	if (snake.body[0].x == food.body.x&&snake.body[0].y==food.body.y) //蛇头和食物xy值相遇
	{
		food.existence=0;
		snake.len++;
	}
}
int snakedie()
{
	//蛇头xy值超出界面
	if (snake.body[0].x < 0 || snake.body[0].x >640 || snake.body[0].y < 0 || snake.body[0].y>480)
	{
		MessageBox(hwnd,"这墙你都能撞到", "撞墙警告",  MB_OK);       //MessageBox函数在主界面显示对话框
		return 1;
	}
	for (int i = 1; i < snake.len; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			MessageBox(hwnd, "手不好用就捐了吧~~", "啃尾警告", MB_OK);    
			return 1;
		}
			
	}
	
}
void showgrade()
{
	snake.grade = (snake.len - 3) * 10;           
}
