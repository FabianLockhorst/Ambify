#include "header.h"

int* detectLightGroups() {

    // TODO: Here should be all the mumbojumbo of doing the PUT request and looping
    // through the JSON result.

    int* groups = (int*) malloc(16 * sizeof(int)); // Allocate array on heap
    groups[0] = 21;  // Ambify Left GID
    groups[1] = 0;   // Ambify Left Count
    groups[2] = 31;  // Ambify Right GID
    groups[3] = 0;   // Ambify Right Count
    groups[4] = 3;   // Ambify VerticalCenter GID
    groups[5] = 0;   // Ambify VerticalCenter Count
    groups[6] = 8;   // Ambify Top GID
    groups[7] = 0;   // Ambify Top Count
    groups[8] = 9;   // Ambify Bottom GID
    groups[9] = 0;   // Ambify Bottom Count
    groups[10] = 2;  // Ambify HorizontalCenter GID
    groups[11] = 0;  // Ambify HorizontalCenter Count
    groups[12] = 15; // Ambify FullScreen GID
    groups[13] = 0;  // Ambify FullScreen Count
    groups[14] = 19; // Ambify Center GID
    groups[15] = 0;  // Ambify Center Count
    return groups; // Return pointer to array

}

int adjustLightGroup(int GID, HSVColor* hsv) {

    // TODO: Here should be all the mumbojumbo of doing the PUT request

}
