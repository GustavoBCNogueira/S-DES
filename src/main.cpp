#include "encrypt_sdes.h"

int main() {
    bitset<8> block("10101011"); // texto claro em binário de 8 bits
    bitset<10> key("1010000010"); // chave de 10 bits
    tuple<bitset<8>, bitset<8>> keys = generate_keys(key);
    bitset<8> key1 = get<0>(keys);
    bitset<8> key2 = get<1>(keys);

    cout << "Input Block: " << block << endl;
    cout << "Key1: " << key1 << endl;
    cout << "Key2: " << key2 << endl;

    bitset<8> encrypted_block = encryption(block, key1, key2);

    cout << "Encrypted Block: " << encrypted_block << endl;

    return 0;
}