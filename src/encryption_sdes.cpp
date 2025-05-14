#include "encrypt_sdes.h"
#include "permutations.h"

using namespace std;


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

bitset<4> fk(bitset<4> &half, bitset<8> &key) {
    cout << "Função FK:" << endl;

    // faz a expansão e permutação dos 4 bits
    bitset<8> expanded_half = expansion_permutation(half);
    cout << "   Metade após expansão e permutação: " << expanded_half << endl;

    // faz o XOR com a chave
    bitset<8> xor_result = expanded_half ^ key;
    cout << "   Metade após o XOR com a chave: " << xor_result << endl;

    // aplica as S-boxes
    bitset<4> sbox_output = sbox_lookup(xor_result);
    cout << "   Metade após aplicar as S-Boxes: " << sbox_output << endl;

    // faz a permutação P4
    bitset<4> p4_output = p4(sbox_output);
    cout << "   Metade após P4: " << p4_output << endl;

    return p4_output;
}

bitset<8> encrypt_sdes(bitset<8> &block, bitset<10> &key) {
    // primeiro, gera as chaves
    tuple<bitset<8>, bitset<8>> keys = generate_keys(key);
    bitset<8> key1 = get<0>(keys);
    bitset<8> key2 = get<1>(keys);
    cout << "Key1: " << key1 << endl;
    cout << "Key2: " << key2 << endl;

    // faz a permutação inicial (IP)
    block = IP(block);
    cout << "Estado depois de IP: " << block << endl;

    // divide o bloco em L e R
    bitset<4> L = bitset<4>(block.to_string().substr(0, 4));
    bitset<4> R = bitset<4>(block.to_string().substr(4, 4));

    cout << "L: " << L << endl;
    cout << "R: " << R << endl;


    // PRIMEIRA RODADA
    bitset<4> fk_output = fk(R, key1);
    cout << "Metade depois de FK: " << fk_output << endl;

    R = L ^ fk_output; // faz o XOR entre L e o resultado da função fk

    // permuta as duas metades
    swap(L, R);
    cout << "Estado após o switch das metades. L:" << L << ". R:" << R << endl;


    // SEGUNDA RODADA
    fk_output = fk(R, key2);
    cout << "Metade depois de FK: " << fk_output << endl;

    R = L ^ fk_output;
    cout << "Metade depois do XOR com FK: " << R << endl;

    // junta L e R
    bitset<8> combined_block = bitset<8>((L.to_ulong() << 4) | R.to_ulong());
    cout << "Estado aṕos juntar L e R: " << combined_block << endl;

    // faz o IP^-1
    block = inv_IP(combined_block);

    return block;
}


bitset<8> decrypt_sdes(bitset<8> &cipher_block, bitset<10> &key) {
    // primeiro, gera as chaves
    tuple<bitset<8>, bitset<8>> keys = generate_keys(key);
    bitset<8> key1 = get<0>(keys);
    bitset<8> key2 = get<1>(keys);
    cout << "Key1: " << key1 << endl;
    cout << "Key2: " << key2 << endl;

    // divide o bloco em L e R
    bitset<4> L = bitset<4>(cipher_block.to_string().substr(0, 4));
    bitset<4> R = bitset<4>(cipher_block.to_string().substr(4, 4));

    cout << "L: " << L << endl;
    cout << "R: " << R << endl;


    // PRIMEIRA RODADA
    bitset<4> fk_output = fk(R, key2);
    cout << "Metade depois de FK: " << fk_output << endl;

    R = L ^ fk_output; // faz o XOR entre L e o resultado da função fk

    // permuta as duas metades
    swap(L, R);
    cout << "Estado após o switch das metades. L:" << L << ". R:" << R << endl;


    // SEGUNDA RODADA
    fk_output = fk(R, key1);
    cout << "Metade depois de FK: " << fk_output << endl;

    R = L ^ fk_output;
    cout << "Metade depois do XOR com FK: " << R << endl;

    // junta L e R
    bitset<8> combined_block = bitset<8>((L.to_ulong() << 4) | R.to_ulong());
    cout << "Estado aṕos juntar L e R: " << combined_block << endl;

    // faz o IP^-1
    bitset<8> block = inv_IP(combined_block);

    return block;
}