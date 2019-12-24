#include "rpc.h"
#include "curl_wrapper.h"

#include <iostream>

#include "decode.h"

bool Rpc::get_tx_status(const std::string &hash) {
    auto json = form_json(eth_method::getTxReceipt, "", hash);
    try {
        while (process_json(eth_method::getTxReceipt, curl.send_request(json)) == "Not mined") {
            sleep(1);
        }
        return process_json(eth_method::getTxReceipt, curl.send_request(json)) == "1";
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}

int Rpc::create_file(std::string path) {
    static std::string func_signature{"create_file(string)"};
    auto json = form_json(eth_method::sendTx, func_signature, path);
    try {
        return get_tx_status(process_json(eth_method::sendTx, curl.send_request(json)));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}

int Rpc::write_file(std::string path, uint8_t *data, size_t length) {
    static std::string func_signature{"write(string,bytes1[])"};
    bytes bt{};
    for (int i = 0; i < length; i++)
        bt.emplace_back(data[i]);
    auto json = form_json(eth_method::sendTx, func_signature, path, bt);
    try {
        return get_tx_status(process_json(eth_method::sendTx, curl.send_request(json)));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

int Rpc::read_file(std::string path, uint8_t *buf, size_t buf_size, off_t offset) {
    static std::string func_signature{"read(string)"};
    auto json = form_json(eth_method::call, func_signature, path);
    try {
        auto tmp = curl.send_request(json);

        auto res = decode_bytes(process_json(eth_method::call, tmp));
        memcpy(buf, res.data() + offset, std::min(buf_size, res.size() - offset));
        return std::min(buf_size, res.size() - offset);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}

std::string Rpc::process_json(eth_method method, const std::string &json) {
    boost::property_tree::ptree pt{};
    std::stringstream ss{json};
    boost::property_tree::json_parser::read_json(ss, pt);
    if (pt.count("error")) {
        throw std::runtime_error{
                std::to_string(pt.get<int>("error.code")) + ": " + pt.get<std::string>("error.message")};
    } else {
        switch (method) {
            case eth_method::call:
            case eth_method::sendTx:
                return pt.get<std::string>("result");
            case eth_method::getTxReceipt:
                if (pt.get_child("result").count("status"))
                    return pt.get<std::string>("result.status");
                return "Not mined";
        }
    }
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
        case eth_method::getTxReceipt:
            pt.put("method", "eth_getTransactionReceipt");
            break;
    }
    pt.put("id", id++);

    boost::property_tree::ptree params_list;
    boost::property_tree::ptree params;

    if (method == eth_method::sendTx || method == eth_method::call) {
        params.put("from", to_string(fromAddr));
        params.put("to", to_string(memoryManagerAddress));
        params.put("data", to_string(encode(func_sig, args...)));
    }
    if (method == eth_method::sendTx) {
        params.put("value", "0x0");
        params.put("gas", "0x2dc6c0");
    }
    if (method == eth_method::getTxReceipt) {
        boost::property_tree::ptree tx_hash;
        tx_hash.put("", std::get<0>(std::tuple(args...)));
        params_list.push_back(std::make_pair("", tx_hash));
    } else {
        params_list.push_back(std::make_pair("", params));
    }
    if (method == eth_method::call) {
        boost::property_tree::ptree block_time;
        block_time.put("", "pending");
        params_list.push_back(std::make_pair("", block_time));
    }
    pt.add_child("params", params_list);

    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    return ss.str();
}

