#ifndef ENCRYPT_SDES_H
#define ENCRYPT_SDES_H

#include <bits/stdc++.h>
#include "key_generation.h"
using namespace std;

bitset<8> expansion_permutation(bitset<4> &block);
bitset<4> sbox_lookup(bitset<8> &xor_result);
bitset<4> p4(bitset<4> &sbox_output);
bitset<4> fk(bitset<4> &half, bitset<8> &key);
bitset<8> encryption(bitset<8> &block, bitset<8> &key1, bitset<8> &key2);

#endif