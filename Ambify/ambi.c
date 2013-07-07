
#include "header.h"

int activateAMBI(int* lightGroups) {

    ////////////////////////////////////
    // Set-up
    //

        printf("A.M.B.I. IS LOADING... PLEASE WAIT...\n\n");
        printf("RETRIEVING SYSTEM HANDLES...\n");

        // Hanlde to device context to the desktop window
        HWND hwind = GetDesktopWindow();
        HDC hdc = GetDC(hwind);

        // Screen resolution:
        int resx, resy;
        screen_dimensions(&resx, &resy);

        printf("CALCULATING CONVERSION FACTORS...\n");

        // Bits for each pixel and color:
        int BitsPerPixel = GetDeviceCaps(hdc,BITSPIXEL);
        int BytesPerPixel = BitsPerPixel / 8;
        // Use for later? int BitsPerColor = BitsPerPixel / 4;
        HDC hdc2 = CreateCompatibleDC(hdc);

        printf("CONFIGURING FORMATS...\n\n");

        // Set the information for the bitmap
        BITMAPINFO info;
        info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        info.bmiHeader.biWidth = resx;
        info.bmiHeader.biHeight = resy;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount  = BitsPerPixel;
        info.bmiHeader.biCompression = BI_RGB;

        printf("PROCESSING RECEIVED DATA...\n");

        // This is where the screen data will be put:
        void *data;

        // Retrieve information about the screen into a bitmap:
        HBITMAP hbitmap;
        hbitmap = CreateDIBSection(hdc2,&info,DIB_RGB_COLORS,(void**)&data,0,0);

        // Set the device context to hbitmap:
        SelectObject(hdc2,hbitmap);

        // Refresh data:
        BitBlt(hdc2,0,0,resx,resy,hdc,0,0,SRCCOPY);


    ////////////////////////////////////
    // Determining constants
    //


        // Data constants:
        unsigned int data_entries = resx * resy; // Amount of pixels
        int data_end = ((int)data) + data_entries * (BytesPerPixel); // End address

        // 1st dimensional array for:
        // left-center, center-right, top-middle, middle-bottom
        int lines[4] = { resx / 4, resx / 4 * 3, resy / 4, resy / 4 * 3 };

        // Calculate amount of entries (pixels) for each screen section:
        int corner_entries = (resx / 4) * (resy / 4);
        int horbar_entries = (resx / 2) * (resy / 4);
        int vertbar_entries = (resx / 4) * (resy / 2);
        int centr_entries = (resx / 2) * (resy / 2);

        // Derived out of the base screen sections:
        int fullsidebar_entries = corner_entries * 2 + vertbar_entries;
        int fullcentvertbar_entries = fullsidebar_entries * 2;
        int fullhorbar_entries = corner_entries * 2 + horbar_entries;
        int fullcenthorbar_entries = fullhorbar_entries * 2;
        int fullscreen_entries = resx * resy;


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

        // Create structures to hold the colors:
        HSVColor hsvLeft;
        HSVColor hsvRight;
        HSVColor hsvVerticalCenter;
        HSVColor hsvTop;
        HSVColor hsvBottom;
        HSVColor hsvHorizontalCenter;
        HSVColor hsvFullScreen;
        HSVColor hsvCenter;

    ////////////////////////////////////
    // Data loop
    //

    char c;



    while (scanf("%c", &c) && c != 'S' && c != 's') {

        // Refresh data:
        BitBlt(hdc2,0,0,resx,resy,hdc,0,0,SRCCOPY);

        // Loop through the data
        int i = ((int)data), x, y; n = 0; m = 0;
        for (; i < data_end; i += BytesPerPixel) {

            // Save the values in the bytes
            byte red   = *((byte*)(i + 2));
            byte green = *((byte*)(i + 1));
            byte blue  = *((byte*)(i));

            // On what x and y coordinate are we?
            x = n % resx;
            y = n / resx;

            if (y < lines[2]) {
                if (x < lines[0]) {
                    // Lefttop
                    sums[0][0] += red;
                    sums[0][1] += green;
                    sums[0][2] += blue;

                } else if (x <= lines[1]) {
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
            } else if (y <= lines[3]) {
                if (x < lines[0]) {
                    // Leftmiddle
                    sums[3][0] += red;
                    sums[3][1] += green;
                    sums[3][2] += blue;
                } else if (x <= lines[1]) {
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
                if (x < lines[0]) {
                    // Leftbottom
                    sums[6][0] += red;
                    sums[6][1] += green;
                    sums[6][2] += blue;

                } else if (x <= lines[1]) {
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

        // Calculate colors and convert:
        createHSV(((sums[0][0] + sums[3][0] + sums[6][0]) / (fullsidebar_entries) * 256), // Left
                  ((sums[0][1] + sums[3][1] + sums[6][1]) / (fullsidebar_entries) * 256),
                  ((sums[0][2] + sums[3][2] + sums[6][2]) / (fullsidebar_entries) * 256), &hsvLeft);
        createHSV(((sums[2][0] + sums[5][0] + sums[8][0]) / (fullsidebar_entries) * 256), // Right
                  ((sums[2][1] + sums[5][1] + sums[8][1]) / (fullsidebar_entries) * 256),
                  ((sums[2][2] + sums[5][2] + sums[8][2]) / (fullsidebar_entries) * 256), &hsvRight);
        createHSV(((sums[1][0] + sums[4][0] + sums[7][0]) / (fullcentvertbar_entries) * 256), // Vertical center
                  ((sums[1][1] + sums[4][1] + sums[7][1]) / (fullcentvertbar_entries) * 256),
                  ((sums[1][2] + sums[4][2] + sums[7][2]) / (fullcentvertbar_entries) * 256), &hsvVerticalCenter);
        createHSV(((sums[0][0] + sums[1][0] + sums[2][0]) / (fullhorbar_entries) * 256), // Top
                  ((sums[0][1] + sums[1][1] + sums[2][1]) / (fullhorbar_entries) * 256),
                  ((sums[0][2] + sums[1][2] + sums[2][2]) / (fullhorbar_entries) * 256), &hsvTop);
        createHSV(((sums[6][0] + sums[7][0] + sums[8][0]) / (fullhorbar_entries) * 256), // Bottom
                  ((sums[6][1] + sums[7][1] + sums[8][1]) / (fullhorbar_entries) * 256),
                  ((sums[6][2] + sums[7][2] + sums[8][2]) / (fullhorbar_entries) * 256), &hsvBottom);
        createHSV(((sums[3][0] + sums[4][0] + sums[5][0]) / (fullcenthorbar_entries) * 256), // Horizontal center
                  ((sums[3][1] + sums[4][1] + sums[5][1]) / (fullcenthorbar_entries) * 256),
                  ((sums[3][2] + sums[4][2] + sums[5][2]) / (fullcenthorbar_entries) * 256), &hsvHorizontalCenter);
        createHSV(((sums[0][0] + sums[1][0] + sums[2][0] + sums[3][0] + sums[4][0] + sums[5][0] + sums[6][0] + sums[7][0] + sums[8][0]) / (fullscreen_entries) * 256), // FullScreen
                  ((sums[0][1] + sums[1][1] + sums[2][1] + sums[3][1] + sums[4][1] + sums[5][1] + sums[6][1] + sums[7][1] + sums[8][1]) / (fullscreen_entries) * 256),
                  ((sums[0][2] + sums[1][2] + sums[2][2] + sums[3][2] + sums[4][2] + sums[5][2] + sums[6][2] + sums[7][2] + sums[8][2]) / (fullscreen_entries) * 256), &hsvFullScreen);
        createHSV(((sums[5][0]) / (centr_entries) * 256), // Center
                  ((sums[5][1]) / (centr_entries) * 256),
                  ((sums[5][2]) / (centr_entries) * 256), &hsvCenter);

        // Print results:
        printf("Left:               HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvLeft.Hue, hsvLeft.Saturation, hsvLeft.Value, hsvLeft.Red, hsvLeft.Green, hsvLeft.Blue);
        printf("Right:              HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvRight.Hue, hsvRight.Saturation, hsvRight.Value, hsvRight.Red, hsvRight.Green, hsvRight.Blue);
        printf("VerticalCenter:     HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvVerticalCenter.Hue, hsvVerticalCenter.Saturation, hsvVerticalCenter.Value, hsvVerticalCenter.Red, hsvVerticalCenter.Green, hsvVerticalCenter.Blue);
        printf("Top:                HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvTop.Hue, hsvTop.Saturation, hsvTop.Value, hsvTop.Red, hsvTop.Green, hsvTop.Blue);
        printf("Bottom:             HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvBottom.Hue, hsvBottom.Saturation, hsvBottom.Value, hsvBottom.Red, hsvBottom.Green, hsvBottom.Blue);
        printf("HorizontalCenter:   HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvHorizontalCenter.Hue, hsvHorizontalCenter.Saturation, hsvHorizontalCenter.Value, hsvHorizontalCenter.Red, hsvHorizontalCenter.Green, hsvHorizontalCenter.Blue);
        printf("FullScreen:         HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvFullScreen.Hue, hsvFullScreen.Saturation, hsvFullScreen.Value, hsvFullScreen.Red, hsvFullScreen.Green, hsvFullScreen.Blue);
        printf("Center:             HSV(%5.0f, %3.0f, %3.0f), RGB(%3.0d, %3.0d, %3.0d)\n", hsvCenter.Hue, hsvCenter.Saturation, hsvCenter.Value, hsvCenter.Red, hsvCenter.Green, hsvCenter.Blue);

        // Now, connect with the bridge and update the lights:

        // Now reset all:
        for (n = 0; n < 9; n++) {
            for (m = 0; m < 3; m++) {
                sums[n][m] = 0;
            }
        }

        printf("Enter 'S' and press enter to stop or only press enter to refresh...\n\n");

    }

    ////////////////////////////////////
    // Cleanup
    //

        DeleteObject(hbitmap);
        ReleaseDC(hwind,hdc);
        if (hdc2) {
            DeleteDC(hdc2);
        }

    return 0;

}

