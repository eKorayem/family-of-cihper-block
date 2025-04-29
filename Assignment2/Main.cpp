#include <iostream>
#include "ECB.h"
#include "CBC.h"
#include "CipherBlock.h"
int main() {
    try {
        // Sample key and IV (should be randomly generated in real applications)
        vector<unsigned char> key = { 'K', 'E', 'Y', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C' };
        vector<unsigned char> iv = { 'I', 'V', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D' };

        // Sample plaintext
        string plaintext = "atiaatiaatiaatia";
        cout << "Original: " << plaintext << std::endl;

        // ECB mode
        ECB ecb(key);
        string ecbEncrypted = ecb.encryptString(plaintext);
        string ecbDecrypted = ecb.decryptString(ecbEncrypted);

        cout << "\nECB Mode:" << endl;
        cout << "Encrypt: "; CipherBlock::print_hexa(ecbEncrypted);
        cout << "\nDcrypted: " << ecbDecrypted << std::endl;

        // CBC mode
        CBC cbc(key, iv);
        string cbcEncrypted = cbc.encryptString(plaintext);
        string cbcDecrypted = cbc.decryptString(cbcEncrypted);

        cout << "\nCBC Mode:" << std::endl;
        cout << "Encrypt: "; CipherBlock::print_hexa(cbcEncrypted);
        cout << "\nDecrypted: " << cbcDecrypted << std::endl;

        // Compare the two methods with identical plaintexts
        string identical_text = "AAAAAAAAAAAAAAAA";  // 16 identical bytes

        string ecb_identical = ecb.encryptString(identical_text);
        string cbc_identical = cbc.encryptString(identical_text);

        cout << "\nComparing encryption of identical blocks:" << std::endl;
        cout << "ECB produces identical ciphertext for identical blocks" << std::endl;
        cout << "CBC produces different ciphertext for identical blocks due to chaining" << std::endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}