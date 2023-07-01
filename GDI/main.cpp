#include "system.h"

int WINAPI wWinMain (
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpszCmdLine,
	int nCmdShow
)
{
	screensize_install ( );
	graphics_install ( );

	HANDLE first = CreateThread ( NULL, 0, ( LPTHREAD_START_ROUTINE ) FirstGDI, NULL, 0, NULL );
	Sleep ( 5000 );
	TerminateThread ( first, 0 );
	CloseHandle ( first );
}