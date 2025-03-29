#include "console.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>

void setCursorPosition(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void setCursorPosition(Coordinate xy) {
    std::cout << "\033[" << xy.y << ";" << xy.x << "H";
}

Coordinate getCursorPosition() {
    Coordinate r; //Структура координат
    CONSOLE_SCREEN_BUFFER_INFO csbi; // Создаем структуру для хранения координат курсора
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем информацию о текущем состоянии консоли
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        r.x = csbi.dwCursorPosition.X;
        r.y = csbi.dwCursorPosition.Y;
    }
    else {
        r.x = -1;
        r.y = -1;
    }
    return r;
}

Coordinate getConsoleSize() {
    Coordinate r;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        r.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        r.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        r.x = -1;
        r.y = -1;
    }
    return r;
}
void FullScreenMode() {
    SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

char convertKey(char key) {
    tolower(key);
    switch (key) {
    case 'w': case 72: case -106: case -26:	return 'w';
    case 'a': case 75: case -108: case -28:	return 'a';
    case 's': case 80: case -101: case -21:	return 's';
    case 'd': case 77: case -126: case -94:	return 'd';
    case 'q': case -87: case -119: return'q';
    case 't': case -97: case -123: return 't';
    case 'r': case -86: case -118: return 'r';
    case 'f': case -64: case -32: return 'f';
    case 13: return 13; //enter
    case 32: return 32; //Пробел
    case 27: return 27; //ESC
    default: return 0;
    }
}

char catchKey() {
    while (true)
    {
        int input = _getch();
        if (input != 0 and input != 0xE0) {
            char key = input;
            return convertKey(key);
        }
    }
}

void setColor(int color) {
    std::cout << "\x1b[" << color << 'm';
}

void setColor(int color1, int color2) {
    std::cout << "\x1b[" << color1 << ';' << color2 << 'm';
}

void resetColor() { setColor(0); }

void printRowChars(int s, char symbol, int color1, int color2) {
    if (color1)
        ((color2) ? setColor(color1, color2) : setColor(color1));
    for (int i = 0; i < s; i++)
        std::cout << symbol;
}

void printRowChars(int s, char l, char c, char r, int color1, int color2) {
    if (color1)
        ((color2) ? setColor(color1, color2) : setColor(color1));
    std::cout << l;
    for (int i = 1; i < s - 1; i++)
        std::cout << c;
    std::cout << r;
}



void drawFillRectangle(Coordinate startPos, Coordinate endPos, int color, bool doubleBoard) {
    if (color) setColor(color);
    system("chcp 866>nul");
    BorderCP866 bord;
    char boardTopLeft = ((doubleBoard) ? bord.LT2 : bord.LT1);
    char boardTopRight = ((doubleBoard) ? bord.RT2 : bord.RT1);
    char boardDownLeft = ((doubleBoard) ? bord.LD2 : bord.LD1);
    char boardDownRight = ((doubleBoard) ? bord.RD2 : bord.RD1);
    char boardHorizontal = ((doubleBoard) ? bord.H2 : bord.H1);
    char boardVertical = ((doubleBoard) ? bord.V2 : bord.V1);
    int lengthX = endPos.x - startPos.x + 1;
    int lengthY = endPos.y - startPos.y;

    setCursorPosition(startPos);
    printRowChars(lengthX, boardTopLeft, boardHorizontal, boardTopRight);

    for (int i = 1; i < lengthY; i++) {
        setCursorPosition(endPos.x, startPos.y + i);
        std::cout << boardVertical;
        setCursorPosition(startPos.x, startPos.y + i);
        std::cout << boardVertical;
    }
    setCursorPosition(startPos.x, endPos.y);
    printRowChars(lengthX, boardDownLeft, boardHorizontal, boardDownRight);
    resetColor();
    system("chcp 1251>nul");
}

void drawEmptyRectangle(int posX, int posY, int rows, int cols, int color) {
    setCursorPosition(posX, posY);
    for (int r = 0; r < rows; r++) {
        printRowChars(cols, ' ', color);
        setCursorPosition(posX, posY + r + 1);
    }
    resetColor();
}

void drawEmptyRectangle(Coordinate s, Coordinate f, int color) {
    drawEmptyRectangle(s.x, s.y, f.y - s.y + 1, f.x - s.x + 1, color);
}
