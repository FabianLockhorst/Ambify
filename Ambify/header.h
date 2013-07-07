#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
//#include "curl/include/config-win32.h"
#include "curl/include/curl/curl.h"
#include "cJSON/cJSON.h"


///////////////////////////////////////////
// Color structures and functions
//

typedef struct HSVColor {
    float Hue;
    float Saturation;
    float Value;
    int Red;
    int Green;
    int Blue;
} HSVColor;


int createHSV(int R, int G, int B, HSVColor* dest);
void process(void* data, int data_end, unsigned int data_entries, int BytesPerPixel, unsigned int scr_width, unsigned int scr_height);

///////////////////////////////////////////
// Light structures and functions
//
int* detectLightGroups();
int adjustLightGroup(int GID, HSVColor* hsv);


///////////////////////////////////////////
// AMBI structures and functions
//
int activateAMBI(int* lightGroups);

///////////////////////////////////////////
// Utility structures and functions
//
void screen_dimensions(int* x, int* y);

///////////////////////////////////////////
// Bridge structures and functions
//
int curltest(void);
