#include "header.h"

/**
 ** Returns maximum of the three arguments.
**/
int maxC(int a, int b, int c) {
    if (a > b) {
        if (a > c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b > c) {
            return b;
        } else {
            return c;
        }
    }
}

/**
 ** Returns minimum of the three arguments.
**/
int minC(int a, int b, int c) {
    if (a < b) {
        if (a < c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b < c) {
            return b;
        } else {
            return c;
        }
    }
}

/**
 ** Converts the RGB (RED,65536-GREEN,65536-BLUE,65536) value into
 ** HSV (HUE,65536-SATURATION,256-BRIGHTNESS,256) and returns the
 ** result in a HSVColor structure.
**/
int createHSV(int R, int G, int B, HSVColor* dest) {

    // Also store RGB, just in case:
    dest->Red = R / 256;
    dest->Green = G / 256;
    dest->Blue = B / 256;

    // Coefficients in equation
	float M = (float) maxC(R, G, B); // Maximum color
	float m = (float) minC(R, G, B); // Minimum color
	float C = (float) (M - m); // Difference between maximum and minimum color
    //Enable to check coefficients: printf("M=%f, m=%f, C=%f\n", M, m, C);

	// Calculating hue
	double H = 0.0;
	if (M == m) {
	} else if (M == R) {
		H = ((((float) (G - B)) / (float) C));
	} else if (M == G) {
		H = (((float) (B - R)) / (float) C) + 2;
	} else if (M == B) {
		H = (((float) (R - G)) / (float) C) + 4;
	}
	H *= 60; // Now its 0 to 360
	H *= ( (65535) / 360); // Now its 0 to 65535

    // Calculating value (aka brightness):
	float V = M / 256;

    // Calculating saturation
	float S;
	if (C == 0) {
		S = 0;
	} else {
		S = 255 * (C / M);
	}

    // Create result structure:
	dest->Hue = (float) H;
	dest->Saturation = S;
	dest->Value = V;

	return 0;

}
