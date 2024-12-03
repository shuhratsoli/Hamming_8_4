#ifndef HAMMING_8_4_H_INCLUDED
#define HAMMING_8_4_H_INCLUDED
#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>

namespace Hamming_8_4
{

    uint8_t EncodeHelper(uint8_t byte);
    std::vector<uint8_t> Encode(const std::vector<uint8_t> bytes);
    uint8_t DecodeHelper(uint8_t x);
    std::vector<uint8_t> Decode(const std::vector<uint8_t> bytes);

}

#endif
