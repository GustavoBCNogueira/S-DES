#include "encrypt_sdes.h"
#include "utils.h"
#include "op_modes.h"

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
        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o texto com caracteres." << endl;
        cout << "2. Inputar o texto em bytes em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o texto a ser cifrado em ECB-SDES: ";
                string text;
                cin.ignore(); // limpa o buffer
                getline(cin, text);
            
                bitset<10> key("1010000010"); // chave de 10 bits
                
                // faz a encriptação com o modo ECB
                vector<bitset<8>> encrypted_blocks = encrypt_ecb_sdes(text, key);
            
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

            else if (option == 2) {
                cout << "Digite os bits a serem cifrados em ECB-SDES (e.g. 11010111 01101100 10111010 11110000): ";
                string binary;
                cin.ignore(); // limpa o buffer
                getline(cin, binary);

                // remove espaços em branco
                removeSpaces(binary);

                // divide a string em blocos de 8 bits
                vector<bitset<8>> blocks;
                for (size_t i = 0; i < binary.size(); i += 8) {
                    string block_str = binary.substr(i, 8);
                    bitset<8> current_block(block_str);
                    blocks.push_back(current_block);
                }

                bitset<10> key("1010000010"); // chave de 10 bits
                
                // faz a encriptação com o modo ECB
                vector<bitset<8>> encrypted_blocks = encrypt_ecb_sdes(blocks, key);
            
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
    }
    

    else if (option == 4) {
        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o texto com caracteres." << endl;
        cout << "2. Inputar o texto em bytes em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o texto a ser cifrado em CBC-SDES: ";
                string text;
                cin.ignore(); // limpa o buffer
                getline(cin, text);

                bitset<10> key("1010000010"); // chave de 10 bits

                // faz a encriptação com o modo CBC
                vector<bitset<8>> encrypted_blocks = encrypt_cbc_sdes(text, key);

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

            else if (option == 2) {
                cout << "Digite os bits a serem cifrados em CBC-SDES (e.g. 11010111 01101100 10111010 11110000): ";
                string binary;
                cin.ignore(); // limpa o buffer
                getline(cin, binary);

                // remove espaços em branco
                removeSpaces(binary);

                // divide a string em blocos de 8 bits
                vector<bitset<8>> blocks;
                for (size_t i = 0; i < binary.size(); i += 8) {
                    string block_str = binary.substr(i, 8);
                    bitset<8> current_block(block_str);
                    blocks.push_back(current_block);
                }

                bitset<10> key("1010000010"); // chave de 10 bits
                
                // faz a encriptação com o modo CBC
                vector<bitset<8>> encrypted_blocks = encrypt_cbc_sdes(blocks, key);

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
    }

    return 0;
}