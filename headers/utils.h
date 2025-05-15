#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
using namespace std;

bitset<8> charToBitset(char c);
char bitsetToChar(const bitset<8>& bits);
void printState(const bitset<4>& L, const bitset<4>& R, string state_name="");
void printState(const bitset<8>& block, string state_name="");
void removeSpaces(string& str);
vector<bitset<8>> binaryStringToBitsetVector(string& binary);
void printCipherTextOpModes(const vector<bitset<8>>& encrypted_blocks);

#endif