#include "header.h"

int curltest(void)
{

  curl_global_init(CURL_GLOBAL_WIN32);
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}

char* serverIP;

void init_server_connection() {
    serverIP = "http://192.168.1.1/";
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
