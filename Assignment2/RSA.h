// RSA.h

#ifndef RSA_H
#define RSA_H


class RSA {
public:
    RSA();

    void generateKeys(); // Generates public/private keys

    int encrypt(int message) const;
    

    int getPublicKeyE() const;
    int getPublicKeyN() const;
    int getPrivateKeyD() const;

private:
    int e, d, n, phi;

    int power(int base, int expo, int m) const;
    int modInverse(int e, int phi) const;
    bool isPrime(int num) const;
    int getRandomPrime(int lower, int upper) const;
};

#endif
