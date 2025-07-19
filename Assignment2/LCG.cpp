#include "LCG.h"
#include <stdexcept>
#include <numeric>
using namespace std;

std::vector<uint64_t> LCG::primesBetween1000And9000;
bool LCG::primesInitialized = false;

LCG::LCG(uint64_t seed, uint64_t a, uint64_t c, uint64_t m)
    : x(seed), a(a), c(c), m(m) {
    if (m == 0) throw std::invalid_argument("Modulus cannot be zero");
}

uint64_t LCG::next() {
    x = (a * x + c) % m;
    return x;
}

void LCG::initializePrimesList() {
    if (primesInitialized) return;

    for (uint64_t num = 1001; num <= 8999; num += 2) {
        if (isPrime(num)) {
            primesBetween1000And9000.push_back(num);
        }
    }
    primesInitialized = true;
}

bool LCG::isPrime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

uint64_t LCG::generatePrimeInRange() {
    initializePrimesList();

    if (primesBetween1000And9000.empty()) {
        throw std::runtime_error("No primes found in range 1000-9000");
    }

    double scale = static_cast<double>(next()) / m;
    size_t index = static_cast<size_t>(scale * primesBetween1000And9000.size());

    return primesBetween1000And9000[index];
}

void LCG::getRSAKeys(int& e, int& n, int &phi) {
    uint64_t p = generatePrimeInRange();
    uint64_t q = generatePrimeInRange();



    n = p * q;
    phi = (p - 1) * (q - 1);

    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }
}




std::vector<unsigned char> LCG::get16DigitKey() {
    std::vector<char> result;
    result.reserve(16);

    const std::string digits = "0123456789";
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 16; i++) {
        next();
        if (x % 2 == 0) {
            result.push_back(digits[x % digits.length()]);
        }
        else {
            result.push_back(letters[x % letters.length()]);
        }
    }

    vector<unsigned char> vec_uchar;

    for (char c : result) {
        vec_uchar.push_back(static_cast<unsigned char>(c));
    }

    return vec_uchar;
}

std::vector<unsigned char> LCG::get8DigitKey() {
    std::vector<char> result;
    result.reserve(8);

    const std::string digits = "0123456789";
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 8; i++) {
        next();
        if (x % 2 == 0) {
            result.push_back(digits[x % digits.length()]);
        }
        else {
            result.push_back(letters[x % letters.length()]);
        }
    }

    vector<unsigned char> vec_uchar;

    for (char c : result) {
        vec_uchar.push_back(static_cast<unsigned char>(c));
    }

    return vec_uchar;
}
// waheed was here