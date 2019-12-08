#ifndef RPC_RPC_H
#define RPC_RPC_H

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <cryptopp/cryptlib.h>
#include <cryptopp/keccak.h>

enum eth_method {
    call,
    send
};

typedef std::array<byte, 4> method_id;

method_id get_method_id(std::string msg);

std::vector<byte> encode_string(std::string);

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
    boost::property_tree::ptree form_json(eth_method method, Args... args);
};

template<typename... Args>
boost::property_tree::ptree rpc::form_json(eth_method method, Args... args) {
    boost::property_tree::ptree pt{};
    pt.put("jsonrpc", 2.0);
    switch (method) {
        case eth_method::call:
            pt.put("method", "eth_call");
        case eth_method::send:
            pt.put("method", "eth_sendTransactioon");
    }


    return pt;
}


#endif //RPC_RPC_H
