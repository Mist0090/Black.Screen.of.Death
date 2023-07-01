#pragma once
#include "system.h"

extern int WIDTH;
extern int HEIGHT;

RECT GetVirtualScreen ( void );
POINT GetVirtualScreenPos ( void );
SIZE GetVirtualScreenSize ( void );

void screensize_install ( void );