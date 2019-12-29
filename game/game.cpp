#include<iostream>
#include<cstdio>
#include<cstring>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<conio.h>
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?0:1)
#define HEIGHT 15
#define WIDTH 50
using namespace std;

struct bullet
{
	int x,y;
	bullet *nxt;
	bullet *pre;
}; 

int dx[8]={0,1,0,-1,-1,-1,1,1};
int dy[8]={1,0,-1,0,-1,1,-1,1};

int player_x=10,player_y=10,boss_x=WIDTH-3,boss_y=HEIGHT-10,boss_health=50,player_health=3;
int totbullet,lastshoot,choice,times;
bullet *player_bullet_head;
bullet *boss_bullet_head;

void boss_move()
{
	int dir=rand()%2;
	if(dir==0)boss_y--;
	else boss_y++;
	if(boss_y<=1)boss_y=1;
	if(boss_y>=HEIGHT-6)boss_y=HEIGHT-6;
}
void shoot()
{
	if(KEYDOWN('J'))lastshoot=1;		//中断 
	if(KEYUP('J')&&lastshoot)
	{
		lastshoot=0;
		bullet *newbullet=(bullet *)malloc(sizeof(bullet));
		while(newbullet==NULL)newbullet=(bullet *)malloc(sizeof(bullet));
		newbullet->nxt=NULL;
		newbullet->x=player_x+1;
		newbullet->y=player_y;
		newbullet->pre=NULL;
		if(player_bullet_head==NULL)player_bullet_head=newbullet;
		else
		{
			bullet *temp=player_bullet_head;
			while(temp->nxt!=NULL)temp=temp->nxt;
			temp->nxt=newbullet;
			newbullet->pre=temp;
		}
	}
}
void HideCursor()						
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}
void init()
{
	srand(time(NULL));
	system("mode con cols=50");
	system("mode con lines=15");
	SetConsoleTitle("game"); 
	HideCursor();
}
void boss_shoot()
{
	bullet *newbullet=(bullet *)malloc(sizeof(bullet));
	while(newbullet==NULL)newbullet=(bullet *)malloc(sizeof(bullet));
	newbullet->nxt=NULL;
	newbullet->x=boss_x-1;
	newbullet->y=boss_y-1+rand()%3;
	newbullet->pre=NULL;
	if(boss_bullet_head==NULL)boss_bullet_head=newbullet;
	else
	{
		bullet *temp=boss_bullet_head;
		while(temp->nxt!=NULL)temp=temp->nxt;
		temp->nxt=newbullet;
		newbullet->pre=temp;
	}
}
void gotoxy(int x,int y)
{
	COORD pos = {(short)x,(short)y};  
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void print()
{
	//print yourself
	gotoxy(player_x,player_y);
	printf("#");
	//print player bullet
	if(player_bullet_head!=NULL)
	{
		bullet *temp=player_bullet_head;
		while(temp!=NULL)
		{
			gotoxy(temp->x,temp->y);
			printf("*");
			temp=temp->nxt;
		}
	}
	//print boss bullet
	if(boss_bullet_head!=NULL)
	{
		bullet *temp=boss_bullet_head;
		while(temp!=NULL)
		{
			gotoxy(temp->x,temp->y);
			printf("<");
			temp=temp->nxt;
		}
	}
	//print boss
	for(int i=0;i<8;i++)
	{
		gotoxy(boss_x+dx[i],boss_y+dy[i]);
		printf("o");
	}
	//print health
	gotoxy(0,HEIGHT-2);
	printf("boss health：%d      player health: %d",boss_health,player_health);
//	for(int i=1;i<=boss_health;i++)
//	{
//		gotoxy(i-1,HEIGHT-1);
//		printf("$");
//	}
}
void player_bullet_del(bullet *x)
{
	if(x==player_bullet_head)
	{
		player_bullet_head=x->nxt;
		if(player_bullet_head!=NULL)player_bullet_head->pre=NULL;
		free(x);
	}
	else
	{
		x->pre->nxt=x->nxt;
		if(x->nxt!=NULL)x->pre->nxt->pre=x->pre;
		free(x);
	}
}
void boss_bullet_del(bullet *x)
{
	if(x==boss_bullet_head)
	{
		boss_bullet_head=x->nxt;
		if(boss_bullet_head!=NULL)boss_bullet_head->pre=NULL;
		free(x);
	}
	else
	{
		x->pre->nxt=x->nxt;
		if(x->nxt!=NULL)x->pre->nxt->pre=x->pre;
		free(x);
	}
}
void player_move()
{
	if(KEYDOWN('W'))player_y--;		//左上角为原点，x轴向右为正，y轴向下为正 
	else if(KEYDOWN('S'))player_y++;
	else if(KEYDOWN('A'))player_x--;
	else if(KEYDOWN('D'))player_x++;
	if(player_y<0)player_y=0;
	if(player_x<0)player_x=0;
	if(player_y>=HEIGHT-5)player_y=HEIGHT-5;
	if(player_x>=WIDTH-10)player_x=WIDTH-10;
}
void player_bullet_move()
{
	if(player_bullet_head!=NULL)
	{
		bullet *temp=player_bullet_head;
		while(temp!=NULL)
		{
			temp->x++;
			bullet *nxt=temp->nxt;
			bool flag=false;
			if((abs(temp->x-boss_x)<=1)&&(abs(temp->y-boss_y)<=1))boss_health--,flag=true;
			if(temp->x>=WIDTH)flag=true;
			if(flag)player_bullet_del(temp);
			temp=nxt;
		}
	}
}
void boss_bullet_move()
{
	if(boss_bullet_head!=NULL)
	{
		bullet *temp=boss_bullet_head;
		while(temp!=NULL)
		{
			temp->x--;
			bullet *nxt=temp->nxt;
			bool flag=false;
			if((temp->x==player_x)&&(temp->y==player_y))
			{
				player_health--;
			}
			if(temp->x<=0)boss_bullet_del(temp);
			temp=nxt;
		}
	}
}
void process_exit()
{
	system("cls");
	printf("感谢您的游玩");
	Sleep(1000);
	exit(0);
}
void victory()
{
	system("cls");
	printf("congratulations\n你是强者");
	Sleep(5000);
	process_exit();
}
void failed()
{
	system("cls");
	printf("cai");
	Sleep(5000);
	process_exit();
//	if(kbhit()&&getch()=='r')times++,player_health=1;
}
void process()
{
	player_move();
	player_bullet_move();
	boss_move();
	if(choice==2)boss_shoot(),choice=0;
	choice++;
	boss_bullet_move();
	shoot();
	if(boss_health<=0)victory();
	if(player_health<=0)failed();
}

int main()
{
	restart: init();
	while(1)
	{
		process();
		print();
		Sleep(25);
		system("cls");
	//	system("PAUSE");
	}
	return 0;
} 
