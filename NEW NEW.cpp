#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
void grid();
using namespace std;

int board[8][8];
int BOARD_START_X = 50;
int BOARD_START_Y = 50;
int BLOCK_SIZE = 50;
int SHAPE_DIFF = 10;
int NO_BLOCKS_IN_BOARD = 8;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void myLine(int x1, int y1, int x2, int y2, int a, int b, int c) // use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	// change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(a, b, c)); // 2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
}

// This function checks if any of the 4 cursor keys are pressed.
// If any cursor key is pressed, then the function returns true, and whichKey identifies which of the 4 cursor keys is pressed.
// whichkey is assigned following values if any cursor key is pressed. 1 for left, 2 for up, 3 for right and 4 for left.
bool isCursorKeyPressed(int &whichKey) // whichKey passed as reference....
{
	char key;
	key = GetAsyncKeyState(37);
	if (key == 1)
	{
		whichKey = 1; // 1 if left key is pressed
		return true;
	}
	key = GetAsyncKeyState(38);
	if (key == 1)
	{

		whichKey = 2; // 2 if up key is pressed
		return true;
	}

	key = GetAsyncKeyState(39);
	if (key == 1)
	{

		whichKey = 3; // 3 if right key is pressed
		return true;
	}
	key = GetAsyncKeyState(40);
	if (key == 1)
	{

		whichKey = 4; // 4 if down key is pressed
		return true;
	}
	key = GetAsyncKeyState(VK_RETURN);
	if (key == 1)
	{

		whichKey = 5; // 4 if enter key is pressed
		return true;
	}
	return false;
}

