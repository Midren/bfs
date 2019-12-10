#include "rpc.h"

#include <iostream>

int Rpc::create_file(std::string path) {
    static std::string func_signature{"create_file(string)"};
    auto json = form_json(eth_method::sendTx, func_signature, path);
    std::cout << json << std::endl;
    std::cout << send_request(json) << std::endl;
    return 0;
}

int Rpc::write_file(std::string path, uint8_t *data, size_t length) {
    static std::string func_signature{"write(string,byte[])"};
    bytes bt(length);
    for (int i = 0; i < length; i++)
        bt.emplace_back(data[i]);
    auto json = form_json(eth_method::sendTx, func_signature, path, bt);
    std::cout << json << std::endl;
    std::cout << send_request(json) << std::endl;
    return 0;
}

int Rpc::read_file(std::string path, uint8_t *buf, size_t buf_size) {
    static std::string func_signature{"read(string)"};
    auto json = form_json(eth_method::call, func_signature, path);
    std::cout << json << std::endl;
    std::cout << send_request(json) << std::endl;
    return 0;
}

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
