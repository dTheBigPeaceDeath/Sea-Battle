
//************************************************************************CONSOLE WINDOWS********************************************************************************
#include "concell.h"

const int max_window_managers_count = 100;
const int max_buttons_count = 100;
const unsigned char lower_left_corner = 200;
const unsigned char upper_left_corner = 201;
const unsigned char lower_right_corner = 188;
const unsigned char upper_right_corner = 187;
const unsigned char upper_lower_border= 205;
const unsigned char right_left_border= 186;

void CloseWindow(void *IN_DATA_1);
void OpenWindow(void *IN_DATA_1);
void ExitProgramm(void *IN_DATA_1);

/////////////////////////////////////////////////////////////WINDOW FAMILY//////////////////////////////////////////////////////////////////////////////////////////////////
class window
{
protected:
	int window_width;
	int window_height;
	pstring window_label;
	COORD window_coords;
	cell **vision_cell_2;
	int *level_int_1;
public:
	virtual void Open() = 0;
	virtual void Close() = 0;
};

/////////////////////////////////////////////////////////////////WINDOW-MANAGER/////////////////////////////////////////////////////////////////////////////////////////////////
struct button
{
	pstring button_name;
	char button_key;
	void (*command_func_1)(void *data);
	void *data_void_1;
};
class window_manager : public window
{
private:
	button buttonstack_button_1[max_buttons_count];
	int buttons_count;
public:
	window_manager(): buttons_count(0) {}
	window_manager(const int INwindow_width, const int INwindow_height, const int INwindowloc_X, const int INwindowloc_Y, const pstring INwindow_label): buttons_count(0)
	{
		int c1;

		// Set data
		window_width = INwindow_width + 2;
		window_height = INwindow_height + 2;
		window_label = INwindow_label;
		window_coords.X = INwindowloc_X;
		window_coords.Y = INwindowloc_Y;
		// Allocate memory for vision
		vision_cell_2 = new cell* [window_height*window_width];
		// Allocate memory for levels
		level_int_1 = new int [window_height*window_width];
		for(c1 = 0; c1 < window_height*window_width; c1++)
		{
			// // Set pointer
			vision_cell_2[c1] = &_VISION_cell_1[(window_coords.Y + c1/window_width)*vision_width + window_coords.X + c1%window_width];
		}
	}
	window_manager(const window_manager &INwindow): buttons_count(0)
	{
		int c1;

		// Set data
		window_width = INwindow.window_width + 2;
		window_height = INwindow.window_height + 2;
		window_label = INwindow.window_label;
		window_coords = INwindow.window_coords;
		// Allocate memory for vision
		vision_cell_2 = new cell* [window_height*window_width];
		// Allocate memory for levels
		level_int_1 = new int [window_height*window_width];
		for(c1 = 0; c1 < window_height*window_width; c1++)
		{
			// // Set pointer
			vision_cell_2[c1] = &_VISION_cell_1[(window_coords.Y + c1/window_width)*vision_width + window_coords.X + c1%window_width];
		}
	}
	~window_manager() {}
	void AddButton(const button &INadding_button);
	void Open();
	void Close();
	void Input();
};

window_manager *_OPENED_window_manager_1[max_window_managers_count];
int window_managers_count = 0;

void window_manager:: AddButton(const button &INadding_button)
{
	if(buttons_count < max_buttons_count)
	{
		buttonstack_button_1[buttons_count] = INadding_button;
		buttons_count++;
	}
}
void window_manager:: Open()
{
	int c1;

	_OPENED_window_manager_1[window_managers_count] = this;
	window_managers_count++;

	// Add symbols
	for(c1 = 0; c1 < window_height*window_width; c1++)
	{
		if(c1%window_width > 0 && c1%window_width <= window_label.Length() && c1/window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(window_label[c1 - 1]);
		else if(c1/window_width > 0 && c1/window_width <= buttons_count && c1%window_width == 1)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol('(');
		else if(c1/window_width > 0 && c1/window_width <= buttons_count && c1%window_width == 2)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(buttonstack_button_1[c1/window_width - 1].button_key);
		else if(c1/window_width > 0 && c1/window_width <= buttons_count && c1%window_width == 3)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(')');
		else if(c1/window_width > 0 && c1/window_width <= buttons_count && c1%window_width > 3 && c1%window_width < buttonstack_button_1[c1/window_width - 1].button_name.Length() + 4)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(buttonstack_button_1[c1/window_width - 1].button_name[c1%window_width - 4]);
		else if(c1/window_width == 0 && c1%window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_left_corner);
		else if (c1/window_width == window_height - 1 && c1%window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(lower_left_corner);
		else if (c1/window_width == 0 && c1%window_width == window_width - 1)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_right_corner);
		else if (c1/window_width == window_height - 1 && c1%window_width == window_width - 1)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(lower_right_corner);
		else if ((c1/window_width == 0 && c1%window_width != 0) || (c1/window_width == window_height - 1 && c1%window_width != window_width - 1))
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_lower_border);
		else if ((c1/window_width != 0 && c1%window_width == 0) || (c1/window_width != window_height - 1 && c1%window_width == window_width - 1))
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(right_left_border);
		else
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(default_symbol);
	}
}
void window_manager:: Close()
{
	int c1;

	window_managers_count--;
	// Delete symbols
	for(c1 = 0; c1 < window_height*window_width; c1++)
	{
		vision_cell_2[c1]->DeleteSymbol(level_int_1[c1]);
		vision_cell_2[c1]->Show();
	}
}
void window_manager:: Input()
{
	int c1;
	bool found = false;
	char input = _getch();

	// Searching for key i need
	for(c1 = 0; c1 < buttons_count && !found; c1++)
		found = input == buttonstack_button_1[c1].button_key;
	if(found)
	{
		if(buttonstack_button_1[c1 - 1].command_func_1 == OpenWindow)
			buttonstack_button_1[c1 - 1].command_func_1(buttonstack_button_1[c1 - 1].data_void_1);
		else
			buttonstack_button_1[c1 - 1].command_func_1(this);
	}

}

