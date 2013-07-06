#include "header.h"


int* lightGroups;

void screen_dimensions(int* x, int* y) {
	*x = GetSystemMetrics(SM_CXSCREEN);
	*y = GetSystemMetrics(SM_CYSCREEN);
}

int activateAMBI() {

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

    // Process the data on the screen:
    process(data, data_end, data_entries, BytesPerPixel, resx, resy);

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

int configureAmbification() {

    int x, y;
    screen_dimensions(&x, &y);

    printf("+++ Ambify Environment +++\n\n");
    printf("Screen dimensions: %dx%d (auto-detect)\n", x, y);
    printf("Amount of lights assigned to (sections of) the screen:\n");
    printf(" Section name:       #:\n");
    printf(" * Left              %d\n", lightGroups[1]);
    printf(" * Right             %d\n", lightGroups[3]);
    printf(" * VerticalCenter    %d\n", lightGroups[5]);
    printf(" * Top               %d\n", lightGroups[7]);
    printf(" * Bottom            %d\n", lightGroups[9]);
    printf(" * HorizontalCenter  %d\n", lightGroups[11]);
    printf(" * FullScreen        %d\n", lightGroups[13]);
    printf(" * Center            %d\n", lightGroups[15]);
    printf("\nTo assign more lights to (sections of) the screen, add lights to the specific Ambify groups. ");
    printf("You can do so by, using the Philips Hue app, adding them to the group \"Ambify <section>\" where <section> is the ");
    printf("section name.\n\n");


}

int main() {


    //Enabeling cURL for the project
    curl_global_init(CURL_GLOBAL_WIN32);

    // Retrieve all the groups from the bridge
    lightGroups = detectLightGroups();



    // Amibification settings
    configureAmbification();

    // Start the Ambification
    activateAMBI();

    // Free the light groups that where allocated on the heap:
    free(lightGroups);

    return 0;

}

