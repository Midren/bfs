#ifndef RPC_ENCODE_H
#define RPC_ENCODE_H

#include <array>
#include <any>
#include <sstream>
#include <string>

#include <cryptopp/cryptlib.h>

#ifdef CRYPTOPP_NO_GLOBAL_BYTE
typedef unsigned char byte;
#endif

typedef std::vector<byte> bytes;

bytes from_hex(const std::string &str);

bytes get_method_id(const std::string &msg);

bytes encode(uint64_t num);

bytes encode(const std::string &str);

bytes encode(const bytes &bytes);

template<typename... Args>
bytes encode(const std::string &func, Args... args) {
    auto res = get_method_id(func);
    std::stringstream ss{func};

    std::string word;
    std::getline(ss, word, '(');

    int param_count = 0;
    std::vector<std::any> values{args...};
    std::vector<bytes> params;
    while (std::getline(ss, word, ',')) {
        if (word[word.size() - 1] == ')')
            word = word.substr(0, word.size() - 1);
        if (word == "string") {
            params.emplace_back(encode(std::any_cast<std::string>(values[param_count])));
        } else if (word == "bytes1[]") {
            params.emplace_back(encode(std::any_cast<bytes>(values[param_count])));
        }
        param_count++;
    }

    for (int i = 0; i < params.size(); i++) {
        auto tmp = encode(param_count * 32 + (i >= 1 ? params[i - 1].size() : 0));
        for (auto j: tmp)
            res.push_back(j);
    }
    for (auto &i: params)
        for (auto &j: i)
            res.push_back(j);
    return res;
}

std::string to_string(const bytes &data);

#endif //RPC_ENCODE_H
