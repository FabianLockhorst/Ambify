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
    printf(" * Left              %d (GID: %d)\n", lightGroups[1], lightGroups[0]);
    printf(" * Right             %d (GID: %d)\n", lightGroups[3], lightGroups[2]);
    printf(" * VerticalCenter    %d (GID: %d)\n", lightGroups[5], lightGroups[4]);
    printf(" * Top               %d (GID: %d)\n", lightGroups[7], lightGroups[6]);
    printf(" * Bottom            %d (GID: %d)\n", lightGroups[9], lightGroups[8]);
    printf(" * HorizontalCenter  %d (GID: %d)\n", lightGroups[11], lightGroups[10]);
    printf(" * FullScreen        %d (GID: %d)\n", lightGroups[13], lightGroups[12]);
    printf(" * Center            %d (GID: %d)\n", lightGroups[15], lightGroups[14]);
    printf("\nTo assign more lights to (sections of) the screen, name lights to the specific Ambify groups. ");
    printf("You can do so by, using the Philips Hue app, naming them \"Ambify <section>\" where <section> is the ");
    printf("section name. To refresh, restart Ambify.\n\n");

    // Return
    return 0;

}

int main() {

    // Initialize the connection to the server (retrieve bridge's IP)
    init_server_connection();

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

