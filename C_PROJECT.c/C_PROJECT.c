#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

typedef struct _record {
    char name[10];
    char date[10];
}record;

enum {
    black, blue, green, cyan, red, purple, brown, lightgray, darkgray, lightbule, lightgreen, lightcyan, lightred, lightpurple, yellow, white
};

void init();//콘솔창의 크기를 설정, 창 제목을 설정,프로그램 실행 직후 초기화 작업을 진행하는 함수 + 커서 숨김처리 기능
void titleDraw();//타이틀 글자를 출력하는 함수
void gotoxy(int, int);//커서 위치 이동하는 함수
int menuDraw();//메뉴 출력하는 함수
int keyControl();//키보드 이벤트 처리하는 함수
void infoDraw();//게임 정보를 출력하는 함수
int diff_listDraw();//game start -> 난이도 선택 창
void drawQuiz(int num, record* r1);//문제를 출력하는 함수, 이거 아마 매개변수 num이런식으로 하나 더 추가해야할거야 동적할당하려면. 하나의 함수에서 n값을 입력받아 5x5, 7x7의 배열을 다 출력할거니까
void setColor(int, int);//글자색과 배경색을 바꿔주는 함수
void panda();//결과화면에서 판다를 출력하는 함수
void input(record*list);//사용자의 게임 날짜와 이름을 입력, save load할때 사용 + 반환형, 매개변수 다시 설정
void SAVE(record* list);//저장할 함수
void LOAD(record** list, int* number);//불러올 함수

