#include <iostream>
#include <string>
#include "SHA1.h"
#include "RSA.h"
#include "LCG.h"
#include "ECB.h"
#include "CBC.h"
#include "CTR.h"

using namespace std;

int main() {
    string input;

    while (true) {
        cout << "\nChoose encryption method (or enter 'q' to quit):\n";
        cout << "1. SHA1\n";
        cout << "2. RSA\n";
        cout << "3. ECB\n";
        cout << "4. CBC\n";
        cout << "5. CTR\n";
        cout << "Choice: ";
        getline(cin, input);

        if (input == "q" || input == "Q") break;

        string message;
        cout << "Enter message (or number for RSA): ";
        getline(cin, message);

        if (input == "1") {
            SHA1 sha;
            char hash[41] = { 0 };
            sha.compute(message.c_str(), message.size(), hash);
            cout << "SHA1 Hash: " << hash << endl;
        }
        else if (input == "2") {
            RSA rsa;
            rsa.generateKeys();
            try {
                int m = stoi(message);
                int encrypted = rsa.encrypt(m);
                cout << "Encrypted (RSA): " << encrypted << endl;
                cout << "Public Key (e, n): (" << rsa.getPublicKeyE() << ", " << rsa.getPublicKeyN() << ")" << endl;
            }
            catch (...) {
                cout << "RSA requires a numeric input." << endl;
            }
        }
        else if (input == "3") {
            LCG lcg;
            vector<unsigned char> key = lcg.get16DigitKey();
            ECB ecb(key);
            string encrypted = ecb.encryptString(message);
            cout << "Encrypted (ECB): " << encrypted << endl;
        }
        else if (input == "4") {
            LCG lcg;
            vector<unsigned char> key = lcg.get16DigitKey();
            vector<unsigned char> iv = lcg.get16DigitKey();
            CBC cbc(key, iv);
            string encrypted = cbc.encryptString(message);
            cout << "Encrypted (CBC): " << encrypted << endl;
        }
        else if (input == "5") {
            LCG lcg;
            vector<unsigned char> key = lcg.get16DigitKey();
            vector<unsigned char> nonce = lcg.get8DigitKey();
            CTR ctr(key, nonce);
            string encrypted = ctr.encryptString(message);
            cout << "Encrypted (CTR): " << encrypted << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }

    cout << "Exiting encryption program." << endl;
    return 0;
}
