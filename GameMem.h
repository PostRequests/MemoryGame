#pragma once
#include "Struct.h"
#include "console/console.h"
#include "menu/menu.h"
#include "GameMem.h"
//���������� �����
void showCard(Card card, Coordinate pos);
//������ � ������ ���������� ������� �����
void hideCard(Coordinate pos);
//�������� �����
void selectCard(Coordinate pos);
//������� ��������� �����
void clsSelect(Coordinate pos);
//��������� �������� �����
void removeCard(Coordinate pos);
//������������� ���������� �����
Coordinate coorToPos(Board& b);
//�������� �������
void drawLogo(Coordinate pos);
//���������� ��������� ������ �� ������ ��������
char getRandChar(const char* t);
//���������� ������ ������������ ����
Card* getDeck(int count);
//��������� ��������� ���� �� �����
void calculateCardLayout(int Cards, int& rows, int& cols);
//������������� �������������� ��������� � ����������� �� ���������� ����
Board createBoard(int cards);
//������ ����� ��������� �����
void drawBackBoard(Board b);
//������� � ��������� ����
void playMenu();
//�������� ������� ����
void playGame(Menu& menu);