#ifndef RPC_RPC_H
#define RPC_RPC_H

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "encode.h"

enum eth_method {
    call,
    send
};

class rpc {
public:

    rpc() {

    }

    /* Work with files */

    int create_file(std::string path);

    int write_file(std::string path, uint8_t *bytes, size_t length);

    int read_file(std::string path, uint8_t *buf, size_t buf_size);

    ssize_t get_file_size(std::string path);

    int remove_file(std::string path);

    /* Work with directories */

    int create_dir(std::string path);

    std::vector<std::string> list_dir(std::string path);

    int remove_dir(std::string path);

private:
    template<typename... Args>
    std::string form_json(eth_method method, const std::string &func_sig, Args... args);
};

template<typename... Args>
std::string rpc::form_json(eth_method method, const std::string &func_sig, Args... args) {
    boost::property_tree::ptree pt{};
    pt.put("jsonrpc", 2.0);
    switch (method) {
        case eth_method::call:
            pt.put("method", "eth_call");
        case eth_method::send:
            pt.put("method", "eth_sendTransactioon");
    }
    pt.put("data", to_string(encode(func_sig, args...)));

    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    return ss.str();
}


#endif //RPC_RPC_H