void myRect(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	// change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(255, 255, 0)); // Fill color is passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	// change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(255, 0, 0)); // Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}

// print shapes coordinates

// print shapes in box
//===============================================================
//
//                ####  ##   ##    ###    #####   #####   ####
//               ##     ##   ##   ## ##   ##  ##  ##     ##
//                ###   #######  ##   ##  #####   #####   ###
//                  ##  ##   ##  #######  ##      ##        ##
//               ####   ##   ##  ##   ##  ##      #####  ####
//
//===============================================================

void drawSquareInBlock(int x, int y)
{
	int blocktodrawx = BOARD_START_X + y * BLOCK_SIZE;
	int blocktodrawy = BOARD_START_Y + (BLOCK_SIZE * x);

	int squareBottomLeftX = blocktodrawx + 50 - SHAPE_DIFF;
	int squareBottomLeftY = blocktodrawy + SHAPE_DIFF;

	int squareTopRightX = blocktodrawx + SHAPE_DIFF;
	int squareTopRightY = blocktodrawy + 50 - SHAPE_DIFF;

	myRect(squareBottomLeftX, squareBottomLeftY, squareTopRightX, squareTopRightY, 255, 255, 0);
}

void drawSquareInBlock_white(int x, int y)
{
	int blocktodrawx = BOARD_START_X + y * BLOCK_SIZE;
	int blocktodrawy = BOARD_START_Y + (BLOCK_SIZE * x);

	int squareBottomLeftX = blocktodrawx + 50 - SHAPE_DIFF;
	int squareBottomLeftY = blocktodrawy + SHAPE_DIFF;

	int squareTopRightX = blocktodrawx + SHAPE_DIFF;
	int squareTopRightY = blocktodrawy + 50 - SHAPE_DIFF;

	myRect(squareBottomLeftX, squareBottomLeftY, squareTopRightX, squareTopRightY, 255, 255, 255);
}

void drawTriangleInBlock(int x, int y)
{
	int blocktodrawx = BOARD_START_X + y * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + x * BLOCK_SIZE; // shape to fill in an board

	int triangleBottomLeftX = blocktodrawx + SHAPE_DIFF;	  // bottom left side
	int triangleBottomLeftY = blocktodrawy + 50 - SHAPE_DIFF; // bottom left side

	int triangleBottomRightX = blocktodrawx + 50 - SHAPE_DIFF; // bottom right side
	int triangleBottomRightY = blocktodrawy + 50 - SHAPE_DIFF; // bottom right side

	int triangleTopXfromright = blocktodrawx + SHAPE_DIFF;
	int triangleTopX = blocktodrawx + 25;
	int triangleTopY = blocktodrawy + 10;

	myLine(triangleBottomLeftX + 1, triangleBottomLeftY - 2, triangleTopX - 10, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 2, triangleBottomLeftY - 4, triangleTopX - 9, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 3, triangleBottomLeftY - 5, triangleTopX - 8, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 4, triangleBottomLeftY - 6, triangleTopX - 7, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 5, triangleBottomLeftY - 8, triangleTopX - 6, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 6, triangleBottomLeftY - 10, triangleTopX - 5, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 7, triangleBottomLeftY - 11, triangleTopX - 4, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 8, triangleBottomLeftY - 13, triangleTopX - 3, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 9, triangleBottomLeftY - 15, triangleTopX - 2, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 10, triangleBottomLeftY - 17, triangleTopX - 1, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 11, triangleBottomLeftY - 19, triangleTopX, triangleBottomLeftY, 255, 0, 255);		 // bottom line
	myLine(triangleBottomLeftX + 12, triangleBottomLeftY - 22, triangleTopX + 1, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 13, triangleBottomLeftY - 24, triangleTopX + 2, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 14, triangleBottomLeftY - 26, triangleTopX + 3, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 15, triangleBottomLeftY - 24, triangleTopX + 4, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 16, triangleBottomLeftY - 22, triangleTopX + 5, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 17, triangleBottomLeftY - 20, triangleTopX + 6, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 18, triangleBottomLeftY - 18, triangleTopX + 7, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 19, triangleBottomLeftY - 16, triangleTopX + 8, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 20, triangleBottomLeftY - 14, triangleTopX + 9, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 21, triangleBottomLeftY - 12, triangleTopX + 10, triangleBottomLeftY, 255, 0, 255); // bottom line
	myLine(triangleBottomLeftX + 22, triangleBottomLeftY - 10, triangleTopX + 11, triangleBottomLeftY, 255, 0, 255); // bottom line
	myLine(triangleBottomLeftX + 23, triangleBottomLeftY - 8, triangleTopX + 12, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 24, triangleBottomLeftY - 6, triangleTopX + 13, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 25, triangleBottomLeftY - 4, triangleTopX + 14, triangleBottomLeftY, 255, 0, 255);	 // bottom line
	myLine(triangleBottomLeftX + 15, triangleBottomLeftY - 27, triangleTopX + 15, triangleBottomLeftY, 255, 0, 255); // bottom line
	myLine(triangleBottomLeftX + 15, triangleBottomLeftY - 26, triangleTopX + 14, triangleBottomLeftY, 108, 0, 108); // bottom line
	myLine(triangleTopX, triangleBottomLeftY - 28, triangleBottomLeftX, triangleBottomLeftY, 108, 0, 108);			 // bottom line

	myLine(triangleBottomLeftX, triangleBottomLeftY, triangleBottomRightX, triangleBottomRightY, 108, 0, 108); // bottom line
	myLine(triangleBottomLeftX, triangleBottomLeftY, triangleTopX, triangleTopY, 108, 0, 108);				   // left line
	myLine(triangleBottomRightX, triangleBottomRightY, triangleTopX, triangleTopY, 108, 0, 108);			   // right line
}
void drawTriangleInBlock_white(int x, int y)
{
	int blocktodrawx = BOARD_START_X + y * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + x * BLOCK_SIZE; // shape to fill in an board

	int triangleBottomLeftX = blocktodrawx + SHAPE_DIFF;	  // bottom left side
	int triangleBottomLeftY = blocktodrawy + 50 - SHAPE_DIFF; // bottom left side

	int triangleBottomRightX = blocktodrawx + 50 - SHAPE_DIFF; // bottom right side
	int triangleBottomRightY = blocktodrawy + 50 - SHAPE_DIFF; // bottom right side

	int triangleTopXfromright = blocktodrawx + SHAPE_DIFF;
	int triangleTopX = blocktodrawx + 25;
	int triangleTopY = blocktodrawy + 10;

	myLine(triangleBottomLeftX + 1, triangleBottomLeftY - 2, triangleTopX - 10, triangleBottomLeftY, 255, 255, 255);   // bottom line
	myLine(triangleBottomLeftX + 2, triangleBottomLeftY - 4, triangleTopX - 9, triangleBottomLeftY, 255, 255, 255);	   // bottom line
	myLine(triangleBottomLeftX + 3, triangleBottomLeftY - 5, triangleTopX - 8, triangleBottomLeftY, 255, 255, 255);	   // bottom line
	myLine(triangleBottomLeftX + 4, triangleBottomLeftY - 6, triangleTopX - 7, triangleBottomLeftY, 255, 255, 255);	   // bottom line
	myLine(triangleBottomLeftX + 5, triangleBottomLeftY - 8, triangleTopX - 6, triangleBottomLeftY, 255, 255, 255);	   // bottom line
	myLine(triangleBottomLeftX + 6, triangleBottomLeftY - 10, triangleTopX - 5, triangleBottomLeftY, 255, 255, 255);   // bottom line
	myLine(triangleBottomLeftX + 7, triangleBottomLeftY - 11, triangleTopX - 4, triangleBottomLeftY, 255, 255, 255);   // bottom line
	myLine(triangleBottomLeftX + 8, triangleBottomLeftY - 13, triangleTopX - 3, triangleBottomLeftY, 255, 255, 255);   // bottom line
	myLine(triangleBottomLeftX + 9, triangleBottomLeftY - 15, triangleTopX - 2, triangleBottomLeftY, 255, 255, 255);   // bottom line
	myLine(triangleBottomLeftX + 10, triangleBottomLeftY - 17, triangleTopX - 1, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 11, triangleBottomLeftY - 19, triangleTopX, triangleBottomLeftY, 255, 255, 255);	   // bottom line
	myLine(triangleBottomLeftX + 12, triangleBottomLeftY - 22, triangleTopX + 1, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 13, triangleBottomLeftY - 24, triangleTopX + 2, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 14, triangleBottomLeftY - 26, triangleTopX + 3, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 15, triangleBottomLeftY - 24, triangleTopX + 4, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 16, triangleBottomLeftY - 22, triangleTopX + 5, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 17, triangleBottomLeftY - 20, triangleTopX + 6, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 18, triangleBottomLeftY - 18, triangleTopX + 7, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 19, triangleBottomLeftY - 16, triangleTopX + 8, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 20, triangleBottomLeftY - 14, triangleTopX + 9, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 21, triangleBottomLeftY - 12, triangleTopX + 10, triangleBottomLeftY, 255, 255, 255); // bottom line
	myLine(triangleBottomLeftX + 22, triangleBottomLeftY - 10, triangleTopX + 11, triangleBottomLeftY, 255, 255, 255); // bottom line
	myLine(triangleBottomLeftX + 23, triangleBottomLeftY - 8, triangleTopX + 12, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 24, triangleBottomLeftY - 6, triangleTopX + 13, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 25, triangleBottomLeftY - 4, triangleTopX + 14, triangleBottomLeftY, 255, 255, 255);  // bottom line
	myLine(triangleBottomLeftX + 15, triangleBottomLeftY - 27, triangleTopX + 15, triangleBottomLeftY, 255, 255, 255); // bottom line
	myLine(triangleBottomLeftX + 15, triangleBottomLeftY - 26, triangleTopX + 14, triangleBottomLeftY, 108, 0, 108);   // bottom line
	myLine(triangleTopX, triangleBottomLeftY - 28, triangleBottomLeftX, triangleBottomLeftY, 108, 0, 108);			   // bottom line

	myLine(triangleBottomLeftX, triangleBottomLeftY, triangleBottomRightX, triangleBottomRightY, 108, 0, 108); // bottom line
	myLine(triangleBottomLeftX, triangleBottomLeftY, triangleTopX, triangleTopY, 108, 0, 108);				   // left line
	myLine(triangleBottomRightX, triangleBottomRightY, triangleTopX, triangleTopY, 108, 0, 108);			   // right line
}

void drawCrystalInBlock(int i, int j)
{
	int blocktodrawx = BOARD_START_X + j * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + i * BLOCK_SIZE; // shape to fill in an board

	int crystalTopX = blocktodrawx + 25; // top point
	int crystalTopY = blocktodrawy + 10; // top point

	int crystalBottomX = blocktodrawx + 25;				 // bottom point x
	int crystalBottomY = blocktodrawy + 50 - SHAPE_DIFF; // bottom point y

	int crystalleftpointx = blocktodrawx + 10; // leftpoint
	int crystalleftpointy = blocktodrawy + 25; // leftpoint

	int crystalrightpointx = blocktodrawx + 50 - SHAPE_DIFF; // rightpoint
	int crystalrightpointy = blocktodrawy + 25;				 // rightpoint

	myLine(crystalTopX, crystalTopY, crystalBottomX, crystalBottomY, 51, 153, 255);
	myLine(crystalTopX + 1, crystalTopY + 1, crystalBottomX + 1, crystalBottomY - 1, 51, 153, 255);
	myLine(crystalTopX + 2, crystalTopY + 2, crystalBottomX + 2, crystalBottomY - 2, 51, 153, 255);
	myLine(crystalTopX + 3, crystalTopY + 3, crystalBottomX + 3, crystalBottomY - 3, 51, 153, 255);
	myLine(crystalTopX + 4, crystalTopY + 4, crystalBottomX + 4, crystalBottomY - 4, 51, 153, 255);
	myLine(crystalTopX + 5, crystalTopY + 5, crystalBottomX + 5, crystalBottomY - 5, 51, 153, 255);
	myLine(crystalTopX + 6, crystalTopY + 6, crystalBottomX + 6, crystalBottomY - 6, 51, 153, 255);
	myLine(crystalTopX + 7, crystalTopY + 7, crystalBottomX + 7, crystalBottomY - 7, 51, 153, 255);
	myLine(crystalTopX + 8, crystalTopY + 8, crystalBottomX + 8, crystalBottomY - 8, 51, 153, 255);
	myLine(crystalTopX + 9, crystalTopY + 9, crystalBottomX + 9, crystalBottomY - 9, 51, 153, 255);
	myLine(crystalTopX + 10, crystalTopY + 10, crystalBottomX + 10, crystalBottomY - 10, 51, 153, 255);
	myLine(crystalTopX + 11, crystalTopY + 11, crystalBottomX + 11, crystalBottomY - 11, 51, 153, 255);
	myLine(crystalTopX + 12, crystalTopY + 12, crystalBottomX + 12, crystalBottomY - 12, 51, 153, 255);
	myLine(crystalTopX + 13, crystalTopY + 13, crystalBottomX + 13, crystalBottomY - 13, 51, 153, 255);
	myLine(crystalTopX + 14, crystalTopY + 14, crystalBottomX + 14, crystalBottomY - 14, 51, 153, 255);

	myLine(crystalTopX - 1, crystalTopY + 1, crystalBottomX - 1, crystalBottomY - 1, 51, 153, 255);
	myLine(crystalTopX - 2, crystalTopY + 2, crystalBottomX - 2, crystalBottomY - 2, 51, 153, 255);
	myLine(crystalTopX - 3, crystalTopY + 3, crystalBottomX - 3, crystalBottomY - 3, 51, 153, 255);
	myLine(crystalTopX - 4, crystalTopY + 4, crystalBottomX - 4, crystalBottomY - 4, 51, 153, 255);
	myLine(crystalTopX - 5, crystalTopY + 5, crystalBottomX - 5, crystalBottomY - 5, 51, 153, 255);
	myLine(crystalTopX - 6, crystalTopY + 6, crystalBottomX - 6, crystalBottomY - 6, 51, 153, 255);
	myLine(crystalTopX - 7, crystalTopY + 7, crystalBottomX - 7, crystalBottomY - 7, 51, 153, 255);
	myLine(crystalTopX - 8, crystalTopY + 8, crystalBottomX - 8, crystalBottomY - 8, 51, 153, 255);
	myLine(crystalTopX - 9, crystalTopY + 9, crystalBottomX - 9, crystalBottomY - 9, 51, 153, 255);
	myLine(crystalTopX - 10, crystalTopY + 10, crystalBottomX - 10, crystalBottomY - 10, 51, 153, 255);
	myLine(crystalTopX - 11, crystalTopY + 11, crystalBottomX - 11, crystalBottomY - 11, 51, 153, 255);
	myLine(crystalTopX - 12, crystalTopY + 12, crystalBottomX - 12, crystalBottomY - 12, 51, 153, 255);
	myLine(crystalTopX - 13, crystalTopY + 13, crystalBottomX - 13, crystalBottomY - 13, 51, 153, 255);
	myLine(crystalTopX - 14, crystalTopY + 14, crystalBottomX - 14, crystalBottomY - 14, 51, 153, 255);
	myLine(crystalBottomX, crystalBottomY, crystalrightpointx, crystalrightpointy, 0, 0, 204); // bottom right
	myLine(crystalrightpointx, crystalrightpointy, crystalTopX, crystalTopY, 0, 0, 204);	   // top right
	myLine(crystalTopX, crystalTopY, crystalleftpointx, crystalleftpointy, 0, 0, 204);		   // top left
	myLine(crystalleftpointx, crystalleftpointy, crystalBottomX, crystalBottomY, 0, 0, 204);   // bottom left
}
void drawCrystalInBlock_white(int i, int j)
{
	int blocktodrawx = BOARD_START_X + j * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + i * BLOCK_SIZE; // shape to fill in an board

	int crystalTopX = blocktodrawx + 25; // top point
	int crystalTopY = blocktodrawy + 10; // top point

	int crystalBottomX = blocktodrawx + 25;				 // bottom point x
	int crystalBottomY = blocktodrawy + 50 - SHAPE_DIFF; // bottom point y

	int crystalleftpointx = blocktodrawx + 10; // leftpoint
	int crystalleftpointy = blocktodrawy + 25; // leftpoint

	int crystalrightpointx = blocktodrawx + 50 - SHAPE_DIFF; // rightpoint
	int crystalrightpointy = blocktodrawy + 25;				 // rightpoint

	myLine(crystalTopX, crystalTopY, crystalBottomX, crystalBottomY, 255, 255, 255);
	myLine(crystalTopX + 1, crystalTopY + 1, crystalBottomX + 1, crystalBottomY - 1, 255, 255, 255);
	myLine(crystalTopX + 2, crystalTopY + 2, crystalBottomX + 2, crystalBottomY - 2, 255, 255, 255);
	myLine(crystalTopX + 3, crystalTopY + 3, crystalBottomX + 3, crystalBottomY - 3, 255, 255, 255);
	myLine(crystalTopX + 4, crystalTopY + 4, crystalBottomX + 4, crystalBottomY - 4, 255, 255, 255);
	myLine(crystalTopX + 5, crystalTopY + 5, crystalBottomX + 5, crystalBottomY - 5, 255, 255, 255);
	myLine(crystalTopX + 6, crystalTopY + 6, crystalBottomX + 6, crystalBottomY - 6, 255, 255, 255);
	myLine(crystalTopX + 7, crystalTopY + 7, crystalBottomX + 7, crystalBottomY - 7, 255, 255, 255);
	myLine(crystalTopX + 8, crystalTopY + 8, crystalBottomX + 8, crystalBottomY - 8, 255, 255, 255);
	myLine(crystalTopX + 9, crystalTopY + 9, crystalBottomX + 9, crystalBottomY - 9, 255, 255, 255);
	myLine(crystalTopX + 10, crystalTopY + 10, crystalBottomX + 10, crystalBottomY - 10, 255, 255, 255);
	myLine(crystalTopX + 11, crystalTopY + 11, crystalBottomX + 11, crystalBottomY - 11, 255, 255, 255);
	myLine(crystalTopX + 12, crystalTopY + 12, crystalBottomX + 12, crystalBottomY - 12, 255, 255, 255);
	myLine(crystalTopX + 13, crystalTopY + 13, crystalBottomX + 13, crystalBottomY - 13, 255, 255, 255);
	myLine(crystalTopX + 14, crystalTopY + 14, crystalBottomX + 14, crystalBottomY - 14, 255, 255, 255);

	myLine(crystalTopX - 1, crystalTopY + 1, crystalBottomX - 1, crystalBottomY - 1, 255, 255, 255);
	myLine(crystalTopX - 2, crystalTopY + 2, crystalBottomX - 2, crystalBottomY - 2, 255, 255, 255);
	myLine(crystalTopX - 3, crystalTopY + 3, crystalBottomX - 3, crystalBottomY - 3, 255, 255, 255);
	myLine(crystalTopX - 4, crystalTopY + 4, crystalBottomX - 4, crystalBottomY - 4, 255, 255, 255);
	myLine(crystalTopX - 5, crystalTopY + 5, crystalBottomX - 5, crystalBottomY - 5, 255, 255, 255);
	myLine(crystalTopX - 6, crystalTopY + 6, crystalBottomX - 6, crystalBottomY - 6, 255, 255, 255);
	myLine(crystalTopX - 7, crystalTopY + 7, crystalBottomX - 7, crystalBottomY - 7, 255, 255, 255);
	myLine(crystalTopX - 8, crystalTopY + 8, crystalBottomX - 8, crystalBottomY - 8, 255, 255, 255);
	myLine(crystalTopX - 9, crystalTopY + 9, crystalBottomX - 9, crystalBottomY - 9, 255, 255, 255);
	myLine(crystalTopX - 10, crystalTopY + 10, crystalBottomX - 10, crystalBottomY - 10, 255, 255, 255);
	myLine(crystalTopX - 11, crystalTopY + 11, crystalBottomX - 11, crystalBottomY - 11, 255, 255, 255);
	myLine(crystalTopX - 12, crystalTopY + 12, crystalBottomX - 12, crystalBottomY - 12, 255, 255, 255);
	myLine(crystalTopX - 13, crystalTopY + 13, crystalBottomX - 13, crystalBottomY - 13, 255, 255, 255);
	myLine(crystalTopX - 14, crystalTopY + 14, crystalBottomX - 14, crystalBottomY - 14, 255, 255, 255);
	myLine(crystalBottomX, crystalBottomY, crystalrightpointx, crystalrightpointy, 0, 0, 204); // bottom right
	myLine(crystalrightpointx, crystalrightpointy, crystalTopX, crystalTopY, 0, 0, 204);	   // top right
	myLine(crystalTopX, crystalTopY, crystalleftpointx, crystalleftpointy, 0, 0, 204);		   // top left
	myLine(crystalleftpointx, crystalleftpointy, crystalBottomX, crystalBottomY, 0, 0, 204);   // bottom left
}

void drawCircleInBlock(int i, int j)
{
	int blocktodrawx = BOARD_START_X + j * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + i * BLOCK_SIZE; // shape to fill in an board

	int pointx1 = blocktodrawx + SHAPE_DIFF;
	int pointy1 = blocktodrawy + SHAPE_DIFF;

	int pointx2 = blocktodrawx + 50 - SHAPE_DIFF;
	int pointy2 = blocktodrawy + 50 - SHAPE_DIFF;

	myEllipse(pointx1, pointy1, pointx2, pointy2, 255, 0, 0);
}
void drawCircleInBlock_white(int i, int j)
{
	int blocktodrawx = BOARD_START_X + j * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + i * BLOCK_SIZE; // shape to fill in an board

	int pointx1 = blocktodrawx + SHAPE_DIFF;
	int pointy1 = blocktodrawy + SHAPE_DIFF;

	int pointx2 = blocktodrawx + 50 - SHAPE_DIFF;
	int pointy2 = blocktodrawy + 50 - SHAPE_DIFF;

	myEllipse(pointx1, pointy1, pointx2, pointy2, 255, 255, 255);
}

void drawDiamondInBlock(int i, int j)
{
	int blocktodrawx = BOARD_START_X + j * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + i * BLOCK_SIZE; // shape to fill in an board

	int diamondleftpointx = blocktodrawx + SHAPE_DIFF; // left point
	int diamondleftpointy = blocktodrawy + 7 + SHAPE_DIFF;

	int diamondupperleftpointx = blocktodrawx + 4 + SHAPE_DIFF; // upper left point
	int diamondupperleftpointy = blocktodrawy + 10;

	int diamondupperrightpointx = blocktodrawx + 20 + SHAPE_DIFF; // upper right point
	int diamondupperrightpointy = blocktodrawy + 10;

	int diamondrightpointx = blocktodrawx + 24 + SHAPE_DIFF; // right point
	int diamondrightpointy = blocktodrawy + 7 + SHAPE_DIFF;

	int diamondbottompointx = blocktodrawx + 22; // bottomm point
	int diamondbottompointy = blocktodrawy + 38;

	myLine(diamondupperleftpointx + 8, diamondupperleftpointy, diamondbottompointx, diamondbottompointy, 255, 140, 0);
	myLine(diamondupperleftpointx + 9, diamondupperleftpointy, diamondbottompointx + 1, diamondbottompointy - 2, 255, 140, 0);
	myLine(diamondupperleftpointx + 10, diamondupperleftpointy, diamondbottompointx + 2, diamondbottompointy - 5, 255, 140, 0);
	myLine(diamondupperleftpointx + 11, diamondupperleftpointy, diamondbottompointx + 3, diamondbottompointy - 7, 255, 140, 0);
	myLine(diamondupperleftpointx + 12, diamondupperleftpointy, diamondbottompointx + 4, diamondbottompointy - 9, 255, 140, 0);
	myLine(diamondupperleftpointx + 13, diamondupperleftpointy, diamondbottompointx + 5, diamondbottompointy - 11, 255, 140, 0);
	myLine(diamondupperleftpointx + 14, diamondupperleftpointy, diamondbottompointx + 6, diamondbottompointy - 13, 255, 140, 0);
	myLine(diamondupperleftpointx + 15, diamondupperleftpointy, diamondbottompointx + 7, diamondbottompointy - 15, 255, 140, 0);
	myLine(diamondupperleftpointx + 16, diamondupperleftpointy + 1, diamondbottompointx + 8, diamondbottompointy - 16, 255, 140, 0);
	myLine(diamondupperleftpointx + 17, diamondupperleftpointy + 2, diamondbottompointx + 9, diamondbottompointy - 18, 255, 140, 0);
	myLine(diamondupperleftpointx + 18, diamondupperleftpointy + 4, diamondbottompointx + 11, diamondbottompointy - 19, 255, 140, 0);
	myLine(diamondupperleftpointx + 7, diamondupperleftpointy, diamondbottompointx - 1, diamondbottompointy - 2, 255, 140, 0);
	myLine(diamondupperleftpointx + 6, diamondupperleftpointy, diamondbottompointx - 2, diamondbottompointy - 4, 255, 140, 0);
	myLine(diamondupperleftpointx + 5, diamondupperleftpointy, diamondbottompointx - 3, diamondbottompointy - 6, 255, 140, 0);
	myLine(diamondupperleftpointx + 4, diamondupperleftpointy, diamondbottompointx - 4, diamondbottompointy - 8, 255, 140, 0);
	myLine(diamondupperleftpointx + 3, diamondupperleftpointy, diamondbottompointx - 5, diamondbottompointy - 10, 255, 140, 0);
	myLine(diamondupperleftpointx + 2, diamondupperleftpointy, diamondbottompointx - 6, diamondbottompointy - 12, 255, 140, 0);
	myLine(diamondupperleftpointx + 1, diamondupperleftpointy + 2, diamondbottompointx - 7, diamondbottompointy - 14, 255, 140, 0);
	myLine(diamondupperleftpointx, diamondupperleftpointy + 2, diamondbottompointx - 9, diamondbottompointy - 16, 255, 140, 0);
	myLine(diamondupperleftpointx - 1, diamondupperleftpointy + 3, diamondbottompointx - 11, diamondbottompointy - 18, 255, 140, 0);
	myLine(diamondleftpointx, diamondleftpointy, diamondupperleftpointx, diamondupperleftpointy, 120, 51, 0);
	myLine(diamondleftpointx, diamondleftpointy, diamondbottompointx, diamondbottompointy, 120, 51, 0);
	myLine(diamondupperleftpointx, diamondupperleftpointy, diamondupperrightpointx, diamondupperrightpointy, 120, 51, 0);
	myLine(diamondupperrightpointx, diamondupperrightpointy, diamondrightpointx, diamondrightpointy, 120, 51, 0);
	myLine(diamondrightpointx, diamondrightpointy, diamondbottompointx, diamondbottompointy, 120, 51, 0);
}
void drawDiamondInBlock_white(int i, int j)
{
	int blocktodrawx = BOARD_START_X + j * BLOCK_SIZE; // shape to fill in an board
	int blocktodrawy = BOARD_START_Y + i * BLOCK_SIZE; // shape to fill in an board

	int diamondleftpointx = blocktodrawx + SHAPE_DIFF; // left point
	int diamondleftpointy = blocktodrawy + 7 + SHAPE_DIFF;

	int diamondupperleftpointx = blocktodrawx + 4 + SHAPE_DIFF; // upper left point
	int diamondupperleftpointy = blocktodrawy + 10;

	int diamondupperrightpointx = blocktodrawx + 20 + SHAPE_DIFF; // upper right point
	int diamondupperrightpointy = blocktodrawy + 10;

	int diamondrightpointx = blocktodrawx + 24 + SHAPE_DIFF; // right point
	int diamondrightpointy = blocktodrawy + 7 + SHAPE_DIFF;

	int diamondbottompointx = blocktodrawx + 22; // bottomm point
	int diamondbottompointy = blocktodrawy + 38;

	myLine(diamondupperleftpointx + 8, diamondupperleftpointy, diamondbottompointx, diamondbottompointy, 255, 255, 255);
	myLine(diamondupperleftpointx + 9, diamondupperleftpointy, diamondbottompointx + 1, diamondbottompointy - 2, 255, 255, 0);
	myLine(diamondupperleftpointx + 10, diamondupperleftpointy, diamondbottompointx + 2, diamondbottompointy - 5, 255, 255, 255);
	myLine(diamondupperleftpointx + 11, diamondupperleftpointy, diamondbottompointx + 3, diamondbottompointy - 7, 255, 255, 255);
	myLine(diamondupperleftpointx + 12, diamondupperleftpointy, diamondbottompointx + 4, diamondbottompointy - 9, 255, 255, 255);
	myLine(diamondupperleftpointx + 13, diamondupperleftpointy, diamondbottompointx + 5, diamondbottompointy - 11, 255, 255, 255);
	myLine(diamondupperleftpointx + 14, diamondupperleftpointy, diamondbottompointx + 6, diamondbottompointy - 13, 255, 255, 255);
	myLine(diamondupperleftpointx + 15, diamondupperleftpointy, diamondbottompointx + 7, diamondbottompointy - 15, 255, 255, 255);
	myLine(diamondupperleftpointx + 16, diamondupperleftpointy + 1, diamondbottompointx + 8, diamondbottompointy - 16, 255, 255, 255);
	myLine(diamondupperleftpointx + 17, diamondupperleftpointy + 2, diamondbottompointx + 9, diamondbottompointy - 18, 255, 255, 255);
	myLine(diamondupperleftpointx + 18, diamondupperleftpointy + 4, diamondbottompointx + 11, diamondbottompointy - 19, 255, 255, 255);
	myLine(diamondupperleftpointx + 7, diamondupperleftpointy, diamondbottompointx - 1, diamondbottompointy - 2, 255, 255, 255);
	myLine(diamondupperleftpointx + 6, diamondupperleftpointy, diamondbottompointx - 2, diamondbottompointy - 4, 255, 255, 255);
	myLine(diamondupperleftpointx + 5, diamondupperleftpointy, diamondbottompointx - 3, diamondbottompointy - 6, 255, 255, 255);
	myLine(diamondupperleftpointx + 4, diamondupperleftpointy, diamondbottompointx - 4, diamondbottompointy - 8, 255, 255, 255);
	myLine(diamondupperleftpointx + 3, diamondupperleftpointy, diamondbottompointx - 5, diamondbottompointy - 10, 255, 255, 255);
	myLine(diamondupperleftpointx + 2, diamondupperleftpointy, diamondbottompointx - 6, diamondbottompointy - 12, 255, 255, 255);
	myLine(diamondupperleftpointx + 1, diamondupperleftpointy + 2, diamondbottompointx - 7, diamondbottompointy - 14, 255, 255, 255);
	myLine(diamondupperleftpointx, diamondupperleftpointy + 2, diamondbottompointx - 9, diamondbottompointy - 16, 255, 255, 255);
	myLine(diamondupperleftpointx - 1, diamondupperleftpointy + 3, diamondbottompointx - 11, diamondbottompointy - 18, 255, 255, 255);
	myLine(diamondleftpointx, diamondleftpointy, diamondupperleftpointx, diamondupperleftpointy, 120, 51, 0);
	myLine(diamondleftpointx, diamondleftpointy, diamondbottompointx, diamondbottompointy, 120, 51, 0);
	myLine(diamondupperleftpointx, diamondupperleftpointy, diamondupperrightpointx, diamondupperrightpointy, 120, 51, 0);
	myLine(diamondupperrightpointx, diamondupperrightpointy, diamondrightpointx, diamondrightpointy, 120, 51, 0);
	myLine(diamondrightpointx, diamondrightpointy, diamondbottompointx, diamondbottompointy, 120, 51, 0);
}

// to print game

void game_set(int board[8][8])
{
	// for different shapes in whole board
	srand(time(0));

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = rand() % 5 + 1;
		}
	}
}
void boardPrint()
{
	// system("cls");
	grid();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			if (board[i][j] == 1)
			{
				drawSquareInBlock(i, j);
			}

			if (board[i][j] == 2)
			{
				drawCrystalInBlock(i, j);
			}

			if (board[i][j] == 3)
			{
				drawDiamondInBlock(i, j);
			}

			if (board[i][j] == 4)
			{
				drawTriangleInBlock(i, j);
			}
			if (board[i][j] == 5)
			{
				drawCircleInBlock(i, j);
			}
			if (board[i][j] == 6)
			{
				drawSquareInBlock_white(i, j);
			}
			if (board[i][j] == 7)
			{
				drawCrystalInBlock_white(i, j);
			}
			if (board[i][j] == 8)
			{
				drawDiamondInBlock_white(i, j);
			}
			if (board[i][j] == 9)
			{
				drawTriangleInBlock_white(i, j);
			}
			if (board[i][j] == 10)
			{
				drawCircleInBlock_white(i, j);
			}
			if (board[i][j] >= 11)
			{
				int blocktodrawx = BOARD_START_X + j * BLOCK_SIZE;
				int blocktodrawy = BOARD_START_Y + (BLOCK_SIZE * i);
				int squareBottomLeftX = blocktodrawx + 50 - SHAPE_DIFF;
				int squareBottomLeftY = blocktodrawy + SHAPE_DIFF;

				int squareTopRightX = blocktodrawx + SHAPE_DIFF;
				int squareTopRightY = blocktodrawy + 50 - SHAPE_DIFF;
				myLine(squareBottomLeftX, squareBottomLeftY, squareTopRightX, squareTopRightY, 255, 255, 255);
			}
		}
	}
}
int new_value()
{
	int check = rand() % 5 + 1;
	return check;
}

