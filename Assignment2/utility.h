#pragma once
#include <iostream>
#include <vector>
#include "ECB.h"
#include "LCG.h"
#include "CBC.h"
#include "CRT.h"
#include "SHA1.h"

#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

// Utility functions
namespace CryptoUtils {
    std::vector<uint8_t> xorVectors(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b);
    std::vector<uint8_t> stringToBytes(const std::string& str);
    std::string bytesToString(const std::vector<uint8_t>& bytes);
    std::string bytesToHex(const std::vector<uint8_t>& bytes);
}