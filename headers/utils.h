#ifndef UTILS_H
#define UTILS_H

#include <bitset>
using namespace std;

bitset<8> charToBitset(char c);
char bitsetToChar(const bitset<8>& bits);

#endif