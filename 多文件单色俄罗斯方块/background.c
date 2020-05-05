﻿#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include"background.h"
#include"mytetris.h"
#include"myconsole.h"
extern Level;
extern Score;
extern Line;
#define FrameX  16  //游戏窗口左上角的X轴坐标
#define FrameY  4  //游戏窗口左上角的Y轴坐标
#define height  20 //游戏窗口的高度
#define width   10//游戏窗口的宽度
#define StartX  1+width/2//俄罗斯方块中心出现位置横坐标 
#define StartY  2//俄罗斯方块中心出现位置纵坐标 
/****************************************
* 打印俄罗斯方块边框
****************************************/
void DrwaGameframe()
{
    int i = 0;
    GotoXY(FrameX + width - 5, FrameY - 2);
    printf("俄 罗 斯 方 块");
    for (i = 1; i <= width; i++)
    {
        GotoXY(FrameX + 2 * i, FrameY);//打印上横框
        printf("■");
        GotoXY(FrameX + 2 * i, FrameY + height + 1);//打印下横框
        printf("■");
        a[height + 1][i] = 1;
    }
    for (i = 0; i <= height + 1; i++)
    {
        GotoXY(FrameX, FrameY + i);//打印左竖框
        printf("■");
        GotoXY(FrameX + 2 * width + 2, FrameY + i);//打印右竖框
        printf("■");
        a[i][0] = 1;
        a[i][width + 1] = 1;
    }
    GotoXY(FrameX + 2 * width + 8, FrameY - 1);
    printf("Level:%d", Level);
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    printf("积分:%d", Score);
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    printf("消去的行数:%d", Line);
}
/****************************************
* 游戏开始界面
****************************************/
void FacePlate()
{
    printf("\n\n\n");
    printf("                           俄  罗  斯  方  块             \n");
    printf("\n\n");
    printf("                  ■                         ■           \n");
    printf("                  ■■   ■■       ■■     ■         ■\n");
    printf("                  ■       ■■     ■■     ■     ■■■\n");
    printf("                                             ■           \n");
    printf("\n\n");
    printf("                         1.开始游戏   2.按键说明          \n");
    printf("\n\n");
    printf("                         3.游戏规则   4.退出游戏          \n");
    printf("\n\n");
    printf("                           请选择[1 2 3 4]:");
}
/****************************************
* 游戏结束界面
****************************************/
void GameOver()
{
    int n;
    system("cls");
    printf("\n\n\n\n\n\n\n\n");
    printf("          ■■■      ■       ■    ■   ■■■■        ■■    ■      ■ ■■■■   ■■■  \n");
    printf("        ■           ■■     ■ ■■ ■  ■            ■    ■   ■    ■  ■         ■   ■ \n");
    printf("        ■   ■■   ■  ■   ■   ■   ■ ■■■       ■      ■   ■  ■   ■■■     ■■■  \n");
    printf("        ■     ■  ■■■■  ■   ■   ■ ■            ■    ■     ■■    ■         ■   ■ \n");
    printf("          ■■■  ■      ■ ■   ■   ■ ■■■■        ■■        ■     ■■■■   ■    ■\n");
    printf("\n\n\n\n\n");
    printf("                                       1:再玩一局          2:退出游戏                             ");
    printf("\n\n");
    printf("                                                 选择[1/2]:");
    scanf_s("%d", &n);
    switch (n)
    {
    case 1:GamePlay(); break;
    case 2:exit(0); break;
    }
}
/****************************************
* 游戏按键介绍界面
****************************************/
void Explation()
{
    system("cls");
    printf("\n\n\n");
    printf("                                    按键说明                \n\n\n");
    printf("                ************************************************\n");
    printf("                *   tip1: 玩家可以通过 ← →方向键来移动方块   *\n");
    printf("                *                                              *\n");
    printf("                *   tip2: 通过 ↑使方块旋转                    *\n");
    printf("                *                                              *\n");
    printf("                *   tip3: 通过 ↓加速方块下落                  *\n");
    printf("                *                                              *\n");
    printf("                *   tip4: 按空格键暂停游戏，再按空格键继续     *\n");
    printf("                *                                              *\n");
    printf("                *   tip5: 按ESC退出游戏，按tab键暂停/播放音乐  *\n");
    printf("                ************************************************\n");
    _getch();//按任意键返回主界面
    system("cls");
    Welcom();
}
/****************************************
* 游戏规则介绍界面
****************************************/
void Regulation()
{
    system("cls");
    GotoXY(0, 3);
    printf("                                         按键说明                     \n\n\n");
    printf("                **********************************************************\n");
    printf("                *   tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整   *\n");
    printf("                *         方块的位置和方向，使他们在屏幕底部拼出完整的   *\n");
    printf("                *         一条或几条                                     *\n");
    printf("                *                                                        *\n");
    printf("                *   tip2: 每消除一行，积分增加100                        *\n");
    printf("                *                                                        *\n");
    printf("                *   tip3: 每累计1000分，会提升一个等级                   *\n");
    printf("                *                                                        *\n");
    printf("                *   tip4: 提升等级会使方块下落速度加快，游戏难度加大     *\n");
    printf("                **********************************************************\n");
    _getch();//按任意键返回主界面
    system("cls");
    Welcom();
}
/****************************************
* 游戏欢迎界面
****************************************/
void Welcom()
{
    int n = 0;
    HideCursor();
    FacePlate();
    PlayMusic();
    scanf_s("%d", &n);//输入选项
    switch (n)
    {
    case 1:GamePlay(); break;//游戏开始 
    case 2:Explation(); break;//按键说明函数 
    case 3:Regulation(); break;//游戏规则 
    case 4:exit(0); break;//关闭游戏 
    }
}