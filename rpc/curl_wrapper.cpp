#include "curl_wrapper.h"

//CURL *curlPtr(bool cleanup) {
//    static CURL *curl = nullptr;
//    static struct curl_slist *headers = nullptr;
//    if (!curl) {
//        curl = curl_easy_init();
//        if (!curl) {
//            std::cerr << "Curl failed to initialize. Quitting..." << std::endl;
//            exit(0);
//        }
//        headers = curl_slist_append(headers, "Content-Type: application/json");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        curl_easy_setopt(curl, CURLOPT_URL, "http:/""/localhost:8545");
//    } else if (cleanup) {
//        if (headers) curl_slist_free_all(headers);
//        if (curl) curl_easy_cleanup(curl);
//        curl = nullptr;
//    }
//    return curl;
//}

Curl::Curl() {
    curl = curl_easy_init();
    if (!curl)
        throw std::runtime_error("Cannot initialize curl");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, "http:/""/localhost:8545");
}

std::string Curl::send_request(const std::string &json) {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json.length());
    std::string result;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        throw std::runtime_error("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    return result;
}

void Curl::cleanup() {
    if (headers) curl_slist_free_all(headers);
    if (curl) curl_easy_cleanup(curl);
}

size_t Curl::write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
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

Curl::~Curl() {
    cleanup();
}
