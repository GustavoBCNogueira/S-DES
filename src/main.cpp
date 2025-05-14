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

    else if (option == 3) {
        string input_bits = "101010111010101110101011"; // texto claro binário de 24 bits (3 blocos)
    
        bitset<10> key("1010000010"); // chave de 10 bits
        vector<bitset<8>> encrypted_blocks;
    
        // número de blocos de 8 bits
        int num_blocks = input_bits.size() / 8;
    
        for (int i = 0; i < num_blocks; i++) {
            string block_str = input_bits.substr(i * 8, 8);
            bitset<8> current_block(block_str);
    
            bitset<8> encrypted_block = encrypt_sdes(current_block, key);
            encrypted_blocks.push_back(encrypted_block);
        }
    
        // mostra os blocos cifrados
        cout << "Blocos cifrados em ECB:" << endl;
        for (const auto& block : encrypted_blocks) {
            cout << block << " ";
        }
        cout << endl;
    
        main();
    }
    

    else if (option == 4) {}

    return 0;
}