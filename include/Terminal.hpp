#pragma once

#include "Foundation.hpp"

#if defined(__OS_WINDOWS__)
#include <windows.h>
#endif

class ITerminal
{
public:
	virtual void ClearScreen() = 0;
	virtual char ReadChar() = 0;
	virtual void WriteStringAt(String const& string, usize row, usize col) = 0;
};

#if  defined(__OS_WINDOWS__)
class Terminal final : public ITerminal
{
public:
	Terminal();
	~Terminal();
	void ClearScreen() override;
	char ReadChar() override;
	void WriteStringAt(String const& string, usize row, usize col) override;
private:
	void MoveCursor(usize row, usize col);
	void WriteStringThrows(String const& string);
	HANDLE standardInput;
	HANDLE standardOutput;
	DWORD originalStandardInputMode;
	DWORD originalStandardOutputMode;
	DWORD standardInputMode;
	DWORD standardOutputMode;
	usize mRow;
	usize mCol;
};
#endif

#if defined(__OS_APPLE__) || defined(__OS_LINUX__)
class Terminal final : public ITerminal
{
public:
	virtual void WriteStringAt(String const& string, usize row, usize col) = 0;
};
#endif
