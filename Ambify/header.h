#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "curl32/include/curl/curl.h"
#include "cJSON/cJSON.h"

#define BRERR_NO_LIGHTS 2852

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
int* detectLightGroups();
int adjustLightGroup(int GID, HSVColor* hsv);

///////////////////////////////////////////
// Server structures and functions
//
void init_server_connection();
char *retrieveGroupsFromServer();
int adjustGroupOnServer(int groupID, char* json_string);
