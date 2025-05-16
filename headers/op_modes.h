#ifndef OP_MODES_H
#define OP_MODES_H

#include <bits/stdc++.h>
using namespace std;

vector<bitset<8>> encrypt_ecb_sdes(string text, bitset<10> key);
vector<bitset<8>> encrypt_ecb_sdes(vector<bitset<8>> blocks, bitset<10> key);
vector<bitset<8>> decrypt_ecb_sdes(string text, bitset<10> key);
vector<bitset<8>> decrypt_ecb_sdes(vector<bitset<8>> blocks, bitset<10> key);
vector<bitset<8>> encrypt_cbc_sdes(string text, bitset<10> key);
vector<bitset<8>> encrypt_cbc_sdes(vector<bitset<8>> blocks, bitset<10> key);
vector<bitset<8>> decrypt_cbc_sdes(string text, bitset<10> key);
vector<bitset<8>> decrypt_cbc_sdes(vector<bitset<8>> blocks, bitset<10> key);

#endif