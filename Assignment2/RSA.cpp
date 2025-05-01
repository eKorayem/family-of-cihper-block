// RSA.cpp

#include "RSA.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LCG.h"



RSA::RSA() {
    e = d = n = 0;
    std::srand(std::time(0));
}

int RSA::power(int base, int expo, int m) const {
    int result = 1;
    base = base % m;

    while (expo > 0) {
        if (expo % 2 == 1)
            result = (result * base) % m;
        base = (base * base) % m;
        expo = expo / 2;
    }

    return result;
}

int RSA::modInverse(int e, int phi) const {
    for (int d = 2; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

bool RSA::isPrime(int num) const {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int RSA::getRandomPrime(int lower, int upper) const {
    int num;
    do {
        num = lower + rand() % (upper - lower + 1);
    } while (!isPrime(num));
    return num;
}

void RSA::generateKeys() {
    LCG lcg(50060);
    lcg.getRSAKeys(e, n, phi);
}

int RSA::encrypt(int message) const {
    return power(message, e, n);
}


int RSA::getPublicKeyE() const {
    return e;
}

int RSA::getPublicKeyN() const {
    return n;
}

int RSA::getPrivateKeyD() const {
    return modInverse(e, phi);
}
