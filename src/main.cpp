#include "encrypt_sdes.h"
#include "utils.h"

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
        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o caractere." << endl;
        cout << "2. Inputar o byte em binário." << endl;
        cin >> option;
        if (option == 1) {
            cout << "Digite o caractere a ser cifrado: ";
            char c;
            cin >> c;
            bitset<8> block = charToBitset(c); // texto claro em binário de 8 bits
            bitset<10> key("1010000010"); // chave de 10 bits
            
            bitset<8> encrypted_block = encrypt_sdes(block, key);
            
            cout << "Bloco cifrado: " << encrypted_block << endl;
        }
        else if (option == 2) {
            cout << "Digite o byte em binário a ser cifrado (e.g. 11010111): ";
            string binary;
            cin >> binary;
            bitset<8> block(binary); // texto claro em binário de 8 bits
            bitset<10> key("1010000010"); // chave de 10 bits
            
            bitset<8> encrypted_block = encrypt_sdes(block, key);
            
            cout << "Bloco cifrado: " << encrypted_block << endl;
        }
        
        main();
    }

    else if (option == 2) {
        cout << "Digite o byte em binário a ser decifrado: ";
        string cipher_binary;
        cin >> cipher_binary;
        bitset<8> cipher_block(cipher_binary); // texto cifrado em binário de 8 bits
        bitset<10> key("1010000010"); // chave de 10 bits

        bitset<8> block = decrypt_sdes(cipher_block, key);

        cout << "Bloco decriptado: " << block << endl;
        // 10101000
        main();
    }

    else if (option == 3) {
        cout << "Digite o texto a ser cifrado em ECB-SDES: ";
        string text;
        cin >> text;
    
        bitset<10> key("1010000010"); // chave de 10 bits
        vector<bitset<8>> encrypted_blocks;
    
        // número de blocos de 8 bits
        int num_blocks = text.size();

        for (int i = 0; i < num_blocks; i++) {
            bitset<8> current_block = charToBitset(text[i]);
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