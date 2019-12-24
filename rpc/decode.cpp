#include "decode.h"

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
