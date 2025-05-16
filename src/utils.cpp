#include "utils.h"
#include <iostream>
using namespace std;

bitset<8> charToBitset(char c) {
    return bitset<8>(static_cast<unsigned char>(c));
}

void printState(const bitset<4>& L, const bitset<4>& R, string state_name) {
    // printa o estado em binário (L e R de 4 bits)
    if (!state_name.empty())
        cout << "Estado após " << state_name << ":" << endl;
    cout << "L: " << L << endl;
    cout << "R: " << R << "\n\n";
}

void printState(const bitset<8>&block, string state_name) {
    // printa o estado em binário (bloco de 8 bits)
    if (!state_name.empty())
        cout << "Estado após " << state_name << ":" << endl;
    cout << block << "\n\n";
}

void removeSpaces(string& str) {
    // remove espaços em branco da string
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

vector<bitset<8>> binaryStringToBitsetVector(string& binary) {
    // remove espaços em branco
    removeSpaces(binary);

    // divide a string em blocos de 8 bits
    vector<bitset<8>> blocks;
    for (size_t i = 0; i < binary.size(); i += 8) {
        string block_str = binary.substr(i, 8); // pega 8 bits
        bitset<8> current_block(block_str);
        blocks.push_back(current_block);
    }
    return blocks;
}

void printEncOrDecText(const vector<bitset<8>>& blocks) {
    // printa os blocos em binário
    cout << "Em binário: ";
    for (const auto& block : blocks) {
        cout << block << " ";
    }
    cout << endl;

    // printa os blocos em hexadecimal
    cout << "Em hexadecimal: 0x";
    for (const auto& block : blocks) {
        cout << hex << uppercase << setw(2) << setfill('0') << block.to_ulong();
    }
    cout << endl;
}