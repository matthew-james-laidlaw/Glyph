#include <Terminal.hpp>

#include <iostream>

class Controller
{
public:
	void Run()
	{
		terminal.ClearScreen();
		while (true)
		{
			char c = terminal.ReadChar();
			if (c == 'k');
			if (c == 'j');
			if (c == 'h');
			if (c == 'l');
		}
		terminal.WriteStringAt("Hello, World!", 5, 5);
	}
private:
	Terminal terminal;
};


int main()
{
	Controller controller;
	controller.Run();
	return 0;
}
 