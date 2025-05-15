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
        cout << "Em binário: ";
        for (const auto& block : encrypted_blocks) {
            cout << block << " ";
        }
        cout << endl;
        cout << "Em hexadecimal: 0x";
        for (const auto& block : encrypted_blocks) {
            cout << hex << uppercase << block.to_ulong();
        }
        cout << endl;
    }
    

    else if (option == 4) {
        cout << "Digite o texto a ser cifrado em CBC-SDES: ";
        string text;
        cin >> text;

        bitset<10> key("1010000010"); // chave de 10 bits
        vector<bitset<8>> encrypted_blocks;

        // número de blocos de 8 bits
        int num_blocks = text.size();

        // vetor de inicialização (IV)
        bitset<8> iv("01010101"); // FIXADO pela especificação do trabalho

        for (int i = 0; i < num_blocks; i++) {
            bitset<8> current_block = charToBitset(text[i]);
            if (i == 0) {
                // pro primeiro bloco, XOR com o vetor de inicialização
                current_block ^= iv;
            }
            else {
                // pro resto dos blocos, XOR com o bloco cifrado anterior
                current_block ^= encrypted_blocks[i - 1];
            }
            bitset<8> encrypted_block = encrypt_sdes(current_block, key);
            encrypted_blocks.push_back(encrypted_block);
        }

        // mostra os blocos cifrados
        cout << "Blocos cifrados em CBC:" << endl;
        cout << "Em binário: ";
        for (const auto& block : encrypted_blocks) {
            cout << block << " ";
        }
        cout << endl;
        cout << "Em hexadecimal: 0x";
        for (const auto& block : encrypted_blocks) {
            cout << hex << uppercase << block.to_ulong();
        }
        cout << endl;
    }

    return 0;
}