#pragma once
//+-------------------------------------------------+
//|�� �������� ��� �����������                      |
//|#include "../console/console.h"                  |
//|� �������� �����                                 |
//+-------------------------------------------------+



struct Menu
{
    Coordinate pos;//��������� ���������� ��������� ����
    char* Caption = nullptr;//����� ����
    Menu* sub = nullptr;//������ ����
    int count_sub = 0;//���������� ������� ����
    void (*Action)(Menu&) = nullptr;//�������� ��� ������ ������� ������ ����
    int selected = 0;//������� ����� ����
    int width;
};

/// <summary>
/// �������� ����
/// </summary>
/// <param name="menu">��������� ����</param>
/// <param name="cap">���������/������� ����</param>
/// <param name="pos">���������� ��������� ����</param>
void CreateMenu(Menu& menu, const char* cap, Coordinate pos);
/// <summary>
/// ��������� ������� ���� � ���������
/// </summary>
/// <param name="menu">��������� ����</param>
/// <param name="cap">������� ����</param>
/// <param name="Action">��������� �� �������� ��� ������� ����</param>
void AddItemMenu(Menu& menu, const char* cap, void (*Action)(Menu&));
//���������� ��� �������� ���� � ���������� ������ ������ �������� ��������
int MaxLen(Menu& menu);
//��������� ��������� ����
void DrawMenu(Menu& menu);
//������ ����
void StartMenu(Menu& menu);
//������� ���������� ������ ����
void clearMenu(Menu menu);
//������� ������� ��������� ����
void clsMenu(Menu menu);