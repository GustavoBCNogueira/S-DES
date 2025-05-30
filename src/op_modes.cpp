#include "op_modes.h"
#include "encrypt_sdes.h"
#include "utils.h"

vector<bitset<8>> encrypt_ecb_sdes(string text, bitset<10> key) {
    vector<bitset<8>> encrypted_blocks;

    // número de blocos de 8 bits
    int num_blocks = text.size();

    // apenas encripta os blocos
    for (int i = 0; i < num_blocks; i++) {
        bitset<8> current_block = charToBitset(text[i]); // primeiro transforma o caractere em bitset
        bitset<8> encrypted_block = encrypt_sdes(current_block, key);
        encrypted_blocks.push_back(encrypted_block);
    }
    return encrypted_blocks;
}


vector<bitset<8>> encrypt_ecb_sdes(vector<bitset<8>> blocks, bitset<10> key) {
    vector<bitset<8>> encrypted_blocks;

    // número de blocos de 8 bits
    int num_blocks = blocks.size();

    // apenas encripta os blocos
    for (int i = 0; i < num_blocks; i++) {
        bitset<8> encrypted_block = encrypt_sdes(blocks[i], key);
        encrypted_blocks.push_back(encrypted_block);
    }
    return encrypted_blocks;
}


vector<bitset<8>> decrypt_ecb_sdes(vector<bitset<8>> blocks, bitset<10> key) {
    vector<bitset<8>> decrypted_blocks;

    // número de blocos de 8 bits
    int num_blocks = blocks.size();

    // apenas decripta os blocos
    for (int i = 0; i < num_blocks; i++) {
        bitset<8> decrypted_block = decrypt_sdes(blocks[i], key);
        decrypted_blocks.push_back(decrypted_block);
    }
    return decrypted_blocks;
}


vector<bitset<8>> encrypt_cbc_sdes(string text, bitset<10> key) {
    vector<bitset<8>> encrypted_blocks;

    // número de blocos de 8 bits
    int num_blocks = text.size();

    // vetor de inicialização (IV)
    bitset<8> iv("01010101"); // FIXADO pela especificação do trabalho

    for (int i = 0; i < num_blocks; i++) {
        bitset<8> current_block = charToBitset(text[i]); // primeiro transforma o caractere em bitset
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
    return encrypted_blocks;
}


vector<bitset<8>> encrypt_cbc_sdes(vector<bitset<8>> blocks, bitset<10> key) {
    vector<bitset<8>> encrypted_blocks;

    // número de blocos de 8 bits
    int num_blocks = blocks.size();

    // vetor de inicialização (IV)
    bitset<8> iv("01010101"); // FIXADO pela especificação do trabalho

    for (int i = 0; i < num_blocks; i++) {
        if (i == 0) {
            // pro primeiro bloco, XOR com o vetor de inicialização
            blocks[i] ^= iv;
        }
        else {
            // pro resto dos blocos, XOR com o bloco cifrado anterior
            blocks[i] ^= encrypted_blocks[i - 1];
        }
        bitset<8> encrypted_block = encrypt_sdes(blocks[i], key);
        encrypted_blocks.push_back(encrypted_block);
    }
    return encrypted_blocks;
}


vector<bitset<8>> decrypt_cbc_sdes(vector<bitset<8>> blocks, bitset<10> key) {
    vector<bitset<8>> decrypted_blocks;

    // número de blocos de 8 bits
    int num_blocks = blocks.size();

    // vetor de inicialização (IV)
    bitset<8> iv("01010101"); // FIXADO pela especificação do trabalho

    for (int i = num_blocks-1; i >= 0; i--) {
        bitset<8> decrypted_block = decrypt_sdes(blocks[i], key);
        if (i == 0) {
            // pro primeiro bloco, XOR com o vetor de inicialização
            decrypted_block ^= iv;
        }
        else {
            // pro resto dos blocos, XOR com o bloco cifrado anterior
            decrypted_block ^= blocks[i - 1];
        }
        decrypted_blocks.insert(decrypted_blocks.begin(), decrypted_block);
    }
    return decrypted_blocks;
}