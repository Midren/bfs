#include "rpc.h"

#include <iostream>

int Rpc::create_file(std::string path) {
    static std::string func_signature{"create_file(string)"};
    auto json = form_json(eth_method::send, func_signature, path);
    std::cout << json << std::endl;
    return 0;
}

int Rpc::write_file(std::string path, uint8_t *data, size_t length) {
    static std::string func_signature{"write(string,byte[])"};
    bytes bt(length);
    for (int i = 0; i < length; i++)
        bt.emplace_back(data[i]);
    auto json = form_json(eth_method::send, func_signature, path, bt);
    return 0;
}

int Rpc::read_file(std::string path, uint8_t *buf, size_t buf_size) {
    static std::string func_signature{"read(string)"};
    auto json = form_json(eth_method::call, func_signature, path);
    return 0;
}
