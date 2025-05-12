#include "encrypt_sdes.h"

using namespace std;

bitset<8> expansion_permutation(bitset<4> &block) {
    int ep[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    bitset<8> permuted_block;
    
    for (int i = 0; i < 8; ++i) {
        permuted_block[7 - i] = block[4 - ep[i]];
    }

    return permuted_block;
}

bitset<4> sbox_lookup(bitset<8> &xor_result) {
    int s0[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };
    
    int s1[4][4] = {
        {0, 1, 2, 3},   
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    int row1_x = (xor_result[7] << 1) | xor_result[4];
    int row1_y = (xor_result[5] << 1) | xor_result[6];
    int row2_x = (xor_result[3] << 1) | xor_result[0];
    int row2_y = (xor_result[1] << 1) | xor_result[2];
    int s0_value = s0[row1_x][row1_y];
    int s1_value = s1[row2_x][row2_y];

    return bitset<4>((bitset<2>(s0_value).to_ulong() << 2) | bitset<2>(s1_value).to_ulong());
}

bitset<4> p4(bitset<4> &sbox_output) {
    int p4[4] = {2, 4, 3, 1};
    bitset<4> permuted_output;
    
    for (int i = 0; i < 4; ++i) {
        permuted_output[3 - i] = sbox_output[4 - p4[i]];
    }

    return permuted_output;
}

bitset<4> fk(bitset<4> &half, bitset<8> &key) {
    // Apply expansion permutation to the half
    bitset<8> expanded_half = expansion_permutation(half);
    
    cout << "Expanded Half: " << expanded_half << endl;

    // XOR with the key
    bitset<8> xor_result = expanded_half ^ key;
    
    cout << "XOR Result: " << xor_result << endl;

    // Apply S-boxes
    bitset<4> sbox_output = sbox_lookup(xor_result);

    bitset<4> p4_output = p4(sbox_output);

    return p4_output;
}

bitset<8> encryption(bitset<8> &block, bitset<8> &key1, bitset<8> &key2) {
    // divide o bloco em L e R
    bitset<4> L = bitset<4>(block.to_string().substr(0, 4));
    bitset<4> R = bitset<4>(block.to_string().substr(4, 4));

    cout << "L: " << L << endl;
    cout << "R: " << R << endl;

    // PRIMEIRA RODADA
    bitset<4> fk_output = fk(R, key1);
    cout << "FK Output: " << fk_output << endl;
    R = L ^ fk_output; 
    cout << "New Right Half: " << R << endl;
    L = bitset<4>(block.to_string().substr(0, 4));
    cout << "New Left Half: " << L << endl;
    // Swap halves
    swap(L, R);
    cout << "After Swap - Left Half: " << L << ", Right Half: " << R << endl;


    // SEGUNDA RODADA
    fk_output = fk(R, key2);
    cout << "FK Output: " << fk_output << endl;
    R = L ^ fk_output;
    cout << "New Right Half: " << R << endl;
    L = bitset<4>(block.to_string().substr(0, 4));
    cout << "New Left Half: " << L << endl;
    // Combine halves
    bitset<8> combined_block = bitset<8>((L.to_ulong() << 4) | R.to_ulong());
    cout << "Combined Block: " << combined_block << endl;

    return combined_block;
}