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

void init();//�ܼ�â�� ũ�⸦ ����, â ������ ����,���α׷� ���� ���� �ʱ�ȭ �۾��� �����ϴ� �Լ� + Ŀ�� ����ó�� ���
void titleDraw();//Ÿ��Ʋ ���ڸ� ����ϴ� �Լ�
void gotoxy(int, int);//Ŀ�� ��ġ �̵��ϴ� �Լ�
int menuDraw();//�޴� ����ϴ� �Լ�
int keyControl();//Ű���� �̺�Ʈ ó���ϴ� �Լ�
void infoDraw();//���� ������ ����ϴ� �Լ�
int diff_listDraw();//game start -> ���̵� ���� â
void drawQuiz(int num, record* r1);//������ ����ϴ� �Լ�, �̰� �Ƹ� �Ű����� num�̷������� �ϳ� �� �߰��ؾ��Ұž� �����Ҵ��Ϸ���. �ϳ��� �Լ����� n���� �Է¹޾� 5x5, 7x7�� �迭�� �� ����ҰŴϱ�
void setColor(int, int);//���ڻ��� ������ �ٲ��ִ� �Լ�
void panda();//���ȭ�鿡�� �Ǵٸ� ����ϴ� �Լ�
void input(record*list);//������� ���� ��¥�� �̸��� �Է�, save load�Ҷ� ��� + ��ȯ��, �Ű����� �ٽ� ����
void SAVE(record* list);//������ �Լ�
void LOAD(record** list, int* number);//�ҷ��� �Լ�

