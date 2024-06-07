/*
	(C) 2007-22 - Luca Deri <deri@ntop.org>
*/

#ifndef _WINTAP_H_
#define _WINTAP_H_

#undef UNICODE
#undef _UNICODE
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#include "n2ngo-wintap/dist/include/tap-windows.h"

extern int initWin32();
extern void destroyWin32();
extern void win_print_available_adapters();

#endif
