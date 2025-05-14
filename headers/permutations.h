#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <bits/stdc++.h>
using namespace std;

bitset<8> IP(bitset<8> &block);
bitset<8> inv_IP(bitset<8> &block);
bitset<4> p4(bitset<4> &sbox_output);
bitset<8> expansion_permutation(bitset<4> &block);

#endif