#include "utils.h"
#include <iostream>
using namespace std;

bitset<8> charToBitset(char c) {
    return bitset<8>(static_cast<unsigned char>(c));
}

char bitsetToChar(const bitset<8>& bits) {
    return static_cast<char>(bits.to_ulong());
}

void printState(const bitset<4>& L, const bitset<4>& R, string state_name) {
    if (!state_name.empty())
        cout << "Estado após " << state_name << ":" << endl;
    cout << "L: " << L << endl;
    cout << "R: " << R << "\n\n";
}

void printState(const bitset<8>&block, string state_name) {
    if (!state_name.empty())
        cout << "Estado após " << state_name << ":" << endl;
    cout << "Bloco: " << "\n\n";
}