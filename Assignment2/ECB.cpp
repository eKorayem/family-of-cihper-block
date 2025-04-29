#include "ECB.h"

// Constructor implementation
ECB::ECB(const std::vector<unsigned char>& key, size_t blockSize)
    : CipherBlock(key, blockSize) {}

// Encrypt data using ECB mode
vector<unsigned char> ECB::encrypt(const std::vector<unsigned char>& data) {
    vector<vector<unsigned char>> blocks = splitIntoBlocks(data);
    vector<unsigned char> result;

    // Process each block independently
    for (const auto& block : blocks) {
        std::vector<unsigned char> encryptedBlock = encryptBlock(block);
        result.insert(result.end(), encryptedBlock.begin(), encryptedBlock.end());
    }

    return result;
}

// Decrypt data using ECB mode
vector<unsigned char> ECB::decrypt(const vector<unsigned char>& data) {
    vector<vector<unsigned char>> blocks = splitIntoBlocks(data);
    vector<unsigned char> result;

    // Process each block independently
    for (const auto& block : blocks) {
        vector<unsigned char> decryptedBlock = decryptBlock(block);
        result.insert(result.end(), decryptedBlock.begin(), decryptedBlock.end());
    }

    return result;
}