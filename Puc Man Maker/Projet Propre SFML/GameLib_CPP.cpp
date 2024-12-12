#include "GameLib_CPP.h"

// Init functions

bool EnableVTMode()
{
	// This output mode handles the virtual terminal
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

bool InitKbInput(HANDLE* _hIn)
{
	*_hIn = GetStdHandle(STD_INPUT_HANDLE);

	if (_hIn == NULL)
	{
		return false; // console not found
	}
	return true;
}

WindowSize InitDisplay()
{
	//First, enable VT mode
	bool fSuccess = EnableVTMode();
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WindowSize ws;

	if (!IsColorConsoleSet(fSuccess, hOut))
	{
		exit(EXIT_FAILURE);
	}

	// Enter the alternate buffer
	printf(CSI "?1049h");
	printf(CSI "?25l");// get rid of cursor

	// Clear screen, tab stops, set, stop at columns 16, 32
	ClearScreen(CLEAR_ALL);

	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &ScreenBufferInfo);

	ws.x = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
	ws.y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;

	return ws;
}

// Input functions

WORD getKey(HANDLE* _hIn)
{
	INPUT_RECORD inRec;
	DWORD cc;

	ReadConsoleInput(_hIn, &inRec, 1, &cc);

	if (inRec.EventType == KEY_EVENT
		&&
		(inRec.Event.KeyEvent).bKeyDown)
	{
		return inRec.Event.KeyEvent.wVirtualKeyCode;
	}
	else return -1;
}

#ifdef _CPP
int getKey()
{
	HANDLE hstdin;
	DWORD  mode;
	int ch;

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hstdin, &mode);
	SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);

	ch = std::cin.get();

	SetConsoleMode(hstdin, mode);
	return ch;
}
#endif

void ClearScreen(enum Clear _clearCode)
{
	printf(CSI "%dJ", _clearCode);
}

void moveUp(int positions)
{
	printf(CSI "%dA", positions);
}

void moveDown(int positions)
{
	printf(CSI "%dB", positions);
}

void moveRight(int positions)
{
	printf(CSI "%dC", positions);
}

void moveLeft(int positions)
{
	printf(CSI "%dD", positions);
}

void moveTo(int row, int col)
{
	printf(CSI "%d;%df", row, col);
}

void SetTxtColor(Color _color)
{
	printf(CSI "%dm", _color);
}

void SetBkGrndColor(Color _color)
{
	printf(CSI "%dm", _color);
}

void SetTxtColorBright(Color _color)
{
	printf(CSI "%d;1m", _color + 60);
}

void SetBkGrndColorBright(Color _color)
{
	printf(CSI "%d;1m", _color + 60);
}

void ResetColor()
{
	printf(CSI "0m");
}

void DrawVerticalLine(Color _center, Color _around, ColorIntensity _intensity)
{
	printf(ESC "(0"); // Enter Line drawing mode

	switch (_intensity)
	{
	case(DARK):
		SetTxtColor(_center);
		SetBkGrndColor(_around);
		break;
	case(BRIGHT):
		SetTxtColorBright(_center);
		SetBkGrndColorBright(_around);
		break;
	default:
		printf("\nColor intensity error!\n");
	}
	printf("x"); // in line drawing mode, \x78 -> \u2502 "Vertical Bar"
	ResetColor();
	printf(ESC "(B"); // exit line drawing mode
}

void DrawHorizontalLine(bool IsTop, Color _center, Color _around, ColorIntensity _intensity, int _from, int _to)
{
	printf(ESC "(0"); // Start Line drawing

	switch (_intensity)
	{
	case(DARK):
		SetTxtColor(_center);
		SetBkGrndColor(_around);
		break;
	case(BRIGHT):
		SetTxtColorBright(_center);
		SetBkGrndColorBright(_around);
		break;
	default:
		printf("\nColor intensity error!\n");
	}

	moveRight(_from);

	printf(IsTop ? "l" : "m"); // draw left corner 

	for (int i = _from; i < _to; i++)
	{
		printf("q");
	}

	printf(IsTop ? "k" : "j"); // draw right corner
	printf(CSI "0m");
	printf(ESC "(B"); // End line drawing
}

