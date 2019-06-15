#include <windows.h>
#include <conio.h>
#include "pstring.h"

const int max_levels_count = 100;
const HANDLE _CONWIN = GetStdHandle(STD_OUTPUT_HANDLE);

class cell
{
private:
	COORD cell_coords;
	char symbolstack_char_1[max_levels_count];
	int visible_level;
public:
	cell(): visible_level(0){}
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
		// Output symbol from symbolstack
		SetConsoleCursorPosition(_CONWIN, cell_coords);
		printf("%c", symbolstack_char_1[visible_level]);

		return visible_level;
	}
	void SetSymbol(const unsigned char INnew_symbol)
	{
		if(visible_level < max_levels_count)
			symbolstack_char_1[visible_level] = INnew_symbol;
		// Output symbol from symbolstack
		SetConsoleCursorPosition(_CONWIN, cell_coords);
		printf("%c", symbolstack_char_1[visible_level]);
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
			visible_level--;
		}
		// Output symbol from symbolstack
		SetConsoleCursorPosition(_CONWIN, cell_coords);
		printf("%c", symbolstack_char_1[visible_level]);
	}
};