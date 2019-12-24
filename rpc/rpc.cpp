#include "rpc.h"
#include "curl_wrapper.h"

#include <iostream>


int Rpc::create_file(std::string path) {
    static std::string func_signature{"create_file(string)"};
    auto json = form_json(eth_method::sendTx, func_signature, path);
    std::cout << json << std::endl;
    std::cout << curl.send_request(json) << std::endl;
    return 0;
}

int Rpc::write_file(std::string path, uint8_t *data, size_t length) {
    static std::string func_signature{"write(string,bytes1[])"};
    bytes bt{};
    for (int i = 0; i < length; i++)
        bt.emplace_back(data[i]);
    auto json = form_json(eth_method::sendTx, func_signature, path, bt);
    std::cout << json << std::endl;
    std::cout << curl.send_request(json) << std::endl;
    return 0;
}

int Rpc::read_file(std::string path, uint8_t *buf, size_t buf_size) {
    static std::string func_signature{"read(string)"};
    auto json = form_json(eth_method::call, func_signature, path);
    std::cout << json << std::endl;
    std::cout << curl.send_request(json) << std::endl;
    return 0;
}

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
        params.put("gas", "0x2dc6c0");
    }
    params_list.push_back(std::make_pair("", params));
    boost::property_tree::ptree block_time;
    if (method == eth_method::call) {
        block_time.put("", "latest");
        params_list.push_back(std::make_pair("", block_time));
    }
    pt.add_child("params", params_list);

    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    return ss.str();
}

