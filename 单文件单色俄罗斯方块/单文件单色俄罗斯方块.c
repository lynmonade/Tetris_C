#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define FrameX  16    //��Ϸ�������Ͻǵ�X������
#define FrameY  4  //��Ϸ�������Ͻǵ�Y������
#define height  20 //��Ϸ���ڵĸ߶�
#define width   10//��Ϸ���ڵĿ��
#define StartX  1+width/2//����˹�������ĳ���λ�ú����� 
#define StartY  2//����˹�������ĳ���λ��������
extern time1, time2;
int Line = 0;//���������� 
int Level = 1;//�ȼ�
int Score = 0;//����
int a[height + 2][width + 2] = { 0 };//����˹������������
int Music = 1;
typedef struct
{
    int kind_current;//��ǰ��������
    int state_current;//��ǰ����״̬
    int kind_next;//��һ��������
    int state_next;//��һ����״̬
    int left;//1Ϊ�����ƣ�0Ϊ�������� 
    int right;//1Ϊ�����ƣ�0Ϊ��������
    int down;//1Ϊ�����ƣ�0Ϊ��������
    int trans;//1Ϊ����ת��0Ϊ������ת 
    int X;//���ķ��������
    int Y;//���ķ���������
    int temp[7][4][5][5];//����˹������������ 
}MyTetris;
//��*********��*********��**************����*******����***����
//������***������***������***��������*****����***����*****����
MyTetris tetris =
{
    0, 0, 0, 0, 1, 1, 1, 1, StartX, StartY,
    { {
        { { 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } }
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0 } },
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0 } },
    }, {
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } },
        { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0 } }
    } }
};
MyTetris *pt = &tetris;
long time1, time2;
void Welcom();
void GamePlay();
/****************************************
* ȷ����Ļ���λ��
****************************************/
void GotoXY(int x, int y)
{
    COORD pos;
    pos.X = x;//������
    pos.Y = y;//������
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/****************************************
* ������Ļ���
****************************************/
void HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = 0; //���ؿ���̨���
    SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}
