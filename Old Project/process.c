#include "header.h"


void process(void* data, int data_end, unsigned int data_entries, int BytesPerPixel, unsigned int scr_width, unsigned int scr_height) {

    // 2nd dimensional array for:
    // Lefttop, centertop, righttop
    // Leftmiddle, centermiddle, rightmiddle
    // Leftbottom, centerbottom, rightbottom
    // And each has 3 color values (red, green, blue)
    unsigned int sums[9][3], n, m;
    for (n = 0; n < 9; n++) {
        for (m = 0; m < 3; m++) {
            sums[n][m] = 0;
        }
    }

    // 1st dimensional array for:
    // left-center, center-right, top-middle, middle-bottom
    int lines[4] = { scr_width / 4, scr_width / 4 * 3, scr_height / 4, scr_height / 4 * 3 };

    // Calculate amount of entries:
    int corner_entries = scr_width / 4 * scr_height / 4;
    int horbar_entries = scr_width / 2 * scr_height / 4;
    int vertbar_entries = scr_width / 4 * scr_height / 2;
    int centr_entries = scr_width / 2 * scr_height / 2;

    // Loop through the data
    int i = ((int)data), x, y; n = 0; m = 0;
    for (; i < data_end; i += BytesPerPixel) {

        // Save the values in the bytes
        byte red   = *((byte*)(i + 2));
        byte green = *((byte*)(i + 1));
        byte blue  = *((byte*)(i));

        // On what x and y coordinate are we?
        x = n % scr_width;
        y = n / scr_width;

        if (x < lines[0]) {
            if (y < lines[2]) {
                // Lefttop
                sums[0][0] += red;
                sums[0][1] += green;
                sums[0][2] += blue;

            } else if (y <= lines[3]) {
                // Centertop
                sums[1][0] += red;
                sums[1][1] += green;
                sums[1][2] += blue;
            } else {
                // Righttop
                sums[2][0] += red;
                sums[2][1] += green;
                sums[2][2] += blue;
            }
        } else if (x <= lines[1]) {
            if (y < lines[2]) {
                // Leftmiddle
                sums[3][0] += red;
                sums[3][1] += green;
                sums[3][2] += blue;
            } else if (y <= lines[3]) {
                // Centermiddle
                sums[4][0] += red;
                sums[4][1] += green;
                sums[4][2] += blue;
            } else {
                // Rightmiddle
                sums[5][0] += red;
                sums[5][1] += green;
                sums[5][2] += blue;
            }
        } else {
            if (y < lines[2]) {
                // Leftbottom
                sums[6][0] += red;
                sums[6][1] += green;
                sums[6][2] += blue;

            } else if (y <= lines[3]) {
                // Centerbottom
                sums[7][0] += red;
                sums[7][1] += green;
                sums[7][2] += blue;

            } else {
                // Rightbottom
                sums[8][0] += red;
                sums[8][1] += green;
                sums[8][2] += blue;
            }
        }
        n++;
    }

    printf("DATA ANALYSIS COMPLETED.\nGENERATING RESULTS...\n\n");

    sums[1][2] = (int) (( (float) sums[1][2]   / (float) horbar_entries  ) * 256);

    // Multiply by 256 for base 2^10
    for (n = 0; n < 9; n++) {
        for (m = 0; m < 3; m++) {
            sums[n][m] = sums[n][m] * 256;
        }
    }

    // Create structures to hold the colors:
    HSVColor hsvLeft;
    HSVColor hsvRight;
    HSVColor hsvVerticalCenter;
    HSVColor hsvTop;
    HSVColor hsvBottom;
    HSVColor hsvHorizontalCenter;
    HSVColor hsvFullScreen;
    HSVColor hsvCenter;

    // Calculate colors and convert:
    createHSV(((sums[0][0] + sums[3][0] + sums[6][0]) / (corner_entries * 2 + vertbar_entries)), // Left
              ((sums[0][1] + sums[3][1] + sums[6][1]) / (corner_entries * 2 + vertbar_entries)),
              ((sums[0][2] + sums[3][2] + sums[6][2]) / (corner_entries * 2 + vertbar_entries)), &hsvLeft);
    createHSV(((sums[2][0] + sums[5][0] + sums[8][0]) / (corner_entries * 2 + vertbar_entries)), // Right
              ((sums[2][1] + sums[5][1] + sums[8][1]) / (corner_entries * 2 + vertbar_entries)),
              ((sums[2][2] + sums[5][2] + sums[8][2]) / (corner_entries * 2 + vertbar_entries)), &hsvRight);
    createHSV(((sums[1][0] + sums[4][0] + sums[7][0]) / (corner_entries * 2 + vertbar_entries)), // Vertical center
              ((sums[1][1] + sums[4][1] + sums[7][1]) / (corner_entries * 2 + vertbar_entries)),
              ((sums[1][2] + sums[4][2] + sums[7][2]) / (corner_entries * 2 + vertbar_entries)), &hsvVerticalCenter);
    createHSV(((sums[0][0] + sums[1][0] + sums[2][0]) / (corner_entries * 2 + horbar_entries)), // Top
              ((sums[0][1] + sums[1][1] + sums[2][1]) / (corner_entries * 2 + horbar_entries)),
              ((sums[0][2] + sums[1][2] + sums[2][2]) / (corner_entries * 2 + horbar_entries)), &hsvTop);
    createHSV(((sums[6][0] + sums[7][0] + sums[8][0]) / (corner_entries * 2 + horbar_entries)), // Bottom
              ((sums[6][1] + sums[7][1] + sums[8][1]) / (corner_entries * 2 + horbar_entries)),
              ((sums[6][2] + sums[7][2] + sums[8][2]) / (corner_entries * 2 + horbar_entries)), &hsvBottom);
    createHSV(((sums[3][0] + sums[4][0] + sums[5][0]) / (corner_entries * 2 + horbar_entries)), // Horizontal center
              ((sums[3][1] + sums[4][1] + sums[5][1]) / (corner_entries * 2 + horbar_entries)),
              ((sums[3][2] + sums[4][2] + sums[5][2]) / (corner_entries * 2 + horbar_entries)), &hsvHorizontalCenter);
    createHSV(((sums[0][0] + sums[1][0] + sums[2][0] + sums[3][0] + sums[4][0] + sums[5][0] + sums[6][0] + sums[7][0] + sums[8][0]) / (scr_width * scr_height)), // FullScreen
              ((sums[0][1] + sums[1][1] + sums[2][1] + sums[3][1] + sums[4][1] + sums[5][1] + sums[6][1] + sums[7][1] + sums[8][1]) / (scr_width * scr_height)),
              ((sums[0][2] + sums[1][2] + sums[2][2] + sums[3][2] + sums[4][2] + sums[5][2] + sums[6][2] + sums[7][2] + sums[8][2]) / (scr_width * scr_height)), &hsvFullScreen);
    createHSV(((sums[5][0]) / (centr_entries)), // Center
              ((sums[5][1]) / (centr_entries)),
              ((sums[5][2]) / (centr_entries)), &hsvCenter);


    //printf("Lefttop: (%d, %d, %d)", )
    //printf("\tRED         : %d (%d) (Avg. of %d pixels and %d)\n", sums[8][0], sums[8][0] / 256, m, centr_entries); //GetBValue(_color));
    //printf("\tGREEN       : %d (%d)\n", sums[8][1], sums[8][1] / 256); //GetBValue(_color));vertbar_
    //printf("\tBLUE        : %d (%d)\n", sums[8][2], sums[8][2] / 256); //GetBValue(_color));

    printf("\tHUE         : %f (%f)\n", hsvRight.Hue, hsvRight.Hue / 256); //GetBValue(_color));
    printf("\tSATURATION  : %f\n", hsvRight.Saturation); //GetBValue(_color));
    printf("\tBRIGHTNESS  : %f\n", hsvRight.Value); //GetBValue(_color));

}
