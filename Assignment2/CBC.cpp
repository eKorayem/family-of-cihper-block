#include "CBC.h"
#include <stdexcept>

// Constructor implementation
CBC::CBC(const vector<unsigned char>& key, const vector<unsigned char>& iv, size_t blockSize)
    : CipherBlock(key, blockSize) {
    // Ensure IV is the correct size
    if (iv.size() != blockSize) {
        throw invalid_argument("IV size must match block size");
    }
    this->iv = iv;
}

// Encrypt data using CBC mode
vector<unsigned char> CBC::encrypt(const vector<unsigned char>& data) {
    vector<vector<unsigned char>> blocks = splitIntoBlocks(data);
    vector<unsigned char> result;

    // First block is XORed with IV before encryption
    vector<unsigned char> previousBlock = iv;
    
    for (const auto& block : blocks) {
        // XOR with previous ciphertext (or IV for first block)
        vector<unsigned char> xoredBlock(blockSize);
        for (size_t i = 0; i < blockSize; i++) {
            xoredBlock[i] = block[i] ^ previousBlock[i];
        }

        // Encrypt the XORed block
        vector<unsigned char> encryptedBlock = encryptBlock(xoredBlock);

        // Add to result
        result.insert(result.end(), encryptedBlock.begin(), encryptedBlock.end());

        // Update previous block for next iteration
        previousBlock = encryptedBlock;
    }

    return result;
}

// Decrypt data using CBC mode
vector<unsigned char> CBC::decrypt(const vector<unsigned char>& data) {
    vector<vector<unsigned char>> blocks = splitIntoBlocks(data);
    vector<unsigned char> result;

    // First block is XORed with IV after decryption
    vector<unsigned char> previousBlock = iv;

    for (const auto& block : blocks) {
        // Decrypt the block
        vector<unsigned char> decryptedBlock = decryptBlock(block);

        // XOR with previous ciphertext (or IV for first block)
        vector<unsigned char> xoredBlock(blockSize);
        for (size_t i = 0; i < blockSize; i++) {
            xoredBlock[i] = decryptedBlock[i] ^ previousBlock[i];
        }

        // Add to result
        result.insert(result.end(), xoredBlock.begin(), xoredBlock.end());

        // Update previous block for next iteration
        previousBlock = block;
    }

    return result;
}