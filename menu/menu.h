#pragma once
//+-------------------------------------------------+
//|Не работает без подключения                      |
//|#include "../console/console.h"                  |
//|В основном файле                                 |
//+-------------------------------------------------+



struct Menu
{
    Coordinate pos;//Стартовые координаты отрисовки меню
    char* Caption = nullptr;//шапка меню
    Menu* sub = nullptr;//пункты меню
    int count_sub = 0;//количество пунктов меню
    void (*Action)(Menu&) = nullptr;//действие при выборе данного пункта меню
    int selected = 0;//текущий пункт меню
    int width;
};

/// <summary>
/// Создание меню
/// </summary>
/// <param name="menu">Структура меню</param>
/// <param name="cap">Заголовок/элемент меню</param>
/// <param name="pos">Координаты отрисовки меню</param>
void CreateMenu(Menu& menu, const char* cap, Coordinate pos);
/// <summary>
/// Добавляет элемент меню в структуру
/// </summary>
/// <param name="menu">Структура меню</param>
/// <param name="cap">элемент меню</param>
/// <param name="Action">Указатель на действие при нажатии меню</param>
void AddItemMenu(Menu& menu, const char* cap, void (*Action)(Menu&));
//Перебирает все элементы меню и возвращает размер самого длинного элемента
int MaxLen(Menu& menu);
//Отрисовка элементов меню
void DrawMenu(Menu& menu);
//Запуск меню
void StartMenu(Menu& menu);
//Очищаем выделенную память меню
void clearMenu(Menu menu);
//Удаляет область видимости меню
void clsMenu(Menu menu);