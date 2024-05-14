#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


// 미로 사이즈 & HP 갯수 & 움직이는 몬스터 수
#define WIDTH 20
#define HEIGHT 20
#define MAX_HP 5
#define NUM_MONSTERS 3

// 키보드
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


// 색깔
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define RED FOREGROUND_RED | FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define SKY_BLUE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY

 // 색깔 colorNum
void textcolor(int colorNum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

// 몬스터 구조체
typedef struct
{
    int x;
    int y;
    int dx;
}Monster;

// 선언
char maze[HEIGHT][WIDTH]; // 미로
int character_x, character_y; // 캐릭터
Monster monsters[NUM_MONSTERS]; // 움직이는 몬스터3
Monster monster1; // 움직이는 몬스터1(벽)
int hp = MAX_HP; // 목숨
int score = 0; // 점수


// 캐릭터 초기화(시작위치)
void InitCharacter() 
{
    character_x = 1;
    character_y = 1;
}
// 몬스터들 초기화(시작위치)
void InitMonsters() 
{
    srand(time(NULL));
    for (int i = 0; i < NUM_MONSTERS; i++) 
    {
        
        monsters[i].x = rand() % (WIDTH - 3) + 1; // 난수 범위: 1 ~ 17
        monsters[i].y = rand() % (HEIGHT - 3) + 1;
        monster1.dx = 1;
        
    }
}
// (움직이는벽)몬스터1 초기화(시작위치)
void InitMonster1()
{
    monster1.x = 3;
    monster1.y = 5;
}

// 미로1 초기화(위치 지정)
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

// 미로2단계
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

// 미로3단계
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

// 미로 출력
void PrintMaze() 
{
    system("cls");
    for (int i = 0; i < HEIGHT; i++) 
    {
        for (int j = 0; j < WIDTH; j++) 
        {
            if (i == character_y && j == character_x)// AND (둘 다 참이어야 참)
            {
                textcolor(YELLOW);
                printf("●"); // 캐릭터
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);// 색 초기화
            }
            else if (i == monster1.y && j == monster1.x)
            {
                textcolor(GREEN);
                printf("■"); // 몬스터1(움직이는벽)
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
           else 
            {
                int is_monster = 0; // 초기화
                for (int k = 0; k < NUM_MONSTERS; k++) 
                {
                    if (i == monsters[k].y && j == monsters[k].x) 
                    {
                        textcolor(RED);
                        printf("▼"); // 몬스터
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        is_monster = 1; // 참
                        break;
                    }
                }
                if (!is_monster)
                {
                    if (maze[i][j] == '1')
                    {
                        textcolor(WHITE);
                        printf("■"); // 벽
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    }
                    else if (maze[i][j] == '2') // 1단계 탈출구
                    {
                        textcolor(YELLOW);
                        printf("↓");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '3')
                    {
                        textcolor(RED);
                        printf("♡");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    }
                    else if (maze[i][j] == '4')
                    {
                        textcolor(SKY_BLUE);
                        printf("♪");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '5')
                    {
                        textcolor(BLUE);
                        printf("♬");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '7') // 2단계 탈출구
                    {
                        textcolor(YELLOW);
                        printf("↓");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if (maze[i][j] == '9') // 3단계 탈출구
                    {
                        textcolor(YELLOW);
                        printf("↓");
                        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else
                    {
                        printf("  "); // 길
                    }
                }       
            }
        }
        printf("\n"); // 미로 출력 다하고 줄바꿈

    }
    printf("HP: ");
    for (int i = 0; i < hp; i++) // 5개
    {
        textcolor(RED);
        printf("♥ ");
        textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    printf("\n\nSCORE: %d\n",score); // 점수 추가
}

// 캐릭터 이동
void MoveCharacter(int dx, int dy) 
{   
    int new_x = character_x + dx;
    int new_y = character_y + dy;

    // 이동할 위치가 벽이 아니면 이동
    if (maze[new_y][new_x] != '1') 
    {
        character_x = new_x;
        character_y = new_y;
    }
}

char input;

// 캐릭터 움직임
void Key()
{

    if (_kbhit())
    {
        input = _getch();
        
        // 입력값
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

// 몬스터들 이동
void MoveMonster() 
{   

    for (int i = 0; i < NUM_MONSTERS; i++) // 3개
    {
        int dx = rand() % 3 - 1; // -1, 0, 1
        int dy = rand() % 3 - 1;

        int new_x = monsters[i].x + dx;
        int new_y = monsters[i].y + dy;

        // 새로운 좌표가 (1, 1)이거나 미로의 2번,7번,9번 부분이면 다시 생성
        while ((new_x == 1 && new_y == 1) || maze[new_y][new_x] == '2' 
            || maze[new_y][new_x] == '7' || maze[new_y][new_x] == '9')
        {
            dx = rand() % 3 - 1;
            dy = rand() % 3 - 1;
            new_x = monsters[i].x + dx;
            new_y = monsters[i].y + dy;
        }

        // 이동할 위치가 벽이 아니면 이동
        if (maze[new_y][new_x] != '1')
        {
            monsters[i].x = new_x;
            monsters[i].y = new_y;
        }
    }
    
}
// 몬스터1 이동(움직이는벽)-좌우로만 이동
void MoveMonster1()
{
    int new_x = monster1.x + monster1.dx;
    if (maze[monster1.y][new_x] != '1') // 벽이 아니라면 움직임
    {
        monster1.x = new_x;
    }
    else
    {
        monster1.dx *= -1; // 벽에 부딪혔을 때 이동 방향 변경
    }


}
// 충돌 검사
void CheckCollision()
{   
    // 캐릭터와 몬스터들 충돌 검사
    for (int i = 0; i < NUM_MONSTERS; i++)
    {
        if (character_x == monsters[i].x && character_y == monsters[i].y)
        {
            hp--; // HP 감소
            if (hp <= 0)
            {
                printf("\n<Game OVER>\n");
                exit(0); // 게임종료
            }
            InitCharacter(); // 캐릭터 위치 초기화 (1,1)
        }
    }
    // 캐릭터와 몬스터1(움직이는벽) 충돌 검사
    if (character_x == monster1.x && character_y == monster1.y)
    {
        hp--; // HP 감소
        if (hp <= 0)
        {
            printf("\n<Game OVER>\n");
            exit(0); // 게임종료
        }
        InitCharacter(); // 캐릭터 위치 초기화

    }

    // 하트와 충돌 검사
    if (maze[character_y][character_x] == '3')
    {
        // 하트를 먹으면 HP 회복
        hp++;
        if (hp > MAX_HP)
        {
            hp = MAX_HP;
        }
        // 하트 삭제(빈공간으로)
        maze[character_y][character_x] = '0';
    }
    // 음표와 충돌 검사
    if (maze[character_y][character_x] == '4')
    {
        score += 100; // 스코어 증가
        maze[character_y][character_x] = '0';
    }
    // 쌍음표와 충돌 체크
    if (maze[character_y][character_x] == '5')
    {
        score += 500;
        maze[character_y][character_x] = '0';
    }

   // 미로1단계 출구에 닿으면
   if (maze[character_y][character_x] == '2') 
   {
       printf("\nGAME CLEAR!\n");

       Sleep(2000); // 2초 대기
       InitMaze2(); // 새로운 미로
       InitCharacter();
       InitMonsters();
   
   }
   // 미로2단계 출구에 닿으면
   if (maze[character_y][character_x] == '7')
   {
       printf("\nGAME CLEAR!\n");
       Sleep(2000);
       InitMaze3(); // 새로운 미로
       InitCharacter();
       InitMonsters();
   }
   // 미로3단계 출구에 닿으면 게임 종료
   if (maze[character_y][character_x] == '9')
   {
       printf("\nGAME CLEAR!\n");
       Sleep(2000);
       exit(1);
   }

}

// 커서 위치
void gotoxy(int x, int y)
{   
    // x축과 y축 좌표 설정
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

// 시작화면
void title(void)
{
    int x = 4;
    int y = 3;

        gotoxy(x, y + 0); printf("■■■■■■■■■■■■■■■■■■■■■■■"); // 23개
        gotoxy(x, y + 1); printf("■                                          ■");
        gotoxy(x, y + 2); printf("■   ■■■■    ■■   ■■■■  ■■■■  ■");
        gotoxy(x, y + 3); printf("■  ■  ■  ■  ■  ■    ■■    ■        ■");
        gotoxy(x, y + 4); printf("■  ■  ■  ■  ■■■   ■■     ■■■■  ■");
        gotoxy(x, y + 5); printf("■  ■  ■  ■  ■  ■  ■■      ■        ■");
        gotoxy(x, y + 6); printf("■  ■  ■  ■  ■  ■  ■■■■  ■■■■  ■");
        gotoxy(x, y + 7); printf("■                                          ■");
        gotoxy(x, y + 8); printf("■■■■■■■■■■■■■■■■■■■■■■■");
        gotoxy(x, y + 9); printf("■                                          ■");
        gotoxy(x, y + 10); printf("■ ♥: HP                                   ■");
        gotoxy(x, y + 11);printf("■ ♡:PLUS HP                               ■");
        gotoxy(x, y + 12);printf("■ ▼: monster                              ■");
        gotoxy(x, y + 13);printf("■ ■: move monster                         ■");
        gotoxy(x, y + 14);printf("■ ♪: score+100                            ■");
        gotoxy(x, y + 15);printf("■ ♬: score+500                            ■");
        gotoxy(x, y + 16);printf("■ ↓: exit                                 ■");
        gotoxy(x, y + 17);printf("■                                          ■");
        gotoxy(x, y + 18);printf("■                                          ■");
        gotoxy(x, y + 19);printf("■          Press enter to start!           ■");
        gotoxy(x, y + 20);printf("■■■■■■■■■■■■■■■■■■■■■■■");
}



int main()
{   
    system("mode con:cols=60 lines=30"); // 콘솔창 크기
    
    title(); // 시작화면

    // 엔터 누를때까지 대기 
    while (_getch() != 13);
    
    // 초기화
    InitCharacter(); // 캐릭터 위치
    InitMonsters(); // 몬스터들 위치
    InitMonster1();// 움직이는벽 위치
    InitMaze();// 미로 배열 

    while (1) 
    {
        Key();

        // 몬스터 이동
        MoveMonster();
        MoveMonster1();

        // 충돌 검사
        CheckCollision();

        // 미로 출력
        PrintMaze();

        Sleep(100);

    }   

    return 0;
}
