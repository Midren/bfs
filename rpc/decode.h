#ifndef RPC_DECODE_H
#define RPC_DECODE_H

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

byte decode_byte(const std::string &str);

bytes decode_bytes(const std::string &str);

uint64_t decode_uint256(const std::string &str);

int decode_stat_struct(const std::string &str, struct stat *st);

std::vector<std::string> decode_strings(const std::string &str);

#endif //RPC_DECODE_H