//!CHANGINGS
int left_right_3()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			{
				if (j <= 5&&board[i][j + 1] == board[i][j] && board[i][j] == board[i][j + 2])
				{
					int col = j;
					for (; col <= j + 2; col++)
					{
						int row = i;
						while (row >= 1)
						{
							board[row][col] = board[row - 1][col];
							row--;
						}
						while (row >= 0)
						{
							board[row][col] = new_value();
							row--;
						}
					}
					return 1;
				}
			}
		}
	}
	return 0;
}
//CHANGINGS
int up_down_3()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i <= 5)
			{
				if (board[i + 1][j] == board[i][j] && board[i][j] == board[i + 2][j])
				{
					int row = i + 2;
					while (row >= 3)
					{
						board[row][j] = board[row-- - 3][j];
					}
					row = 2;
					while (row >= 0)
					{
						board[row][j] = new_value();
						row--;
					}
					return 1;
				}
			}
		}
	}
	return 0;
}
//CHANGINGS
int left_right_4(int &score)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j <= 4)
			{
				if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3])
				{
					board[i][j] = board[i][j] + 5;
					while (left_right_3())
						score += 3;
					return 1;
				}
			}
		}
	}
	return 0;
}
//CHANGINGS
int up_down_4(int &score)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i <= 4)
			{
				if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j])
				{
					board[i + 3][j] = board[i + 3][j] + 5;
					while (up_down_3())
					{
						score += 3;
					}
					return 1;
				}
			}
		}
	}
	return 0;
}
//CHANGINGS
int left_right_5()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j <= 3)
			{
				if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4])
				{
					board[i][j] = board[i][j] + 10;
					int col = j + 1;
					for (; col <= j + 4; col++)
					{
						int row = i;
						while (row >= 1)
						{
							board[row][col] = board[row - 1][col];
							row--;
						}
						while (row >= 0)
						{
							board[row][col] = new_value();
							row--;
						}
					}
					return 1;
				}
			}
		}
	}
	return 0;
}
//CHANGINGS
int up_down_5()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i <= 3)
			{
				if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j] && board[i][j] == board[i + 4][j])
				{
					board[i + 4][j] = board[i + 4][j] + 20;
					int row = i + 3;
					while (row >= 4)
					{
						board[row][j] = board[row-- - 4][j];
					}
					row = 3;
					while (row >= 0)
					{
						board[row--][j] = new_value();
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

bool plus_destroy_checking_up_down(int i, int j)
{
	int check = board[i][j];
	check -= 10;
	bool flag = 0;
	if (i <= 5 && check == board[i + 1][j] && check == board[i + 2][j])
		return 1;
	if (i > 0 && i < 7 && check == board[i + 1][j] && check == board[i - 1][j])
	{
		return 1;
	}
	if (i >= 2 && check == board[i - 1][j] && check == board[i - 2][j])
	{
		return 1;
	}
	return 0;
}

bool plus_destroy_checking_left_right(int i, int j)
{
	int check = board[i][j];
	check -= 10;
	if (i < 6 && check == board[i + 1][j] && check == board[i + 2][j])
	{
		return true;
	}
	if (i > 0 && i < 7 && check == board[i + 1][j] && check == board[i - 1][j])
	{
		return true;
	}
	if (i >= 2 && check == board[i - 1][j] && check == board[i - 2][j])
	{
		return true;
	}
	return false;
}
//CHANGINGS
void plus_destroy(int i, int j)
{
	int row = i;
	int col = j;
	row = 7;
	while (row >= 0)
	{
		board[row][j] = new_value();
		row--;
	}
	for (col = 0; col < 7; col++)
	{
		row = i;
		while (row >= 1)
		{
			board[row][col] = board[row - 1][col];
			row--;
		}
		while (row >= 0)
		{
			board[row][col] = new_value();
			row--;
		}
	}
}
bool plus_destroy()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 11 || board[i][j] == 13 || board[i][j] == 12 || board[i][j] == 15 || board[i][j] == 14)
			{
				if (plus_destroy_checking_up_down(i, j))
				{
					plus_destroy(i, j);
					return true;
				}
				if (plus_destroy_checking_left_right(i, j))
				{
					plus_destroy(i, j);
					return true;
				}
			}
		}
	}
	return false;
}
//CHANGINGS
void destroy_radius(int i, int j)
{
	if (i == 0 && j == 0)
	{
		board[i][j + 1] = new_value();
		board[i + 1][j] = new_value();
		board[i][j] = new_value();
		board[i + 1][j + 1] = new_value();
	}
	else if (i == 7 && j == 0)
	{
		int row = 7;
		while (row >= 2)
		{
			board[row][j + 1] = board[row - 2][j + 1];
			board[row][j] = board[row - 2][j];
			row--;
		}
		while (row >= 0)
		{
			board[row][j + 1] = new_value();
			board[row][j] = new_value();
			row--;
		}
	}
	else if (i > 0 && i < 7 && j == 0)
	{
		int row = i + 1;
		while (row >= 3)
		{
			board[row][j + 1] = board[row - 3][j + 1];
			board[row][j] = board[row - 3][j];
			row--;
		}
		while (row >= 0)
		{
			board[row][j + 1] = new_value();
			board[row][j] = new_value();
			row--;
		}
	}
	else if (i == 0 && j == 7)
	{
		board[i][j] = new_value();
		board[i + 1][j - 1] = new_value();
		board[i + 1][j] = new_value();
		board[i][j - 1] = new_value();
	}
	else if (i == 7 && j == 7)
	{
		int row = 7;
		while (row >= 2)
		{
			board[row][j] = board[row - 2][j];
			board[row][j - 1] = board[row - 2][j - 1];
			row--;
		}
		while (row >= 0)
		{
			board[row][j - 1] = new_value();
			board[row][j] = new_value();
			row--;
		}
	}
	else if (i > 0 && i < 7 && j == 7)
	{
		int row = i + 1;
		while (row >= 3)
		{
			board[row][j - 1] = board[row - 3][j - 1];
			board[row][j] = board[row - 3][j];
			row--;
		}
		while (row >= 0)
		{
			board[row][j - 1] = new_value();
			board[row][j] = new_value();
			row--;
		}
	}
	else if (i == 0 && j > 0 && j < 7)
	{
		board[i + 1][j - 1] = new_value();
		board[i][j] = new_value();
		board[i + 1][j] = new_value();
		board[i][j + 1] = new_value();
		board[i + 1][j + 1] = new_value();
		board[i][j - 1] = new_value();
	}
	else if (i == 7 && j > 0 && j < 7)
	{
		int col = j - 1;
		for (; col <= j + 1; col++)
		{
			int row = 7;
			while (row >= 2)
			{
				board[row][col] = board[row - 2][col];
				row--;
			}
			while (row >= 0)
			{
				board[row][col] = new_value();
				row--;
			}
		}
	}
	else if (i > 0 && i < 7 && j > 0 && j < 7)
	{
		int col = j - 1;
		for (; col <= j + 1; col++)
		{
			int row = i + 1;
			while (row >= 3)
			{
				board[row][col] = board[row - 3][col];
				row--;
			}
			while (row >= 0)
			{
				board[row][col] = new_value();
				row--;
			}
		}
	}
}

