#ifndef RPC_CURL_WRAPPER_H
#define RPC_CURL_WRAPPER_H

#include <iostream>
#include <string>
#include <exception>


#include <curl/curl.h>

class Curl {
public:
    Curl();

    ~Curl();

    std::string send_request(const std::string &json);

private:
    CURL *curl = nullptr;
    struct curl_slist *headers = nullptr;

    void cleanup();

    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
};
//void curl_init();
//
//void curl_clean();
//
//std::string send_request(const std::string &json);


#endif //RPC_CURL_WRAPPER_H
