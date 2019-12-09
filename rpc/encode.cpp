#include "encode.h"

#include <cryptopp/keccak.h>
#include <boost/locale.hpp>

bytes get_method_id(const std::string &msg) {
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

bytes encode(const std::string &str) {
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

std::string to_string(const bytes &data) {
    std::string res;
    char hex_byte[2];
    for (const auto &byte: data) {
        sprintf(hex_byte, "%02x", byte);
        res.push_back(hex_byte[0]);
        res.push_back(hex_byte[1]);
    }
    return "0x" + res;
}
