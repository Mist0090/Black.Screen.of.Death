#pragma once
#include "system.h"

typedef union tagHRGBQUAD {
	COLORREF rgb;
	struct {
		byte b, g, r, unused;
	};
}HRGBQUAD;

typedef struct tagHSLCOLOR {
	float h, s, l;
}HSLCOLOR;

extern HWND hWnd;
extern HDC hDC, hMemDC;
extern HBITMAP hBmp;
extern HRGBQUAD *buffer;
extern HRGBQUAD *screen;

void graphics_install ( void );
void GetScreen ( HRGBQUAD *buffer );
void ApplyScreen ( HRGBQUAD *buffer );

HSLCOLOR rgb2hsl ( HRGBQUAD rgb );
HRGBQUAD hsl2rgb ( HSLCOLOR rgb );