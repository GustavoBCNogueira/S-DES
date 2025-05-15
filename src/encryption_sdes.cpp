#include "encrypt_sdes.h"
#include "permutations.h"
#include "utils.h"

using namespace std;


bitset<4> sbox_lookup(bitset<8>& input) {
    // s-box 0
    int s0[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    // s-box 1
    int s1[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };
    // s-boxes são definidas pelo algoritmo (FIXAS)

    // pega os bits para s0

    int s0_row_bit1 = input[7];
    int s0_row_bit0 = input[4];
    // junta os dois bits para formar a linha
    int s0_row = (s0_row_bit1 << 1) | s0_row_bit0;

    int s0_col_bit1 = input[6];
    int s0_col_bit0 = input[5];
    // junta os dois bits para formar a coluna
    int s0_col = (s0_col_bit1 << 1) | s0_col_bit0;


    // pega os bits para s1

    int s1_row_bit1 = input[3];
    int s1_row_bit0 = input[0];
    // junta os dois bits para formar a linha
    int s1_row = (s1_row_bit1 << 1) | s1_row_bit0;

    int s1_col_bit1 = input[2];
    int s1_col_bit0 = input[1];
    // junta os dois bits para formar a coluna
    int s1_col = (s1_col_bit1 << 1) | s1_col_bit0;

    // aplica as S-boxes
    int s0_value = s0[s0_row][s0_col];
    int s1_value = s1[s1_row][s1_col];

    // junta os dois valores em um único de 4 bits
    int value = (s0_value << 2) | s1_value;

    bitset<4> result(value);
    return result;
}


bitset<4> fk(bitset<4> &half, bitset<8> &key) {
    cout << "Função FK:" << endl;

    // faz a expansão e permutação dos 4 bits
    bitset<8> expanded_half = expansion_permutation(half);
    cout << "   R após expansão e permutação: " << expanded_half << endl;

    // faz o XOR com a chave
    bitset<8> xor_result = expanded_half ^ key;
    cout << "   R após o XOR com a chave: " << xor_result << endl;

    // aplica as S-boxes
    bitset<4> sbox_output = sbox_lookup(xor_result);
    cout << "   R após aplicar as S-Boxes: " << sbox_output << endl;

    // faz a permutação P4
    bitset<4> p4_output = p4(sbox_output);
    cout << "   R após P4: " << p4_output << "\n\n";

    return p4_output;
}

bitset<8> encrypt_sdes(bitset<8> &block, bitset<10> &key) {
    cout << "Bloco a ser cifrado em binário: " << block << "\n\n";
    // primeiro, gera as chaves
    tuple<bitset<8>, bitset<8>> keys = generate_keys(key);
    bitset<8> key1 = get<0>(keys);
    bitset<8> key2 = get<1>(keys);
    cout << "Key1: " << key1 << endl;
    cout << "Key2: " << key2 << "\n\n";

    // faz a permutação inicial (IP)
    block = IP(block);
    printState(block, "IP");

    // divide o bloco em L e R
    bitset<4> L = bitset<4>(block.to_string().substr(0, 4));
    bitset<4> R = bitset<4>(block.to_string().substr(4, 4));

    printState(L, R);


    // PRIMEIRA RODADA
    bitset<4> fk_output = fk(R, key1);
    
    L = L ^ fk_output; // faz o XOR entre L e o resultado da função fk
    printState(L, R, "Feistel");

    // permuta as duas metades
    swap(L, R);
    printState(L, R, "SWITCH"),


    // SEGUNDA RODADA
    fk_output = fk(R, key2);
    
    // faz o XOR entre L e o resultado da função fk
    L = L ^ fk_output;
    printState(L, R, "Feistel");

    // junta L e R
    bitset<8> combined_block = bitset<8>((L.to_ulong() << 4) | R.to_ulong());
    printState(block, "juntar L e R");

    // faz o IP^-1
    block = inv_IP(combined_block);
    printState(block, "IP^-1");

    return block;
}


bitset<8> decrypt_sdes(bitset<8> &cipher_block, bitset<10> &key) {
    // primeiro, gera as chaves
    tuple<bitset<8>, bitset<8>> keys = generate_keys(key);
    bitset<8> key1 = get<0>(keys);
    bitset<8> key2 = get<1>(keys);
    cout << "Key1: " << key1 << endl;
    cout << "Key2: " << key2 << "\n\n";

    // faz a permutação inicial (IP)
    cipher_block = IP(cipher_block);
    printState(cipher_block, "IP");

    // divide o bloco em L e R
    bitset<4> L = bitset<4>(cipher_block.to_string().substr(0, 4));
    bitset<4> R = bitset<4>(cipher_block.to_string().substr(4, 4));

    printState(L, R);


    // PRIMEIRA RODADA
    bitset<4> fk_output = fk(R, key2);
    
    L = L ^ fk_output; // faz o XOR entre L e o resultado da função fk
    printState(L, R, "Feistel");

    // permuta as duas metades
    swap(L, R);
    printState(L, R, "SWITCH"),


    // SEGUNDA RODADA
    fk_output = fk(R, key1);
    
    // faz o XOR entre L e o resultado da função fk
    L = L ^ fk_output;
    printState(L, R, "Feistel");

    // junta L e R
    bitset<8> combined_block = bitset<8>((L.to_ulong() << 4) | R.to_ulong());
    printState(cipher_block, "juntar L e R");

    // faz o IP^-1
    cipher_block = inv_IP(combined_block);
    printState(cipher_block, "IP^-1");

    return cipher_block;
}