/////////////////////////////////////////////////////////////////////////////WINDOW-MESSENGER/////////////////////////////////////////////////////////////////////////////
struct message
{
	pstring text;
};
class window_messenger : public window
{
private:
	message *messagestack_message_1;
	int messages_count;
public:
	window_messenger(): messages_count(0) {}
	window_messenger(const int INwindow_width, const int INwindow_height, const int INwindowloc_X, const int INwindowloc_Y, const pstring INwindow_label): messages_count(0)
	{
		int c1;

		// Set data
		window_width = INwindow_width + 2;
		window_height = INwindow_height + 2;
		window_label = INwindow_label;
		window_coords.X = INwindowloc_X;
		window_coords.Y = INwindowloc_Y;
		// Allocate memory for vision
		vision_cell_2 = new cell* [window_height*window_width];
		// Allocate memory for levels
		level_int_1 = new int [window_height*window_width];
		for(c1 = 0; c1 < window_height*window_width; c1++)
		{
			// // Set pointer
			vision_cell_2[c1] = &_VISION_cell_1[(window_coords.Y + c1/window_width)*vision_width + window_coords.X + c1%window_width];
		}
		// Allocate memory for messages
		messagestack_message_1 = new message [window_height - 2];
	}
	window_messenger(const window_messenger &INwindow): messages_count(0)
	{
		int c1;

		// Set data
		window_width = INwindow.window_width + 2;
		window_height = INwindow.window_height + 2;
		window_label = INwindow.window_label;
		window_coords = INwindow.window_coords;
		// Allocate memory for vision
		vision_cell_2 = new cell* [window_height*window_width];
		// Allocate memory for levels
		level_int_1 = new int [window_height*window_width];
		for(c1 = 0; c1 < window_height*window_width; c1++)
		{
			// // Set pointer
			vision_cell_2[c1] = &_VISION_cell_1[(window_coords.Y + c1/window_width)*vision_width + window_coords.X + c1%window_width];
		}
		// Allocate memory for messages
		messagestack_message_1 = new message [window_height - 2];
	}
	~window_messenger() {}
	void Open();
	void Close();
	void Write(const pstring INpstring, const int INmessenge_index);
	void Output(const message INoutput_message);
};

void window_messenger:: Open()
{
	int c1;

	// Add symbols
	for(c1 = 0; c1 < window_height*window_width; c1++)
	{
		if(c1%window_width > 0 && c1%window_width <= window_label.Length() && c1/window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(window_label[c1 - 1]);
		else if(c1/window_width == 0 && c1%window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_left_corner);
		else if (c1/window_width == window_height - 1 && c1%window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(lower_left_corner);
		else if (c1/window_width == 0 && c1%window_width == window_width - 1)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_right_corner);
		else if (c1/window_width == window_height - 1 && c1%window_width == window_width - 1)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(lower_right_corner);
		else if ((c1/window_width == 0 && c1%window_width != 0) || (c1/window_width == window_height - 1 && c1%window_width != window_width - 1))
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_lower_border);
		else if ((c1/window_width != 0 && c1%window_width == 0) || (c1/window_width != window_height - 1 && c1%window_width == window_width - 1))
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(right_left_border);
		else
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(default_symbol);
	}
}
void window_messenger:: Close()
{
	int c1;

	// Delete symbols
	for(c1 = 0; c1 < window_height*window_width; c1++)
	{
		vision_cell_2[c1]->DeleteSymbol(level_int_1[c1]);
		vision_cell_2[c1]->Show();
	}
}
void window_messenger:: Write(const pstring INpstring, const int INmessenge_index)
{
	int c1;

	messagestack_message_1[INmessenge_index - 1].text = INpstring;

	for(c1 = 0; c1 < window_width - 2 && c1 < INpstring.Length(); c1++)
		vision_cell_2[c1 + window_width*INmessenge_index + 1]->SetSymbol(INpstring[c1]);
}
void window_messenger:: Output(const message INoutput_message)
{
	int c1;

	if(messages_count < window_height - 2)
	{
		Write(INoutput_message.text, messages_count + 1);
		messages_count++;
	}
	else
	{
		for(c1 = 0; c1 < window_height - 2 - 1; c1++)
		{
			messagestack_message_1[c1].text = messagestack_message_1[c1 + 1].text;
			Write(messagestack_message_1[c1].text, c1 + 1);
		}
		messagestack_message_1[c1].text = INoutput_message.text;
		Write(INoutput_message.text, c1 + 1);
	}
}