bool destroy_radius_check_up_down(int i, int j)
{
	int check = board[i][j];
	check -= 5;
	if (i < 6 && check == board[i + 1][j] && check == board[i + 2][j])
	{
		return true;
	}
	if (i > 0 && i < 7 && check == board[i + 1][j] && check == board[i - 1][j])
	{
		return true;
	}
	if (i >= 2 && check == board[i - 1][j] && check == board[i - 2][j])
	{
		return true;
	}
	return false;
}

bool destroy_radius_check_left_right(int i, int j)
{
	int check = board[i][j];
	check -= 5;

	if (j < 6 && check == board[i][j + 1] && check == board[i][j + 2])
	{
		return true;
	}
	if (j > 0 && j < 7 && check == board[i][j + 1] && check == board[i][j - 1])
	{
		return true;
	}
	if (j >= 2 && check == board[i][j - 1] && check == board[i][j - 2])
	{
		return true;
	}
	return false;
}

bool destroy_radius()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 6 || board[i][j] == 10 || board[i][j] == 7 || board[i][j] == 8 || board[i][j] == 9)
			{
				if (destroy_radius_check_up_down(i, j))
				{
					destroy_radius(i, j);
					return true;
				}
				if (destroy_radius_check_left_right(i, j))
				{
					destroy_radius(i, j);
					return true;
				}
			}
		}
	}
	return false;
}