/****************************************
* ���ִ򿪲����ź���
****************************************/
void PlayMusic()
{
    mciSendString(TEXT("open D:\\Music\\˦�и�.mp3 alias Song1"), NULL, 0, NULL);
    mciSendString(TEXT("play Song1 repeat"), NULL, 0, NULL);
}
/****************************************
* �������²��ź���
****************************************/
void RestartMusic()
{
    mciSendString(TEXT("resume Song1"), NULL, 0, NULL);
}
/****************************************
* ������ͣ���ź���
****************************************/
void PauseMusic()
{
    mciSendString(TEXT("pause Song1"), NULL, 0, NULL);
}
/****************************************
* ��ӡ����˹����߿�
****************************************/
void DrwaGameframe()
{
    int i = 0;
    GotoXY(FrameX + width - 5, FrameY - 2);
    printf("�� �� ˹ �� ��");
    for (i = 1; i <= width; i++)
    {
        GotoXY(FrameX + 2 * i, FrameY);//��ӡ�Ϻ��
        printf("��");
        GotoXY(FrameX + 2 * i, FrameY + height + 1);//��ӡ�º��
        printf("��");
        a[height + 1][i] = 1;
    }
    for (i = 0; i <= height + 1; i++)
    {
        GotoXY(FrameX, FrameY + i);//��ӡ������
        printf("��");
        GotoXY(FrameX + 2 * width + 2, FrameY + i);//��ӡ������
        printf("��");
        a[i][0] = 1;
        a[i][width + 1] = 1;
    }
    GotoXY(FrameX + 2 * width + 8, FrameY - 1);
    printf("Level:%d", Level);
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    printf("����:%d", Score);
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    printf("��ȥ������:%d", Line);
}
/****************************************
* ��Ϸ��ʼ����
****************************************/
void FacePlate()
{
    printf("\n\n\n");
    printf("                           ��  ��  ˹  ��  ��             \n");
    printf("\n\n");
    printf("                  ��                         ��           \n");
    printf("                  ����   ����       ����     ��         ��\n");
    printf("                  ��       ����     ����     ��     ������\n");
    printf("                                             ��           \n");
    printf("\n\n");
    printf("                         1.��ʼ��Ϸ   2.����˵��          \n");
    printf("\n\n");
    printf("                         3.��Ϸ����   4.�˳���Ϸ          \n");
    printf("\n\n");
    printf("                           ��ѡ��[1 2 3 4]:");
}
/****************************************
* ��Ϸ��������
****************************************/
void GameOver()
{
    int n;
    system("cls");
    printf("\n\n\n\n\n\n\n\n");
    printf("          ������      ��       ��    ��   ��������        ����    ��      �� ��������   ������  \n");
    printf("        ��           ����     �� ���� ��  ��            ��    ��   ��    ��  ��         ��   �� \n");
    printf("        ��   ����   ��  ��   ��   ��   �� ������       ��      ��   ��  ��   ������     ������  \n");
    printf("        ��     ��  ��������  ��   ��   �� ��            ��    ��     ����    ��         ��   �� \n");
    printf("          ������  ��      �� ��   ��   �� ��������        ����        ��     ��������   ��    ��\n");
    printf("\n\n\n\n\n");
    printf("                                       1:����һ��          2:�˳���Ϸ                             ");
    printf("\n\n");
    printf("                                                 ѡ��[1/2]:");
    scanf("%d", &n);
    switch (n)
    {
    case 1:GamePlay(); break;
    case 2:exit(0); break;
    }
}
/****************************************
* ��Ϸ�������ܽ���
****************************************/
void Explation()
{
    system("cls");
    printf("\n\n\n");
    printf("                                    ����˵��                \n\n\n");
    printf("                ************************************************\n");
    printf("                *   tip1: ��ҿ���ͨ�� �� ����������ƶ�����   *\n");
    printf("                *                                              *\n");
    printf("                *   tip2: ͨ�� ��ʹ������ת                    *\n");
    printf("                *                                              *\n");
    printf("                *   tip3: ͨ�� �����ٷ�������                  *\n");
    printf("                *                                              *\n");
    printf("                *   tip4: ���ո����ͣ��Ϸ���ٰ��ո������     *\n");
    printf("                *                                              *\n");
    printf("                *   tip5: ��ESC�˳���Ϸ����tab����ͣ/��������  *\n");
    printf("                ************************************************\n");
    getch();//�����������������
    system("cls");
    Welcom();
}
/****************************************
* ��Ϸ������ܽ���
****************************************/
void Regulation()
{
    system("cls");
    GotoXY(0, 3);
    printf("                                         ����˵��                     \n\n\n");
    printf("                **********************************************************\n");
    printf("                *   tip1: ��ͬ��״��С�������Ļ�Ϸ����£����ͨ������   *\n");
    printf("                *         �����λ�úͷ���ʹ��������Ļ�ײ�ƴ��������   *\n");
    printf("                *         һ������                                     *\n");
    printf("                *                                                        *\n");
    printf("                *   tip2: ÿ����һ�У���������100                        *\n");
    printf("                *                                                        *\n");
    printf("                *   tip3: ÿ�ۼ�1000�֣�������һ���ȼ�                   *\n");
    printf("                *                                                        *\n");
    printf("                *   tip4: �����ȼ���ʹ���������ٶȼӿ죬��Ϸ�ѶȼӴ�     *\n");
    printf("                **********************************************************\n");
    getch();//�����������������
    system("cls");
    Welcom();
}
/****************************************
* ��Ϸ��ӭ����
****************************************/
void Welcom()
{
    int n = 0;
    HideCursor();
    FacePlate();
    PlayMusic();
    scanf("%d", &n);//����ѡ��
    switch (n)
    {
    case 1:GamePlay(); break;//��Ϸ��ʼ 
    case 2:Explation(); break;//����˵������ 
    case 3:Regulation(); break;//��Ϸ���� 
    case 4:exit(0); break;//�ر���Ϸ 
    }
}
/****************************************
* ��Ϸ������ʼ��
****************************************/
void Initialization()
{
    int i = 0, j = 0;
    pt->kind_current = rand() % 7;
    pt->kind_next = rand() % 7;
    pt->state_current = rand() % 4;
    pt->state_next = rand() % 4;
    pt->left = 1;
    pt->right = 1;
    pt->down = 1;
    pt->trans = 1;
    pt->X = StartX;
    pt->Y = StartY;
    Line = 0;
    Level = 1;
    Score = 0;
    for (i = 1; i <= height + 1; i++)
    for (j = 1; j <= width + 1; j++)a[i][j] = 0;
    for (i = 1; i <= width; i++)a[height + 1][i] = 1;
    for (i = 0; i <= height + 1; i++)
    {
        a[i][0] = 1;
        a[i][width + 1] = 1;
    }
}
/****************************************
* ���ɶ���˹����
****************************************/
void MakeTetris()
{
    srand(time(NULL));
    pt->kind_current = pt->kind_next;
    pt->state_current = pt->state_next;
    pt->kind_next = rand() % 7;
    pt->state_next = rand() % 4;
}
/****************************************
* ��ӡ������˹����
****************************************/
void PrintTetris()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
        a[pt->Y - 2 + i][pt->X - 2 + j] += pt->temp[pt->kind_current][pt->state_current][i][j];
    for (i = 1; i <= height; i++)
    {
        GotoXY(FrameX + 2, FrameY + i);
        for (j = 1; j <= width; j++)
        if (a[i][j])printf("��");
        else printf("  ");
    }
}
/****************************************
* ����ɵĶ���˹����
****************************************/
void CleanOld()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    if (pt->temp[pt->kind_current][pt->state_current][i][j])
    {
        a[pt->Y - 2 + i][pt->X - 2 + j] = 0;
        GotoXY(FrameX + 2 * pt->X - 4 + 2 * j, FrameY + pt->Y - 2 + i);
        printf("  ");
    }
}
/****************************************
* ��ӡ�µĶ���˹����
****************************************/
void DrawNew()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    if (pt->temp[pt->kind_current][pt->state_current][i][j])
    {
        a[pt->Y + i - 2][pt->X + j - 2] = pt->temp[pt->kind_current][pt->state_current][i][j];
        GotoXY(FrameX + 2 * pt->X - 4 + 2 * j, FrameY + pt->Y - 2 + i);
        printf("��");
    }
}
/****************************************
* ��ת����˹����
****************************************/
void Transform()
{
    if (pt->state_current != 3)pt->state_current++;
    else pt->state_current = 0;
}
/****************************************
* �ж϶���˹�����Ƿ���ƶ��ͱ���
****************************************/
void Judge_MoveAndTansform()
{
    int t;
    switch (pt->kind_current)
    {
    case 0:
    case 1:
    case 2:t = 4 * pt->kind_current + pt->state_current + 1; break;
    case 3:
    case 4:
    case 5:t = 2 * pt->kind_current + pt->state_current % 2 + 7; break;
    case 6:t = 19; break;
    }
    switch (t)
    {
    case 1:
        if (a[pt->Y - 1][pt->X - 2] == 0 && a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 2:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 3:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 4:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 5:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 6:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 7:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 8:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 9:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y - 1][pt->X] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 10:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 11:
        if (a[pt->Y][pt->X - 2] == 0 && a[pt->Y + 1][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 12:
        if (a[pt->Y - 1][pt->X - 2] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 2][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 13:
        if (a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 3] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 2][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 14:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 2][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 3][pt->X] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 15:
        if (a[pt->Y - 1][pt->X - 2] == 0 && a[pt->Y][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 16:
        if (a[pt->Y - 1][pt->X] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y - 1][pt->X] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 17:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 2] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 2] == 0 && a[pt->Y][pt->X + 1] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0 && a[pt->Y][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y][pt->X + 1] == 0 && a[pt->Y + 1][pt->X + 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 18:
        if (a[pt->Y - 1][pt->X - 1] == 0 && a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 1][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        if (a[pt->Y - 1][pt->X + 1] == 0 && a[pt->Y][pt->X - 1] == 0)pt->trans = 1; else pt->trans = 0;
        break;
    case 19:
        if (a[pt->Y][pt->X - 1] == 0 && a[pt->Y + 1][pt->X - 1] == 0)pt->left = 1; else pt->left = 0;
        if (a[pt->Y][pt->X + 2] == 0 && a[pt->Y + 1][pt->X + 2] == 0)pt->right = 1; else pt->right = 0;
        if (a[pt->Y + 2][pt->X] == 0 && a[pt->Y + 2][pt->X + 1] == 0)pt->down = 1; else pt->down = 0;
        pt->trans = 0;
        break;
    default:break;
    }
}
/****************************************
* �ؼ�������ʾ����(���ڵ���)
****************************************/
void JustForDebugging()
{
    int i = 0, j = 0;
    for (i = 0; i < height + 2; i++)
    {
        GotoXY(FrameX + 2 * width + 24, FrameY + i);
        for (j = 0; j < width + 2; j++)printf("%d", a[i][j]);
    }
    GotoXY(FrameX + 3 * width + 30, FrameY + 2);
    printf("X=%2d", pt->X);
    GotoXY(FrameX + 3 * width + 30, FrameY + 3);
    printf("Y=%2d", pt->Y);
    GotoXY(FrameX + 3 * width + 30, FrameY + 4);
    printf("Left=%d", pt->left);
    GotoXY(FrameX + 3 * width + 30, FrameY + 5);
    printf("Right=%d", pt->right);
    GotoXY(FrameX + 3 * width + 30, FrameY + 6);
    printf("Down=%d", pt->down);
    GotoXY(FrameX + 3 * width + 30, FrameY + 7);
    printf("Trans=%d", pt->trans);
}

/****************************************
* ��ӡ��һ������˹����
****************************************/
void PrintNextTetris()
{
    int i = 0, j = 0;
    GotoXY(FrameX + 2 * width + 8, FrameY + 5);
    printf("��һ������:%2d", pt->kind_next);
    for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
    {
        GotoXY(FrameX + 2 * width + 2 * j + 8, FrameY + 6 + i);
        if (pt->temp[pt->kind_next][pt->state_next][i][j])printf("��");
        else printf("  ");
    }
}
/****************************************
* �������
****************************************/
void CleanLine()
{
    int i = height, j = 1, k = 0, sum = 0;
    for (i = height; i > 0; i--)
    {
        sum = 0;
        for (j = 1; j <= width; j++)sum += a[i][j];
        if (sum == width)
        {
            Line++;
            for (k = i; k > 1; k--)
            for (j = 1; j <= width; j++)a[k][j] = a[k - 1][j];
            i++;
        }
    }
    Level = 1 + Line / 10;
    Score = Line * 100;
    GotoXY(FrameX + 2 * width + 8, FrameY - 1);
    printf("Level:%d", Level);
    GotoXY(FrameX + 2 * width + 8, FrameY + 1);
    printf("����:%d", Score);
    GotoXY(FrameX + 2 * width + 8, FrameY + 3);
    printf("��ȥ������:%d", Line);
}
/****************************************
* �Զ����亯��
****************************************/
void AutoDown()
{
    int i = 0, j = 0;
    time2 = clock();
    if (time2 - time1 > 1000 - 100 * Level)
    {
        Judge_MoveAndTansform();
        if (pt->down)
        {
            CleanOld();
            pt->Y++;
            DrawNew();
            //JustForDebugging();
        }
        if (!pt->down)
        {
            CleanLine();
            pt->X = StartX;
            pt->Y = StartY;
            MakeTetris();
            Judge_MoveAndTansform();
            if (!pt->down)
            {
                PrintTetris();
                Sleep(2000);//ͣ������
                GameOver();
            }
            PrintTetris();
            PrintNextTetris();
        }
        //JustForDebugging();
        time1 = clock();
    }
}
/****************************************
* ���������ж�
****************************************/
void KeyControl()
{
    int i = 0, j = 0, ch = 0;
    if (_kbhit())
    {
        ch = getch();
        Judge_MoveAndTansform();
        switch (ch)
        {
        case 72:if (pt->trans){ CleanOld(); Transform(); DrawNew(); }break;//����
        case 75:if (pt->left){ CleanOld(); pt->X--; DrawNew(); }break;//����
        case 77:if (pt->right){ CleanOld(); pt->X++; DrawNew(); }break;//->����
        case 80:if (pt->down){ CleanOld(); pt->Y++; DrawNew(); }break;//����
        case 32:getch(); break;//�ո�� ��ͣ��Ϸ
        case 9: Music = -Music;
            if (Music > 0)RestartMusic();
            else RestartMusic(); break;//tap�� ��ͣ����
        case 27:system("cls"); exit(0); break;//ESC�� �˳� 
        default:break;
        }
    }
}
/****************************************
* ��Ϸ��ʼ����
****************************************/
void GamePlay()
{
    system("cls");
    Initialization();
    DrwaGameframe();
    MakeTetris();
    DrawNew();
    PrintNextTetris();
    time1 = clock();
    while (1)
    {
        KeyControl();
        //JustForDebugging();
        AutoDown();
    }
}
int main()
{
    Welcom();
    return 0;
}