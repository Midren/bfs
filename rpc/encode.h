#ifndef RPC_ENCODE_H
#define RPC_ENCODE_H

#include <array>
#include <string>
#include <sstream>
#include <any>

#include <cryptopp/cryptlib.h>
#include <cryptopp/keccak.h>
#include <boost/locale.hpp>

typedef std::vector<byte> bytes;

bytes get_method_id(std::string msg) {
    bytes digest;
    CryptoPP::Keccak_256 hash;
    hash.Update((const byte *) msg.data(), msg.size());
    std::string tmp;
    tmp.resize(hash.DigestSize());
    hash.Final((byte *) &tmp[0]);
    for (int i = 0; i < 4; i++)
        digest.push_back(tmp[i]);
    return digest;
}

bytes encode(uint64_t num) {
    bytes vec;
    byte tmp[4];
    memcpy(tmp, (byte *) &num, 4);
    int non_zero = 0;
    while ((num >> 8 * non_zero) << 8 * non_zero == num)
        non_zero++;
    while (non_zero++ < 32)
        vec.push_back(0);
    for (auto i: tmp)
        if (i)
            vec.push_back(i);
    return vec;
}

bytes encode(std::string str) {
    auto utf_str = boost::locale::conv::to_utf<char>(str, "UTF-8");
    uint32_t sz = utf_str.length();
    auto vec = encode(sz);
    for (auto i : utf_str)
        vec.push_back(i);
    while (vec.size() % 32 != 0)
        vec.push_back(0);
    return vec;
}

bytes encode(const bytes &bytes) {
    auto vec = encode(bytes.size());
    for (auto byte : bytes)
        vec.push_back(byte);
    while (vec.size() % 32 != 0)
        vec.push_back(0);
    return vec;
}

template<typename... Args>
bytes encode(std::string func, Args... args) {
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
        } else if (word == "byte[]") {
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

std::string to_string(bytes data) {
    std::string res;
    char hex_byte[2];
    for (const auto &byte: data) {
        sprintf(hex_byte, "%02x", byte);
        res.push_back(hex_byte[0]);
        res.push_back(hex_byte[1]);
    }
    return "0x" + res;
}

#endif //RPC_ENCODE_H
