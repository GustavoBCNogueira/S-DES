#include "encrypt_sdes.h"

int main() {
    int option;
    cout << "\n\nEscolha uma opção:" << endl;
    cout << "1. Encriptar com S-DES" << endl;
    cout << "2. Decriptar com S-DES" << endl;
    cout << "3. Encriptar com ECB-SDES" << endl;
    cout << "4. Encriptar com CBC-SDES" << endl;
    cout << "Qualquer outro caractere irá sair do programa" << endl;
    cin >> option;

    if (option == 1) {
        bitset<8> block("10101011"); // texto claro em binário de 8 bits
        bitset<10> key("1010000010"); // chave de 10 bits
    
        bitset<8> encrypted_block = encrypt_sdes(block, key);
    
        cout << "Bloco cifrado: " << encrypted_block << endl;

        main();
    }

    else if (option == 2) {
        bitset<8> cipher_block("01101101"); // texto cifrado em binário de 8 bits
        bitset<10> key("1010000010"); // chave de 10 bits

        bitset<8> block = decrypt_sdes(cipher_block, key);

        cout << "Bloco decriptado: " << block << endl;

        main();
    }
    else if (option == 3) {}
    else if (option == 4) {}

    return 0;
}