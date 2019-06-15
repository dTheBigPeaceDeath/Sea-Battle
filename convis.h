#include "concell.h"
#include <fstream>
#include <iostream>

CONSOLE_CURSOR_INFO _CCI;

class vision
{
private:
public:
	cell *_VISION_cell_1;
	int vision_width;
	int vision_height;
	int default_symbol;

	vision()
	{
		int c1;
		COORD current_coords;
		std:: ifstream vis("vis.txt");

		// Set data
		vis >> vision_width;
		vis >> vision_height;
		vis >> default_symbol;

		// Removing the cursor
		_CCI.dwSize = 1;
		_CCI.bVisible = FALSE;
		SetConsoleCursorInfo(_CONWIN, &_CCI);

		// Allocate memory for vision
		_VISION_cell_1 = new cell [vision_width*vision_height];

		// Set coords
		for(c1 = 0; c1 < vision_width*vision_height; c1++)
		{
			current_coords.X = c1%vision_width;
			current_coords.Y = c1/vision_width;
			_VISION_cell_1[c1].SetCoords(current_coords);
			_VISION_cell_1[c1].SetSymbol(default_symbol);
		}
	}
};

vision _VISION;