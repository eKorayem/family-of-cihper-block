#include <iostream>
#include "ECB.h"
#include "CBC.h"
#include "CipherBlock.h"
#include "CTR.h"
#include "SHA1.h"
#include "LCG.h"
#include "RSA.h"

int main() {
    try {
        LCG lcg(50060);

        // Sample key and IV (should be randomly generated in real applications)
        
        vector<unsigned char> key = lcg.get16DigitKey();
        vector<unsigned char> iv = lcg.get16DigitKey();
        vector<unsigned char> nonce = lcg.get8DigitKey();

        // Sample plaintext
        string plaintext = "To be or not";
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


        // CTR mode
        CTR ctr(key, nonce);
        string ctrEncrypted = ctr.encryptString(plaintext);
        string ctrDecrypted = ctr.decryptString(ctrEncrypted);

        cout << "\nCTR Mode:" << endl;
        cout << "Encrypted: ";
        CipherBlock::print_hexa(ctrEncrypted);
        cout << "\nDecrypted: " << ctrDecrypted << endl;

        
        char input[100] = "to be or not", hash[41];

        SHA1 sha1;
        sha1.compute(input, strlen(input), hash);
        cout << "\nSHA-1 Hash: \nEncrypted: " << hash << endl;


        RSA rsa;
        rsa.generateKeys();

        int e = rsa.getPublicKeyE();
        int n = rsa.getPublicKeyN();

        cout << "\nRSA\n";
        std::cout << std::dec << "Public Key (e, n): (" << e << ", " << n << ")\n";
        

        int message = 123;
        int encrypted = rsa.encrypt(message);

        std::cout << std::dec << "Original Message: " << message << "\n";
        std::cout << std::dec << "The Private Key D: " << rsa.getPrivateKeyD() << "\n";
        std::cout << std::dec << "Encrypted Message: " << encrypted << "\n";

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}