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
        // ENCRIPTAÇÃO S-DES

        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o caractere." << endl;
        cout << "2. Inputar o byte em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o caractere a ser cifrado (e.g 'a'): ";
                char c;
                cin >> c;
                bitset<8> block = charToBitset(c); // texto claro em binário de 8 bits
                
                // faz a encriptação
                bitset<8> encrypted_block = encrypt_sdes(block, key);
                
                // mostra o bloco cifrado
                cout << "Bloco cifrado em S-DES: " << endl;
                printEncOrDecText({encrypted_block});
            }
            else if (option == 2) {
                cout << "Digite o byte em binário a ser cifrado (e.g. 11010111): ";
                string binary;
                cin >> binary;
                bitset<8> block(binary); // texto claro em binário de 8 bits
                
                bitset<8> encrypted_block = encrypt_sdes(block, key);
                
                cout << "Bloco cifrado em S-DES: " << endl;
                printEncOrDecText({encrypted_block});
            }
    }

    else if (option == 2) {
        // DECRIPTAÇÃO S-DES

        cout << "Digite o byte em binário a ser decifrado (e.g. 10101000): ";
        string cipher_binary;
        cin >> cipher_binary;
        bitset<8> cipher_block(cipher_binary); // texto cifrado em binário de 8 bits

        // faz a decriptação
        bitset<8> block = decrypt_sdes(cipher_block, key);

        // mostra o bloco decifrado
        cout << "Bloco decriptado: " << endl;
        printEncOrDecText({block});
    }

    else if (option == 3) {
        // ENCRIPTAÇÃO ECB-SDES

        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o texto com caracteres." << endl;
        cout << "2. Inputar o texto em bytes em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o texto a ser cifrado em ECB-SDES (e.g. 'ola'): ";
                string text;
                cin.ignore(); // limpa o buffer
                getline(cin, text);
                
                // faz a encriptação com o modo ECB
                vector<bitset<8>> encrypted_blocks = encrypt_ecb_sdes(text, key);
            
                // mostra os blocos cifrados
                cout << "Blocos cifrados em ECB:" << endl;
                printEncOrDecText(encrypted_blocks);
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
                printEncOrDecText(encrypted_blocks);
            }
    }

    else if (option == 4) {
        // DECRIPTAÇÃO ECB-SDES

        cout << "Digite os bits a serem decifrados em ECB-SDES (e.g. 10101000 00001101 00101110 01101101): ";
        string binary;
        cin.ignore(); // limpa o buffer
        getline(cin, binary);

        // transforma a string binária em um vetor de bitsets
        vector<bitset<8>> blocks = binaryStringToBitsetVector(binary);
        
        // faz a decriptação com o modo ECB
        vector<bitset<8>> decrypted_blocks = decrypt_ecb_sdes(blocks, key);
    
        // mostra os blocos decifrados
        cout << "Blocos decifrados em ECB:" << endl;
        printEncOrDecText(decrypted_blocks);
    }
    
    else if (option == 5) {
        // ENCRIPTAÇÃO CBC-SDES

        cout << "Escolha uma opção:" << endl;
        cout << "1. Inputar o texto com caracteres." << endl;
        cout << "2. Inputar o texto em bytes em binário." << endl;
        cin >> option;
            if (option == 1) {
                cout << "Digite o texto a ser cifrado em CBC-SDES (e.g. 'ola'): ";
                string text;
                cin.ignore(); // limpa o buffer
                getline(cin, text);

                // faz a encriptação com o modo CBC
                vector<bitset<8>> encrypted_blocks = encrypt_cbc_sdes(text, key);

                // mostra os blocos cifrados
                cout << "Blocos cifrados em CBC:" << endl;
                printEncOrDecText(encrypted_blocks);
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
                printEncOrDecText(encrypted_blocks);
            }
    }

    else if (option == 6) {
        // DECRIPTAÇÃO CBC-SDES
        
        cout << "Digite os bits a serem decifrados em CBC-SDES (e.g. 00001011 10101001 10011011 01101010): ";
        string binary;
        cin.ignore(); // limpa o buffer
        getline(cin, binary);

        // transforma a string binária em um vetor de bitsets
        vector<bitset<8>> blocks = binaryStringToBitsetVector(binary);
        
        // faz a decriptação com o modo CBC
        vector<bitset<8>> decrypted_blocks = decrypt_cbc_sdes(blocks, key);

        // mostra os blocos decifrados
        cout << "Blocos decifrados em CBC:" << endl;
        printEncOrDecText(decrypted_blocks);
    }

    return 0;
}