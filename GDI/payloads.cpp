#include "system.h"

void FirstGDI ( void )
{
	for( int t = 0;; t++ )
	{
		GetScreen ( buffer );

		uint32_t u;
		uint32_t v;
		float div = ( float ) t / 10.f;
		float a = sinf ( div ) * 32.f;
		float b = cosf ( div ) * 32.f;
		float f = 1.f / 32.f;
		HRGBQUAD rgbDst;
		HRGBQUAD rgbSrc;
		HSLCOLOR hsl;

		HRGBQUAD rgbTemp;
		for( int x = 0; x < WIDTH; x++ )
		{
			for( int y = 0; y < HEIGHT; y++ )
			{
				float a = sinf ( y / 10.f + t / 15.f ) * 20.f;

				u = x + ( int ) a, v = y;
				u %= WIDTH;
				v %= HEIGHT;

				rgbTemp = buffer[ v * WIDTH + u ];
				screen[ y * WIDTH + x ].rgb += rgbTemp.rgb;
			}
		}
		BitBlt ( hDC, 0, 0, WIDTH, HEIGHT, hMemDC, 0, 0, SRCCOPY );

		for( int y = 0; y < HEIGHT; y++ )
		{
			for( int x = 0; x < WIDTH; x++ )
			{
				u = x + ( int ) a + ( int ) ( SawtoothWave ( y, 10, HEIGHT ) * 16.f );
				v = y + ( int ) b;

				Reflect2D ( ( int * ) &u, ( int * ) &v, WIDTH, HEIGHT );

				rgbDst = buffer[ v * WIDTH + u ];
				rgbSrc = buffer[ y * WIDTH + x ];

				if( !rgbSrc.rgb )
				{
					rgbSrc.rgb = 1;
				}

				rgbDst.rgb &= rgbDst.rgb % ( ( rgbSrc.rgb << 8 ) + 1 );
				float _r = ( float ) rgbDst.r * f + ( float ) rgbSrc.r * ( 1.f - f ),
					_g = ( float ) rgbDst.g * f + ( float ) rgbSrc.g * ( 1.f - f ),
					_b = ( float ) rgbDst.b * f + ( float ) rgbSrc.b * ( 1.f - f );
				rgbDst.rgb = RGB ( ( uint8_t ) _r, ( uint8_t ) _g, ( uint8_t ) _b );

				hsl = rgb2hsl ( rgbDst );
				hsl.h /= 1.0125f;
				hsl.s = 0.6f;//1.0125f;
				hsl.l /= 1.2125f;
				rgbDst = hsl2rgb ( hsl );

				buffer[ y * WIDTH + x ] = rgbDst;
			}
		}
		ApplyScreen ( buffer );
	}
}