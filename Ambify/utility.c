#include "header.h"

void screen_dimensions(int* x, int* y) {
	*x = GetSystemMetrics(SM_CXSCREEN);
	*y = GetSystemMetrics(SM_CYSCREEN);
}