void matching_check(int &score)
{
	while (plus_destroy())
	{
		score += 10;
		system("cls");
		boardPrint();
	}
	while (destroy_radius())
	{
		score += 6;
		system("cls");
		boardPrint();
	}
	while (up_down_5())
	{
		score += 4;
		system("cls");
		boardPrint();
	}
	while (left_right_5())
	{
		score += 4;
		system("cls");
		boardPrint();
	}
	while (up_down_4(score))
	{
		score += 1;
		system("cls");
		boardPrint();
	}
	while (left_right_4(score))
	{
		score += 1;
		system("cls");
		boardPrint();
	}
	while (left_right_3())
	{
		score += 3;
		system("cls");
		boardPrint();
	}
	while (up_down_3())
	{
		score += 3;
		system("cls");
		boardPrint();
	}
}

void grid()
{
	int r = 0, c = 0;
	for (int i = 0; i < 9; i++)
	{
		myLine(BOARD_START_X + (BLOCK_SIZE * NO_BLOCKS_IN_BOARD), BOARD_START_Y + c, BOARD_START_X, BOARD_START_Y + c, 105, 105, 105); // upper line
		c = c + BLOCK_SIZE;

		myLine(BOARD_START_X + r, BOARD_START_Y + (BLOCK_SIZE * NO_BLOCKS_IN_BOARD), BOARD_START_X + r, BOARD_START_Y, 105, 105, 105); // left line
		r = r + BLOCK_SIZE;
	}
}

