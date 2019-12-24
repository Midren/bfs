#ifndef RPC_RPC_H
#define RPC_RPC_H

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <curl/curl.h>
#include "encode.h"

std::string send_request(const std::string &json);

CURL *curlPtr(bool cleanup);

inline void curl_init() {
    curlPtr(false);
}

inline void curl_clean() {
    curlPtr(true);
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

enum eth_method {
    call,
    sendTx
};

class Rpc {
public:
    explicit Rpc(const bytes &userAddr, const bytes &mmAddress) : fromAddr{userAddr}, memoryManagerAddress{mmAddress} {
        curl_init();
    }

    explicit Rpc(const std::string &userAddr, const std::string &mmAddress) : fromAddr{from_hex(userAddr)},
                                                                              memoryManagerAddress{
                                                                                      from_hex(mmAddress)} {
        curl_init();
    }

    ~Rpc() {
        curl_clean();
    }

    /* Work with files */

    int create_file(std::string path);

    int write_file(std::string path, uint8_t *data, size_t length);

    int read_file(std::string path, uint8_t *buf, size_t buf_size);

    ssize_t get_file_size(std::string path);

    int remove_file(std::string path);

    /* Work with directories */

    int create_dir(std::string path);

    std::vector<std::string> list_dir(std::string path);

    int remove_dir(std::string path);

private:
    bytes fromAddr;

    template<typename... Args>
    std::string form_json(eth_method method, const std::string &func_sig, Args... args);

    bytes memoryManagerAddress;
};


template<typename... Args>
std::string Rpc::form_json(eth_method method, const std::string &func_sig, Args... args) {
    static int id = 1;
    boost::property_tree::ptree pt{};
    pt.put("jsonrpc", "2.0");
    switch (method) {
        case eth_method::call:
            pt.put("method", "eth_call");
            break;
        case eth_method::sendTx:
            pt.put("method", "eth_sendTransaction");
            break;
    }
    pt.put("id", id++);

    boost::property_tree::ptree params_list;
    boost::property_tree::ptree params;

    params.put("from", to_string(fromAddr));
    params.put("to", to_string(memoryManagerAddress));
    params.put("data", to_string(encode(func_sig, args...)));
    if (method == eth_method::sendTx) {
        params.put("value", "0x0");
        params.put("gas", "0x76c0");
    }
    params_list.push_back(std::make_pair("", params));
    boost::property_tree::ptree block_time;
    if (method == eth_method::call) {
        block_time.put("", "latest");
        params_list.push_back(std::make_pair("", block_time));
    }
//    params.put("", "latest");
    pt.add_child("params", params_list);

    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    return ss.str();
}


#endif //RPC_RPC_H
