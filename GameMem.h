#pragma once
#include "Struct.h"
#include "console/console.h"
#include "menu/menu.h"
#include "GameMem.h"
//Показывает карту
void showCard(Card card, Coordinate pos);
//Скрыть а точнее нарисовать рубашку карты
void hideCard(Coordinate pos);
//Выделить карту
void selectCard(Coordinate pos);
//Стереть выделение карты
void clsSelect(Coordinate pos);
//Полностью скрывает карту
void removeCard(Coordinate pos);
//Пересичтывает координаты карты
Coordinate coorToPos(Board& b);
//Печатает логотип
void drawLogo(Coordinate pos);
//Возвращает случайный символ из списка символов
char getRandChar(const char* t);
//Возвращает колоду перемешанных карт
Card* getDeck(int count);
//Вычесляет положение карт на доске
void calculateCardLayout(int Cards, int& rows, int& cols);
//Устанавливаем первоначальные настройки в зависимости от количества карт
Board createBoard(int cards);
//Рисует доску рубашками вверх
void drawBackBoard(Board b);
//Создает и запускает меню
void playMenu();
//Основная функция игры
void playGame(Menu& menu);