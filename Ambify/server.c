#include "header.h"

char* serverIP;

void init_server_connection() {

  curl_global_init(CURL_GLOBAL_WIN32);
  serverIP = "http://192.168.1.1/api/Fablock/";

  CURL *curl;
  char *url = NULL;
  sprintf(url, "%s/lights", serverIP);
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
printf("\n\nHere\n\n");
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    printf("\n\nHere222\n\n");
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
}

/**
URL: /api/<username>/lights
*/
char *retrieveGroupsFromServer() {
    return NULL;
}

/**
URL: api/<username>/lights/<id>/state
*/
int adjustGroupOnServer(int groupID, char* json_string) {
    return 0;
}
