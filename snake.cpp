//因为音乐文件过大无法上传，可在.cpp文件同地址中建立res文件夹并将音乐放入其中，并修改音乐文件名
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>



#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")//多媒体设备接口
using namespace std;

#define SNAKE_NUM 500 //蛇的最大节数
IMAGE img;//存储背景图片




enum DIR //蛇的方向
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};
//蛇的结构
struct Snake
{

    int size;//蛇的节数
    int dir;//蛇的方向
    int speed;//蛇的速度
    POINT coor[SNAKE_NUM];//蛇的坐标
}snake;
//食物结构
struct Food
{
    int x;
    int y;
    int r;       //食物大小
    bool flag;   //食物是否存在
    DWORD color; //食物颜色
}food;
//数据的初始化
void GameInit()
{
    //播放背景音乐
    PlaySound(TEXT("./res/1.wav"), NULL, SND_FILENAME | SND_ASYNC);

    //init初始化 graph图形窗口
    initgraph(640, 480);

   
}
    
    
   
   void Snake_foodInit()
{
    //设置随机数种子 GetTickCount()获取系统开机，到现在所经过的毫秒数
    srand(GetTickCount());
    //c初始化蛇
    snake.size = 3;
    snake.speed = 10;
    snake.dir=RIGHT;
    for (int i = 0;i<snake.size;i++)
    {
        snake.coor[i].x = 40-10*i;
        snake.coor[i].y = 10;
    }

    //初始化食物 rand()随机产生一个整数，如果没有设置随机数种子，每次产生的都是国定的整数,设置种子需要头文件
    food.x = rand() % 640;
    food.y = rand() % 480;
    food.color = RGB(rand() % 256, rand() % 256, rand() % 256, );
    food.r = 5;
    food.flag = true;
}
void GameDraw()
{
    //双缓冲绘图
    BeginBatchDraw();
    
    
    cleardevice();
    
    //绘制蛇
    setfillcolor(BLUE);
    for (int i = 0; i < snake.size; i++)
    {
        solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
    }
    if (food.flag)
    {
        solidcircle(food.x, food.y,food.r);
      
    }
    int score = 0; //得分
    score = (snake.size - 3) * 10;
    char s[5];
    settextcolor(RED);
    settextstyle(15, 0, "STCAIYUN");
    outtextxy(30,10, "贪吃蛇小游戏");
    outtextxy(30, 30, "王勇杰制作");
    sprintf_s(s, "%d", score);
    outtextxy(30, 50, "得分：");
    outtextxy(80, 50, s);
    
    EndBatchDraw();
   
    
}

//移动蛇
void snakeMove()
{
    for (int i = snake.size-1; i>0; i--)
    {
        snake.coor[i] = snake.coor[i - 1];
       
    }
    switch (snake.dir)
    {
    case UP:
        snake.coor[0].y-=snake.speed;
        if (snake.coor[0].y +10<= 0)
        {
            snake.coor[0].y = 480;//待优化
        }
        break;
    case DOWN:
        snake.coor[0].y+= snake.speed;
        if (snake.coor[0].y -10>= 480)
        {
            snake.coor[0].y = 0;//待优化
        }
        break;
    case LEFT:
        snake.coor[0].x-= snake.speed;
        if (snake.coor[0].x +10<= 0)
        {
            snake.coor[0].x = 640;//待优化
        }
        break;
    case RIGHT:
        snake.coor[0].x+= snake.speed;
        if (snake.coor[0].x -10>= 640)
        {
            snake.coor[0].x = 0;//待优化
        }
        break;
    }
}

//通过方向键改变蛇的移动方向
void keyControl()
{
    //判断是否有按键,如果有返回真
    if (_kbhit())
    {
        //72 80 75 77 上下左右
        switch (_getch())
        {
        case 'w':
        case 'W':
        case 72:
            if (snake.dir != DOWN)//不能掉投诉
            {
                snake.dir = UP;
            }
            break;
        case 's':
        case 'S':
        case 80:
            if (snake.dir != UP)
            {
                snake.dir = DOWN;
            }
            break;
        case 'a':
        case 'A':
        case 75:
            if (snake.dir != RIGHT)
            {
                snake.dir = LEFT;
            }
            break;
        case 'd':
        case 'D':
        case 77:
            if (snake.dir != LEFT)
            {
                snake.dir = RIGHT;
            }
            break;
        case ' '://空格实现游戏暂停
            while (1)
            {
                if (_getch() == ' ')
                    return;
            }
        }
    }
}
void EatFood()
{
    {
        if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r && snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
        {
            food.flag = false;
            snake.size++;
        }
    }
    //如果吃掉食物则重新生成一个食物
    if (!food.flag)
    {
        food.x = rand() % 640;
        food.y = rand() % 480;
        food.color = RGB(rand() % 256, rand() % 256, rand() % 256, );
        food.r = 5;
        food.flag = true;

    }
    
    
}



int main(void)//主函数
{
    int a_if = 0;
    GameInit();
    while (1) {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'G':
            case 'g':
                Snake_foodInit();

                while (1)
                {
                    GameDraw();
                    snakeMove();
                    Sleep(80);
                    EatFood();
                    keyControl();
                }
            }
        }
        else
        {
            BeginBatchDraw();


            cleardevice();
            setbkcolor(RGB(28, 115, 119));
            settextcolor(RED);
            settextstyle(20, 0, "STCAIYUN");
            outtextxy(100, 100, "贪吃蛇小游戏");
            outtextxy(100, 140, "按空格暂停游戏");
            outtextxy(100, 180, "默认可越边界");
            outtextxy(100, 180, "按G or g开始游戏");
            if (_kbhit())
            {
                switch (_getch())
                {
                case 'G':
                case 'g':
                    Snake_foodInit();
                    while (1)
                    {
                        GameDraw();
                        snakeMove();
                        Sleep(80);
                        EatFood();
                        keyControl();
                    }
                }
            }
            EndBatchDraw();
           
                
            
        }
    }


    return 0;
}
