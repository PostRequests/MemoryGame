#pragma once

struct Coordinate {
    int x; //Ряд
    int y; //Строка
};

struct ColorANSI3b {//Цвета ANSI 3бит 
    const int BlackBG = 40;   // Фоновый черный
    const int BlackFG = 30;   // Текстовый черный
    const int RedBG = 41;     // Фоновый красный
    const int RedFG = 31;     // Текстовый красный
    const int GreenBG = 42;   // Фоновый зеленый
    const int GreenFG = 32;   // Текстовый зеленый
    const int YellowBG = 43;  // Фоновый желтый
    const int YellowFG = 33;  // Текстовый желтый
    const int BlueBG = 44;    // Фоновый синий
    const int BlueFG = 34;    // Текстовый синий
    const int MagentaBG = 45; // Фоновый пурпурный
    const int MagentaFG = 35; // Текстовый пурпурный
    const int CyanBG = 46;    // Фоновый циановый
    const int CyanFG = 36;    // Текстовый циановый
    const int WhiteBG = 47;   // Фоновый белый
    const int WhiteFG = 37;   // Текстовый белый
};

/// Набор символов для рисования таблиц
//LT1: "┌" H1 : "─" RT1 : "┐" V1 : "│" LD1 : "└" RD1 : "┘" LV1 : "├" RV1 : "┤" DH1 : "┴" UH1 : "┬"C1 : "┼" 
struct BorderCP866 {
    const char LT2 = 201; //╔ левый верхний двойной
    const char H2 = 205; //═ горизонтальный двойной
    const char RT2 = 187; //╗ правый верхний двойной
    const char V2 = 186; //║ вертикальный двойной
    const char LD2 = 200; //╚ левый нижний двойной
    const char RD2 = 188; //╝ правый нижний двойной
    const char LV2 = 204; //╠ левый вертикальный двойной
    const char RV2 = 185; //╣ правый вертикальный двойной
    const char DH2 = 202; //╩ нижний горизонтальный двойной
    const char UH2 = 203; //╦ верхний горизонтальный двойной
    const char C2 = 206; //╬ центральный двойной

    const char LT1 = 218; // ┌ левый верхний одинарный
    const char H1 = 196;  // ─ горизонтальный одинарный
    const char RT1 = 191; // ┐ правый верхний одинарный
    const char V1 = 179;  // │ вертикальный одинарный
    const char LD1 = 192; // └ левый нижний одинарный
    const char RD1 = 217; // ┘ правый нижний одинарный
    const char LV1 = 195; // ├ левый вертикальный одинарный
    const char RV1 = 180; // ┤ правый вертикальный одинарный
    const char DH1 = 193; // ┴ нижний горизонтальный одинарный
    const char UH1 = 194; // ┬ верхний горизонтальный одинарный
    const char C1 = 197;  // ┼ центральный одинарный
};

/// <summary>Конвертирует нажатые клавиши на русском и английском вединый вид </summary>
/// <param name="key">Символ который в итоге конвертируется</param>
/// <returns>Обработанный символ например ц==Ц==W==(w) возвращает w</returns>
char convertKey(char key);
/// <summary> Устанавливаем курсор в нужную позицию </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void setCursorPosition(int x, int y);
/// <summary>
/// Устанавливаем курсор в нужную позицию
/// </summary>
/// <param name="xy">Структура координат курсора xy.x xy.y</param>
void setCursorPosition(Coordinate xy);
/// <summary>
/// Определяет в какой позиции сейчас находиться курсор
/// </summary>
/// <returns>Возвращает структуру координат Coordinate.x Coordinate.y</returns>
Coordinate getCursorPosition();
/// <summary>
/// Определяет текущий размер экрана в символах
/// </summary>
/// <returns>Возвращает структуру координат максимальных точек Coordinate.x/y</returns>
Coordinate getConsoleSize();
/// <summary>
/// Раскрывает консоль в полный экран
/// </summary>
void FullScreenMode();
/// <returns>Возвращает нажатый символ</returns>
char catchKey();
/// <summary>
/// Устанавливаем 1 цвет консоли
/// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
/// </summary>
/// <param name="color">Цвет</param>
void setColor(int color);
/// <summary>
/// Устанавливаем 2 цвета консоли, для фона и для символа
/// </summary>
/// <param name="color1">Цвет1</param>
/// <param name="color2">Цвет2</param>
void setColor(int color1, int color2);
/// <summary>/// Сбрасываем все цвета консоли на стандартный/// </summary>
void resetColor();
/// <summary>
/// Печатает линию
/// </summary>
/// <param name="s">Длинна линии</param>
/// <param name="symbol">Элемент заполнения</param>
/// <param name="color1">Цвет консоли ANSI</param>
/// <param name="color2">Цвет консоли ANSI</param>
void printRowChars(int s, char symbol, int color1 = 0, int color2 = 0);
/// <summary>
/// Печатает линию
/// </summary>
/// <param name="s">Длинна линии</param>
/// <param name="l">Первый символ в линии</param>
/// <param name="c">Символ который будет заполнять центр линии</param>
/// <param name="r">Последний символ линии</param>
/// <param name="color1">Цвет консоли ANSI (не обязательный параметр)</param>
/// <param name="color2">Цвет консоли ANSI (не обязательный параметр)</param>
void printRowChars(int s, char l, char c, char r, int color1 = 0, int color2 = 0);
/// <summary>
/// Рисует квадрат с одинарной или двойной рамкой
/// </summary>
/// <param name="startPos">Верхняя левая координата</param>
/// <param name="endPos">Нижняя правая координата</param>
/// <param name="doubleBoard">True - двойная, false - одинарная</param>
void drawFillRectangle(Coordinate startPos, Coordinate endPos, int color = 0, bool doubleBoard = true);
/// <summary>
/// Закрашивает/Удаляет область прямоугольную 
/// </summary>
/// <param name="posX">Позиция строки</param>
/// <param name="posY">Позиция колонки</param>
/// <param name="rows">Количество закрашиваемых строк</param>
/// <param name="cols">Количество закрашиваемых колонок</param>
/// <param name="color">Параметр цвета (указываем только задний фон)</param>
void drawEmptyRectangle(int posX, int posY, int rows, int cols, int color = 0);
void drawEmptyRectangle(Coordinate s, Coordinate f, int color = 0);