void cursorout()
{
	int r = 0, c = 0;
	int key = 0;
	int x = 50;
	int y = 50; // no swap on other coordinates
	// myLine(x, y, x + 50, y, 255, 255, 255);
	// myLine(x + 50, y, x + 50, y + 50, 255, 255, 255);
	// myLine(x, y + 50, x + 50, y + 50, 255, 255, 255);
	// myLine(x, y, x, y + 50, 255, 255, 255);
	int score = 0;
	int clock = 200;
	boardPrint();
	while (1)
	{
		if (clock < 0)
		{
			system("cls");
			cout << "Your score is: " << score << endl;
			Sleep(10000);
			break;
		}
		else
		{
			gotoxy(0, 0);
			cout << clock;
			Sleep(250);
			matching_check(score);
			if (isCursorKeyPressed(key))
			{

				myLine(x, y, x + 50, y, 0, 0, 0);
				myLine(x + 50, y, x + 50, y + 50, 0, 0, 0);
				myLine(x, y + 50, x + 50, y + 50, 0, 0, 0);
				myLine(x, y, x, y + 50, 0, 0, 0);
				if (key == 1)
				{
					if (x >= 100) // left
					{
						x = x - 50;
						c--;
					}
				}
				if (key == 2) // up
				{
					if (y >= 100)
					{
						y = y - 50;
						r--;
					}
				}
				if (key == 3) //  right
				{
					if (x <= 350)
					{
						c++;
						x = x + 50;
					}
				}
				if (key == 4) // down
				{
					if (y <= 350)
					{
						r++;
						y = y + 50;
					}
				}
				if (key == 5)
				{
					while (true)
					{
						if (isCursorKeyPressed(key))
						{
							system("cls");
							if (key == 1 && c != 0) // condition for the cursor to not exceed the border limit
							{
								swap(board[r][c], board[r][c - 1]); // left
							}
							if (key == 2 && r != 0)
							{
								swap(board[r][c], board[r - 1][c]);
							}
							if (key == 3 && c != 8)
							{
								swap(board[r][c], board[r][c + 1]);
							}
							if (key == 4 && r != 8)
							{
								swap(board[r][c], board[r + 1][c]);
							}

							boardPrint();
							break;
						}
					}
				}
				myLine(x, y, x + 50, y, 255, 255, 255);
				myLine(x + 50, y, x + 50, y + 50, 255, 255, 255);
				myLine(x, y + 50, x + 50, y + 50, 255, 255, 255);
				myLine(x, y, x, y + 50, 255, 255, 255);
			}
			clock--;
		}
	}
}
int main()
{

	game_set(board);
	grid();
	boardPrint();
	cursorout();
	return 0;
}