int main(void) {
    record* r1 = (record*)calloc(sizeof(record), 1);
    int number = 0;

    srand((unsigned)time(NULL));

    init();
    while (1) {//menuDraw���� ��(y-20)�� ��ȯ�ϰ� �װ��� menuCode�� �����Ѵ�. ��ȯ ���� 0,1,2 �� �ϳ��̰� ���ӽ��ۿ��� y�� ���� 20, y-20�ϸ� �� ���� 0, ���� menuCode���� 0�̸� ���� ���� ...
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {//���� ���� �ϰ� ���� 
            //�̸� ��¥ �Է� �ް� ���̵� �ܰ�� �Ѿ
            input(r1);
            
            int n = diff_listDraw();
            if (n == 0) {//easy ��带 ������ ���
                drawQuiz(5, r1);
            }
            else if (n == 1) {//hard��带 ������ ���
                drawQuiz(7, r1);
            }
        }
        else if (menuCode == 1) {//���� ����
            infoDraw();
        }
        else if (menuCode == 2) {//���� �ҷ�����
            LOAD(&r1, &number);
        }
        else if (menuCode == 3) {//���� ����
            return 0;
        }
        system("cls");//�޴��� �����ϸ� �ٽ� ó������ ���ƿ´�.
    }
    return 0;
}
//�Լ� ����
void init() {
    system("mode con cols = 400 lines= 50 | title The Hidden Catch");// �ܼ� â ũ�� ����, â ���� ����

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//�ܼ� �ڵ� ��������
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;//Ŀ�� �����
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
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//�ܼ� �ڵ� ��������
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
    //gotoxy(3,7)�� ȣ���ϰ� �Ǹ�, x��ġ�� 3, y��ġ�� 7�� �������� Ŀ���� �̵��ϰ� �ȴ�.
    //�̵��� ��ġ���� ����ϴ� ������� ���� �Լ��̴�.
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
            if (y > 20) {//y�� 20-22������ �̵�
                gotoxy(x - 2, y);//x-2�ϴ� ����: > ��� ����
                printf(" ");//���� �ִ� >�� �������� ������
                gotoxy(x - 2, --y);//���� �̵��� ��ġ�� �̵��Ͽ�
                printf(">");//�ٽ� ����ϱ� >> Ŀ���� �̵��� ��ó�� ���δ�.
            }
            break;
        }

        case DOWN: {
            if (y < 23) {//�ִ� 22
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {//����
            return y - 20;//�����̽��� �Ǿ��� ��� y-20
            //y ���� ��ġ�� 20�����Ƿ� y-20�� �ϸ� 0,1,2 �� ���ڸ� ���� �� �ִ�.
        }
        }
    }
}
int keyControl() {
    char temp = _getch();
    //���͸� �Է����� �ʾƵ� Ű�� ������ �ٷ� ��ȯ���ִ� �Է��Լ�
    //scanf �� cin���� �Է� ���� �� ���ڸ� �Է��ϰ� ���͸� ������ �Է��� ������ getch�� aŰ�� ������ �ٷ� ��ȯ�ع�����.
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
    else if (temp == ' ') {// space bar ���� ��ư
        return SUBMIT;
    }
    else return 5;
}
void infoDraw() {
    system("cls");//ȭ�� ��� �����
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
    int x = 50;//�ٲ� �̵��� ȭ�� ���鼭
    int y = 6;
    system("cls");//ȭ�� ��� �����
    printf("\n\n");
    printf("                                        [ CHOOSE  DIFFICULTY ]\n\n");

    gotoxy(x - 2, y);
    printf("> EASY");//���߿� ����� ����
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
                printf(" ");//���� ��ġ �������� ����
                gotoxy(x - 2, --y);//���� �̵��� ��ġ, up�� ������ ���� �ö󰡾���
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
     
    //arr1, arr2 �����Ҵ�
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
    //a. �ΰ��� ������ �迭�� 0,1 ����
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
    //c. �°� Ʋ���� �Ǵ��ϰ� cnt�� 2�� �ø��鼭 cnt�� �� ���� Ȯ��, ���� ��ٸ� cnt �ʱ�ȭ �Ǵ� �ӽú����� ���� ���
    int cnt = 0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (arr1[i][j] != arr2[i][j]) {
                cnt += 2;
            }
        }
    }
    //d. cnt ������ 2���� ������ �迭�� ũ�⸦ �����Ҵ�(���� �����(��,���� ���), ����� �Է¿�(�ʱ�ȭ))
    int* answer = (int*)calloc(cnt, sizeof(int));
    int* userAnswer = (int*)calloc(cnt, sizeof(int));
    
    //e. �ѹ��� ���ϸ鼭 �� Ʋ�� ��� ���� �ϳ��� ������ �迭�� ���� (¦����°���� ��, Ȧ����°���� ���� ����) - ������ �����ϴ°���
    int n = 1;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (arr1[i][j] != arr2[i][j]) {//�ٸ��� �׶��� ��� ���� ����
                answer[2*(n - 1)] = i;//�� ����, 0,2,4,6,8 
                answer[2 * n - 1 ] = j;//�� ����, 1,3,5,7,9
                n += 1;
            }
        }
    }
  
    while (1) {
        printf("FIND THE HIDDEN CATCH ! \n\n\n");
        //b. �ΰ��� ������ �迭�� ��� 
        if (num == 5) {
            printf("*  0  1  2  3  4\n");
            printf("����������������������������������\n");
        }
        else if (num == 7) {
            printf("*  0  1  2  3  4  5  6\n");
            printf("��������������������������������������������\n");
        }

        for (int i = 0; i < num; i++) {
            printf("%d��", i);
            for (int j = 0; j < num; j++) {
                printf("%2d ", *(*(arr1 + i) + j));
            }
            printf("\n");
        }
        printf("\n");
        if (num == 5) {
            printf("*  0  1  2  3  4\n");
            printf("����������������������������������\n");
        }
        else if (num == 7) {
            printf("*  0  1  2  3  4  5  6\n");
            printf("��������������������������������������������\n");
        }
        for (int i = 0; i < num; i++) {
            printf("%d��", i);
            for (int j = 0; j < num; j++) {
                printf("%2d ", *(*(arr2 + i) + j));
            }
            printf("\n");
        }
        //f. answer ��µ� �κп� �Է��ϵ��� �ϰ� scanf�� ������Է¿�迭�� �޾�
        
        //����ó���Ҷ�, scanf�� ��ȯ���� �ùٸ��� �Էµ� ���� ����, �ݺ����� ����Ͽ� scanf�� �Է��Ҷ� �ѹ��ѹ� �Է��Ҷ����� 1�� ��ȯ���ٵ� �� ���� a�� ��� ���ϸ� ����
        //a���� cnt���̶�� ��� ���ڰ� �ԷµǾ��ٴ� ��, �ƴ϶�� ���ڰ� �ԷµǾ��ٴ� ��. ���Ͱ��� ���������� �Է¹��۸� �� ���� �ʱ�ȭ�ϰ� �ٽ� �Է�.
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
       
        //g. ������Է¹迭�� ���������迭�� �ϳ��ϳ� ���ϸ鼭 ����������(����) 1�� ����
        int answerCnt = 0;
        for (int i = 0; i < cnt; i++) {
            if (answer[i] == userAnswer[i]) {
                answerCnt += 1;
            }
        }
        printf("\n\n"); 
        if (answerCnt == cnt) {
            panda();//���ȭ��
            SAVE(r1);
            Sleep(3000);//3�� �ڿ� ����
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
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//�ܼ� �ڵ� ��������
    int code = forground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}
void panda() {
    system("cls");
    printf("�Ȧ�������������������������������������������\n");
    printf("��   CONGRATULATION    ��\n");
    printf("����������������������������������������������\n");
    printf("             �� /       \n");
    printf("             ��/        \n");

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
                printf("��");
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
    FILE* fs = fopen("record.txt", "a+");//record�̸��� ���Ͽ� �����Ѵ�.
   
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
