#include "system.h"

int WIDTH = 0;
int HEIGHT = 0;

BOOL CALLBACK MonitorEnumProc ( HMONITOR hMonitor, HDC hdcMonitor, PRECT prcBounds, LPARAM lParam )
{
	PRECT prcParam = ( RECT * ) lParam;
	UnionRect ( prcParam, prcParam, prcBounds );
	return TRUE;
}

RECT GetVirtualScreen ( void )
{
	RECT rcScreen = { 0 };
	EnumDisplayMonitors ( NULL, NULL, MonitorEnumProc, ( LPARAM ) &rcScreen );
	return rcScreen;
}

POINT GetVirtualScreenPos ( void )
{
	RECT rcScreen = GetVirtualScreen ( );
	POINT ptScreen = {
		rcScreen.left,
		rcScreen.top
	};
	return ptScreen;
}

SIZE GetVirtualScreenSize ( void )
{
	RECT rcScreen = GetVirtualScreen ( );
	SIZE szScreen = { rcScreen.right - rcScreen.left, rcScreen.bottom - rcScreen.top };
	return szScreen;
}

void screensize_install ( void )
{
	SIZE scrSize = GetVirtualScreenSize ( );
	WIDTH = scrSize.cx;
	HEIGHT = scrSize.cy;
}