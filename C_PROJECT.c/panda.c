enum {
    black, blue, green, cyan, red, purple, brown, lightgray, darkgray, lightbule, lightgreen, lightcyan, lightred, lightpurple, yellow, white
};

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>
void setColor(int forground, int background) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//콘솔 핸들 가져오기
    int code = forground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}

int main(void) {
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
    return 0;
}