#ifndef ENCRYPT_SDES_H
#define ENCRYPT_SDES_H

#include <bits/stdc++.h>
#include "key_generation.h"
using namespace std;

bitset<4> sbox_lookup(bitset<8> &xor_result);
bitset<4> fk(bitset<4> &half, bitset<8> &key);
bitset<8> encrypt_sdes(bitset<8> &block, bitset<10> &key);

#endif