void PrintStatusLine(const char* const pszMessage, WindowSize const Size)
{
	printf(CSI "%d;1H", Size.y);
	printf(CSI "K"); // clear the line
	printf(pszMessage);
}

// Here, row and col are in units of the grid cells
void DrawSquareInGrid(Color _color, ColorIntensity _intensity, Grid _grid, int _x, int _y)
{
	int X_Start = _grid.Start_X + _grid.squareSize * (_x - 1) + _x + 1;
	int Y_Start = _grid.Start_Y + _grid.squareSize * (_y - 1) + _y;

	switch (_intensity)
	{
	case(DARK):
		SetTxtColor(_color);
		SetBkGrndColor(_color);
		break;
	case(BRIGHT):
		SetTxtColorBright(_color);
		SetBkGrndColorBright(_color);
		break;
	default:
		printf("\nColor intensity error!\n");
	}

	for (size_t row = 0; row < _grid.squareSize; row++)
	{
		for (size_t col = 0; col < _grid.squareSize; col++)
		{
			moveTo(Y_Start + row, X_Start + col);
			printf(" ");
		}
	}
}

void DrawSquare(Color _color, ColorIntensity _intensity, int _x, int _y)
{
	switch (_intensity)
	{
	case(DARK):
		SetTxtColor(_color);
		SetBkGrndColor(_color);
		break;
	case(BRIGHT):
		SetTxtColorBright(_color);
		SetBkGrndColorBright(_color);
		break;
	default:
		printf("\nColor intensity error!\n");
	}

	moveTo(_y, _x);
	printf(" ");
}

void DrawGridLines(Grid _grid, Color _colorCenterLine, Color _colorAroundLine, ColorIntensity _intensity)
{
	// draw game grid, starts at 3rd row
	for (int line = 0; line < _grid.numLines + 1; line++)
	{
		moveTo(_grid.Start_Y + line * _grid.squareSize + line, 1);
		if (line == _grid.numLines)
		{
			DrawHorizontalLine(false, _colorCenterLine, _colorAroundLine, _intensity, _grid.Start_X, _grid.End_X);
		}
		else
		{
			DrawHorizontalLine(true, _colorCenterLine, _colorAroundLine, _intensity, _grid.Start_X, _grid.End_X);
		}
	}

	// draw vertical lines
	for (int line = 0; line < _grid.numLines * _grid.squareSize + _grid.numLines - 1; line++)
	{
		moveTo(_grid.Start_Y + 1 + line, _grid.Start_X + 1);
		for (int col = 0; col < _grid.numCol + 1; col++)
		{
			if (col != 0)
			{
				moveRight(_grid.squareSize);
			}
			DrawVerticalLine(_colorCenterLine, _colorAroundLine, _intensity);
		}
	}
}

bool IsColorConsoleSet(bool _success, HANDLE _hOut)
{
	if (!_success)
	{
		printf("Unable to enter VT processing mode. Quitting.\n");
		_getwch();
		return false;
	}

	if (_hOut == INVALID_HANDLE_VALUE)
	{
		printf("Couldn't get the console handle. Quitting.\n");
		_getwch();
		return false;
	}
	return true;
}



void CloseDisplay()
{
	// Exit the alternate buffer
	printf(CSI "?1049l");
}

void DrawTextLine(WindowSize _winSize, Color _textCol, Color _bkgndCol, Pos _pos, char* _string)
{
	SetTxtColor(_textCol);
	SetBkGrndColor(_bkgndCol);
	moveTo(_pos.y, _pos.x);
	printf(_string);
	ResetColor();
}

void DrawLetter(WindowSize _winSize, Color _textCol, Color _bkgndCol, Pos _pos, char _letter)
{
	SetTxtColor(_textCol);
	SetBkGrndColor(_bkgndCol);
	moveTo(_pos.y, _pos.x);
	printf("%c", _letter);
	ResetColor();
}

void ClearLine()
{
	printf(CSI "K");
}

void Blink()
{
	printf(CSI "5m");
}

void Unblink()
{
	printf(CSI "25m");
}
