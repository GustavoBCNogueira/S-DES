#ifndef KEY_GENERATION_H
#define KEY_GENERATION_H

#include <bits/stdc++.h>
using namespace std;

// Function prototypes
bitset<5> left_circular_shift(const bitset<5>& key);
bitset<10> p10(const bitset<10>& input);
bitset<8> p8(bitset<10> &key);
tuple<bitset<8>, bitset<8>> generate_keys(bitset<10> &key);

#endif