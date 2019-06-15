#include <windows.h>
#include <conio.h>
#include "pstring.h"

const int max_levels_count = 100;
const unsigned char default_symbol = 0/*'+'*//*0*/;
const HANDLE _CONWIN = GetStdHandle(STD_OUTPUT_HANDLE);

int vision_width = 120;
int vision_height = 29;
CONSOLE_CURSOR_INFO _CCI;

class cell
{
private:
	COORD cell_coords;
	char symbolstack_char_1[max_levels_count];
	int visible_level;
public:
	cell(): visible_level(0)
	{
		int c1;

		// Set default value
		for(c1 = 0; c1 < max_levels_count; c1++)
			symbolstack_char_1[c1] = default_symbol;
	}
	cell(cell &INcell): visible_level(0)
	{
		int c1;

		// Copy coords
		cell_coords = INcell.cell_coords;
		// Copy symbolstack
		for(c1 = 0; c1 < max_levels_count; c1++)
			symbolstack_char_1[c1] = INcell.symbolstack_char_1[c1];
		// Copy visible level
		visible_level = INcell.visible_level;
	}
	~cell() {}
	void SetCoords(const COORD &INcell_coords)
	{
		// Set coords
		cell_coords = INcell_coords;
	}
	int AddSymbol(const unsigned char INnew_symbol)
	{
		visible_level++;
		if(visible_level < max_levels_count)
		{
			//visible_level++;
			symbolstack_char_1[visible_level] = INnew_symbol;
		}
		Show();

		return visible_level;
	}
	void SetSymbol(const unsigned char INnew_symbol)
	{
		if(visible_level < max_levels_count)
			symbolstack_char_1[visible_level] = INnew_symbol;
		Show();
	}
	void DeleteSymbol(int INsymbol_level)
	{
		int c1;

		// Deleting
		if(visible_level > 0)
		{
			// // Offset
			for(c1 = INsymbol_level; c1 < visible_level; c1++)
				symbolstack_char_1[c1] = symbolstack_char_1[c1 + 1];
			symbolstack_char_1[c1] = default_symbol;
			visible_level--;
		}
	}
	void Show() const
	{
		// Output symbol from symbolstack
		SetConsoleCursorPosition(_CONWIN, cell_coords);
		printf("%c", symbolstack_char_1[visible_level]);
	}
};

cell *_VISION_cell_1;

void VisionInicialisation()
{
	int c1;
	COORD current_coords;

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
		_VISION_cell_1[c1].Show();
	}
}