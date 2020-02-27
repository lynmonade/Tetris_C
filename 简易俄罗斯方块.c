#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define FrameX  16  //��Ϸ�������Ͻǵ�X������
#define FrameY  4  //��Ϸ�������Ͻǵ�Y������
#define height  20 //��Ϸ���ڵĸ߶�
#define width   10//��Ϸ���ڵĿ�� 
#define StartX  1+width/2//����˹�������ĳ���λ�ú����� 
#define StartY  2//����˹�������ĳ���λ�������� 

int s[5][5]={0};//����˹������������ 
int a[height+2][width+2]={0};//����˹�����ӡ����
int flag_old=0;	//��ǰ����˹������� 
int flag_next=0;//��һ������˹������� 
int left=1;	//1Ϊ�����ƣ�0Ϊ�������� 
int right=1;//1Ϊ�����ƣ�0Ϊ��������
int down=1;	//1Ϊ�����ƣ�0Ϊ��������
int trans=1;//1Ϊ����ת��0Ϊ������ת 
int X=StartX;//���ķ��������
int Y=StartY;//���ķ���������
int Line=0;	//���������� 
int Level=1;//�ȼ�
int Score=0;//����
int Music=1;
clock_t start_t,end_t;	//��ȡϵͳʱ�� 

void GameOver();
void Welcom();
/****************************************
 * ȷ����Ļ���λ��
****************************************/
void gotoxy(int x, int y)
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
 * ���ɶ���˹���� 
