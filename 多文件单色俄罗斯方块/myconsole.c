#include<time.h>
#include<windows.h>
#include"myconsole.h"
long time1, time2;
/****************************************
* ʱ���ȡ����
****************************************/
long GetTime()
{
    return clock();
}
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