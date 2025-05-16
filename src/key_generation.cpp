#include "key_generation.h"

bitset<5> left_circular_shift(bitset<5> &key) {
    // faz um shift circular à esquerda de 1 bit
    // o bit mais à esquerda vai para o final e os outros bits são deslocados para a esquerda
    return (key << 1) | (key >> 4);
}

bitset<10> p10(bitset<10> &key) {
    int p10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6}; // fixada pelo algoritmo
    bitset<10> permuted_key;
    
    for (int i = 0; i < 10; i++) {
        // permutação com ordem inversa por causa do bitset
        permuted_key[9 - i] = key[10 - p10[i]];
    }

    return permuted_key;
}

bitset<8> p8(bitset<10> &key) {
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 9}; // fixada pelo algoritmo
    bitset<8> permuted_key;
    
    for (int i = 0; i < 8; i++) {
        // permutação com ordem inversa por causa do bitset
        permuted_key[7 - i] = key[10 - p8[i]];
    }   

    return permuted_key;
}

tuple<bitset<8>, bitset<8>> generate_keys(bitset<10> &key) {
    cout << "Geração de chaves:" << endl;

    // faz a permutação P10
    bitset<10> permuted_key = p10(key);

    cout << "   Chave depois da permutação: " << permuted_key << endl;
    
    // divide a chave em duas metades
    bitset<5> left_half = bitset<5>(permuted_key.to_string().substr(0, 5));
    bitset<5> right_half = bitset<5>(permuted_key.to_string().substr(5, 5));

    // faz o shift circular à esquerda no L e R
    left_half = left_circular_shift(left_half);
    right_half = left_circular_shift(right_half);

    cout << "   Primeira metade depois do shift: " << left_half << endl;
    cout << "   Segunda metade depois do shift: " << right_half << endl;
    
    // junta as duas metades
    permuted_key = bitset<10>((left_half.to_ulong() << 5) | right_half.to_ulong());

    cout << "   Chave depois de juntar as duas metades: " << permuted_key << endl;

    // faz a permutação P8 e gera a primeira subchave
    bitset<8> key1 = p8(permuted_key);
   
    cout << "   Chave 1 (depois de P8): " << key1 << endl;

    // faz o shift circular à esquerda no L e R (2 vezes)
    for (int i = 0; i < 2; i++) {
        left_half = left_circular_shift(left_half);
        right_half = left_circular_shift(right_half);
    }

    cout << "   Primeira metade depois dos shifts: " << left_half << endl;
    cout << "   Segunda metade depois dos shifts: " << right_half << endl;

    // junta as duas metades
    permuted_key = bitset<10>((left_half.to_ulong() << 5) | right_half.to_ulong());

    cout << "   Chave depois de juntar as duas metades: " << permuted_key << endl;
    
    // faz a permutação P8 e gera a segunda subchave
    bitset<8> key2 = p8(permuted_key);

    cout << "   Chave 2 (depois de P8): " << key2 << "\n\n";

    return {key1, key2};
}