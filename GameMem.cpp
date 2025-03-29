#include "Struct.h"
#include "console/console.h"
#include "menu/menu.h"
#include "GameMem.h"
#include <iostream>
#include <Windows.h>

void showCard(Card card, Coordinate pos) {
	Suit S;
	int x = pos.x;
	int y = pos.y;
	setCursorPosition(x, y);
	for (int row = 0; row < cHeight; row++)
	{
		std::cout << S.f[card.suit][row] ;
		setCursorPosition(x, ++y);
	}
	setCursorPosition(x + cWidth - 2, y - 2);
	std::cout << card.cost;
	setCursorPosition(pos.x + 1, pos.y + 1);
	std::cout << card.cost;
}
void hideCard(Coordinate pos) {
	Suit S;
	int x = pos.x;
	int y = pos.y;
	setCursorPosition(x, y);
	for (int row = 0; row < cHeight; row++)
	{
		std::cout << S.b[row];
		setCursorPosition(x, ++y);
	}
}
void selectCard(Coordinate pos) {
	drawFillRectangle({ pos.x - 1, pos.y - 1 }, { pos.x + cWidth, pos.y + cHeight });
}
void clsSelect(Coordinate pos) {
	ColorANSI3b c;
	setColor(c.BlackFG);
	drawFillRectangle({ pos.x - 1, pos.y - 1 }, { pos.x + cWidth, pos.y + cHeight });
	resetColor();
}
void removeCard(Coordinate pos) {
	drawEmptyRectangle({ pos.x - 1, pos.y - 1 }, { pos.x + cWidth, pos.y + cHeight });
}
void drawLogo(Coordinate pos) {
	char logo[] = { "Память" };
	int lLogo = sizeof(logo) / sizeof(logo[0]) - 1;
	setCursorPosition(pos.x, pos.y + cHeight);
	printRowChars(lLogo * (cWidth + 2) - 2, '=');
	for (int letter = 0; letter < lLogo; letter++) {
		showCard({ rand() % cCount,logo[letter],0 }, pos);
		pos.x += cWidth + 2;
	}
	
		
}
char getRandChar(const char* t) {
	return t[rand() % strlen(t)];
}
Card* getDeck(int count) {
	Card* deck = new Card[count];
	//Добавляем карты
	for (int i = 0; i < count; i += 2)
	{
		deck[i].cost = getRandChar("123456789XВДКТ");
		deck[i].suit = rand() % cCount;
		deck[i + 1].cost = deck[i].cost;
		deck[i + 1].suit = deck[i].suit;
	}
	//Перемешиваем карты
	for (int i = 0; i < count; i++)
		std::swap(deck[i], deck[rand() % count]);
	return deck;
}
void calculateCardLayout(int сards, int& rows, int& cols) {
	int mr = 6;//Максимальное количество рядов
	for (int i = mr; i > 0; i -= 2)
		if (сards % i == 0 and сards / i != 1 and сards / i != 2) {
			rows = i;
			cols = сards / i;
			return;
		}
}
Board createBoard(int cards) {
	Coordinate CS = getConsoleSize();
	Board board;
	calculateCardLayout(cards, board.rows, board.cols);
	board.sel = { 0,0 };
	board.cDeck = cards;
	board.deck = getDeck(cards);
	board.sPos = {CS.x / 2 - ((board.cols - 1) * (cWidth + 2)) / 2, cHeight + 3};
	return board;
}
void drawBackBoard(Board b) {
	for (int r = 0; r < b.rows; r++)
		for (int c = 0; c < b.cols; c++)
			hideCard({b.sPos.x + (c * (cWidth +2)), b.sPos.y + (r * (cHeight +1)) });
}
Coordinate coorToPos(Board& b) {
	return { b.sPos.x + b.sel.x * (cWidth + 2), b.sPos.y + b.sel.y * (cHeight + 1)};
}
int coorToNum(Board& b) {
	return b.sel.y * b.cols + b.sel.x;
}
Coordinate numToCoor(Board& b, int num) {
	int y = num / b.cols;
	int x = num % b.cols;
	return { b.sPos.x + x * (cWidth + 2), b.sPos.y + y * (cHeight + 1) };
}
void playGame(Menu& menu) {
	if (menu.count_sub == menu.selected + 1) exit(0);
	clsMenu(menu);
	clearMenu(menu);
	Board bor = createBoard(8 + menu.selected * 4);
	drawBackBoard(bor);
	selectCard(coorToPos(bor));
	bor.st = time(0);
	while (true)
	{
		if (!bor.cDeck)
		{
			setCursorPosition(20, 11);
			int timeSec = time(0) - bor.st;
			int minute = timeSec / 60;
			int sec = timeSec % 60;
			std::cout << "Затрачено времени: " << minute << " мин. " << sec << " сек.";
			setCursorPosition(20, 12);
			system("pause");
			drawEmptyRectangle({ 20, 10 }, { 80, 13 });
			return;
		}
		setCursorPosition(20, 10);
		std::cout << "Количество ходов: " << bor.flips;
		char key = catchKey();
		if (!key) continue;
		switch (key)
		{
		case 'w': {
			clsSelect(coorToPos(bor));
			bor.sel.y = ((!bor.sel.y)? bor.rows - 1: bor.sel.y -1);
			selectCard(coorToPos(bor));
			break;
		}
		case 's': {
			clsSelect(coorToPos(bor));
			bor.sel.y = ((bor.sel.y == bor.rows - 1) ? 0 : bor.sel.y + 1);
			selectCard(coorToPos(bor));
			break;
		}
		case 'a': {
			clsSelect(coorToPos(bor));
			bor.sel.x = ((!bor.sel.x) ? bor.cols - 1 : bor.sel.x - 1);
			selectCard(coorToPos(bor));
			break;
		}
		case 'd': {
			clsSelect(coorToPos(bor));
			bor.sel.x = ((bor.sel.x == bor.cols - 1) ? 0 : bor.sel.x + 1);
			selectCard(coorToPos(bor));
			break;
		}
		case 13: {
			if (bor.oc != coorToNum(bor) and bor.deck[coorToNum(bor)].active)
				bor.flips++;
			else
				break;

			if (bor.oc == -1) //Если первое открытие
			{
				bor.oc = coorToNum(bor);
				showCard(bor.deck[bor.oc], coorToPos(bor));
			}
			else //Если вторая карта
			{
				int numCard = coorToNum(bor);
				showCard(bor.deck[numCard], coorToPos(bor));
				if (bor.deck[numCard].cost == bor.deck[bor.oc].cost and//Если угадал
					bor.deck[numCard].suit == bor.deck[bor.oc].suit) {
					bor.cDeck -= 2;
					//Деактивируем карты;
					bor.deck[numCard].active = false;
					bor.deck[bor.oc].active = false;
					removeCard(coorToPos(bor));//Удаляем с листа текущую карту
					removeCard(numToCoor(bor, bor.oc));
				}
				else//Если не угадал
				{
					system("pause>nul");
					hideCard(coorToPos(bor)); //Скрываем текущую карту
					hideCard(numToCoor(bor, bor.oc));//Скрываем карту предыдущую
				}
				bor.oc = -1;
			}
			
			break;
		}

		}
	}
}
void playMenu() {
	Coordinate CS = getConsoleSize();
	Menu menu;
	CreateMenu(menu, "Выбор игры", { CS.x / 2 - 10 / 2, 10 });
	AddItemMenu(menu, "8 карт", playGame);
	AddItemMenu(menu, "12 карт", playGame);
	AddItemMenu(menu, "16 карт", playGame);
	AddItemMenu(menu, "20 карт", playGame);
	AddItemMenu(menu, "24 карты", playGame);
	AddItemMenu(menu, "28 карт", playGame);
	AddItemMenu(menu, "32 карты", playGame);
	AddItemMenu(menu, "Выход", playGame);
	StartMenu(menu);
}