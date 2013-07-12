#include "header.h"


/**
 * Function: addToGroup
 *
 * Parameters:
 *      - cJSON* name :: The name of the lamp
 *      - char* identifeir :: The identifier of the lamp
 *      - int* dest :: The array of lamps and their ID's (only single lamps are currently supported)
 *
 * Description: adds the given lamp to the array if the name matches.
*/
void addToGroup(cJSON* name, char* identifier, int* dest) {
    if (strcmp(name->valuestring, "Ambify Left") == 0) {
        dest[0] = strtol(identifier, NULL, 0);  // Ambify Left GID
        dest[1] = 1;   // Ambify Left Count
    } else if (strcmp(name->valuestring, "Ambify Right") == 0) {
        dest[2] = strtol(identifier, NULL, 0);  // Ambify Right GID
        dest[3] = 1;   // Ambify Right Count
    } else if (strcmp(name->valuestring, "Ambify VerticalCenter") == 0) {
        dest[4] = strtol(identifier, NULL, 0);  // Ambify VerticalCenter GID
        dest[5] = 1;   // Ambify VerticalCenter Count
    } else if (strcmp(name->valuestring, "Ambify Top") == 0) {
        dest[6] = strtol(identifier, NULL, 0);  // Ambify Top GID
        dest[7] = 1;   // Ambify Top Count
    } else if (strcmp(name->valuestring, "Ambify Bottom") == 0) {
        dest[8] = strtol(identifier, NULL, 0);  // Ambify Bottom GID
        dest[9] = 1;   // Ambify Bottom Count
    } else if (strcmp(name->valuestring, "Ambify HorizontalCenter") == 0) {
        dest[10] = strtol(identifier, NULL, 0);  // Ambify HorizontalCenter GID
        dest[11] = 1;   // Ambify HorizontalCenter Count
    } else if (strcmp(name->valuestring, "Ambify FullScreen") == 0) {
        dest[12] = strtol(identifier, NULL, 0);  // Ambify FullScreen GID
        dest[13] = 1;   // Ambify FullScreen Count
    } else if (strcmp(name->valuestring, "Ambify Center") == 0) {
        dest[14] = strtol(identifier, NULL, 0);  // Ambify Center GID
        dest[15] = 1;   // Ambify Center Count
    }
}

/**
 * Function: detectLightGroups
 *
 * Parameters:
 *      None
 *
 * Description: does a request to the server and adds the ID's of the groups to the array.
*/
int* detectLightGroups() {

    char *json_string = retrieveGroupsFromServer();
    json_string = "{ \"1\": {\"name\": \"Ambify Right\"},\"2\": {\"name\": \"Ambify Left\"} }";

    // This is where all the groups will be stored
    int* groups = (int*) malloc(16 * sizeof(int)); // Allocate array on heap
    groups[0] = -1;  // Ambify Left GID
    groups[1] = 0;   // Ambify Left Count
    groups[2] = -1;  // Ambify Right GID
    groups[3] = 0;   // Ambify Right Count
    groups[4] = -1;   // Ambify VerticalCenter GID
    groups[5] = 0;   // Ambify VerticalCenter Count
    groups[6] = -1;   // Ambify Top GID
    groups[7] = 0;   // Ambify Top Count
    groups[8] = -1;   // Ambify Bottom GID
    groups[9] = 0;   // Ambify Bottom Count
    groups[10] = -1;  // Ambify HorizontalCenter GID
    groups[11] = 0;  // Ambify HorizontalCenter Count
    groups[12] = -1; // Ambify FullScreen GID
    groups[13] = 0;  // Ambify FullScreen Count
    groups[14] = -1; // Ambify Center GID
    groups[15] = 0;  // Ambify Center Count

    // Parse the JSON returned by the server
    cJSON *arr = cJSON_Parse(json_string)->child;
    cJSON *p = arr;

    // If there are no lights, return
    if (p != NULL) {

        // First light
        addToGroup(cJSON_GetObjectItem(p,"name"), p->string, groups);

        // All other lights
        while (p->next != NULL && p->next != arr) {
            p = p->next;
            addToGroup(cJSON_GetObjectItem(p,"name"), p->string, groups);
        }

    }

    return groups; // Return pointer to array

}

/**
 * Function: adjustLightGroup
 *
 * Parameters:
 *      - int GID :: The identifier of the group
 *      - HSVColor* hsv :: The color the lights of that group need to be
 *
 * Description: changes the color of the lights that have the given group ID
*/
int adjustLightGroup(int GID, HSVColor* hsv) {
    if (GID != -1) {
        char *json_string = NULL;
        sprintf(json_string, "{ \"on\": true, \"hue\": %d, \"sat\": %d, \"bri\": %d }", (int) hsv->Hue, (int) hsv->Saturation, (int) hsv->Value);
        return adjustGroupOnServer(GID, json_string);
    } else {
        return 2;
    }
}

