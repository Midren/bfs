#include "curl_wrapper.h"

#include <iostream>

#include <curl/curl.h>

CURL *curlPtr(bool cleanup) {
    static CURL *curl = NULL;
    static struct curl_slist *headers = NULL;
    if (!curl) {
        curl = curl_easy_init();
        if (!curl) {
            std::cerr << "Curl failed to initialize. Quitting..." << std::endl;
            exit(0);
        }
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "http:/""/localhost:8545");
    } else if (cleanup) {
        if (headers) curl_slist_free_all(headers);
        if (curl) curl_easy_cleanup(curl);
        curl = NULL;
    }
    return curl;
}


void curl_init() {
    curlPtr(false);
}

void curl_clean() {
    curlPtr(true);
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::string tmpStr;
    int cnt = 0;
    for (int i = 0; i < nmemb; i++) {
        if (ptr[i] != '\n' && ptr[i] != '\r') {
            tmpStr += ptr[i];
            cnt++;
        }
    }
    tmpStr[cnt] = '\0';

    // store it away in the caller's string
    (*(std::string *) userdata) += tmpStr;

    // we handeled everything, tell curl to send more if there is any
    return size * nmemb;
}

std::string send_request(const std::string &json) {
    curl_easy_setopt(curlPtr(false), CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curlPtr(false), CURLOPT_POSTFIELDSIZE, json.length());
    std::string result;
    curl_easy_setopt(curlPtr(false), CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curlPtr(false), CURLOPT_WRITEFUNCTION, write_callback);
    CURLcode res = curl_easy_perform(curlPtr(false));
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return ""; // FIXME: ERROR STRING
    }
    return result;
}
