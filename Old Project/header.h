#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////
// Color structures and functions
//

typedef struct HSVColor {
    float Hue;
    float Saturation;
    float Value;
} HSVColor;


int createHSV(int R, int G, int B, HSVColor* dest);
void process(void* data, int data_end, unsigned int data_entries, int BytesPerPixel, unsigned int scr_width, unsigned int scr_height);

///////////////////////////////////////////
// Light structures and functions
//


int* detectLightGroups();
int adjustLightGroup(int GID, HSVColor* hsv);
