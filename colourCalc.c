#include <windows.h>
#include <stdio.h>
#include <Wingdi.h>

int screen_dimensions(int* x, int* y) {
	*x = GetSystemMetrics(SM_CXSCREEN);
	*y = GetSystemMetrics(SM_CYSCREEN);
}
int colourCalc() {

    printf("A.M.B.I. IS LOADING... PLEASE WAIT...\n\n");

    printf("RETRIEVING SYSTEM HANDLES...\n");

    // Hanlde to device context to the desktop window
    HWND hwind = GetDesktopWindow();
    HDC hdc = GetDC(hwind);

    // Screen resolutions:
    int resx = GetSystemMetrics(SM_CXSCREEN);
    int resy = GetSystemMetrics(SM_CYSCREEN);

    printf("CALCULATING CONVERSION FACTORS...\n");

    // Bits for each pixel and color:
    int BitsPerPixel = GetDeviceCaps(hdc,BITSPIXEL);
    int BytesPerPixel = BitsPerPixel / 8;
    int BitsPerColor = BitsPerPixel / 4;
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

    // Data constants:
    unsigned int data_entries = resx * resy; // Amount of pixels
    int data_end = ((int)data) + data_entries * (BytesPerPixel); // End address

    // Show memory locations
    printf("DATA STARTING LOCATION: %d\n", ((int)data));
    printf("DATA END LOCATION:      %d\n", ((int)data_end));
    printf("\nANALYZING DATA... ");

    unsigned long sum_red = 0;
    unsigned long sum_blue = 0;
    unsigned long sum_green = 0;

    int i = ((int)data);
    for (; i < data_end; i += BytesPerPixel) {
        sum_red += *((byte*)(i + 2));
        sum_green += *((byte*)(i + 1));
        sum_blue += *((byte*)(i));
    }
    printf("DATA ANALYSIS COMPLETED.\nGENERATING RESULTS...\n\n");

    printf("\tRED       : %lu\n", sum_red); //GetBValue(_color));
    printf("\tGREEN     : %lu\n", sum_green); //GetBValue(_color));
    printf("\tBLUE      : %lu\n", sum_blue); //GetBValue(_color));

    printf("\tAVG RED   : %d\n", sum_red / data_entries); //GetBValue(_color));
    printf("\tAVG GREEN : %d\n", sum_green / data_entries); //GetBValue(_color));
    printf("\tAVG BLUE  : %d\n", sum_blue / data_entries); //GetBValue(_color));

    // Refresh data:
    BitBlt(hdc2,0,0,resx,resy,hdc,0,0,SRCCOPY);

    // Cleanup:
    DeleteObject(hbitmap);
    ReleaseDC(hwind,hdc);
    if (hdc2) {
        DeleteDC(hdc2);
    }

    printf("\nPRESS ANY KEY TO EXIT...\n");
    char c;
    scanf("%c", &c);

    return 0;

}
