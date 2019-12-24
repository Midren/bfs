#ifndef RPC_CURL_WRAPPER_H
#define RPC_CURL_WRAPPER_H

#include <string>

void curl_init();

void curl_clean();

std::string send_request(const std::string &json);


#endif //RPC_CURL_WRAPPER_H
