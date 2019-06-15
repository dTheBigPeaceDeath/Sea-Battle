#include "conwin.h"

const unsigned char fieldcell = '.';

button _EXIT = {"Exit", 'e', ExitProgramm};
button _S1 = {"S-class(1 cell)", '1', CloseWindow};
button _S2 = {"U-class(2 cell)", '2', CloseWindow};
button _S3 = {"L-class(3 cell)", '3', CloseWindow};
button _S4 = {"UL-class(4 cell)", '4', CloseWindow};
button _CLOSE = {"Close", 'c', CloseWindow};

void Fields(void *IN_DATA_1);
void AddShip(void *IN_DATA_1);

void PrintField(window_printer &INwindow_printer);

void Inicialisation()
{
	VisionInicialisation();
	
	// WINDOWS
	static window_manager _MAIN(118, 27, 0, 0, "Sea Battle");
	

	// BUTTONS
	static button _PLAY = {"Play", 'p', Fields};
	
	// ADDING
	_MAIN.AddButton(_PLAY);
	_MAIN.AddButton(_EXIT);
	_MAIN.Open();
}

void Fields(void *IN_DATA_1)
{
	static window_printer _FIELD(32, 15, 0, 0, "Battle");
	static window_manager _COMMANDS(15, 15, 34, 0, "Commands");
	static window_messenger _OUTPUT(49, 5, 0, 17, "Output");

	button _ADDSHIP = {"Add Ship", 'a', AddShip};

	_COMMANDS.AddButton(_ADDSHIP);
	_COMMANDS.AddButton(_EXIT);

	_OPENED_window_manager_1[window_managers_count - 1]->Close();
	_FIELD.Open();
	_COMMANDS.Open();
	_OUTPUT.Open();
	PrintField(_FIELD);
	message m1 = {"if you cant press \"e\" i cant stop writing"};
	for(; _getch() != 'e';)
	{
		_OUTPUT.Output(m1);
		m1.text += '.';
	}
}

void PrintField(window_printer &INwindow_printer)
{
	int c1, c2;

	// Print Oy in main field
	for(c1 = 0; c1 < 9; c1++)
		INwindow_printer.Print(1 + 2, c1 + 1 + 2, c1 + 49);
	INwindow_printer.Print(0 + 2, c1 + 1 + 2, 49);
	INwindow_printer.Print(1 + 2, c1 + 1 + 2, 48);
	// Print Ox in main field
	for(c1 = 0; c1 < 10; c1++)
		INwindow_printer.Print(c1 + 2 + 2, 0 + 2, c1 + 97);
	// Print mine field
	for(c1 = 0; c1 < 10; c1++)
		for(c2 = 0; c2 < 10; c2++)
			INwindow_printer.Print(c2 + 2 + 2, c1 + 1 + 2, fieldcell);
	// Print Oy in enemy field
	for(c1 = 0; c1 < 9; c1++)
		INwindow_printer.Print(14 + 5, c1 + 1 + 2, c1 + 49);
	INwindow_printer.Print(13 + 5, c1 + 1 + 2, 49);
	INwindow_printer.Print(14 + 5, c1 + 1 + 2, 48);
	// Print Ox in enemy field
	for(c1 = 0; c1 < 10; c1++)
		INwindow_printer.Print(c1 + 15 + 5, 0 + 2, c1 + 97);
	// Print enemy field
	for(c1 = 0; c1 < 10; c1++)
		for(c2 = 0; c2 < 10; c2++)
			INwindow_printer.Print(c2 + 15 + 5, c1 + 1 + 2, fieldcell);
}

void AddShip(void *IN_DATA_1)
{
	static window_manager _WHAT(20, 15, 34, 0, "What Ship?");
	_WHAT.AddButton(_S1);
	_WHAT.AddButton(_S2);
	_WHAT.AddButton(_S3);
	_WHAT.AddButton(_S4);
	_WHAT.AddButton(_CLOSE);
	_WHAT.Open();
}