#include <iostream>
#include "decode.h"
#include <boost/locale.hpp>
#include <sys/stat.h>

bytes from_hex(const std::string &str) {
    bytes res;
    for (auto i = 0; i < str.length(); i += 2) {
        std::stringstream ss;
        auto byte_str = str.substr(i, 2);
        if (byte_str == "0x")
            continue;
        unsigned int byte;
        ss << std::hex << byte_str;
        ss >> byte;
        res.push_back(byte);
    }
    return res;
}

byte decode_byte(const std::string &str) {
    int padding = 0;
    while (str[str.length() - 1 - padding++] == '0') {}
    if (padding % 2 != 0)
        --padding;
    if (padding != 64)
        return from_hex(str.substr(0, str.length() - padding))[0];
    else
        return 0x00;
}

bytes decode_bytes(const std::string &str) {
    bytes res;
    for (size_t i = 2 + 64 + 64; i < str.length(); i += 64) {
        res.push_back(decode_byte(str.substr(i, 64)));
    }
    return res;
}

uint64_t decode_uint256(const std::string &str) {
    uint64_t res;
    std::stringstream ss;
    ss << std::hex << str;
    ss >> res;
    return res;
}

std::string decode_string(const std::string &str) {
    size_t len = decode_uint256(str.substr(0, 64));
    int padding = 0;
    while (str[str.length() - 1 - padding++] == '0') {}
    if (padding % 2 != 0)
        --padding;
    std::string res;
    for (size_t i = 64; i < str.length() - padding; i += 2)
        res += decode_byte(str.substr(i, 2));
    return boost::locale::conv::from_utf(res, "UTF-8");
}

std::vector<std::string> decode_strings(const std::string &str) {
    std::vector<std::string> res;
    if (!str.length())
        return res;
    size_t st_index = str.substr(0, 2) == "0x" ? 2 : 0;
    st_index += 64;
    const size_t len = decode_uint256(str.substr(st_index, 64));
    if (len == 0)
        return res;
    st_index += 64;
    std::vector<size_t> string_indeces;
    for (size_t i = 0; i < str.length() - st_index; i += 64) {
        auto x = decode_uint256(str.substr(st_index + i, 64));
        string_indeces.push_back(x);
    }
    for (size_t i = 1; i < len; i++) {
        auto st = st_index + string_indeces[i - 1] * 2, en = st_index + string_indeces[i] * 2;
        res.push_back(decode_string(str.substr(st, en - st)));
    }
    auto st = st_index + string_indeces[len - 1] * 2, en = str.length();
    res.push_back(decode_string(str.substr(st, en - st)));
    return res;
}

int decode_stat_struct(const std::string &str, struct stat *st) {
    std::vector<uint64_t> values;
    if (!str.length())
        return 0;
    size_t st_index = str.substr(0, 2) == "0x" ? 2 : 0;
    for (int i = st_index; i < str.length(); i += 64)
        values.push_back(decode_uint256(str.substr(i, 64)));

    st->st_nlink = 1;
    st->st_mode = values[2];
    st->st_size = values[6];
    st->st_atime = values[9];
    st->st_mtime = values[10];
    st->st_ctime = values[11];

    return 0;
}
