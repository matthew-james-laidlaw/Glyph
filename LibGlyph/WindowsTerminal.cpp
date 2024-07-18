#include "Terminal.hpp"

#if defined(__OS_WINDOWS__)

HANDLE GetStdHandleThrows(DWORD identifier)
{
	HANDLE handle = GetStdHandle(identifier);
	if (handle == INVALID_HANDLE_VALUE)
	{
		throw RuntimeError("Error: GetStdHandle");
	}
	return handle;
}

DWORD GetConsoleModeThrows(HANDLE handle)
{
	DWORD mode;
	if (!GetConsoleMode(handle, &mode))
	{
		throw RuntimeError("Error: GetConsoleMode");
	}
	return mode;
}

void SetConsoleModeThrows(HANDLE handle, DWORD mode)
{
	if (!SetConsoleMode(handle, mode))
	{
		throw RuntimeError("Error: SetConsoleMode");
	}
}

Terminal::Terminal()
	: standardInput(GetStdHandleThrows(STD_INPUT_HANDLE))
	, standardOutput(GetStdHandleThrows(STD_OUTPUT_HANDLE))
	, originalStandardInputMode(GetConsoleModeThrows(standardInput))
	, originalStandardOutputMode(GetConsoleModeThrows(standardOutput))
	, standardInputMode(0 | ENABLE_INSERT_MODE | ENABLE_PROCESSED_INPUT | ENABLE_VIRTUAL_TERMINAL_INPUT)
	, standardOutputMode(0 | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING)
	, mRow(1)
	, mCol(1)
{
	SetConsoleModeThrows(standardInput, standardInputMode);
	SetConsoleModeThrows(standardOutput, standardOutputMode);
}

Terminal::~Terminal()
{
	SetConsoleModeThrows(standardInput, originalStandardInputMode);
	SetConsoleModeThrows(standardOutput, originalStandardOutputMode);
}

void Terminal::ClearScreen()
{
	WriteStringThrows("\033[2J");
}

char Terminal::ReadChar()
{
	char c;
	DWORD charsRead;
	ReadConsoleA(standardInput, &c, 1, &charsRead, nullptr);
	return c;
}

void Terminal::WriteStringAt(String const& string, usize row, usize col)
{
	MoveCursor(row, col);
	WriteStringThrows(string);
	MoveCursor(mRow, mCol);
}

void Terminal::MoveCursor(usize row, usize col)
{
	WriteStringThrows("\033[" + std::to_string(row) + ";" + std::to_string(col) + "H");
}

void Terminal::WriteStringThrows(String const& strinde)
{
	DWORD charsWritten;
	WriteConsoleA(standardOutput, strinde.data(), strinde.length(), &charsWritten, nullptr);
	if (charsWritten != strinde.length())
	{
		throw RuntimeError("Error: WriteConsoleA");
	}
}

#endif
