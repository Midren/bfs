#ifndef RPC_RPC_H
#define RPC_RPC_H

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "encode.h"
#include "curl_wrapper.h"

enum eth_method {
    call,
    sendTx
};

class Rpc {
public:
    Rpc(const bytes &userAddr, const bytes &mmAddress) : fromAddr{userAddr},
                                                         memoryManagerAddress{mmAddress},
                                                         curl{} {}

    Rpc(const std::string &userAddr, const std::string &mmAddress) : fromAddr{from_hex(userAddr)},
                                                                     memoryManagerAddress{from_hex(mmAddress)},
                                                                     curl{} {}

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
    bytes memoryManagerAddress;
    Curl curl;

    template<typename... Args>
    std::string form_json(eth_method method, const std::string &func_sig, Args... args);
};

#include "rpc.cpp"

#endif //RPC_RPC_H
