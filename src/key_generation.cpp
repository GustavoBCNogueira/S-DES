#include <bits/stdc++.h>

using namespace std;

bitset<5> left_circular_shift(bitset<5> &key) {
    return (key << 1) | (key >> 4);
}

bitset<10> p10(bitset<10> &key) {
    int p10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    bitset<10> permuted_key;
    
    for (int i = 0; i < 10; ++i) {
        permuted_key[9 - i] = key[10 - p10[i]];
    }

    return permuted_key;
}

bitset<8> p8(bitset<10> &key) {
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
    bitset<8> permuted_key;
    
    for (int i = 0; i < 8; ++i) {
        permuted_key[7 - i] = key[10 - p8[i]];
    }   

    return permuted_key;
}

tuple<bitset<8>, bitset<8>> generate_keys(bitset<10> &key) {
    bitset<10> permuted_key = p10(key);

    cout << "Permuted Key: " << permuted_key << endl;
    
    bitset<5> left_half = bitset<5>(permuted_key.to_string().substr(0, 5));
    bitset<5> right_half = bitset<5>(permuted_key.to_string().substr(5, 5));

    cout << "Left Half: " << left_half << endl;
    cout << "Right Half: " << right_half << endl;

    left_half = left_circular_shift(left_half);
    right_half = left_circular_shift(right_half);

    cout << "Left Half after shift: " << left_half << endl;
    cout << "Right Half after shift: " << right_half << endl;
    
    permuted_key = bitset<10>((left_half.to_ulong() << 5) | right_half.to_ulong());

    cout << "Combined Key after shift: " << permuted_key << endl;

    bitset<8> key1 = p8(permuted_key);
   
    cout << "Key 1: " << key1 << endl;

    for (int i = 0; i < 2; i++) {
        left_half = left_circular_shift(left_half);
        right_half = left_circular_shift(right_half);
    }

    cout << "Left Half after second shift: " << left_half << endl;
    cout << "Right Half after second shift: " << right_half << endl;

    permuted_key = bitset<10>((left_half.to_ulong() << 5) | right_half.to_ulong());

    cout << "Combined Key after second shift: " << permuted_key << endl;
    
    bitset<8> key2 = p8(permuted_key);

    cout << "Key 2: " << key2 << endl;

    return {key1, key2};
}

int main() {
    string key_str;
    cout << "Enter a 10-bit binary key: ";
    cin >> key_str;

    if (key_str.length() != 10) {
        cerr << "Key must be 10 bits long." << endl;
        return 1;
    }

    bitset<10> key(key_str);
    auto [key1, key2] = generate_keys(key);

    cout << "Generated Key 1: " << key1 << endl;
    cout << "Generated Key 2: " << key2 << endl;

    return 0;
}   