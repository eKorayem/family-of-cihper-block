#include "CipherBlock.h"
#include <stdexcept>

// Constructor implementation
CipherBlock::CipherBlock(const vector<unsigned char>& key, size_t blockSize)
    : blockSize(blockSize), key(key) {
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
}

// Virtual destructor implementation
CipherBlock::~CipherBlock() {}

// Encrypt a single block (basic XOR implementation)
vector<unsigned char> CipherBlock::encryptBlock(const vector<unsigned char>& block) const {
    // In a real implementation, this would use the actual cipher algorithm
    // This is a placeholder that simply XORs each byte with the corresponding key byte
    vector<unsigned char> result(block.size());

    for (size_t i = 0; i < block.size(); i++) {
        result[i] = block[i] ^ key[i % key.size()];
    }
    return result;
}

// Decrypt a single block (basic XOR implementation)
vector<unsigned char> CipherBlock::decryptBlock(const vector<unsigned char>& block) const {
    // For our simple XOR cipher, encryption and decryption are the same operation
    return encryptBlock(block);
}

// Split data into blocks
vector<vector<unsigned char>> CipherBlock::splitIntoBlocks(const vector<unsigned char>& data) const {
    vector<vector<unsigned char>> blocks;

    for (size_t i = 0; i < data.size(); i += blockSize) {
        vector<unsigned char> block;
        for (size_t j = 0; j < blockSize && i + j < data.size(); j++) {
            block.push_back(data[i + j]);
        }

        // Pad the last block if necessary
        while (block.size() < blockSize) {
            block.push_back(0);  // Padding with zeros for simplicity
        }

        blocks.push_back(block);
    }

    return blocks;
}

// Convenience function to encrypt a string
string CipherBlock::encryptString(const string& str) {
    vector<unsigned char> data(str.begin(), str.end());
    vector<unsigned char> encrypted = encrypt(data);
    return string(encrypted.begin(), encrypted.end());
}

// Convenience function to decrypt a string
string CipherBlock::decryptString(const string& str) {
    vector<unsigned char> data(str.begin(), str.end());
    vector<unsigned char> decrypted = decrypt(data);
    return string(decrypted.begin(), decrypted.end());
}

void CipherBlock::print_hexa(string ecbEncrypted)
{
    for (unsigned char c : ecbEncrypted) {
        std::cout << hex << uppercase
            << std::setw(2) << std::setfill('0')
            << static_cast<int>(c);
    }
}