int main(void) {
    record* r1 = (record*)calloc(sizeof(record), 1);
    int number = 0;

    srand((unsigned)time(NULL));

    init();
    while (1) {//menuDraw에서 값(y-20)을 반환하고 그것을 menuCode에 저장한다. 반환 값은 0,1,2 중 하나이고 게임시작에서 y의 값은 20, y-20하면 그 값은 0, 따라서 menuCode값이 0이면 게임 시작 ...
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {//게임 시작 하고 나면 
            //이름 날짜 입력 받고 난이도 단계로 넘어감
            input(r1);
            
            int n = diff_listDraw();
            if (n == 0) {//easy 모드를 선택한 경우
                drawQuiz(5, r1);
            }
            else if (n == 1) {//hard모드를 선택한 경우
                drawQuiz(7, r1);
            }
        }
        else if (menuCode == 1) {//게임 정보
            infoDraw();
        }
        else if (menuCode == 2) {//게임 불러오기
            LOAD(&r1, &number);
        }
        else if (menuCode == 3) {//게임 종료
            return 0;
        }
        system("cls");//메뉴를 선택하면 다시 처음으로 돌아온다.
    }
    return 0;
}
//함수 정의
void init() {
    system("mode con cols = 400 lines= 50 | title The Hidden Catch");// 콘솔 창 크기 설정, 창 제목 설정

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//콘솔 핸들 가져오기
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;//커서 숨기기
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
void titleDraw() {
    //setColor(white, black);
    char thc[12][101] = {
        {"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"},
        {"00111111111001000000000000000100010000000010000010000000000000000001111100000000000000000000000010000"},
        {"00000010000001000000000000000100010000000010000010000000000000000001000000000000000000000000000010000"},
        {"00000010000001000000000000000100010000000010000010000000000000000001000000000000000000000000000010000"},
        {"00000010000001000000000000000100010010000010000010000000000000000001000000000000000000000000000010000"},
        {"00000010000001000000000000000100010000000010000010000000000000000001000000000000000000000000000010000"},
        {"00000010000001111100111110000111110010011110011110011111001111100001000000011111000010000111110011111"},
        {"00000010000001000100100010000100010010010010010010010001001000100001000000000001000010000100000010001"},
        {"00000010000001000100100010000100010010010010010010010001001000100001000000011111001111100100000010001"},
        {"00000010000001000100111110000100010010010010010010011111001000100001000000010001000010000100000010001"},
        {"00000010000001000100100000000100010010010010010010010000001000100001000000010001000010000100000010001"},
        {"00000010000001000100111110000100010010011110011110011111001000100001111110011111000010000111110010001"}
    };
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 101; j++) {
            char temp = thc[i][j];
            if (temp == '0') {
                setColor(black, black);
                printf(" ");
            }
            else if (temp == '1') {
                setColor(white, white);
                printf("#");
            }
        }
        printf("\n");
    }
   setColor(white, black);
}
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//콘솔 핸들 가져오기
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
    //gotoxy(3,7)로 호출하게 되면, x위치가 3, y위치가 7인 지점으로 커서가 이동하게 된다.
    //이동한 위치에서 출력하는 방식으로 사용될 함수이다.
}
int menuDraw() {
    int x = 50;
    int y = 20;
    gotoxy(x - 2, y);
    printf("> GAME START");
    gotoxy(x, y + 1);
    printf("GAME INFORMATION");
    gotoxy(x, y + 2);
    printf("GAME RECORD");
    gotoxy(x, y + 3);
    printf("GAME OVER");
    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 20) {//y는 20-22까지만 이동
                gotoxy(x - 2, y);//x-2하는 이유: > 출력 위함
                printf(" ");//원래 있던 >은 공백으로 덮어씌우고
                gotoxy(x - 2, --y);//새로 이동한 위치로 이동하여
                printf(">");//다시 출력하기 >> 커서가 이동한 것처럼 보인다.
            }
            break;
        }

        case DOWN: {
            if (y < 23) {//최대 22
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {//선택
            return y - 20;//스페이스바 되었을 경우 y-20
            //y 시작 위치가 20였으므로 y-20을 하면 0,1,2 세 숫자를 받을 수 있다.
        }
        }
    }
}
int keyControl() {
    char temp = _getch();
    //엔터를 입력하지 않아도 키가 눌리면 바로 반환해주는 입력함수
    //scanf 나 cin으로 입력 받을 땐 글자를 입력하고 엔터를 눌러야 입력이 되지만 getch는 a키를 누르면 바로 반환해버린다.
    if ((temp == 'w') || temp == 'W') {
        return UP;
    }
    else if ((temp == 'a') || (temp == 'A')) {
        return LEFT;
    }
    else if ((temp == 's') || (temp == 'S')) {
        return DOWN;
    }
    else if ((temp == 'd') || (temp == 'D')) {
        return RIGHT;
    }
    else if (temp == ' ') {// space bar 선택 버튼
        return SUBMIT;
    }
    else return 5;
}
void infoDraw() {
    system("cls");//화면 모두 지우기
    printf("\n\n");
    printf("                                         [ CONTROL ]\n\n\n\n");
    printf("                                     MOVE:  W(up),  S(down)\n\n");
    printf("                                     SELECT: SPACE BAR \n\n\n\n\n\n");
    printf("                       PRESS THE SPACE BAR TO RETURN TO THE MAIN SCREEN.\n\n");

    while (1) {
        if (keyControl() == SUBMIT) {
            break;
        }
    }

}
int diff_listDraw() {
    int x = 50;//바꿔 이따가 화면 보면서
    int y = 6;
    system("cls");//화면 모두 지우기
    printf("\n\n");
    printf("                                        [ CHOOSE  DIFFICULTY ]\n\n");

    gotoxy(x - 2, y);
    printf("> EASY");//나중에 사이즈도 기입
    gotoxy(x, y + 1);
    printf("HARD");
    gotoxy(x, y + 2);
    printf("BACK\n");

    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 6) {
                gotoxy(x - 2, y);
                printf(" ");//원래 위치 공백으로 덮고
                gotoxy(x - 2, --y);//새로 이동한 위치, up을 했으니 위로 올라가야지
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 8) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            return y - 6;//0,1,2
        }
        }
    }
}
void drawQuiz(int num, record* r1) {
    system("cls");
     
    //arr1, arr2 동적할당
    int** arr1 = (int**)calloc(num, sizeof(int*));
    if (arr1 == NULL) {
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        arr1[i] = (int*)calloc(num, sizeof(int));
        for (int j = 0; j < num; j++)
            *(*(arr1 + i) + j) = 0;
           
    }
    int** arr2 = (int**)calloc(num, sizeof(int*));
    if (arr2 == NULL) {
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        arr2[i] = (int*)calloc(num, sizeof(int));
        for (int j = 0; j < num; j++)
            *(*(arr2 + i) + j) = 0;
    }
    //a. 두개의 이차원 배열에 0,1 저장
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            arr1[i][j] = rand() % 2;
        }
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            arr2[i][j] = rand() % 2;
        }
    }
    //c. 맞고 틀리고를 판단하고 cnt를 2씩 늘리면서 cnt의 총 값을 확정, 오류 뜬다면 cnt 초기화 또는 임시변수에 저장 고려
    int cnt = 0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (arr1[i][j] != arr2[i][j]) {
                cnt += 2;
            }
        }
    }
    //d. cnt 값으로 2개의 일차원 배열의 크기를 동적할당(정답 저장용(행,열을 기록), 사용자 입력용(초기화))
    int* answer = (int*)calloc(cnt, sizeof(int));
    int* userAnswer = (int*)calloc(cnt, sizeof(int));
    
    //e. 한번더 비교하면서 그 틀린 행과 열을 하나의 일차원 배열에 저장 (짝수번째에는 행, 홀수번째에는 열을 저장) - 정답을 저장하는거지
    int n = 1;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (arr1[i][j] != arr2[i][j]) {//다를때 그때의 행과 열을 저장
                answer[2*(n - 1)] = i;//행 저장, 0,2,4,6,8 
                answer[2 * n - 1 ] = j;//열 저장, 1,3,5,7,9
                n += 1;
            }
        }
    }
  
    while (1) {
        printf("FIND THE HIDDEN CATCH ! \n\n\n");
        //b. 두개의 이차원 배열을 출력 
        if (num == 5) {
            printf("*  0  1  2  3  4\n");
            printf("─────────────────\n");
        }
        else if (num == 7) {
            printf("*  0  1  2  3  4  5  6\n");
            printf("──────────────────────\n");
        }

        for (int i = 0; i < num; i++) {
            printf("%d│", i);
            for (int j = 0; j < num; j++) {
                printf("%2d ", *(*(arr1 + i) + j));
            }
            printf("\n");
        }
        printf("\n");
        if (num == 5) {
            printf("*  0  1  2  3  4\n");
            printf("─────────────────\n");
        }
        else if (num == 7) {
            printf("*  0  1  2  3  4  5  6\n");
            printf("──────────────────────\n");
        }
        for (int i = 0; i < num; i++) {
            printf("%d│", i);
            for (int j = 0; j < num; j++) {
                printf("%2d ", *(*(arr2 + i) + j));
            }
            printf("\n");
        }
        //f. answer 출력된 부분에 입력하도록 하고 scanf로 사용자입력용배열을 받아
        
        //예외처리할때, scanf의 반환값은 올바르게 입력된 값의 개수, 반복문을 사용하여 scanf에 입력할때 한번한번 입력할때마다 1을 반환할텐데 그 값을 a에 계속 더하며 저장
        //a값이 cnt값이라면 모두 숫자가 입력되었다는 뜻, 아니라면 문자가 입력되었다는 뜻. 엔터값을 만날때까지 입력버퍼를 다 지워 초기화하고 다시 입력.
        int a = 0;
        printf("\n\n\nANSWER:(row, column)\n");
        while (1) {
            for (int i = 0; i < cnt; i++) {
                a += scanf("%d", &userAnswer[i]);
            }           
            if (a ==cnt) {
                break;
            }
            else {
                while (getchar() != '\n');
                printf("YOU ENTERED INCORRECT VALUE.PLEASE ENTER THE NUMBERS\n");
               
            }
        }
       
        //g. 사용자입력배열과 정답저장용배열을 하나하나 비교하면서 맞을때마다(변수) 1씩 증가
        int answerCnt = 0;
        for (int i = 0; i < cnt; i++) {
            if (answer[i] == userAnswer[i]) {
                answerCnt += 1;
            }
        }
        printf("\n\n"); 
        if (answerCnt == cnt) {
            panda();//결과화면
            SAVE(r1);
            Sleep(3000);//3초 뒤에 종료
            break;
        }
        else { 
            printf("TRY AGAIN..\n\n"); 
        }       
    }
    free(arr1);
    free(arr2);
}
void setColor(int forground, int background) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//콘솔 핸들 가져오기
    int code = forground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}
