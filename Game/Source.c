#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


// �̷� ������ & HP ���� & �����̴� ���� ��
#define WIDTH 20
#define HEIGHT 20
#define MAX_HP 5
#define NUM_MONSTERS 3

// Ű����
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


// ����
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define RED FOREGROUND_RED | FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define SKY_BLUE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY

 // ���� colorNum
void textcolor(int colorNum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

// ���� ����ü
typedef struct
{
    int x;
    int y;
    int dx;
}Monster;

// ����
char maze[HEIGHT][WIDTH]; // �̷�
int character_x, character_y; // ĳ����
Monster monsters[NUM_MONSTERS]; // �����̴� ����3
Monster monster1; // �����̴� ����1(��)
int hp = MAX_HP; // ���
int score = 0; // ����


// ĳ���� �ʱ�ȭ(������ġ)
void InitCharacter() 
{
    character_x = 1;
    character_y = 1;
}
// ���͵� �ʱ�ȭ(������ġ)
void InitMonsters() 
{
    srand(time(NULL));
    for (int i = 0; i < NUM_MONSTERS; i++) 
    {
        
        monsters[i].x = rand() % (WIDTH - 3) + 1; // ���� ����: 1 ~ 17
        monsters[i].y = rand() % (HEIGHT - 3) + 1;
        monster1.dx = 1;
        
    }
}
// (�����̴º�)����1 �ʱ�ȭ(������ġ)
void InitMonster1()
{
    monster1.x = 3;
    monster1.y = 5;
}

// �̷�1 �ʱ�ȭ(��ġ ����)
void InitMaze() 
{
    strcpy(maze[0], "1111111111111111111");
    strcpy(maze[1], "1000000001500000101");
    strcpy(maze[2], "1110110111111110101");
    strcpy(maze[3], "1510440100004440101");
    strcpy(maze[4], "1010110110111110001");
    strcpy(maze[5], "1010000000000000111"); // monster1
    strcpy(maze[6], "1011510101101010101");
    strcpy(maze[7], "1010010100001010001");
    strcpy(maze[8], "1010010113311511151");
    strcpy(maze[9], "1000010101101010001");
    strcpy(maze[10],"1111010100001010101");
    strcpy(maze[11],"1000000101111000101");
    strcpy(maze[12],"1011110101000010101");
    strcpy(maze[13],"1010014001011010101");
    strcpy(maze[14],"1000004100010010141");
    strcpy(maze[15],"1111014101010111141");
    strcpy(maze[16],"1300014101300100141");
    strcpy(maze[17],"1011010101110001101");
    strcpy(maze[18],"1000005000100150001");
    strcpy(maze[19],"1111111111111121111");
}

// �̷�2�ܰ�
void InitMaze2()
{
    strcpy(maze[0], "1111111111111111111");
    strcpy(maze[1], "1000000030000144441");
    strcpy(maze[2], "1011111110110141141");
    strcpy(maze[3], "1000000100010100151");
    strcpy(maze[4], "1111100100010110111");
    strcpy(maze[5], "1000000000000000101"); // monster1
    strcpy(maze[6], "1111111333311111101");
    strcpy(maze[7], "1000001000015000001");
    strcpy(maze[8], "1011101441011111101");
    strcpy(maze[9], "1015001441000000101");
    strcpy(maze[10],"1011111441011110001");
    strcpy(maze[11],"1300000000010011101");
    strcpy(maze[12],"1111101011111000001");
    strcpy(maze[13],"1004441500101011141");
    strcpy(maze[14],"1011111010101000141");
    strcpy(maze[15],"1000044010001010141");
    strcpy(maze[16],"1111111110150010041");
    strcpy(maze[17],"1510051030111010001");
    strcpy(maze[18],"1005100010100000501");
    strcpy(maze[19],"1111111111111111711");
}

// �̷�3�ܰ�
void InitMaze3()
{
    strcpy(maze[0], "1111111111111111111");
    strcpy(maze[1], "1011110003000111131");
    strcpy(maze[2], "1011110155510111101");
    strcpy(maze[3], "1011110111110111101");
    strcpy(maze[4], "1000000000000000001");
    strcpy(maze[5], "1000000505050500001"); // monster1
    strcpy(maze[6], "1011114411144111101");
    strcpy(maze[7], "1000000000000000001");
    strcpy(maze[8], "1410111010010014141");
    strcpy(maze[9], "1115144010510514141");
    strcpy(maze[10],"1410111011011011111");
    strcpy(maze[11],"1000000000000300001");
    strcpy(maze[12],"1111001111011011101");
    strcpy(maze[13],"1051300151000000101");
    strcpy(maze[14],"1001110101011011101");
    strcpy(maze[15],"1001000001010000001");
    strcpy(maze[16],"1000010111011110111");
    strcpy(maze[17],"1011110000010000001");
    strcpy(maze[18],"1044440100100111501");
    strcpy(maze[19],"1111111111111111911");
}

// �̷� ���
void PrintMaze() 
{
    system("cls");
    for (int i = 0; i < HEIGHT; i++) 
    {
        for (int j = 0; j < WIDTH; j++) 
        {
            if (i == character_y && j == character_x)// AND (�� �� ���̾�� ��)
            {
                textcolor(YELLOW);
                printf("��"); // ĳ����
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);// �� �ʱ�ȭ
            }
            else if (i == monster1.y && j == monster1.x)
            {
                textcolor(GREEN);
                printf("��"); // ����1(�����̴º�)
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
           else 
            {
                int is_monster = 0; // �ʱ�ȭ
                for (int k = 0; k < NUM_MONSTERS; k++) 
                {
                    if (i == monsters[k].y && j == monsters[k].x) 
                    {
                        textcolor(RED);
                        printf("��"); // ����
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        is_monster = 1; // ��
                        break;
                    }
                }
                if (!is_monster)
                {
                    if (maze[i][j] == '1')
                    {
                        textcolor(WHITE);
                        printf("��"); // ��
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    }
                    else if (maze[i][j] == '2') // 1�ܰ� Ż�ⱸ
                    {
                        textcolor(YELLOW);
                        printf("��");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '3')
                    {
                        textcolor(RED);
                        printf("��");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    }
                    else if (maze[i][j] == '4')
                    {
                        textcolor(SKY_BLUE);
                        printf("��");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '5')
                    {
                        textcolor(BLUE);
                        printf("��");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '7') // 2�ܰ� Ż�ⱸ
                    {
                        textcolor(YELLOW);
                        printf("��");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '9') // 3�ܰ� Ż�ⱸ
                    {
                        textcolor(YELLOW);
                        printf("��");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else
                    {
                        printf("  "); // ��
                    }
                }       
            }
        }
        printf("\n"); // �̷� ��� ���ϰ� �ٹٲ�

    }
    printf("HP: ");
    for (int i = 0; i < hp; i++) // 5��
    {
        textcolor(RED);
        printf("�� ");
        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    printf("\n\nSCORE: %d\n",score); // ���� �߰�
}

// ĳ���� �̵�
void MoveCharacter(int dx, int dy) 
{   
    int new_x = character_x + dx;
    int new_y = character_y + dy;

    // �̵��� ��ġ�� ���� �ƴϸ� �̵�
    if (maze[new_y][new_x] != '1') 
    {
        character_x = new_x;
        character_y = new_y;
    }
}

char input;

// ĳ���� ������
void Key()
{

    if (_kbhit())
    {
        input = _getch();
        
        // �Է°�
        switch (input)
        {
        case UP:
            MoveCharacter(0, -1);
            break;
        case DOWN:
            MoveCharacter(0, 1);
            break;
        case LEFT:
            MoveCharacter(-1, 0);
            break;
        case RIGHT:
            MoveCharacter(1, 0);
            break;
        }
    }
}

// ���͵� �̵�
void MoveMonster() 
{   

    for (int i = 0; i < NUM_MONSTERS; i++) // 3��
    {
        int dx = rand() % 3 - 1; // -1, 0, 1
        int dy = rand() % 3 - 1;

        int new_x = monsters[i].x + dx;
        int new_y = monsters[i].y + dy;

        // ���ο� ��ǥ�� (1, 1)�̰ų� �̷��� 2��,7��,9�� �κ��̸� �ٽ� ����
        while ((new_x == 1 && new_y == 1) || maze[new_y][new_x] == '2' 
            || maze[new_y][new_x] == '7' || maze[new_y][new_x] == '9')
        {
            dx = rand() % 3 - 1;
            dy = rand() % 3 - 1;
            new_x = monsters[i].x + dx;
            new_y = monsters[i].y + dy;
        }

        // �̵��� ��ġ�� ���� �ƴϸ� �̵�
        if (maze[new_y][new_x] != '1')
        {
            monsters[i].x = new_x;
            monsters[i].y = new_y;
        }
    }
    
}
// ����1 �̵�(�����̴º�)-�¿�θ� �̵�
void MoveMonster1()
{
    int new_x = monster1.x + monster1.dx;
    if (maze[monster1.y][new_x] != '1') // ���� �ƴ϶�� ������
    {
        monster1.x = new_x;
    }
    else
    {
        monster1.dx *= -1; // ���� �ε����� �� �̵� ���� ����
    }


}
// �浹 �˻�
void CheckCollision()
{   
    // ĳ���Ϳ� ���͵� �浹 �˻�
    for (int i = 0; i < NUM_MONSTERS; i++)
    {
        if (character_x == monsters[i].x && character_y == monsters[i].y)
        {
            hp--; // HP ����
            if (hp <= 0)
            {
                printf("\n<Game OVER>\n");
                exit(0); // ��������
            }
            InitCharacter(); // ĳ���� ��ġ �ʱ�ȭ (1,1)
        }
    }
    // ĳ���Ϳ� ����1(�����̴º�) �浹 �˻�
    if (character_x == monster1.x && character_y == monster1.y)
    {
        hp--; // HP ����
        if (hp <= 0)
        {
            printf("\n<Game OVER>\n");
            exit(0); // ��������
        }
        InitCharacter(); // ĳ���� ��ġ �ʱ�ȭ

    }

    // ��Ʈ�� �浹 �˻�
    if (maze[character_y][character_x] == '3')
    {
        // ��Ʈ�� ������ HP ȸ��
        hp++;
        if (hp > MAX_HP)
        {
            hp = MAX_HP;
        }
        // ��Ʈ ����(���������)
        maze[character_y][character_x] = '0';
    }
    // ��ǥ�� �浹 �˻�
    if (maze[character_y][character_x] == '4')
    {
        score += 100; // ���ھ� ����
        maze[character_y][character_x] = '0';
    }
    // ����ǥ�� �浹 üũ
    if (maze[character_y][character_x] == '5')
    {
        score += 500;
        maze[character_y][character_x] = '0';
    }

   // �̷�1�ܰ� �ⱸ�� ������
   if (maze[character_y][character_x] == '2') 
   {
       printf("\nGAME CLEAR!\n");

       Sleep(2000); // 2�� ���
       InitMaze2(); // ���ο� �̷�
       InitCharacter();
       InitMonsters();
   
   }
   // �̷�2�ܰ� �ⱸ�� ������
   if (maze[character_y][character_x] == '7')
   {
       printf("\nGAME CLEAR!\n");
       Sleep(2000);
       InitMaze3(); // ���ο� �̷�
       InitCharacter();
       InitMonsters();
   }
   // �̷�3�ܰ� �ⱸ�� ������ ���� ����
   if (maze[character_y][character_x] == '9')
   {
       printf("\nGAME CLEAR!\n");
       Sleep(2000);
       exit(1);
   }

}

// Ŀ�� ��ġ
void gotoxy(int x, int y)
{   
    // x��� y�� ��ǥ ����
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

// ����ȭ��
void title(void)
{
    int x = 4;
    int y = 3;

        gotoxy(x, y + 0); printf("������������������������"); // 23��
        gotoxy(x, y + 1); printf("��                                          ��");
        gotoxy(x, y + 2); printf("��   �����    ���   �����  �����  ��");
        gotoxy(x, y + 3); printf("��  ��  ��  ��  ��  ��    ���    ��        ��");
        gotoxy(x, y + 4); printf("��  ��  ��  ��  ����   ���     �����  ��");
        gotoxy(x, y + 5); printf("��  ��  ��  ��  ��  ��  ���      ��        ��");
        gotoxy(x, y + 6); printf("��  ��  ��  ��  ��  ��  �����  �����  ��");
        gotoxy(x, y + 7); printf("��                                          ��");
        gotoxy(x, y + 8); printf("������������������������");
        gotoxy(x, y + 9); printf("��                                          ��");
        gotoxy(x, y + 10); printf("�� ��: HP                                   ��");
        gotoxy(x, y + 11);printf("�� ��:PLUS HP                               ��");
        gotoxy(x, y + 12);printf("�� ��: monster                              ��");
        gotoxy(x, y + 13);printf("�� ��: move monster                         ��");
        gotoxy(x, y + 14);printf("�� ��: score+100                            ��");
        gotoxy(x, y + 15);printf("�� ��: score+500                            ��");
        gotoxy(x, y + 16);printf("�� ��: exit                                 ��");
        gotoxy(x, y + 17);printf("��                                          ��");
        gotoxy(x, y + 18);printf("��                                          ��");
        gotoxy(x, y + 19);printf("��          Press enter to start!           ��");
        gotoxy(x, y + 20);printf("������������������������");
}



int main()
{   
    system("mode con:cols=60 lines=30"); // �ܼ�â ũ��
    
    title(); // ����ȭ��

    // ���� ���������� ��� 
    while (_getch() != 13);
    
    // �ʱ�ȭ
    InitCharacter(); // ĳ���� ��ġ
    InitMonsters(); // ���͵� ��ġ
    InitMonster1();// �����̴º� ��ġ
    InitMaze();// �̷� �迭 

    while (1) 
    {
        Key();

        // ���� �̵�
        MoveMonster();
        MoveMonster1();

        // �浹 �˻�
        CheckCollision();

        // �̷� ���
        PrintMaze();

        Sleep(100);

    }   

    return 0;
}