****************************************/
void MakeTetris()
{
	int i=0,j=0;
	srand(time(NULL));
	if(flag_old==0)flag_old=rand()%19+1;
	else flag_old=flag_next;
	flag_next=rand()%19+1;
	for(i=0;i<5;i++)for(j=0;j<5;j++)s[i][j]=0;		
	switch(flag_old)
	{
		case  1:s[1][1]=1;s[2][1]=1;s[2][2]=1;s[2][3]=1;break;//��
		case  2:s[1][2]=1;s[1][3]=1;s[2][2]=1;s[3][2]=1;break;//������
		case  3:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[3][3]=1;break;
		case  4:s[1][2]=1;s[2][2]=1;s[3][1]=1;s[3][2]=1;break;
	
		case  5:s[1][2]=1;s[2][1]=1;s[2][2]=1;s[2][3]=1;break;//  ��
		case  6:s[1][2]=1;s[2][2]=1;s[2][3]=1;s[3][2]=1;break;//������
		case  7:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[3][2]=1;break;//
		case  8:s[1][2]=1;s[2][1]=1;s[2][2]=1;s[3][2]=1;break;

		case  9:s[1][3]=1;s[2][1]=1;s[2][2]=1;s[2][3]=1;break;//    ��
		case 10:s[1][2]=1;s[2][2]=1;s[3][2]=1;s[3][3]=1;break;//������
		case 11:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[3][1]=1;break;
		case 12:s[1][1]=1;s[1][2]=1;s[2][2]=1;s[3][2]=1;break;
		
		case 13:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[2][4]=1;break;//��������
		case 14:s[1][2]=1;s[2][2]=1;s[3][2]=1;s[4][2]=1;break;
		
		case 15:s[1][1]=1;s[1][2]=1;s[2][2]=1;s[2][3]=1;break;//����
		case 16:s[1][3]=1;s[2][2]=1;s[2][3]=1;s[3][2]=1;break;//  ����
		
		case 17:s[1][2]=1;s[1][3]=1;s[2][1]=1;s[2][2]=1;break;//  ����
		case 18:s[1][2]=1;s[2][2]=1;s[2][3]=1;s[3][3]=1;break;//����
		
		case 19:s[2][2]=1;s[2][3]=1;s[3][2]=1;s[3][3]=1;break;//����
														      //����
		default :break;
	}
}
/****************************************
 * ��ӡ������˹���� 
****************************************/
void PrintTetris()
{
	int i=0,j=0;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)a[Y-2+i][X-2+j]=s[i][j];			
	for(i=1;i<=height;i++)
		{
		gotoxy(FrameX+2,FrameY+i);
		for(j=1;j<=width;j++)
			if(a[i][j])printf("��");
			else printf("  ");
		}
}
/****************************************
 * ����ɵĶ���˹���� 
****************************************/
void CleanOld()
{
	int i=0,j=0;
	switch(flag_old)
	{
		case  1:a[Y-1][X-1]=0;a[Y][X-1]=0;a[Y][X]=0;a[Y][X+1]=0;break;//��
		case  2:a[Y-1][X]=0;a[Y-1][X+1]=0;a[Y][X]=0;a[Y+1][X]=0;break;//������
		case  3:a[Y][X-1]=0;a[Y][X]=0;a[Y][X+1]=0;a[Y+1][X+1]=0;break;
		case  4:a[Y-1][X]=0;a[Y][X]=0;a[Y+1][X-1]=0;a[Y+1][X]=0;break;
	
		case  5:a[Y-1][X]=0;a[Y][X-1]=0;a[Y][X]=0;a[Y][X+1]=0;break;//  ��
		case  6:a[Y-1][X]=0;a[Y][X]=0;a[Y+1][X]=0;a[Y][X+1]=0;break;//������
		case  7:a[Y][X-1]=0;a[Y][X]=0;a[Y][X+1]=0;a[Y+1][X]=0;break;//
		case  8:a[Y-1][X]=0;a[Y][X-1]=0;a[Y][X]=0;a[Y+1][X]=0;break;

		case  9:a[Y-1][X+1]=0;a[Y][X-1]=0;a[Y][X]=0;a[Y][X+1]=0;break;//    ��
		case 10:a[Y-1][X]=0;a[Y][X]=0;a[Y+1][X]=0;a[Y+1][X+1]=0;break;//������
		case 11:a[Y][X-1]=0;a[Y][X]=0;a[Y][X+1]=0;a[Y+1][X-1]=0;break;
		case 12:a[Y-1][X-1]=0;a[Y-1][X]=0;a[Y][X]=0;a[Y+1][X]=0;break;
		
		case 13:a[Y][X-1]=0;a[Y][X]=0;a[Y][X+1]=0;a[Y][X+2]=0;break;//��������
		case 14:a[Y-1][X]=0;a[Y][X]=0;a[Y+1][X]=0;a[Y+2][X]=0;break;
		
		case 15:a[Y-1][X-1]=0;a[Y-1][X]=0;a[Y][X]=0;a[Y][X+1]=0;break;//����
		case 16:a[Y-1][X+1]=0;a[Y][X]=0;a[Y][X+1]=0;a[Y+1][X]=0;break;//  ����
		
		case 17:a[Y-1][X]=0;a[Y-1][X+1]=0;a[Y][X-1]=0;a[Y][X]=0;break;//  ����
		case 18:a[Y-1][X]=0;a[Y][X]=0;a[Y][X+1]=0;a[Y+1][X+1]=0;break;//����
		
		case 19:a[Y][X]=0;a[Y][X+1]=0;a[Y+1][X]=0;a[Y+1][X+1]=0;break;//����
														      		  //����
		default :break;
	}
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(s[i][j]==1)
			{
				a[Y+i-2][X+j-2]=0;
				gotoxy(FrameX+2*X-4+2*j,FrameY+Y-2+i);
				printf("  ");
			}
}
/****************************************
 * ��ӡ�µĶ���˹���� 
****************************************/     
void DrawNew()
{
	int i=0,j=0;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(s[i][j]==1)
			{
				a[Y+i-2][X+j-2]=1;
				gotoxy(FrameX+2*X-4+2*j,FrameY+Y-2+i);
				printf("��");
			}
}
/****************************************
 * ��ת����˹���� 
****************************************/
void Transform()
{
int i=0,j=0;
if(flag_old==4||flag_old==8||flag_old==12)flag_old=flag_old-3;
else if(flag_old==14||flag_old==16||flag_old==18)flag_old=flag_old-1;
else if(flag_old==19)flag_old=19;
else flag_old++;
for(i=0;i<5;i++)
	for(j=0;j<5;j++)s[i][j]=0;
	switch(flag_old)
	{
		case  1:s[1][1]=1;s[2][1]=1;s[2][2]=1;s[2][3]=1;break;//��
		case  2:s[1][2]=1;s[1][3]=1;s[2][2]=1;s[3][2]=1;break;//������
		case  3:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[3][3]=1;break;
		case  4:s[1][2]=1;s[2][2]=1;s[3][1]=1;s[3][2]=1;break;
	
		case  5:s[1][2]=1;s[2][1]=1;s[2][2]=1;s[2][3]=1;break;//  ��
		case  6:s[1][2]=1;s[2][2]=1;s[2][3]=1;s[3][2]=1;break;//������
		case  7:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[3][2]=1;break;//
		case  8:s[1][2]=1;s[2][1]=1;s[2][2]=1;s[3][2]=1;break;

		case  9:s[1][3]=1;s[2][1]=1;s[2][2]=1;s[2][3]=1;break;//    ��
		case 10:s[1][2]=1;s[2][2]=1;s[3][2]=1;s[3][3]=1;break;//������
		case 11:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[3][1]=1;break;
		case 12:s[1][1]=1;s[1][2]=1;s[2][2]=1;s[3][2]=1;break;
		
		case 13:s[2][1]=1;s[2][2]=1;s[2][3]=1;s[2][4]=1;break;//��������
		case 14:s[1][2]=1;s[2][2]=1;s[3][2]=1;s[4][2]=1;break;
		
		case 15:s[1][1]=1;s[1][2]=1;s[2][2]=1;s[2][3]=1;break;//����
		case 16:s[1][3]=1;s[2][2]=1;s[2][3]=1;s[3][2]=1;break;//  ����
		
		case 17:s[1][2]=1;s[1][3]=1;s[2][1]=1;s[2][2]=1;break;//  ����
		case 18:s[1][2]=1;s[2][2]=1;s[2][3]=1;s[3][3]=1;break;//����
		
		case 19:s[2][2]=1;s[2][3]=1;s[3][2]=1;s[3][3]=1;break;//����
														      //����	
		default :break;
	}
}
/****************************************
 * �ж϶���˹�����Ƿ���ƶ��ͱ��� 
****************************************/
void Judge_MoveAndTansform()
{
switch(flag_old)
	{
		case  1:if(a[Y-1][X-2]==0&&a[Y][X-2]==0)left=1;else left=0;										//��
				if(a[Y-1][X]==0&&a[Y][X+2]==0)right=1;else right=0;										//������
				if(a[Y+1][X-1]==0&&a[Y+1][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;
				if(a[Y-1][X]==0&&a[Y-1][X+1]==0&&a[Y+1][X]==0)trans=1;else trans=0;
				break;
		case  2:if(a[Y-1][X-1]==0&&a[Y][X-1]==0&&a[Y+1][X-1]==0)left=1;else left=0;  					//����
				if(a[Y-1][X+2]==0&&a[Y][X+1]==0&&a[Y+1][X+1]==0)right=1;else right=0;					//��
				if(a[Y+2][X]==0&&a[Y][X+1]==0)down=1;else down=0;					 					//��
				if(a[Y][X-1]==0&&a[Y][X+1]==0&&a[Y+1][X+1]==0)trans=1;else trans=0;
				break;
		case  3:if(a[Y][X-2]==0&&a[Y+1][X]==0)left=1;else left=0;										//������
				if(a[Y][X+2]==0&&a[Y+1][X+2]==0)right=1;else right=0;									//    ��
				if(a[Y+1][X-1]==0&&a[Y+1][X]==0&&a[Y+2][X+1]==0)down=1;else down=0;
				if(a[Y-1][X]==0&&a[Y+1][X-1]==0&&a[Y+1][X]==0)trans=1;else trans=0;
				break;
		case  4:if(a[Y-1][X-1]==0&&a[Y][X-1]==0&&a[Y+1][X-2]==0)left=1;else left=0;	 					//  ��
				if(a[Y-1][X+1]==0&&a[Y][X+1]==0&&a[Y+1][X+1]==0)right=1;else right=0;					//  ��
				if(a[Y+2][X-1]==0&&a[Y+2][X]==0)down=1;else down=0;					 					//����
				if(a[Y-1][X-1]==0&&a[Y][X-1]==0&&a[Y][X+1]==0)trans=1;else trans=0;
				break;
		case  5:if(a[Y-1][X-1]==0&&a[Y][X-2]==0)left=1;else left=0;				    					//  ��
				if(a[Y-1][X+1]==0&&a[Y][X+2]==0)right=1;else right=0;									//������
				if(a[Y+1][X-1]==0&&a[Y+1][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;
				if(a[Y+1][X]==0)trans=1;else trans=0;
				break;
		case  6:if(a[Y-1][X-1]==0&&a[Y][X-1]==0&&a[Y+1][X-1]==0)left=1;else left=0;	 					//��
				if(a[Y-1][X+1]==0&&a[Y][X+2]==0&&a[Y+1][X+1]==0)right=1;else right=0;					//����
				if(a[Y+2][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;					 					//��
				if(a[Y][X-1]==0)trans=1;else trans=0;
				break;
		case  7:if(a[Y][X-2]==0&&a[Y+1][X-1]==0)left=1;else left=0;	 						 			//������
				if(a[Y][X+2]==0&&a[Y+1][X+1]==0)right=1;else right=0;						 			//  ��
				if(a[Y+1][X-1]==0&&a[Y+2][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;
				if(a[Y-1][X]==0)trans=1;else trans=0;
				break;
		case  8:if(a[Y-1][X-1]==0&&a[Y][X-2]==0&&a[Y+1][X-1]==0)left=1;else left=0;	 					//  ��
				if(a[Y-1][X+1]==0&&a[Y][X+1]==0&&a[Y+1][X+1]==0)right=1;else right=0;					//����
				if(a[Y+1][X-1]==0&&a[Y+2][X]==0)down=1;else down=0;										//  ��
				if(a[Y][X+1]==0)trans=1;else trans=0;
				break;
		case  9:if(a[Y][X-2]==0&&a[Y-1][X]==0)left=1;else left=0;										//    ��
				if(a[Y-1][X+2]==0&&a[Y][X+2]==0)right=1;else right=0;									//������
				if(a[Y+1][X-1]==0&&a[Y+1][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;
				if(a[Y-1][X]==0&&a[Y+1][X]==0&&a[Y+1][X+1]==0)trans=1;else trans=0;
				break;
		case 10:if(a[Y-1][X-1]==0&&a[Y][X-1]==0&&a[Y+1][X-1]==0)left=1;else left=0;  					//��
				if(a[Y-1][X+1]==0&&a[Y][X+1]==0&&a[Y+1][X+2]==0)right=1;else right=0;					//��
				if(a[Y+2][X]==0&&a[Y+2][X+1]==0)down=1;else down=0;										//����
				if(a[Y][X-1]==0&&a[Y+1][X-1]==0&&a[Y][X+1]==0)trans=1;else trans=0;
				break;		
		case 11:if(a[Y][X-2]==0&&a[Y+1][X-2]==0)left=1;else left=0;					 					//������
				if(a[Y][X+2]==0&&a[Y+1][X]==0)right=1;else right=0;					 					//��
				if(a[Y+2][X-1]==0&&a[Y+1][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;
				if(a[Y-1][X-1]==0&&a[Y-1][X]==0&&a[Y+1][X]==0)trans=1;else trans=0;
				break;
		case 12:if(a[Y-1][X-2]==0&&a[Y][X-1]==0&&a[Y+1][X-1]==0)left=1;else left=0;  					//����
				if(a[Y-1][X+1]==0&&a[Y][X+1]==0&&a[Y+1][X+1]==0)right=1;else right=0;					//  ��
				if(a[Y][X-1]==0&&a[Y+2][X]==0)down=1;else down=0;					 					//  ��
				if(a[Y-1][X+1]==0&&a[Y][X-1]==0&&a[Y][X+1]==0)trans=1;else trans=0;
				break;
		case 13:if(a[Y][X-2]==0)left=1;else left=0;														//��������
				if(a[Y][X+3]==0)right=1;else right=0;										
				if(a[Y+1][X-1]==0&&a[Y+1][X]==0&&a[Y+1][X+1]==0&&a[Y+1][X+2]==0)down=1;else down=0;
				if(a[Y-1][X]==0&&a[Y+1][X]==0&&a[Y+2][X]==0)trans=1;else trans=0;
				break;
		case 14:if(a[Y-1][X-1]==0&&a[Y][X-1]==0&&a[Y+1][X-1]==0&&a[Y+2][X-1]==0)left=1;else left=0;		//��
				if(a[Y-1][X+1]==0&&a[Y][X+1]==0&&a[Y+1][X+1]==0&&a[Y+2][X+1]==0)right=1;else right=0;	//��
				if(a[Y+3][X]==0)down=1;else down=0;														//��
				if(a[Y][X-1]==0&&a[Y][X+1]==0&&a[Y][X+2]==0)trans=1;else trans=0;						//��
				break;
		case 15:if(a[Y-1][X-2]==0&&a[Y][X-1]==0)left=1;else left=0;										//����
				if(a[Y-1][X+1]==0&&a[Y][X+2]==0)right=1;else right=0;									//  ����
				if(a[Y][X-1]==0&&a[Y+1][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;
				if(a[Y-1][X+1]==0&&a[Y+1][X]==0)trans=1;else trans=0;
				break;
		case 16:if(a[Y-1][X]==0&&a[Y][X-1]==0&&a[Y+1][X-1]==0)left=1;else left=0;						//  ��
				if(a[Y-1][X+2]==0&&a[Y][X+2]==0&&a[Y+1][X+1]==0)right=1;else right=0;					//����
				if(a[Y+2][X]==0&&a[Y+1][X+1]==0)down=1;else down=0;										//��
				if(a[Y-1][X-1]==0&&a[Y-1][X]==0)trans=1;else trans=0;
				break;
		case 17:if(a[Y-1][X-1]==0&&a[Y][X-2]==0)left=1;else left=0; 									//  ����
				if(a[Y-1][X+2]==0&&a[Y][X+1]==0)right=1;else right=0;									//����
				if(a[Y+1][X-1]==0&&a[Y+1][X]==0&&a[Y][X+1]==0)down=1;else down=0;
				if(a[Y][X+1]==0&&a[Y+1][X+1]==0)trans=1;else trans=0;
				break;
		case 18:if(a[Y-1][X-1]==0&&a[Y][X-1]==0&&a[Y+1][X]==0)left=1;else left=0;						//��
				if(a[Y-1][X+1]==0&&a[Y][X+2]==0&&a[Y+1][X+2]==0)right=1;else right=0;					//����
				if(a[Y+1][X]==0&&a[Y+2][X+1]==0)down=1;else down=0;										//  ��
				if(a[Y+1][X-1]==0&&a[Y+1][X]==0)trans=1;else trans=0;
				break;
		case 19:if(a[Y][X-1]==0&&a[Y+1][X-1]==0)left=1;else left=0;										//����
				if(a[Y][X+2]==0&&a[Y+1][X+2]==0)right=1;else right=0;									//����
				if(a[Y+2][X]==0&&a[Y+2][X+1]==0)down=1;else down=0;
				trans=0;
				break;
		default :break;
	}
}
/****************************************
 * ���������ж� 
****************************************/
void KeyControl()
{
int i=0,j=0,ch=0;
if(_kbhit())       				  	
	{ 
    	ch=_getch();
    	Judge_MoveAndTansform();
        switch (ch)
            {
            	case 72:if(trans){CleanOld();Transform();DrawNew();}break;//����
            	case 75:if(left){CleanOld();X--;DrawNew();}break;//����
                case 77:if(right){CleanOld();X++;DrawNew();}break;//->����
                case 80:if (down){ CleanOld();Y++; DrawNew(); }break;//����
                case 32:_getch(); break;//�ո�� ��ͣ��Ϸ
                case 9: Music = -Music;
                        if(Music>0)mciSendString(TEXT("resume Song1"), NULL, 0, NULL); 
                        else mciSendString(TEXT("pause Song1"), NULL, 0, NULL);break;//tap�� ��ͣ����
                case 27:system("cls");exit(0);break;//ESC�� �˳� 
                default:break;
            }
	}
}
/****************************************
 * ��ӡ����˹����߿� 
****************************************/
void DrwaGameframe()
{
	int i=0;
	gotoxy(FrameX+width-5,FrameY-2);
	printf("�� �� ˹ �� ��");
 	gotoxy(FrameX,FrameY);
	printf("��");									//��ӡ���
 	gotoxy(FrameX+2*width+2,FrameY);
 	printf("��");
 	gotoxy(FrameX,FrameY+height+1);
 	printf("��");
 	gotoxy(FrameX+2*width+2,FrameY+height+1);
 	printf("��");
	for(i=1;i<=width;i++)
 	{
  		gotoxy(FrameX+2*i,FrameY);
  		printf("��");         						//��ӡ�Ϻ��
 	}
 	for(i=1;i<=width;i++)
 	{
  		gotoxy(FrameX+2*i,FrameY+height+1);
  		printf("��");         						//��ӡ�º��
 	}
 	for(i=1;i<=height;i++)
	{
  		gotoxy(FrameX,FrameY+i);
  		printf("��");        	 					//��ӡ������
 	}
 	for(i=1;i<=height;i++)
 	{
  		gotoxy(FrameX+2*width+2,FrameY+i);
  		printf("��");         						 //��ӡ������ 
    }
    for(i=1;i<=width;i++)
 	{
  		a[height+1][i]=1;
 	}
 	for(i=0;i<=height+1;i++)
	{
  	 	a[i][0]=1;     
		a[i][width+1]=1;
 	}
 	gotoxy(FrameX+2*width+8,FrameY-1);
	printf("Level:%d",Level);
	gotoxy(FrameX+2*width+8,FrameY+1);
	printf("����:%d",Score);
 	gotoxy(FrameX+2*width+8,FrameY+3);
	printf("��ȥ������:%d",Line);
}
/****************************************
 * ��Ϸ������ʼ�� 
****************************************/
void Initialization()
{
	Line = 0;							
	Level = 1;
	Score = 0;
	int i=0,j=0;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)s[i][j]=0;
	for(i=0;i<=height+2;i++)
		for(j=0;j<=width+2;j++)a[i][j]=0;
	for(i=1;i<=width;i++)a[height+1][i]=1;
 	for(i=0;i<=height+1;i++)
	{
  	 	a[i][0]=1;     
		a[i][width+1]=1;
 	}
}
/****************************************
 * ������� 
****************************************/
void CleanLine()
{
int i=height,j=1,k=0,sum=0;
for(i=height;i>0;i--)
	{
	sum=0;
	for(j=1;j<=width;j++)sum+=a[i][j];
		if(sum==width)
		{
		Line++;
		for(k=i;k>1;k--)
			for(j=1;j<width;j++)a[k][j]=a[k-1][j];
			i++;
		}
	}
	Level=1+Line/10;
	Score=Line*100;
	gotoxy(FrameX+2*width+8,FrameY-1);
	printf("Level:%d",Level);
	gotoxy(FrameX+2*width+8,FrameY+1);
	printf("����:%d",Score);
	gotoxy(FrameX+2*width+8,FrameY+3);
	printf("��ȥ������:%d",Line);
}
/****************************************
 * �ؼ�������ʾ����(���ڵ���) 
****************************************/
/*
void JustForDebugging()
{
	int i=0,j=0;
	for(i=0;i<height+2;i++)
		{
			gotoxy(FrameX+2*width+24,FrameY+i);
			for(j=0;j<width+2;j++)
    		printf("%d",a[i][j]);		
		}
	 gotoxy(FrameX+3*width+30,FrameY+1);
	 printf("flag_old=%2d",flag_old);
	 gotoxy(FrameX+3*width+30,FrameY+2);
	 printf("X=%d",X);
	 gotoxy(FrameX+3*width+30,FrameY+3);
	 printf("Y=%d",Y);
	 gotoxy(FrameX+3*width+30,FrameY+4);
	 printf("Left=%d",left);
	 gotoxy(FrameX+3*width+30,FrameY+5);
	 printf("Right=%d",right);
	 gotoxy(FrameX+3*width+30,FrameY+6);
	 printf("Down=%d",down);
	 gotoxy(FrameX+3*width+30,FrameY+7);
	 printf("Trans=%d",trans);
}
*/
/****************************************
 * ��ӡ��һ������˹���� 
****************************************/
void PrintNextTetris()
{
int i=0,j=0,temp[5][5];
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)temp[i][j]=0;
	switch(flag_next)
	{
		case  1:temp[1][1]=1;temp[2][1]=1;temp[2][2]=1;temp[2][3]=1;break;//��
		case  2:temp[1][2]=1;temp[1][3]=1;temp[2][2]=1;temp[3][2]=1;break;//������
		case  3:temp[2][1]=1;temp[2][2]=1;temp[2][3]=1;temp[3][3]=1;break;
		case  4:temp[1][2]=1;temp[2][2]=1;temp[3][1]=1;temp[3][2]=1;break;
	
		case  5:temp[1][2]=1;temp[2][1]=1;temp[2][2]=1;temp[2][3]=1;break;//  ��
		case  6:temp[1][2]=1;temp[2][2]=1;temp[2][3]=1;temp[3][2]=1;break;//������
		case  7:temp[2][1]=1;temp[2][2]=1;temp[2][3]=1;temp[3][2]=1;break;//
		case  8:temp[1][2]=1;temp[2][1]=1;temp[2][2]=1;temp[3][2]=1;break;

		case  9:temp[1][3]=1;temp[2][1]=1;temp[2][2]=1;temp[2][3]=1;break;//    ��
		case 10:temp[1][2]=1;temp[2][2]=1;temp[3][2]=1;temp[3][3]=1;break;//������
		case 11:temp[2][1]=1;temp[2][2]=1;temp[2][3]=1;temp[3][1]=1;break;
		case 12:temp[1][1]=1;temp[1][2]=1;temp[2][2]=1;temp[3][2]=1;break;
		
		case 13:temp[2][1]=1;temp[2][2]=1;temp[2][3]=1;temp[2][4]=1;break;//��������
		case 14:temp[1][2]=1;temp[2][2]=1;temp[3][2]=1;temp[4][2]=1;break;
		
		case 15:temp[1][1]=1;temp[1][2]=1;temp[2][2]=1;temp[2][3]=1;break;//����
		case 16:temp[1][3]=1;temp[2][2]=1;temp[2][3]=1;temp[3][2]=1;break;//  ����
		
		case 17:temp[1][2]=1;temp[1][3]=1;temp[2][1]=1;temp[2][2]=1;break;//  ����
		case 18:temp[1][2]=1;temp[2][2]=1;temp[2][3]=1;temp[3][3]=1;break;//����
		
		case 19:temp[2][2]=1;temp[2][3]=1;temp[3][2]=1;temp[3][3]=1;break;//����
																		  //����	
		default :break;
	}
	gotoxy(FrameX+2*width+8,FrameY+5);
	printf("��һ������:");
	printf("%2d",flag_next);
	
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
		{
		gotoxy(FrameX+2*width+2*j+8,FrameY+6+i);
			if(temp[i][j])printf("��");
			else printf("  ");
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
	start_t=clock();
	while(1)
	{
		KeyControl();
		end_t=clock();
		//JustForDebugging();
			if(end_t-start_t>1000-100*Level)  
			{
				Judge_MoveAndTansform();
				//JustForDebugging();
				if(down)
				{	
					CleanOld();
					Y++;
					DrawNew();
				}
				//JustForDebugging();	
				if(!down)
				{
					CleanLine();
					X=StartX;
					Y=StartY;
					MakeTetris();
					Judge_MoveAndTansform();
					if(!down)
					{
						int i=0,j=0;
						for(i=0;i<5;i++)
							for(j=0;j<5;j++)a[Y-2+i][X-2+j]+=s[i][j];			
							for(i=1;i<=height;i++)
								{
									gotoxy(FrameX+2,FrameY+i);
									for(j=1;j<=width;j++)
										if(a[i][j])printf("��");
										else printf("  ");
								}
						Sleep(1);
						GameOver();
					}
					PrintTetris(); 
					PrintNextTetris();					
				}
				//JustForDebugging();
				start_t=clock();
			}
	}
} 
/****************************************
 * ��Ϸ�������� 
****************************************/
void GameOver()
{
   				system("cls");
                gotoxy(0,8);
				printf("\t  ������      ��       ��    ��   ��������        ����    ��      �� ��������   ������  \n");
                printf("\t��           ����     �� ���� ��  ��            ��    ��   ��    ��  ��         ��   �� \n");
                printf("\t��   ����   ��  ��   ��   ��   �� ������       ��      ��   ��  ��   ������     ������  \n");
				printf("\t��     ��  ��������  ��   ��   �� ��            ��    ��     ����    ��         ��   �� \n");
				printf("\t  ������  ��      �� ��   ��   �� ��������        ����        ��     ��������   ��    ��\n");
				gotoxy(40,18); 
				printf("1:����һ��");
				gotoxy(60,18);
				printf("2:�˳�");
				int n;				
				gotoxy(48,20);
				printf("ѡ��1/2����");
				scanf_s("%d", &n);
    			switch (n)
    			{
    				case 1:GamePlay();break;
    				case 2:exit(0);break;
    			}
}
/****************************************
 * ��Ϸ�������ܽ��� 
****************************************/
void Explation()
{
	int i,j = 1;
    system("cls");
    gotoxy(32,3);
    printf("����˵��");
    for (i = 6; i <= 16; i++)   	//������±߿�
	{
		for (j = 15; j <= 60; j++)  //������ұ߿�
		{
			gotoxy(j, i);
			if (i == 6 || i == 16) printf("*");
			else if (j == 15 || j == 60) printf("*");
		}
	}
    gotoxy(18,7);
    printf("tip1: ��ҿ���ͨ�� �� ����������ƶ�����");
    gotoxy(18,9);
    printf("tip2: ͨ�� ��ʹ������ת");
    gotoxy(18,11);
    printf("tip3: ͨ�� �����ٷ�������");
    gotoxy(18,13);
    printf("tip4: ���ո����ͣ��Ϸ���ٰ��ո������");
    gotoxy(18,15);
    printf("tip5: ��ESC�˳���Ϸ����tap����ͣ/��������");
    _getch();                //�����������������
    system("cls");
    Welcom();
}
/****************************************
 * ��Ϸ������ܽ��� 
****************************************/
void Regulation()
{
	int i,j = 1;
    system("cls");
    gotoxy(34,3);
    printf("��Ϸ����");
    for (i = 6; i <= 18; i++)   	//������±߿�
	{
		for (j = 12; j <= 70; j++)  //������ұ߿�
		{
			gotoxy(j, i);
			if (i == 6 || i == 18) printf("*");
			else if (j == 12 || j == 70) printf("*");
		}
	}
    gotoxy(16,7);
    printf("tip1: ��ͬ��״��С�������Ļ�Ϸ����£����ͨ������");
    gotoxy(22,9);
    printf("�����λ�úͷ���ʹ��������Ļ�ײ�ƴ��������");
    gotoxy(22,11);
    printf("һ������");
    gotoxy(16,13);
    printf("tip2: ÿ����һ�У���������100");
    gotoxy(16,15);
    printf("tip3: ÿ�ۼ�1000�֣�������һ���ȼ�");
    gotoxy(16,17);
    printf("tip4: �����ȼ���ʹ���������ٶȼӿ죬��Ϸ�ѶȼӴ�");
	_getch();//�����������������
	system("cls");
	Welcom();
}
/****************************************
 * ��Ϸ��ӭ���� 
****************************************/
void Welcom()
{
	int n=0;
    HideCursor();
	gotoxy(28,3);
    printf("��  ��  ˹  ��  ��\n");	
    
	gotoxy(18,5);
    printf("��");						//��
    gotoxy(18,6);						//����
    printf("����");						//��
	gotoxy(18,7);
    printf("��");

	gotoxy(26,6);
    printf("����");					    //����
	gotoxy(28,7);						//  ����
    printf("����");
    
	gotoxy(36,6);						//����
    printf("����");						//����
    gotoxy(36,7);
    printf("����");

	gotoxy(45,5);
    printf("��");						//��
    gotoxy(45,6);						//��
	printf("��");						//��
	gotoxy(45,7);						//��
	printf("��");
	gotoxy(45,8);
	printf("��");
	
	gotoxy(56,6);
    printf("��");						//    ��
    gotoxy(52,7); 						//������
	printf("������");
					
	gotoxy(25,12);				
	printf("1.��ʼ��Ϸ");			
	gotoxy(40,12);
	printf("2.����˵��");
	gotoxy(25,15);
	printf("3.��Ϸ����");
	gotoxy(40,15);
	printf("4.�˳�");
	gotoxy(25,18);
	printf("��ѡ��[1 2 3 4]:");
    mciSendString(TEXT("open D:\\Music\\˦�и�.mp3 alias Song1"), NULL, 0, NULL);
    mciSendString(TEXT("play Song1 repeat"), NULL, 0, NULL);
    scanf_s("%d", &n);    			//����ѡ��
    switch (n)
    {
    	case 1:GamePlay();break;//��Ϸ��ʼ 
    	case 2:Explation();break;//����˵������ 
    	case 3:Regulation();break;//��Ϸ���� 
    	case 4:exit(0);break;//�ر���Ϸ 
    }
}
/****************************************
 * ������ 
****************************************/
int main()
{	
	Welcom();	
	return 0;
}
