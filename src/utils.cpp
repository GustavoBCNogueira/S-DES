#include "utils.h"

bitset<8> charToBitset(char c) {
    return bitset<8>(static_cast<unsigned char>(c));
}

char bitsetToChar(const bitset<8>& bits) {
    return static_cast<char>(bits.to_ulong());
}