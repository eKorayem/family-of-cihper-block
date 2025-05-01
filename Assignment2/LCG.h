#ifndef LCG_H
#define LCG_H

#include <cstdint>
#include <vector>

class LCG {
private:
    uint64_t x;
    const uint64_t a;
    const uint64_t c;
    const uint64_t m;

    static std::vector<uint64_t> primesBetween1000And9000;
    static bool primesInitialized;

    void initializePrimesList();
    bool isPrime(uint64_t n);
    uint64_t generatePrimeInRange();

public:
    LCG(uint64_t seed=50060, uint64_t a = 1664525, uint64_t c = 1013904223, uint64_t m = 1ull << 32);

    uint64_t next();
    void getRSAKeys(int& e, int& n, int &phi);
    
    std::vector<unsigned char> get16DigitKey();
    std::vector<unsigned char> get8DigitKey();
};

#endif
