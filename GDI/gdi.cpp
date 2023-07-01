#include "system.h"

HWND hWnd = NULL;
HDC hDC = NULL;
HDC hMemDC = NULL;
HBITMAP hBmp = NULL;
HRGBQUAD *buffer = NULL;
HRGBQUAD *screen = NULL;

void graphics_install ( void )
{
	HANDLE hHeap = GetProcessHeap ( );
	int w = WIDTH, h = HEIGHT;

	buffer = ( HRGBQUAD * ) HeapAlloc ( hHeap, NULL, w * h * sizeof ( HRGBQUAD ) );

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof ( BITMAPINFOHEADER );
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = 0;

	hWnd = HWND_DESKTOP;
	hDC = GetDC ( hWnd );
	hMemDC = CreateCompatibleDC ( hDC );
	hBmp = CreateDIBSection ( hDC, &bmi, DIB_RGB_COLORS, ( void ** ) &screen, NULL, 0 );
	SelectObject ( hMemDC, hBmp );
}

void GetScreen ( HRGBQUAD *buffer )
{
	BitBlt ( hMemDC, 0, 0, WIDTH, HEIGHT, hDC, 0, 0, SRCCOPY );
	for( int x = 0; x < WIDTH; x++ )
	{
		for( int y = 0; y < HEIGHT; y++ )
		{
			buffer[ y * WIDTH + x ] = screen[ y * WIDTH + x ];
		}
	}
}

void ApplyScreen ( HRGBQUAD *buffer )
{
	for( int x = 0; x < WIDTH; x++ )
	{
		for( int y = 0; y < HEIGHT; y++ )
		{
			screen[ y * WIDTH + x ] = buffer[ y * WIDTH + x ];
		}
	}
	BitBlt ( hDC, 0, 0, WIDTH, HEIGHT, hMemDC, 0, 0, SRCCOPY );
}

HSLCOLOR rgb2hsl ( HRGBQUAD rgb )
{
	HSLCOLOR hsl;

	uint8_t r = rgb.r, g = rgb.g, b = rgb.b;

	float _r = ( float ) r / 255.f, _g = ( float ) g / 255.f, _b = ( float ) b / 255.f;

	float rgbMin = min ( min ( _r, _g ), _b );
	float rgbMax = max ( max ( _r, _g ), _b );

	float fDelta = rgbMax - rgbMin, deltaR, deltaG, deltaB;

	float h = 0.f, s = 0.f, l = ( float ) ( ( rgbMax + rgbMin ) / 2.f );

	if( fDelta != 0.f )
	{
		s = l < .5f ? ( float ) ( fDelta / ( rgbMax + rgbMin ) ) : ( float ) ( fDelta / ( 2.f - rgbMax - rgbMin ) );
		deltaR = ( float ) ( ( ( rgbMax - _r ) / 6.f + ( fDelta / 2.f ) ) / fDelta );
		deltaG = ( float ) ( ( ( rgbMax - _g ) / 6.f + ( fDelta / 2.f ) ) / fDelta );
		deltaB = ( float ) ( ( ( rgbMax - _b ) / 6.f + ( fDelta / 2.f ) ) / fDelta );

		if( _r == rgbMax )
			h = deltaB - deltaG;

		else if( _g == rgbMax )
			h = ( 1.f / 3.f ) + deltaR - deltaB;

		else if( _b == rgbMax )
			h = ( 2.f / 3.f ) + deltaG - deltaR;

		if( h < 0.f )
			h += 1.f;

		if( h > 1.f )
			h -= 1.f;
	}

	hsl.h = h, hsl.s = s, hsl.l = l;
	return hsl;
}

HRGBQUAD hsl2rgb ( HSLCOLOR hsl )
{
	HRGBQUAD rgb;

	float r = hsl.l, g = hsl.l, b = hsl.l,
		h = hsl.h, sl = hsl.s, l = hsl.l,
		v = ( l <= .5f ) ? ( l * ( 1.f + sl ) ) : ( l + sl - l * sl ),
		m, sv, fract, vsf, mid1, mid2;

	int sextant;

	if( v > 0.f )
	{
		m = l + l - v;
		sv = ( v - m ) / v;
		h *= 6.f;
		sextant = ( int ) h;
		fract = h - sextant;
		vsf = v * sv * fract;
		mid1 = m + vsf;
		mid2 = v - vsf;

		switch( sextant )
		{
		case 0:
			r = v;
			g = mid1;
			b = m;
			break;
		case 1:
			r = mid2;
			g = v;
			b = m;
			break;
		case 2:
			r = m;
			g = v;
			b = mid1;
			break;
		case 3:
			r = m;
			g = mid2;
			b = v;
			break;
		case 4:
			r = mid1;
			g = m;
			b = v;
			break;
		case 5:
			r = v;
			g = m;
			b = mid2;
			break;
		}
	}

	rgb.r = ( uint8_t ) ( r * 255.f ), rgb.g = ( uint8_t ) ( g * 255.f ), rgb.b = ( uint8_t ) ( b * 255.f );

	return rgb;
}