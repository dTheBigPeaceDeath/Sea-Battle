// Sea Battle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "SBengine.h"

void Void(void *IN_DATA){}

int _tmain(int argc, _TCHAR* argv[])
{
	Inicialisation();
	
	for(;;)
	{
		_OPENED_window_manager_1[window_managers_count - 1]->Input();
	}

	return 0;
}