/////////////////////////////////////////////////WINDOW-PRINTER///////////////////////////////////////////////////////////////////////////////////////
class window_printer : public window
{
private:
public:
	window_printer() {}
	window_printer(const int INwindow_width, const int INwindow_height, const int INwindowloc_X, const int INwindowloc_Y, const pstring INwindow_label)
	{
		int c1;

		// Set data
		window_width = INwindow_width + 2;
		window_height = INwindow_height + 2;
		window_label = INwindow_label;
		window_coords.X = INwindowloc_X;
		window_coords.Y = INwindowloc_Y;
		// Allocate memory for vision
		vision_cell_2 = new cell* [window_height*window_width];
		// Allocate memory for levels
		level_int_1 = new int [window_height*window_width];
		for(c1 = 0; c1 < window_height*window_width; c1++)
		{
			// // Set pointer
			vision_cell_2[c1] = &_VISION_cell_1[(window_coords.Y + c1/window_width)*vision_width + window_coords.X + c1%window_width];
		}
	}
	window_printer(const window_printer &INwindow)
	{
		int c1;

		// Set data
		window_width = INwindow.window_width + 2;
		window_height = INwindow.window_height + 2;
		window_label = INwindow.window_label;
		window_coords = INwindow.window_coords;
		// Allocate memory for vision
		vision_cell_2 = new cell* [window_height*window_width];
		// Allocate memory for levels
		level_int_1 = new int [window_height*window_width];
		for(c1 = 0; c1 < window_height*window_width; c1++)
		{
			// // Set pointer
			vision_cell_2[c1] = &_VISION_cell_1[(window_coords.Y + c1/window_width)*vision_width + window_coords.X + c1%window_width];
		}
	}
	~window_printer() {}
	void Open();
	void Close();
	void Print(const int INcellloc_X, const int INcellloc_Y, const char INcell_symbol);
};

void window_printer:: Open()
{
	int c1;

	// Add symbols
	for(c1 = 0; c1 < window_height*window_width; c1++)
	{
		if(c1%window_width > 0 && c1%window_width <= window_label.Length() && c1/window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(window_label[c1 - 1]);
		else if(c1/window_width == 0 && c1%window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_left_corner);
		else if (c1/window_width == window_height - 1 && c1%window_width == 0)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(lower_left_corner);
		else if (c1/window_width == 0 && c1%window_width == window_width - 1)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_right_corner);
		else if (c1/window_width == window_height - 1 && c1%window_width == window_width - 1)
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(lower_right_corner);
		else if ((c1/window_width == 0 && c1%window_width != 0) || (c1/window_width == window_height - 1 && c1%window_width != window_width - 1))
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(upper_lower_border);
		else if ((c1/window_width != 0 && c1%window_width == 0) || (c1/window_width != window_height - 1 && c1%window_width == window_width - 1))
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(right_left_border);
		else
			level_int_1[c1] = vision_cell_2[c1]->AddSymbol(default_symbol);
	}
}
void window_printer:: Close()
{
	int c1;

	window_managers_count--;
	// Delete symbols
	for(c1 = 0; c1 < window_height*window_width; c1++)
	{
		vision_cell_2[c1]->DeleteSymbol(level_int_1[c1]);
		vision_cell_2[c1]->Show();
	}
}
void window_printer:: Print(const int INcellloc_X, const int INcellloc_Y, const char INcell_symbol)
{
	vision_cell_2[window_width*(INcellloc_Y + 1) + INcellloc_X + 1]->SetSymbol(INcell_symbol);
}

/////////////////////////////////////////////////////////////////////////////COMMANDS//////////////////////////////////////////////////////////////////////////////////////
void CloseWindow(void *IN_DATA_1)
{
	static_cast<window*>(IN_DATA_1)->Close();
}

void OpenWindow(void *IN_DATA_1)
{
	static_cast<window*>(IN_DATA_1)->Open();
}

void ExitProgramm(void *IN_DATA_1)
{
	exit(0);
}