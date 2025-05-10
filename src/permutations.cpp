#include <bits/stdc++.h>

using namespace std;

bitset<8> initial_permutation(bitset<8> &block) {
    int ip[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    bitset<8> permuted_block;
    
    for (int i = 0; i < 8; ++i) {
        permuted_block[7 - i] = block[8 - ip[i]];
    }

    return permuted_block;
}

bitset<8> inverse_initial_permutation(bitset<8> &block) {
    int ip[8] = {4, 1, 3, 5, 7, 2, 8, 6};
    bitset<8> permuted_block;
    
    for (int i = 0; i < 8; ++i) {
        permuted_block[7 - i] = block[8 - ip[i]];
    }

    return permuted_block;
}