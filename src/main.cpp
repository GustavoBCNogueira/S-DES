#include "encrypt_sdes.h"
#include "utils.h"
#include "op_modes.h"

int main() {
    bitset<10> key("1010000010"); // chave de 10 bits

    int option;
    cout << "\n\nEscolha uma opção:" << endl;
    cout << "1. Encriptar com S-DES" << endl;
    cout << "2. Decriptar com S-DES" << endl;
    cout << "3. Encriptar com ECB-SDES" << endl;
    cout << "4. Decriptar com ECB-SDES" << endl;
    cout << "5. Encriptar com CBC-SDES" << endl;
    cout << "6. Decriptar com CBC-SDES" << endl;
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
                
                bitset<8> encrypted_block = encrypt_sdes(block, key);
                
                cout << "Bloco cifrado: " << encrypted_block << endl;
            }
            else if (option == 2) {
                cout << "Digite o byte em binário a ser cifrado (e.g. 11010111): ";
                string binary;
                cin >> binary;
                bitset<8> block(binary); // texto claro em binário de 8 bits
                
                bitset<8> encrypted_block = encrypt_sdes(block, key);
                
                cout << "Bloco cifrado: " << encrypted_block << endl;
            }
    }

    else if (option == 2) {
        cout << "Digite o byte em binário a ser decifrado: ";
        string cipher_binary;
        cin >> cipher_binary;
        bitset<8> cipher_block(cipher_binary); // texto cifrado em binário de 8 bits

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
                
                // faz a encriptação com o modo ECB
                vector<bitset<8>> encrypted_blocks = encrypt_ecb_sdes(text, key);
            
                // mostra os blocos cifrados
                cout << "Blocos cifrados em ECB:" << endl;
                printCipherTextOpModes(encrypted_blocks);
            }

            else if (option == 2) {
                cout << "Digite os bits a serem cifrados em ECB-SDES (e.g. 11010111 01101100 10111010 11110000): ";
                string binary;
                cin.ignore(); // limpa o buffer
                getline(cin, binary);

                // transforma a string binária em um vetor de bitsets
                vector<bitset<8>> blocks = binaryStringToBitsetVector(binary);
                
                // faz a encriptação com o modo ECB
                vector<bitset<8>> encrypted_blocks = encrypt_ecb_sdes(blocks, key);
            
                // mostra os blocos cifrados
                cout << "Blocos cifrados em ECB:" << endl;
                printCipherTextOpModes(encrypted_blocks);
            }
    }

    else if (option == 4) {
        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o texto com caracteres." << endl;
        cout << "2. Inputar o texto em bytes em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o texto a ser decifrado em ECB-SDES: ";
                string text;
                cin.ignore(); // limpa o buffer
                getline(cin, text);
                
                // faz a decriptação com o modo ECB
                vector<bitset<8>> decrypted_blocks = decrypt_ecb_sdes(text, key);
            
                // mostra os blocos decifrados
                cout << "Blocos decifrados em ECB:" << endl;
                printCipherTextOpModes(decrypted_blocks);
            }

            else if (option == 2) {
                cout << "Digite os bits a serem decifrados em ECB-SDES (e.g. 11010111 01101100 10111010 11110000): ";
                string binary;
                cin.ignore(); // limpa o buffer
                getline(cin, binary);

                // transforma a string binária em um vetor de bitsets
                vector<bitset<8>> blocks = binaryStringToBitsetVector(binary);
                
                // faz a decriptação com o modo ECB
                vector<bitset<8>> decrypted_blocks = decrypt_ecb_sdes(blocks, key);
            
                // mostra os blocos decifrados
                cout << "Blocos decifrados em ECB:" << endl;
                printCipherTextOpModes(decrypted_blocks);
            }
    }
    
    else if (option == 5) {
        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o texto com caracteres." << endl;
        cout << "2. Inputar o texto em bytes em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o texto a ser cifrado em CBC-SDES: ";
                string text;
                cin.ignore(); // limpa o buffer
                getline(cin, text);

                // faz a encriptação com o modo CBC
                vector<bitset<8>> encrypted_blocks = encrypt_cbc_sdes(text, key);

                // mostra os blocos cifrados
                cout << "Blocos cifrados em CBC:" << endl;
                printCipherTextOpModes(encrypted_blocks);
            }

            else if (option == 2) {
                cout << "Digite os bits a serem cifrados em CBC-SDES (e.g. 11010111 01101100 10111010 11110000): ";
                string binary;
                cin.ignore(); // limpa o buffer
                getline(cin, binary);

                // transforma a string binária em um vetor de bitsets
                vector<bitset<8>> blocks = binaryStringToBitsetVector(binary);
                
                // faz a encriptação com o modo CBC
                vector<bitset<8>> encrypted_blocks = encrypt_cbc_sdes(blocks, key);

                // mostra os blocos cifrados
                cout << "Blocos cifrados em CBC:" << endl;
                printCipherTextOpModes(encrypted_blocks);
            }
    }

    else if (option == 6) {
        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o texto com caracteres." << endl;
        cout << "2. Inputar o texto em bytes em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o texto a ser decifrado em CBC-SDES: ";
                string text;
                cin.ignore(); // limpa o buffer
                getline(cin, text);

                // faz a decriptação com o modo CBC
                vector<bitset<8>> decrypted_blocks = decrypt_cbc_sdes(text, key);

                // mostra os blocos decifrados
                cout << "Blocos decifrados em CBC:" << endl;
                printCipherTextOpModes(decrypted_blocks);
            }

            else if (option == 2) {
                cout << "Digite os bits a serem decifrados em CBC-SDES (e.g. 11010111 01101100 10111010 11110000): ";
                string binary;
                cin.ignore(); // limpa o buffer
                getline(cin, binary);

                // transforma a string binária em um vetor de bitsets
                vector<bitset<8>> blocks = binaryStringToBitsetVector(binary);
                
                // faz a decriptação com o modo CBC
                vector<bitset<8>> decrypted_blocks = decrypt_cbc_sdes(blocks, key);

                // mostra os blocos decifrados
                cout << "Blocos decifrados em CBC:" << endl;
                printCipherTextOpModes(decrypted_blocks);
            }
    }

    return 0;
}