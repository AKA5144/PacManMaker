#ifndef GAMELIB_H
#define GAMELIB_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h> // for srand
#include <math.h>
#include <wchar.h>
#include <string.h>
#include <time.h> // for rand
#include <windows.h>

//#define _C
#define _CPP

#define PI 3.14159265
#define ESC "\x1b"
#define CSI "\x1b["

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

#ifdef _CPP
#include <iostream>
#include <fstream>
#include <vector>
#endif

// Customized types

enum Clear
{
	CLEAR_FROM_CURSOR_TO_END,
	CLEAR_FROM_CURSOR_TO_BEGIN,
	CLEAR_ALL
};

typedef enum Players
{
	player1 = 1,
	player2
}Players;

typedef enum ColorIntensity
{
	DARK,
	BRIGHT
}ColorIntensity;

typedef enum Color
{
	COLOR_RESET_COLOR,
	COLOR_TXT_BLACK = 30,
	COLOR_TXT_RED,
	COLOR_TXT_GREEN,
	COLOR_TXT_YELLOW,
	COLOR_TXT_BLUE,
	COLOR_TXT_MAGENTA,
	COLOR_TXT_CYAN,
	COLOR_TXT_WHITE,
	
	COLOR_BKG_BLACK = 40,
	COLOR_BKG_RED,
	COLOR_BKG_GREEN,
	COLOR_BKG_YELLOW,
	COLOR_BKG_BLUE,
	COLOR_BKG_MAGENTA,
	COLOR_BKG_CYAN,
	COLOR_BKG_WHITE
}Color;

typedef struct WindowSize
{
	int x;
	int y;
}WindowSize;

typedef struct Grid
{
	int numLines;
	int numCol;
	int squareSize;
	int Start_X;
	int End_X;
	int Start_Y;
	int Width;
}Grid;

typedef struct Pos
{
	int x;
	int y;
}Pos;

// **************************
// Function prototypes
// **************************

// Init functions

bool EnableVTMode();
bool InitKbInput(HANDLE* _hIn);
WindowSize InitDisplay();

// Input functions

WORD getKey(HANDLE* _hIn);
#ifdef _CPP
int getKey();
#endif

void ClearScreen(enum Clear _clearCode);
void moveUp(int positions);
void moveDown(int positions);
void moveRight(int positions);
void moveLeft(int positions);

void moveTo(int row, int col);
void SetTxtColor(Color _color);
void SetBkGrndColor(Color _color);
void SetTxtColorBright(Color _color);
void SetBkGrndColorBright(Color _color);
void ResetColor();
void DrawVerticalLine(Color _center, Color _around, ColorIntensity _intensity);
void DrawHorizontalLine(bool IsTop, Color _center, Color _around, ColorIntensity _intensity, int _from, int _to);
void PrintStatusLine(const char* const pszMessage, WindowSize const Size);

// Here, row and col are in units of the grid cells
void DrawSquareInGrid(Color _color, ColorIntensity _intensity, Grid _grid, int _x, int _y);
void DrawSquare(Color _color, ColorIntensity _intensity, int _x, int _y);
void DrawGridLines(Grid _grid, Color _colorCenterLine, Color _colorAroundLine, ColorIntensity _intensity);
bool IsColorConsoleSet(bool _success, HANDLE _hOut);
void CloseDisplay();
void DrawTextLine(WindowSize _winSize, Color _textCol, Color _bkgndCol, Pos _pos, char* _string);
void DrawLetter(WindowSize _winSize, Color _textCol, Color _bkgndCol, Pos _pos, char _letter);
void ClearLine();
void Blink();
void Unblink();

#endif