#include "CTR.h"
#include <stdexcept>
#include <algorithm> // For std::min

// Constructor implementation
CTR::CTR(const vector<unsigned char>& key, const vector<unsigned char>& nonce, size_t blockSize)
    : CipherBlock(key, blockSize) {
        // Ensure nonce size is valid (should be smaller than block size to allow counter space)
        if (nonce.size() >= blockSize) {
            throw invalid_argument("Nonce size must be smaller than block size");
    }
    this->nonce = nonce;
}

// Generate a counter block for a given block index
vector<unsigned char> CTR::generateCounterBlock(size_t blockIndex) const {
    vector<unsigned char> counterBlock(blockSize, 0);

    // Copy nonce to the beginning of the counter block
    copy(nonce.begin(), nonce.end(), counterBlock.begin());

    // Set the counter value in the remaining bytes
    // We're using a simple big-endian counter here
    size_t counterOffset = nonce.size();
    size_t counterSize = blockSize - nonce.size();

    // Convert block index to bytes and place in counter block
    for (int i = counterSize - 1; i >= 0 && blockIndex > 0; i--) {
        counterBlock[counterOffset + i] = blockIndex & 0xFF;
        blockIndex >>= 8;
    }

    return counterBlock;
}

// Encrypt data using CTR mode
vector<unsigned char> CTR::encrypt(const vector<unsigned char>& data) {
    vector<vector<unsigned char>> blocks = splitIntoBlocks(data);
    vector<unsigned char> result;

    for (size_t blockIndex = 0; blockIndex < blocks.size(); blockIndex++) {
        // Generate counter block for this block index
        vector<unsigned char> counterBlock = generateCounterBlock(blockIndex);

        // Encrypt the counter block to generate keystream
        vector<unsigned char> keystream = encryptBlock(counterBlock);

        // XOR plaintext with keystream
        const vector<unsigned char>& plaintext = blocks[blockIndex];
        vector<unsigned char> ciphertext(blockSize);

        for (size_t i = 0; i < blockSize; i++) {
            ciphertext[i] = plaintext[i] ^ keystream[i];
        }

        // Add to result
        result.insert(result.end(), ciphertext.begin(), ciphertext.end());
    }

    // Trim the result to match the original data size
    // (CTR mode doesn't require padding, but our splitIntoBlocks adds it)
    result.resize(data.size());

    return result;
}

// Decrypt data using CTR mode
// In CTR mode, decryption is identical to encryption
vector<unsigned char> CTR::decrypt(const vector<unsigned char>& data) {
    // Create a vector for the result that's the same size as the input
    vector<unsigned char> result;
    result.reserve(data.size());

    // Process each block
    size_t numFullBlocks = data.size() / blockSize;
    size_t remainingBytes = data.size() % blockSize;

    for (size_t blockIndex = 0; blockIndex < numFullBlocks; blockIndex++) {
        // Generate counter block for this block index
        vector<unsigned char> counterBlock = generateCounterBlock(blockIndex);

        // Encrypt the counter block to generate keystream
        std::vector<unsigned char> keystream = encryptBlock(counterBlock);

        // XOR ciphertext with keystream to get plaintext
        for (size_t i = 0; i < blockSize; i++) {
            result.push_back(data[blockIndex * blockSize + i] ^ keystream[i]);
        }
    }

    // Handle any remaining bytes in the last partial block
    if (remainingBytes > 0) {
        // Generate counter block for the last block
        std::vector<unsigned char> counterBlock = generateCounterBlock(numFullBlocks);

        // Encrypt the counter block to generate keystream
        std::vector<unsigned char> keystream = encryptBlock(counterBlock);

        // XOR the remaining bytes
        for (size_t i = 0; i < remainingBytes; i++) {
            result.push_back(data[numFullBlocks * blockSize + i] ^ keystream[i]);
        }
    }

    return result;
}