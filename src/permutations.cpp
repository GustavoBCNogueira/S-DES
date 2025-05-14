#include "permutations.h"

bitset<8> IP(bitset<8> &block) {
    int ip[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    bitset<8> permuted_block;
    
    for (int i = 0; i < 8; ++i) {
        permuted_block[7 - i] = block[8 - ip[i]];
    }

    return permuted_block;
}

bitset<8> inv_IP(bitset<8> &block) {
    int ip[8] = {4, 1, 3, 5, 7, 2, 8, 6};
    bitset<8> permuted_block;
    
    for (int i = 0; i < 8; ++i) {
        permuted_block[7 - i] = block[8 - ip[i]];
    }

    return permuted_block;
}

bitset<4> p4(bitset<4> &sbox_output) {
    int p4[4] = {2, 4, 3, 1};
    bitset<4> permuted_output;
    
    for (int i = 0; i < 4; ++i) {
        permuted_output[3 - i] = sbox_output[4 - p4[i]];
    }

    return permuted_output;
}

bitset<8> expansion_permutation(bitset<4> &block) {
    int ep[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    bitset<8> permuted_block;
    
    for (int i = 0; i < 8; i++) {
        permuted_block[7 - i] = block[4 - ep[i]];
    }

    return permuted_block;
}