#include "header.h"

int* lightGroups;

int configureAmbification() {

    // Retrieve screen dimensions
    int x, y;
    screen_dimensions(&x, &y);

    // Show the current state of the groups:
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
    printf("section name. To refresh, restart Ambify.\n\n");

    // Return
    return 0;

}

int main() {

    //Enabeling cURL for the project
    curltest();

    // Retrieve all the groups from the bridge:
    lightGroups = detectLightGroups();

    // Amibification settings:
    configureAmbification();

    // Start the Ambification:
    int result = activateAMBI(lightGroups);

    // Free the light groups that where allocated on the heap:
    free(lightGroups);

    // Before ending program, ask for key:
    printf("\nPRESS ANY KEY TO EXIT...\n");
    char c;
    scanf("%c", &c);

    return result;

}