void panda() {
    system("cls");
    printf("┍─────────────────────┐\n");
    printf("│   CONGRATULATION    │\n");
    printf("└─────────────────────┘\n");
    printf("             ㅣ /       \n");
    printf("             ㅣ/        \n");

    char arr1[22][22] = {
       {"0000000000000000000000"},
       {"0000000001110000001100"},
       {"0000000011110000011110"},
       {"0000000011100000001110"},
       {"0000100010000000000100"},
       {"0001100010000000000000"},
       {"0010001100000000000000"},
       {"0110001000000000000010"},
       {"0110011000110000000010"},
       {"0110011001110001100010"},
       {"0110011001100001110010"},
       {"0110011100000000110010"},
       {"0110011100001110000110"},
       {"0111011111100100011110"},
       {"0111101111111101111100"},
       {"0011111111111111111100"},
       {"0011110111110001111000"},
       {"0001110111110001111000"},
       {"0000110011111001110000"},
       {"0000000001111001100000"},
       {"0000000000111000000000"},
       {"0000000000000000000000"}
    };

    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 22; j++) {
            char temp = arr1[i][j];
            if (temp == '0') {
                setColor(white, white);
                printf("■");
            }
            else if (temp == '1') {
                setColor(black, black);

                printf(" ");
            }
        }printf("\n");
    }
    setColor(white, black);
}
void SAVE(record* list) {
    FILE* fs = fopen("record.txt", "a+");//record이름의 파일에 저장한다.
   
    fprintf(fs, "%s\n", (*list).name);
    fprintf(fs, "%s\n", (*list).date);
    
    fclose(fs);
}
void input(record*list) {
    system("cls");
    printf("NAME: ");
    scanf("%s", (*list).name);
    printf("\n");
    printf("DATE: ");
    scanf("%s", (*list).date);
}
void LOAD(record** list, int* number) {
    system("cls");
    FILE* fl = fopen("record.txt", "r");
    * number = 1;
    if (list != NULL) {
        for (int i = 0; i < *number; i++) {

            *list = (record*)realloc(*list, (*number) * sizeof(record));

            fscanf(fl, "%s", (*(*list+i)).name);
            fscanf(fl, "%s", (*(*list+i)).date);
            if (feof(fl) != 0) {
                break;//
            }
           *number += 1;
        }
    }
    for (int i = 0; i < *number - 1; i++) {
        printf("%s\n", (*(*list + i)).name);
        printf("%s\n", (*(*list + i)).date);
    }
    
    fclose(fl);

    printf("\n\n\n\n\n\n                       PRESS THE 'SPACE BAR' TO RETURN TO THE MAIN SCREEN.\n\n");

    while (1) {
        if (keyControl() == SUBMIT) {
            break;
        }
    }

}
